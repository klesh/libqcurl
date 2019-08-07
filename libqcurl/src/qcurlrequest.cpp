#include "qcurlrequest.h"
#include "qcurlresponse.h"

#define encode(text) text.toUtf8().constData()

size_t QCurlRequest::readCallback(char *buffer, size_t size, size_t nitems, void *arg)
{
    auto dev = static_cast<QIODevice*>(arg);
    auto left = static_cast<size_t>(dev->size() - dev->pos());
    nitems *= size;
    auto s = left > nitems ? nitems : left;
    dev->read(buffer, static_cast<qint64>(s));
    return s;
}

int QCurlRequest::seekCallback(void *arg, curl_off_t offset, int origin)
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

void QCurlRequest::freeCallback(void *arg)
{
    auto dev = static_cast<QIODevice*>(arg);
    dev->close();
}

QCurlRequest::QCurlRequest(QCurlData &data)
    : _data(data)
{
    assert(_data.counter++ == 0); // decrease only if request is performed.
    curl_easy_reset(_data.curl);
}

void QCurlRequest::setHeader(const QString &name, const QString &value)
{
    _data.headers = curl_slist_append(_data.headers, encode(QString("%1: %2").arg(name).arg(value)));
}

void QCurlRequest::setHeaders(const QMap<QString, QString> &headers)
{
    for (const auto &headerName : headers) {
        setHeader(headerName, headers[headerName]);
    }
}

void QCurlRequest::setUserAgent(const QString &userAgent)
{
    curl_easy_setopt(_data.curl, CURLOPT_USERAGENT, encode(userAgent));
}

void QCurlRequest::setProxyUrl(const QUrl &proxyUrl)
{
    curl_easy_setopt(_data.curl, CURLOPT_PROXY, encode(proxyUrl.toString()));
}

void QCurlRequest::setPrivateKeyPath(const QString &privateKeyPath)
{
    curl_easy_setopt(_data.curl, CURLOPT_SSH_PRIVATE_KEYFILE, encode(privateKeyPath));
}

void QCurlRequest::setPublicKeyPath(const QString &publicKeyPath)
{
    curl_easy_setopt(_data.curl, CURLOPT_SSH_PUBLIC_KEYFILE, encode(publicKeyPath));
}

void QCurlRequest::setKeyPassword(const QString &keyPassword)
{
    curl_easy_setopt(_data.curl, CURLOPT_KEYPASSWD, encode(keyPassword));
}

void QCurlRequest::setVerbose(bool verbose)
{
    curl_easy_setopt(_data.curl, CURLOPT_VERBOSE, verbose);
}

void QCurlRequest::setBody(const QCurlBytes &bytes)
{
    _data.body = bytes;
    curl_easy_setopt(_data.curl, CURLOPT_POSTFIELDS, _data.body.constData());
}

void QCurlRequest::setBody(const QCurlFormData &form)
{
    _data.body.clear();
    for (auto &pair : form) {
        if (!_data.body.isEmpty()) _data.body.append('&');
        _data.body.append(curl_easy_escape(_data.curl, pair.first.toUtf8().constData(), 0));
        _data.body.append('=');
        _data.body.append(curl_easy_escape(_data.curl, pair.second.toUtf8().constData(), 0));
    }
    curl_easy_setopt(_data.curl, CURLOPT_POSTFIELDS, _data.body.constData());
}

void QCurlRequest::setBody(const QCurlJson &json)
{
    _data.body = json.toJson();
    setHeader("Content-Type", "application/json; charset=utf-8");
    curl_easy_setopt(_data.curl, CURLOPT_POSTFIELDS, _data.body.constData());
}

void QCurlRequest::setBody(QCurlMultipart &parts)
{
    if (_data.form) curl_mime_free(_data.form);
    _data.form = curl_mime_init(_data.curl);

    for (auto &pair : parts) {
        auto part = curl_mime_addpart(_data.form);
        auto name = pair.first;
        auto value = pair.second;
        curl_mime_name(part, encode(name));
        if (value.canConvert<QIODevice*>()) {
            auto dev = value.value<QIODevice*>();
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
    curl_easy_setopt(_data.curl, CURLOPT_MIMEPOST, _data.form);
}

void QCurlRequest::setBody(QIODevice &stream)
{
    setHeader("Content-Type", "application/octec-stream");
    curl_easy_setopt(_data.curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(_data.curl, CURLOPT_READFUNCTION, readCallback);
    curl_easy_setopt(_data.curl, CURLOPT_READDATA, &stream);
    curl_easy_setopt(_data.curl, CURLOPT_INFILESIZE_LARGE, static_cast<curl_off_t>(stream.size()));
}

void QCurlRequest::setNoBody(bool nobody)
{
    curl_easy_setopt(_data.curl, CURLOPT_NOBODY, nobody);
}

void QCurlRequest::setFlowLocation(bool flow)
{
    curl_easy_setopt(_data.curl, CURLOPT_FOLLOWLOCATION, flow);
}

QCurlResponse QCurlRequest::perform(const QString &method, const QUrl &url)
{
    QString METHOD = method.toUpper();
    const QUrl finalUrl = url.isRelative() ? _data.baseUrl.resolved(url) : url;
    if (METHOD == "HEAD") {
        curl_easy_setopt(_data.curl, CURLOPT_NOBODY, 1L);
        curl_easy_setopt(_data.curl, CURLOPT_HEADER, 1L);
    } else {
        if (METHOD != "GET" && finalUrl.scheme().toLower().startsWith("http")) {
            curl_easy_setopt(_data.curl, CURLOPT_CUSTOMREQUEST, encode(METHOD));
        }
    }
    if (_data.headers) curl_easy_setopt(_data.curl, CURLOPT_HTTPHEADER, _data.headers);
    curl_easy_setopt(_data.curl, CURLOPT_URL, encode(finalUrl.toString()));
    QCurlResponse res(_data);
    _data.counter--;

    // release resources
    if (_data.headers) {
        curl_slist_free_all(_data.headers);
        _data.headers = nullptr;
    }
    if (!_data.body.isNull()) {
        _data.body = QByteArray();
    }
    if (_data.form) {
        curl_mime_free(_data.form);
        _data.form = nullptr;
    }
    return res;
}
