#include "qcurlrequest.h"
#include "qcurlresponse.h"

#define encode(text) text.toUtf8().constData()

QCurlRequest::QCurlRequest(QCurlData &data)
    : _data(data)
{
    assert(_data.counter++ == 0); // decrease only if request is performed.
    curl_easy_reset(_data.curl);
    _data.headers = nullptr;
}

QCurlRequest::QCurlRequest(const QCurlRequest &other)
    : _data(other._data)
{
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

void QCurlRequest::setUserName(const QString &userName)
{
    curl_easy_setopt(_data.curl, CURLOPT_USERNAME, encode(userName));
}

void QCurlRequest::setPassword(const QString &password)
{
    curl_easy_setopt(_data.curl, CURLOPT_PASSWORD, encode(password));
}

void QCurlRequest::setPrivateKeyPath(const QString &privateKeyPath)
{
    curl_easy_setopt(_data.curl, CURLOPT_SSH_PRIVATE_KEYFILE, encode(privateKeyPath));
}

void QCurlRequest::setPublicKeyPath(const QString &publicKeyPath)
{
    curl_easy_setopt(_data.curl, CURLOPT_SSH_PUBLIC_KEYFILE, encode(publicKeyPath));
}

void QCurlRequest::setVerbose(bool verbose)
{
    curl_easy_setopt(_data.curl, CURLOPT_VERBOSE, verbose);
}

void QCurlRequest::setBody(const QString &text)
{
    _body = text.toUtf8();
    curl_easy_setopt(_data.curl, CURLOPT_POSTFIELDS, _body.constData());
}

void QCurlRequest::setBody(const QCurlFormData &form)
{
    _body.clear();
    for (auto &pair : form) {
        if (!_body.isEmpty()) _body.append('&');
        _body.append(curl_easy_escape(_data.curl, pair.first.toUtf8().constData(), 0));
        _body.append('=');
        _body.append(curl_easy_escape(_data.curl, pair.second.toUtf8().constData(), 0));
    }
    curl_easy_setopt(_data.curl, CURLOPT_POSTFIELDS, _body.constData());
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
    if (METHOD != "GET" && url.scheme().toLower().startsWith("http")) {
        curl_easy_setopt(_data.curl, CURLOPT_CUSTOMREQUEST, encode(METHOD));
    }
    if (_data.headers) curl_easy_setopt(_data.curl, CURLOPT_HTTPHEADER, _data.headers);
    curl_easy_setopt(_data.curl, CURLOPT_URL, encode(url.toString()));
    QCurlResponse res(_data);
    _data.counter--;
    return res;
}
