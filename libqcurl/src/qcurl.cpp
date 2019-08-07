#include "qcurl.h"

QCurl::QCurl(const QUrl &baseUrl)
{
    _data.curl = curl_easy_init();
    _data.baseUrl = baseUrl;
}

QCurl::~QCurl()
{
    curl_easy_cleanup(_data.curl);
    if (_data.cookies) curl_slist_free_all(_data.cookies);
    _data.curl = nullptr;
    _data.cookies = nullptr;
}

QCurlRequest QCurl::request(const QCurlHeaders &headers)
{
    QCurlRequest req(_data);
    req.setHeaders(headers);
    if (!_userAgent.isEmpty()) req.setUserAgent(_userAgent);
    if (!_proxyUrl.isEmpty()) req.setProxyUrl(_proxyUrl);
    if (!_privateKeyPath.isEmpty()) req.setPrivateKeyPath(_privateKeyPath);
    if (!_publicKeyPath.isEmpty()) req.setPublicKeyPath(_publicKeyPath);
    if (!_keyPassword.isEmpty()) req.setKeyPassword(_keyPassword);
    req.setVerbose(_verbose);
    req.setFlowLocation(_flowLocation);
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


QCurlResponse QCurl::post(const QString &path, const QCurlBytes &bytes, const QCurlHeaders &headers)
{
    QCurlRequest req = request(headers);
    req.setBody(bytes);
    return req.perform("POST", path);
}
QCurlResponse QCurl::post(const QString &path, const QCurlFormData &form, const QCurlHeaders &headers)
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
QCurlResponse QCurl::put(const QString &path, const QCurlFormData &form, const QCurlHeaders &headers)
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



QCurlResponse QCurl::post(const QUrl &url, const QCurlBytes &bytes, const QCurlHeaders &headers)
{
    QCurl curl(url);
    return curl.post(bytes, headers);
}
QCurlResponse QCurl::post(const QUrl &url, const QCurlFormData &form, const QCurlHeaders &headers)
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

QCurlResponse QCurl::put(const QUrl &url, const QCurlFormData &form, const QCurlHeaders &headers)
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
