#ifndef QCURLREQUEST_H
#define QCURLREQUEST_H

#include "qcurlbase.h"

class Q_DECL_EXPORT QCurlRequest : public QObject
{
    Q_OBJECT

    QCurlData &_data;
    static size_t readCallback(char *buffer, size_t size, size_t nitems, void *arg);
    static int seekCallback(void *arg, curl_off_t offset, int origin);
    static void freeCallback (void *arg);

public:
    QCurlRequest(QCurlData &data);
    QCurlRequest(const QCurlRequest &other);
    void setHeader(const QString &name, const QString &value);
    void setHeaders(const QCurlHeaders &headers);
    void setUserAgent(const QString &userAgent);
    void setProxyUrl(const QUrl &proxyUrl);
    void setPrivateKeyPath(const QString &privateKeyPath);
    void setPublicKeyPath(const QString &publicKeyPath);
    void setKeyPassword(const QString &keyPassword);
    void setVerbose(bool verbose);
    void setNoBody(bool nobody);
    void setFlowLocation(bool flow);
    void setBody(const QCurlBytes &bytes);
    void setBody(const QCurlFormData &form);
    void setBody(const QCurlJson &json);
    void setBody(QCurlMultipart &parts);
    void setBody(QIODevice &stream);
    void setRange(QString range);

    QCurlResponse perform(const QString &method, const QUrl &url = QUrl());
};

#endif // QCURLREQUEST_H
