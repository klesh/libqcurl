#ifndef QCURLBASE_H
#define QCURLBASE_H

#include <QtCore>

#define QCurlHeaders QMap<QString, QString>
#define QCurlHeadersEmpty QMap<QString, QString>()
#define QCurlForm QList<QPair<QString, QString>>
#define QCurlMultipart QList<QPair<QString, QVariant>>
#define QCurlJson QJsonDocument
#define QCurlBytes QByteArray

class QCurlRequestData;
class QCurlResponseData;
class QCurlData;

class QCurlRequest;
class QCurlResponse;
class QCurl;


#endif // QCURLBASE_H
