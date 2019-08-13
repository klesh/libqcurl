#include "qcurlresponse.h"
#include <curl/curl.h>

size_t writeCallback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    int l = static_cast<int>(size * nmemb);
    auto out = static_cast<QIODevice*>(userdata);
    out->write(ptr, l);
    return static_cast<size_t>(l);
}

size_t headerCallback(char *buffer, size_t size, size_t nitems, void *userdata)
{
    int l = static_cast<int>(size * nitems);
    auto resdata = static_cast<QCurlResponseData*>(userdata);
    QByteArray bytes;
    bytes.append(buffer, l);
    QString text(bytes);
    text = text.trimmed();
    auto scheme = resdata->url.scheme();
    if (scheme.startsWith("http")) {
        if (text.contains(':')) {
            auto tmp = text.split(':');
            resdata->headers.insert(tmp[0], tmp[1].trimmed());
        } else if (!text.isEmpty()) {
            int fs = text.indexOf(' ');
            int ss = text.indexOf(' ', fs + 1);
            QString statusCode = text.mid(fs + 1, ss - fs - 1);
            resdata->statusCode = statusCode.toLong();
            resdata->status = text.mid(ss + 1).trimmed();
        }
    }
    return static_cast<size_t>(l);
}

QCurlResponse::QCurlResponse(QCurlRequestData &data, const QUrl &url, QIODevice *body)
    : d(new QCurlResponseData(data, url, body))
{
    // actually perform curl request
    curl_easy_setopt(d->request.session.curl, CURLOPT_HEADERFUNCTION, headerCallback);
    curl_easy_setopt(d->request.session.curl, CURLOPT_HEADERDATA, d.data());
    curl_easy_setopt(d->request.session.curl, CURLOPT_WRITEFUNCTION, writeCallback);

    curl_easy_setopt(d->request.session.curl, CURLOPT_WRITEDATA, d->body);

    d->code = curl_easy_perform(d->request.session.curl);
    d->body->seek(0);

    if (d->code == CURLE_OK) {
        curl_easy_getinfo(d->request.session.curl, CURLINFO_RESPONSE_CODE, &d->statusCode);
    }
}

QCurlResponse::QCurlResponse(const QCurlResponse &other) : QObject(), d(other.d)
{

}

int QCurlResponse::code()
{
    return d->code;
}

QString QCurlResponse::message()
{
    return d->message;
}

QMap<QString, QString> &QCurlResponse::headers()
{
    return d->headers;
}

long QCurlResponse::statusCode()
{
    return d->statusCode;
}

QString QCurlResponse::status()
{
    return d->status;
}


QString QCurlResponse::responseText()
{
    if (d->responseText.isNull()) {
        assert(d->body->openMode() & QIODevice::ReadOnly);
        d->responseText = QString(d->body->readAll());
    }
    return d->responseText;
}

QJsonDocument QCurlResponse::responseJson()
{
    if (d->responseJson.isNull()) {
        d->responseJson = QJsonDocument::fromJson(this->responseText().toUtf8());
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
