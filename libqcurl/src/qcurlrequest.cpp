#include "qcurlrequest.h"
#include "qcurlresponse.h"
#include <curl/curl.h>

#define encode(text) text.toUtf8().constData()

size_t readCallback(char *buffer, size_t size, size_t nitems, void *arg)
{
    auto dev = static_cast<QIODevice*>(arg);
    auto left = static_cast<size_t>(dev->size() - dev->pos());
    nitems *= size;
    auto s = left > nitems ? nitems : left;
    dev->read(buffer, static_cast<qint64>(s));
    return s;
}

int seekCallback(void *arg, curl_off_t offset, int origin)
{
    auto dev = static_cast<QIODevice*>(arg);

    switch (origin) {
    case SEEK_END:
        offset += dev->size();
        break;
    case SEEK_CUR:
        offset += dev->pos();
        break;
    }
    if(offset < 0)
        return CURL_SEEKFUNC_FAIL;
    dev->seek(static_cast<qint64>(offset));
    return CURL_SEEKFUNC_OK;
}

void freeCallback(void *arg)
{
    auto dev = static_cast<QIODevice*>(arg);
    dev->close();
}

QCurlRequest::QCurlRequest(QCurlData &data)
    : d(new QCurlRequestData(data))
{
    assert(d->session.counter++ == 0);
    if (!data.userAgent.isEmpty()) setUserAgent(data.userAgent);
    if (!data.proxyUrl.isEmpty()) setProxyUrl(data.proxyUrl);
    if (!data.privateKeyPath.isEmpty()) setPrivateKeyPath(data.privateKeyPath);
    if (!data.publicKeyPath.isEmpty()) setPublicKeyPath(data.publicKeyPath);
    if (!data.keyPassword.isEmpty()) setKeyPassword(data.keyPassword);
    setVerbose(data.verbose);
    setFlowLocation(data.flowLocation);
    d->performed = false;
    curl_easy_reset(data.curl);
}

void QCurlRequest::setHeader(const QString &name, const QString &value)
{
    d->headers = curl_slist_append(CURL_SLIST(d->headers), encode(QString("%1: %2").arg(name).arg(value)));
}

void QCurlRequest::setHeaders(const QMap<QString, QString> &headers)
{
    for (const auto &headerName : headers) {
        setHeader(headerName, headers[headerName]);
    }
}

void QCurlRequest::setQuote(const QStringList quote)
{
    for (const auto &line : quote) {
        d->quote = curl_slist_append(CURL_SLIST(d->quote), encode(line));
    }
}

void QCurlRequest::setUserAgent(const QString &userAgent)
{
    curl_easy_setopt(d->session.curl, CURLOPT_USERAGENT, encode(userAgent));
}

void QCurlRequest::setProxyUrl(const QUrl &proxyUrl)
{
    curl_easy_setopt(d->session.curl, CURLOPT_PROXY, encode(proxyUrl.toString()));
}

void QCurlRequest::setPrivateKeyPath(const QString &privateKeyPath)
{
    curl_easy_setopt(d->session.curl, CURLOPT_SSH_PRIVATE_KEYFILE, encode(privateKeyPath));
}

void QCurlRequest::setPublicKeyPath(const QString &publicKeyPath)
{
    curl_easy_setopt(d->session.curl, CURLOPT_SSH_PUBLIC_KEYFILE, encode(publicKeyPath));
}

void QCurlRequest::setKeyPassword(const QString &keyPassword)
{
    curl_easy_setopt(d->session.curl, CURLOPT_KEYPASSWD, encode(keyPassword));
}

void QCurlRequest::setVerbose(bool verbose)
{
    curl_easy_setopt(d->session.curl, CURLOPT_VERBOSE, verbose);
}

void QCurlRequest::setBody(const QCurlBytes &bytes)
{
    d->body = bytes;
    curl_easy_setopt(d->session.curl, CURLOPT_POSTFIELDS, d->body.constData());
}

void QCurlRequest::setBody(const QCurlForm &form)
{
    d->body.clear();
    for (auto &pair : form) {
        if (!d->body.isEmpty()) d->body.append('&');
        d->body.append(curl_easy_escape(d->session.curl, pair.first.toUtf8().constData(), 0));
        d->body.append('=');
        d->body.append(curl_easy_escape(d->session.curl, pair.second.toUtf8().constData(), 0));
    }
    curl_easy_setopt(d->session.curl, CURLOPT_POSTFIELDS, d->body.constData());
}

