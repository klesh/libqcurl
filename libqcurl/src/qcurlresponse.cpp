#include "qcurlresponse.h"

size_t QCurlResponse::writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    int l = static_cast<int>(size * nmemb);
    auto out = static_cast<QIODevice*>(userdata);
    out->write(ptr, l);
    return static_cast<size_t>(l);
}

size_t QCurlResponse::headerCallback(char *buffer, size_t size, size_t nitems, void *userdata)
{
    int l = static_cast<int>(size * nitems);
    auto res = static_cast<QCurlResponse*>(userdata);
    QByteArray bytes;
    bytes.append(buffer, l);
    QString text(bytes);
    text = text.trimmed();
    auto scheme = res->d->url.scheme();
    if (scheme.startsWith("http")) {
        if (text.contains(':')) {
            auto tmp = text.split(':');
            res->d->headers.insert(tmp[0], tmp[1].trimmed());
        } else if (!text.isEmpty()) {
            int fs = text.indexOf(' ');
            int ss = text.indexOf(' ', fs + 1);
            QString statusCode = text.mid(fs + 1, ss - fs - 1);
            res->d->statusCode = statusCode.toLong();
            res->d->status = text.mid(ss + 1).trimmed();
        }
    } else if (scheme.startsWith("ftp")) {
        qDebug() << "** header" << text;
    }
    return static_cast<size_t>(l);
}

QCurlResponse::QCurlResponse(QCurlData &data, const QUrl &url)
    : d(new QCurlResponseData(data, url))
{
    // actually perform curl request
    curl_easy_setopt(d->data.curl, CURLOPT_HEADERFUNCTION, headerCallback);
    curl_easy_setopt(d->data.curl, CURLOPT_HEADERDATA, this);
    curl_easy_setopt(d->data.curl, CURLOPT_WRITEFUNCTION, writeCallback);

    QBuffer buffer(&d->body);
    buffer.open(QIODevice::WriteOnly);
    curl_easy_setopt(d->data.curl, CURLOPT_WRITEDATA, &buffer);

    d->code = curl_easy_perform(d->data.curl);

    if (d->code == CURLE_OK) {
        curl_easy_getinfo(d->data.curl, CURLINFO_RESPONSE_CODE, &d->statusCode);
    }
}

QCurlResponse::QCurlResponse(const QCurlResponse &other) : QObject(), d(other.d)
{

}


QString QCurlResponse::responseText()
{
    if (d->responseText.isNull()) {
        d->responseText = QString(d->body);
    }
    return d->responseText;
}

QJsonDocument QCurlResponse::responseJson()
{
    if (d->responseJson.isNull() && !d->body.isEmpty()) {
        d->responseJson = QJsonDocument::fromJson(d->body);
    }
    return d->responseJson;
}

QString QCurlResponse::getHeader(const QString &name)
{
    auto lowerName = name.toLower();
    for (auto &key : d->headers.keys()) {
        if (key.toLower() == lowerName) {
            return d->headers[key];
        }
    }
    return nullptr;
}
