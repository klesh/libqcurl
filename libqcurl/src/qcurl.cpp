#include "qcurl.h"


QCurlSession::QCurlSession()
{
    _data.curl = curl_easy_init();
}

QCurlSession::~QCurlSession()
{
    curl_easy_cleanup(_data.curl);
    if (_data.cookies) curl_slist_free_all(_data.cookies);
    _data.curl = nullptr;
    _data.cookies = nullptr;
}

QCurlRequest QCurlSession::request(const QCurlHeaders &headers)
{
    QCurlRequest req(_data);
    req.setHeaders(headers);
    if (!_userAgent.isEmpty()) req.setUserAgent(_userAgent);
    if (!_proxyUrl.isEmpty()) req.setProxyUrl(_proxyUrl);
    if (!_userName.isEmpty()) req.setUserName(_userName);
    if (!_password.isEmpty()) req.setPassword(_password);
    if (!_privateKeyPath.isEmpty()) req.setPrivateKeyPath(_privateKeyPath);
    if (!_publicKeyPath.isEmpty()) req.setPublicKeyPath(_publicKeyPath);
    req.setVerbose(_verbose);
    req.setFlowLocation(_flowLocation);
    return req;
}

QCurlResponse QCurlSession::get(const QUrl &url, const QCurlHeaders &headers)
{
    QCurlRequest req = request(headers);
    return req.perform("GET", url);
}

QCurlResponse QCurlSession::put(const QUrl &url, const QString &text, const QCurlHeaders &headers)
{
    QCurlRequest req = request(headers);
    req.setBody(text);
    return req.perform("PUT", url);
}

QCurlResponse QCurlSession::post(const QUrl &url, const QMap<QString, QString> &headers)
{
    QCurlRequest req = request(headers);
    return req.perform("POST", url);
}

QCurlResponse QCurlSession::post(const QUrl &url, const QString &text, const QCurlHeaders &headers)
{

    QCurlRequest req = request(headers);
    req.setBody(text);
    return req.perform("POST", url);
}

QCurlResponse QCurlSession::post(const QUrl &url, const QCurlFormData &form, const QMap<QString, QString> &headers)
{
    QCurlRequest req = request(headers);
    req.setBody(form);
    return req.perform("POST", url);
}

QCurlResponse QCurlSession::post(const QUrl &url, const QJsonDocument &json, const QMap<QString, QString> &headers)
{
    QCurlRequest req = request(headers);
    req.setBody(json);
    return req.perform("POST", url);
}

QCurlResponse QCurlSession::dele(const QUrl &url, const QCurlHeaders &headers)
{
    QCurlRequest req = request(headers);
    return req.perform("DELETE", url);
}

