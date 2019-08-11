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

    QSharedDataPointer<QCurlResponseData> d;

public:
    QCurlResponse(QCurlRequestData &data, const QUrl &url, QIODevice *b = nullptr);
    QCurlResponse(const QCurlResponse &other);

    //! CURLcode returned by curl_easy_perform
    int code();

    //! CURLcode message if any
    QString message();

    //! Response headers
    QCurlHeaders &headers();

    //! HTTP STATUS CODE
    long statusCode();

    //! HTTP STATUS TEXT
    QString status();

    //! Full response text
    QString responseText();

    //! Parse response text to QJsonDocument
    QCurlJson responseJson();

    //! Headers
    QString getHeader(const QString &name);
};

#endif // QCURLRESPONSE_H