void QCurlRequest::setBody(const QCurlJson &json)
{
    d->body = json.toJson();
    setHeader("Content-Type", "application/json; charset=utf-8");
    curl_easy_setopt(d->session.curl, CURLOPT_POSTFIELDS, d->body.constData());
}

void QCurlRequest::setBody(QCurlMultipart &parts)
{
    if (d->form) curl_mime_free(CURL_MIME(d->form));
    d->form = curl_mime_init(d->session.curl);

    for (auto &pair : parts) {
        auto part = curl_mime_addpart(CURL_MIME(d->form));
        auto name = pair.first;
        auto value = pair.second;
        curl_mime_name(part, encode(name));
        if (value.canConvert<QIODevice*>()) {
            auto dev = value.value<QIODevice*>();
            if (dev->isOpen() == false) {
                dev->open(QIODevice::ReadOnly);
            }
            curl_mime_data_cb(part, dev->size(), readCallback, seekCallback, freeCallback, dev);
            if (value.canConvert<QFileDevice*>()) {
                auto file = value.value<QFileDevice*>();
                curl_mime_filename(part, encode(file->fileName()));
            } else {
                auto filename = dev->property("filename").toString();
                if (!filename.isNull()) {
                    curl_mime_filename(part, encode(filename));
                }
            }
        } else {
            curl_mime_data(part, encode(value.toString()), CURL_ZERO_TERMINATED);
        }
    }
    curl_easy_setopt(d->session.curl, CURLOPT_MIMEPOST, d->form);
}

void QCurlRequest::setBody(QIODevice &stream)
{
    if (stream.isOpen() == false) {
        stream.open(QIODevice::ReadOnly);
    }
    setHeader("Content-Type", "application/octec-stream");
    curl_easy_setopt(d->session.curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(d->session.curl, CURLOPT_READFUNCTION, readCallback);
    curl_easy_setopt(d->session.curl, CURLOPT_READDATA, &stream);
    curl_easy_setopt(d->session.curl, CURLOPT_INFILESIZE_LARGE, static_cast<curl_off_t>(stream.size()));
}

void QCurlRequest::setRange(QString range)
{
    curl_easy_setopt(d->session.curl, CURLOPT_RANGE, encode(range));
}

void QCurlRequest::setNoBody(bool nobody)
{
    curl_easy_setopt(d->session.curl, CURLOPT_NOBODY, nobody);
}

void QCurlRequest::setFlowLocation(bool flow)
{
    curl_easy_setopt(d->session.curl, CURLOPT_FOLLOWLOCATION, flow);
}

QCurlResponse QCurlRequest::perform(const QString &method, const QString &path, QIODevice *responseBody)
{
    assert(!d->performed);
    d->performed = true;

    QUrl url(path);
    assert(url.isRelative());

    QString METHOD = method.toUpper();
    const QUrl finalUrl = d->session.baseUrl.resolved(url);
    if (METHOD == "HEAD") {
        curl_easy_setopt(d->session.curl, CURLOPT_NOBODY, 1L);
        curl_easy_setopt(d->session.curl, CURLOPT_HEADER, 1L);
    } else if (METHOD != "GET") {
        auto scheme = finalUrl.scheme();
        if (scheme.startsWith("http")) {
            curl_easy_setopt(d->session.curl, CURLOPT_CUSTOMREQUEST, encode(METHOD));
        } else if (scheme.startsWith("ftp")) {
            if (METHOD == "POST" || METHOD == "PUT") {
                curl_easy_setopt(d->session.curl, CURLOPT_UPLOAD, 1L);
            } else if (METHOD == "DELETE") {
                setQuote({QString("DELE %1").arg(path)});
                curl_easy_setopt(d->session.curl, CURLOPT_QUOTE, d->quote);
            }
        }
    }
    if (d->headers) curl_easy_setopt(d->session.curl, CURLOPT_HTTPHEADER, d->headers);
    curl_easy_setopt(d->session.curl, CURLOPT_URL, encode(finalUrl.toString()));
    QCurlResponse res(*d, finalUrl, responseBody);
    d->session.counter--;

    return res;
}

int QCurlRequest::exists(const QString &path)
{
    if (d->session.baseUrl.scheme().startsWith("http")) {
        return this->perform("HEAD", path).statusCode() != 404;
    }
    if (d->session.baseUrl.scheme().startsWith("ftp")) {
        this->setRange("0-0");
        return this->perform("GET", path).code() != CURLE_FTP_COULDNT_RETR_FILE;
    }
    if (d->session.baseUrl.scheme() == "sftp") {
        return this->perform("HEAD", path).code() != CURLE_REMOTE_FILE_NOT_FOUND;
    }
    return -1;
}
