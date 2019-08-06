#ifndef QCURLREQUEST_H
#define QCURLREQUEST_H

#include "qcurlbase.h"

class Q_DECL_EXPORT QCurlRequest : public QObject
{
    Q_OBJECT

    QCurlData &_data;
    QByteArray _body;

public:
    QCurlRequest(QCurlData &data);
    QCurlRequest(const QCurlRequest &other);
    void setHeader(const QString &name, const QString &value);
    void setHeaders(const QCurlHeaders &headers);
    void setUserAgent(const QString &userAgent);
    void setProxyUrl(const QUrl &proxyUrl);
    void setUserName(const QString &userName);
    void setPassword(const QString &password);
    void setPrivateKeyPath(const QString &privateKeyPath);
    void setPublicKeyPath(const QString &publicKeyPath);
    void setVerbose(bool verbose);
    void setNoBody(bool nobody);
    void setFlowLocation(bool flow);
    void setBody(const QString &text);
    void setBody(const QCurlFormData &form);
//    void setBody(const QCurlJson &json);
//    void setBody(QCurlMultipart &parts);
//    void setBody(QDataStream &stream);

    QCurlResponse perform(const QString &method, const QUrl &url);
};

#endif // QCURLREQUEST_H
