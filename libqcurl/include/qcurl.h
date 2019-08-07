#ifndef QCURL_H
#define QCURL_H

#include "qcurlbase.h"
#include "qcurlrequest.h"
#include "qcurlresponse.h"

class Q_DECL_EXPORT QCurlSession : public QObject
{
    Q_OBJECT

    QCurlHeaders _headers;
    QString _userAgent;
    QUrl _proxyUrl;
    QString _userName;
    QString _password;
    QString _privateKeyPath;
    QString _publicKeyPath;
    bool _verbose = false;
    bool _flowLocation = true;

    QCurlData _data;

public:
    QCurlSession();
    ~QCurlSession();

    void setHeaders(const QCurlHeaders &headers) { _headers = headers; }
    void setUserAgent(const QString &userAgent) { _userAgent = userAgent; }
    void setProxyUrl(const QUrl &proxyUrl) { _proxyUrl = proxyUrl; }
    void setUserName(const QString &userName) { _userName = userName; }
    void setPassword(const QString &password) { _password = password; }
    void setSshKeyFiles(const QString &privateKeyPath, const QString &publicKeyPath = QString()) {
        _privateKeyPath = privateKeyPath;
        _publicKeyPath = publicKeyPath;
    }
    void setVerbose(bool verbose) { _verbose = verbose; }
    void setFlowLocation(bool flowLocation) { _flowLocation = flowLocation; }

    QCurlRequest request(const QCurlHeaders &headers = QCurlHeadersEmpty);

    QCurlResponse get(const QUrl &url, const QCurlHeaders &headers = QCurlHeadersEmpty);

    QCurlResponse post(const QUrl &url, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse post(const QUrl &url, const QString &text, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse post(const QUrl &url, const QCurlFormData &form, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse post(const QUrl &url, const QCurlJson &json, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse post(const QUrl &url, QCurlMultipart &parts, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse post(const QUrl &url, QIODevice &stream, const QCurlHeaders &headers = QCurlHeadersEmpty);

    QCurlResponse put(const QUrl &url, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse put(const QUrl &url, const QString &text, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse put(const QUrl &url, const QCurlFormData &form, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse put(const QUrl &url, const QCurlJson &json, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse put(const QUrl &url, QCurlMultipart &parts, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse put(const QUrl &url, QIODevice &stream, const QCurlHeaders &headers = QCurlHeadersEmpty);

    QCurlResponse dele(const QUrl &url, const QCurlHeaders &headers = QCurlHeadersEmpty);
};

#endif // QCURL_H
