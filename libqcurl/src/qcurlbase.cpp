#include "qcurlbase.h"
#include <curl/curl.h>

QCurlData::QCurlData(const QUrl &baseUrl)
    : baseUrl(baseUrl)
{
    curl = curl_easy_init();
}

QCurlData::~QCurlData()
{
    curl_easy_cleanup(curl);
    if (cookies) curl_slist_free_all(CURL_SLIST(cookies));
    curl = nullptr;
    cookies = nullptr;
}

QCurlRequestData::QCurlRequestData(QCurlData &session)
    : session(session)
{

}

QCurlRequestData::~QCurlRequestData()
{
    if (headers) curl_slist_free_all(CURL_SLIST(headers));
    if (quote) curl_slist_free_all(CURL_SLIST(quote));
    if (form) curl_mime_free(CURL_MIME(form));
    body.clear();
}

QCurlResponseData::QCurlResponseData(QCurlRequestData &d, const QUrl &u, QIODevice *b)
    : request(d), url(u), body(b)
{
    if (!b) {
        body = new QBuffer();
        body->open(QIODevice::ReadWrite);
        bodyDeletion = true;
    } else if (body->isOpen() == false) {
        body->open(QIODevice::ReadWrite);
    }
    assert(body->openMode() != QIODevice::ReadOnly);
}

QCurlResponseData::QCurlResponseData::~QCurlResponseData()
{
    if (bodyDeletion) {
        body->close();
        delete body;
    }
}
