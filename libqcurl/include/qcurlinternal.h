#ifndef QCURLINTERNAL_H
#define QCURLINTERNAL_H

#include "qcurlbase.h"
#include <curl/curl.h>

class QCurlData: public QSharedData
{
public:
    CURL *curl = nullptr;
    struct curl_slist *cookies = nullptr; // struct_slist
    QCurlHeaders headers;
    QString userAgent;
    QUrl proxyUrl;
    QString privateKeyPath;
    QString publicKeyPath;
    QString keyPassword;
    bool verbose = false;
    bool flowLocation = true;
    const QUrl &baseUrl;
    int counter = 0; // make sure only one request at a time

    QCurlData(const QUrl &baseUrl)
        : baseUrl(baseUrl)
    {
        curl = curl_easy_init();
    }

    ~QCurlData()
    {
        curl_easy_cleanup(curl);
        if (cookies) curl_slist_free_all(cookies);
        curl = nullptr;
        cookies = nullptr;
    }
};

class QCurlRequestData : public QSharedData
{
public:
    QCurlData &session;
    struct curl_slist *headers = nullptr;
    struct curl_slist *quote = nullptr;
    curl_mime *form = nullptr; // curl_mime

    QByteArray body; // for small text base body
    bool performed = false;

    QCurlRequestData(QCurlData &data)
        : session(data)
    {
    }

    ~QCurlRequestData()
    {
        if (headers) curl_slist_free_all(headers);
        if (quote) curl_slist_free_all(quote);
        if (form) curl_mime_free(form);
        body.clear();
    }
};

class QCurlResponseData : public QSharedData
{
public:
    QCurlRequestData &request;
    CURLcode code;
    QString message;
    QCurlHeaders headers;
    long statusCode;
    QString status;
    const QUrl &url;
    QIODevice *body;
    QString responseText;
    QJsonDocument responseJson;
    bool bodyDeletion = false;

    QCurlResponseData(QCurlRequestData &d, const QUrl &u, QIODevice *b = nullptr)
        : request(d), url(u), body(b) {
        if (!b) {
            body = new QBuffer();
            body->open(QIODevice::ReadWrite);
            bodyDeletion = true;
        } else if (body->isOpen() == false) {
            body->open(QIODevice::ReadWrite);
        }
        assert(body->openMode() != QIODevice::ReadOnly);
    }

    ~QCurlResponseData() {
        if (bodyDeletion) {
            body->close();
            delete body;
        }
    }
};

#endif // QCURLINTERNAL_H
