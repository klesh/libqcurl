#include "qcurl.h"

QCurl::QCurl(const QUrl &baseUrl)
    : d(new QCurlData(baseUrl))
{
}

QCurl::QCurl(const QCurl &other)
    : QObject(), d(other.d)
{

}

QCurl::~QCurl()
{
}

void QCurl::setHeaders(const QMap<QString, QString> &headers)
{
    d->headers = headers;
}

void QCurl::setUserAgent(const QString &userAgent)
{
    d->userAgent = userAgent;
}

void QCurl::setProxyUrl(const QUrl &proxyUrl)
{
    d->proxyUrl = proxyUrl;
}

void QCurl::setPrivateKeyPath(const QString &privateKeyPath)
{
    d->privateKeyPath = privateKeyPath;
}

void QCurl::setPublicKeyPath(const QString &publicKeyPath)
{
    d->publicKeyPath = publicKeyPath;
}

void QCurl::setKeyPassword(const QString &keyPassword)
{
    d->keyPassword = keyPassword;
}

void QCurl::setVerbose(bool verbose)
{
    d->verbose = verbose;
}

void QCurl::setFlowLocation(bool flowLocation)
{
    d->flowLocation = flowLocation;
}

void QCurl::setCaPath(const QString &path)
{
    d->caPath = path;
}

void QCurl::setTimeout(long seconds)
{
    d->timeout = seconds;
}

QCurlRequest QCurl::request(const QCurlHeaders &headers)
{
    QCurlRequest req(*d);
    req.setHeaders(headers);
    return req;
}

QCurlResponse QCurl::get(const QString &path, const QCurlHeaders &headers)
{
    QCurlRequest req = request(headers);
    return req.perform("GET", path);
}
QCurlResponse QCurl::post(const QString &path, const QCurlHeaders &headers)
{
    QCurlRequest req = request(headers);
    return req.perform("POST", path);
}
QCurlResponse QCurl::put(const QString &path, const QCurlHeaders &headers)
{
    QCurlRequest req = request(headers);
    return req.perform("PUT", path);
}
QCurlResponse QCurl::dele(const QString &path, const QCurlHeaders &headers)
{
    QCurlRequest req = request(headers);
    return req.perform("DELETE", path);
}

QCurlResponse QCurl::head(const QString &path, const QMap<QString, QString> &headers)
{
    QCurlRequest req = request(headers);
    return req.perform("HEAD", path);
}

QCurlResponse QCurl::exists(int &result, const QString &path)
{
    QCurlRequest req = request();
    return req.exists(result, path);
}


QCurlResponse QCurl::post(const QString &path, const QCurlBytes &bytes, const QCurlHeaders &headers)
{
    QCurlRequest req = request(headers);
    req.setBody(bytes);
    return req.perform("POST", path);
}
QCurlResponse QCurl::post(const QString &path, const QCurlForm &form, const QCurlHeaders &headers)
{
    QCurlRequest req = request(headers);
    req.setBody(form);
    return req.perform("POST", path);
}
QCurlResponse QCurl::post(const QString &path, const QJsonDocument &json, const QCurlHeaders &headers)
{
    QCurlRequest req = request(headers);
    req.setBody(json);
    return req.perform("POST", path);
}
QCurlResponse QCurl::post(const QString &path, QCurlMultipart &parts, const QCurlHeaders &headers)
{
    QCurlRequest req = request(headers);
    req.setBody(parts);
    return req.perform("POST", path);
}
QCurlResponse QCurl::post(const QString &path, QIODevice &stream, const QCurlHeaders &headers)
{
    QCurlRequest req = request(headers);
    req.setBody(stream);
    return req.perform("POST", path);
}


QCurlResponse QCurl::put(const QString &path, const QCurlBytes &bytes, const QCurlHeaders &headers)
{
    QCurlRequest req = request(headers);
    req.setBody(bytes);
    return req.perform("PUT", path);
}
QCurlResponse QCurl::put(const QString &path, const QCurlForm &form, const QCurlHeaders &headers)
{
    QCurlRequest req = request(headers);
    req.setBody(form);
    return req.perform("PUT", path);
}
QCurlResponse QCurl::put(const QString &path, const QJsonDocument &json, const QCurlHeaders &headers)
{
    QCurlRequest req = request(headers);
    req.setBody(json);
    return req.perform("PUT", path);
}
QCurlResponse QCurl::put(const QString &path, QCurlMultipart &parts, const QCurlHeaders &headers)
{
    QCurlRequest req = request(headers);
    req.setBody(parts);
    return req.perform("PUT", path);

}
QCurlResponse QCurl::put(const QString &path, QIODevice &stream, const QCurlHeaders &headers)
{
    QCurlRequest req = request(headers);
    req.setBody(stream);
    return req.perform("PUT", path);
}



QCurlResponse QCurl::get(const QUrl &url, const QCurlHeaders &headers)
{
    QCurl curl(url);
    return curl.get(headers);
}
QCurlResponse QCurl::post(const QUrl &url, const QCurlHeaders &headers)
{
    QCurl curl(url);
    return curl.post(headers);
}
QCurlResponse QCurl::put(const QUrl &url, const QCurlHeaders &headers)
{
    QCurl curl(url);
    return curl.put(headers);
}
QCurlResponse QCurl::dele(const QUrl &url, const QCurlHeaders &headers)
{
    QCurl curl(url);
    return curl.dele(headers);
}

QCurlResponse QCurl::head(const QUrl &url, const QMap<QString, QString> &headers)
{
    QCurl curl(url);
    return curl.head(headers);
}

QCurlResponse QCurl::exists(int &result, const QUrl &url)
{
    QCurl curl(url);
    return curl.exists(result);
}



QCurlResponse QCurl::post(const QUrl &url, const QCurlBytes &bytes, const QCurlHeaders &headers)
{
    QCurl curl(url);
    return curl.post(bytes, headers);
}
QCurlResponse QCurl::post(const QUrl &url, const QCurlForm &form, const QCurlHeaders &headers)
{
    QCurl curl(url);
    return curl.post(form, headers);
}
QCurlResponse QCurl::post(const QUrl &url, const QJsonDocument &json, const QCurlHeaders &headers)
{
    QCurl curl(url);
    return curl.post(json, headers);
}

QCurlResponse QCurl::post(const QUrl &url, QCurlMultipart &parts, const QCurlHeaders &headers)
{
    QCurl curl(url);
    return curl.post(parts, headers);
}

QCurlResponse QCurl::post(const QUrl &url, QIODevice &stream, const QCurlHeaders &headers)
{
    QCurl curl(url);
    return curl.post(stream, headers);
}


QCurlResponse QCurl::put(const QUrl &url, const QCurlBytes &bytes, const QCurlHeaders &headers)
{
    QCurl curl(url);
    return curl.put(bytes, headers);
}

QCurlResponse QCurl::put(const QUrl &url, const QCurlForm &form, const QCurlHeaders &headers)
{
    QCurl curl(url);
    return curl.put(form, headers);
}

QCurlResponse QCurl::put(const QUrl &url, const QJsonDocument &json, const QCurlHeaders &headers)
{
    QCurl curl(url);
    return curl.put(json, headers);
}

QCurlResponse QCurl::put(const QUrl &url, QCurlMultipart &parts, const QCurlHeaders &headers)
{
    QCurl curl(url);
    return curl.put(parts, headers);
}

QCurlResponse QCurl::put(const QUrl &url, QIODevice &stream, const QCurlHeaders &headers)
{
    QCurl curl(url);
    return curl.put(stream, headers);
}
