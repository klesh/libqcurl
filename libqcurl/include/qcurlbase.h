#ifndef QCURLBASE_H
#define QCURLBASE_H

#include <curl/curl.h>
#include <QtCore>

#define QCurlHeaders QMap<QString, QString>
#define QCurlHeadersEmpty QMap<QString, QString>()
#define QCurlForm QList<QPair<QString, QString>>
#define QCurlMultipart QList<QPair<QString, QVariant>>
#define QCurlJson QJsonDocument
#define QCurlBytes QByteArray


class QCurl;
class QCurlRequest;
class QCurlResponse;

struct QCurlData {
    CURL *curl = nullptr;
    struct curl_slist *cookies = nullptr;
    struct curl_slist *headers = nullptr;
    struct curl_slist *quote = nullptr;
    QUrl baseUrl;
    QByteArray body; // for small text base body
    curl_mime *form = nullptr; // for big multipart form
    int counter = 0; // make sure only one request at a time
    bool performed = false;
};

#endif // QCURLBASE_H
