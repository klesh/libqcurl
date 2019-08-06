#ifndef QCURLBASE_H
#define QCURLBASE_H

#include <curl/curl.h>
#include <QtCore>
#include <QtDebug>

#define QCurlHeaders QMap<QString, QString>
#define QCurlHeadersEmpty QMap<QString, QString>()
#define QCurlFormData QList<QPair<QString, QString>>
#define QCurlMultipart QList<QPair<QString, QVariant>>
#define QCurlJson QVariantMap

class QCurlSession;
class QCurlRequest;
class QCurlResponse;

struct QCurlData {
    CURL *curl = nullptr;
    struct curl_slist *cookies = nullptr;
    struct curl_slist *headers = nullptr;
    int counter = 0; // make sure only one request at a time
};

#endif // QCURLBASE_H
