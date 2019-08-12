#ifndef QCURLBASE_H
#define QCURLBASE_H

#include <QtCore>

#define QCurlHeaders QMap<QString, QString>
#define QCurlHeadersEmpty QMap<QString, QString>()
#define QCurlForm QList<QPair<QString, QString>>
#define QCurlMultipart QList<QPair<QString, QVariant>>
#define QCurlJson QJsonDocument
#define QCurlBytes QByteArray

#define CURL(d) static_cast<CURL>(d)
#define CURL_SLIST(d) static_cast<struct curl_slist*>(d)
#define CURL_MIME(d) static_cast<curl_mime*>(d)

struct QCurlData: public QSharedData
{
    void *curl = nullptr;
    void *cookies = nullptr; // struct curl_slist
    QCurlHeaders headers;
    QString userAgent;
    QUrl proxyUrl;
    QString privateKeyPath;
    QString publicKeyPath;
    QString keyPassword;
    bool verbose = false;
    bool flowLocation = true;
    const QUrl baseUrl;
    int counter = 0; // make sure only one request at a time

    QCurlData(const QUrl &baseUrl);
    virtual ~QCurlData();
};

struct QCurlRequestData : public QSharedData
{
    QCurlData &session;
    void *headers = nullptr; // struct curl_slist
    void *quote = nullptr;
    void *form = nullptr; // curl_mime

    QByteArray body; // for small text base body
    bool performed = false;

    QCurlRequestData(QCurlData &data);
    virtual ~QCurlRequestData();
};

struct QCurlResponseData : public QSharedData
{
    QCurlRequestData &request;
    int code;
    QString message;
    QCurlHeaders headers;
    long statusCode;
    QString status;
    const QUrl url;
    QIODevice *body;
    QString responseText;
    QJsonDocument responseJson;
    bool bodyDeletion = false;

    QCurlResponseData(QCurlRequestData &d, const QUrl &u, QIODevice *b = nullptr);
    virtual ~QCurlResponseData();
};

class QCurlRequest;
class QCurlResponse;
class QCurl;


#endif // QCURLBASE_H
