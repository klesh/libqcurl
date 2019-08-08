#ifndef QCURL_H
#define QCURL_H

#include "qcurlbase.h"
#include "qcurlrequest.h"
#include "qcurlresponse.h"

class Q_DECL_EXPORT QCurl : public QObject
{
    Q_OBJECT

    QCurlHeaders _headers;
    QString _userAgent;
    QUrl _proxyUrl;
    QString _privateKeyPath;
    QString _publicKeyPath;
    QString _keyPassword;
    bool _verbose = false;
    bool _flowLocation = true;

    QCurlData _data;

public:
    QCurl(const QUrl &baseUrl);
    ~QCurl();

    void setHeaders(const QCurlHeaders &headers) { _headers = headers; }
    void setUserAgent(const QString &userAgent) { _userAgent = userAgent; }
    void setProxyUrl(const QUrl &proxyUrl) { _proxyUrl = proxyUrl; }
    void setSshKeyFiles(const QString &privateKeyPath, const QString &publicKeyPath = QString(), const QString &keyPassword = QString()) {
        _privateKeyPath = privateKeyPath;
        _publicKeyPath = publicKeyPath;
        _keyPassword = keyPassword;
    }
    void setVerbose(bool verbose) { _verbose = verbose; }
    void setFlowLocation(bool flowLocation) { _flowLocation = flowLocation; }

    QCurlRequest request(const QCurlHeaders &headers = QCurlHeadersEmpty);

    QCurlResponse get(const QString &path, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse post(const QString &path, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse put(const QString &path, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse dele(const QString &path, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse head(const QString &path, const QCurlHeaders &headers = QCurlHeadersEmpty);
    int exists(const QString &path = QString());

    QCurlResponse post(const QString &path, const QCurlBytes &bytes, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse post(const QString &path, const QCurlFormData &form, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse post(const QString &path, const QCurlJson &json, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse post(const QString &path, QCurlMultipart &parts, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse post(const QString &path, QIODevice &stream, const QCurlHeaders &headers = QCurlHeadersEmpty);

    QCurlResponse put(const QString &path, const QCurlBytes &bytes, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse put(const QString &path, const QCurlFormData &form, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse put(const QString &path, const QCurlJson &json, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse put(const QString &path, QCurlMultipart &parts, const QCurlHeaders &headers = QCurlHeadersEmpty);
    QCurlResponse put(const QString &path, QIODevice &stream, const QCurlHeaders &headers = QCurlHeadersEmpty);


    QCurlResponse get(const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return get(QString(), headers); }
    QCurlResponse post(const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return post(QString(), headers); }
    QCurlResponse put(const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return put(QString(), headers); }
    QCurlResponse dele(const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return dele(QString(), headers); }
    QCurlResponse head(const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return head(QString(), headers); }

    QCurlResponse post(const QCurlBytes &bytes, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return post(QString(), bytes, headers); }
    QCurlResponse post(const QCurlFormData &form, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return post(QString(), form, headers); }
    QCurlResponse post(const QCurlJson &json, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return post(QString(), json, headers); }
    QCurlResponse post(QCurlMultipart &parts, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return post(QString(), parts, headers); }
    QCurlResponse post(QIODevice &stream, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return post(QString(), stream, headers); }

    QCurlResponse put(const QCurlBytes &bytes, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return put(QString(), bytes, headers); }
    QCurlResponse put(const QCurlFormData &form, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return put(QString(), form, headers); }
    QCurlResponse put(const QCurlJson &json, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return put(QString(), json, headers); }
    QCurlResponse put(QCurlMultipart &parts, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return put(QString(), parts, headers); }
    QCurlResponse put(QIODevice &stream, const QCurlHeaders &headers = QCurlHeadersEmpty)
    { return put(QString(), stream, headers); }


    static QCurlResponse get(const QUrl &url, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse post(const QUrl &url, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse put(const QUrl &url, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse dele(const QUrl &url, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse head(const QUrl &url, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static int exists(const QUrl &url);

    static QCurlResponse post(const QUrl &url, const QCurlBytes &bytes, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse post(const QUrl &url, const QCurlFormData &form, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse post(const QUrl &url, const QCurlJson &json, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse post(const QUrl &url, QCurlMultipart &parts, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse post(const QUrl &url, QIODevice &stream, const QCurlHeaders &headers = QCurlHeadersEmpty);

    static QCurlResponse put(const QUrl &url, const QCurlBytes &bytes, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse put(const QUrl &url, const QCurlFormData &form, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse put(const QUrl &url, const QCurlJson &json, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse put(const QUrl &url, QCurlMultipart &parts, const QCurlHeaders &headers = QCurlHeadersEmpty);
    static QCurlResponse put(const QUrl &url, QIODevice &stream, const QCurlHeaders &headers = QCurlHeadersEmpty);

};

#endif // QCURL_H
