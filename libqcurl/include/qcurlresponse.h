#ifndef QCURLRESPONSE_H
#define QCURLRESPONSE_H

#include "qcurlbase.h"

//! QCurlResponse represents specific Response to your Request
/*!
 * QCurlResponse use QShareDataPointer to hold its data, so it's safe to pass/return
 * instance between functions
 */
class Q_DECL_EXPORT QCurlResponse : public QObject
{
    Q_OBJECT

    struct QCurlResponseData : public QSharedData
    {
        QCurlData &data;
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

        QCurlResponseData(QCurlData &d, const QUrl &u, QIODevice *b = nullptr)
            : data(d), url(u), body(b) {
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
        // skip the copy constructor since this should never be deep copied
    };

    QSharedDataPointer<QCurlResponseData> d;

    static size_t writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata);
    static size_t headerCallback(char *buffer, size_t size, size_t nitems, void *userdata);

public:
    QCurlResponse(QCurlData &data, const QUrl &url, QIODevice *b = nullptr);
    QCurlResponse(const QCurlResponse &other);

    //! CURLcode returned by curl_easy_perform
    CURLcode code() { return d->code; }

    //! CURLcode message if any
    QString message() { return d->message; }

    //! Response headers
    QCurlHeaders &headers() { return d->headers; }

    //! HTTP STATUS CODE
    long statusCode() { return d->statusCode; }

    //! HTTP STATUS TEXT
    QString status() { return d->status; }

    //! Full response text
    QString responseText();

    //! Parse response text to QJsonDocument
    QCurlJson responseJson();

    //! Headers
    QString getHeader(const QString &name);
};

#endif // QCURLRESPONSE_H
