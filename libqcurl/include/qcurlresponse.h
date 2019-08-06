#ifndef QCURLRESPONSE_H
#define QCURLRESPONSE_H

#include "qcurlbase.h"

struct QCurlResponseData : public QSharedData
{
    QCurlData &data;
    CURLcode code;
    QString message;
    QCurlHeaders headers;
    uint statusCode;
    QString status;
    QByteArray body;
    QString responseText;
    QJsonDocument responseJson;

    QCurlResponseData(QCurlData &d) : data(d) {}
    ~QCurlResponseData() { }
    // skip the copy constructor since this should never be deep copied
};

class Q_DECL_EXPORT QCurlResponse : public QObject
{
    Q_OBJECT

    QSharedDataPointer<QCurlResponseData> d;

    static size_t writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata);
    static size_t headerCallback(char *buffer, size_t size, size_t nitems, void *userdata);

public:
    QCurlResponse(QCurlData &data);
    QCurlResponse(const QCurlResponse &other) : QObject(), d(other.d) {}
    CURLcode code() { return d->code; }
    QString message() { return d->message; }
    QCurlHeaders &headers() { return d->headers; }
    uint statusCode() { return d->statusCode; }
    QString status() { return d->status; }
    QString responseText();
    QCurlJson responseJson();
    QString getHeader(const QString &name);
};

#endif // QCURLRESPONSE_H
