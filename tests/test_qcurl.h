#ifndef TEST_QCURL_H
#define TEST_QCURL_H

#include "qcurl.h"
#include <QtDebug>


void test_header() {
    QCurlSession curl;
    curl.setVerbose(true);
    QCurlResponse res = curl.get(QUrl("https://baidu.com"));
    qDebug() << "* code" << res.code() << "status code" << res.statusCode() << "status" << res.status();
    for (const auto &name : res.headers().keys()) {
        qDebug() << "* header " << name << res.getHeader(name);
    }
    qDebug() << res.responseText();
}

void test_qcurl() {
    QCurlSession curl;
    curl.setHeaders({{"Authroization", "Bearer: foobar"}});
    curl.setUserAgent("ua");
    curl.setUserName("test");
    curl.setPassword("test");
    curl.setSshKeyFiles("path/to/id_rsa", "path/to/id_rsa.pub");
    curl.setVerbose(true);

//    auto latestUrlRes = curl.get(QUrl("http://example.com/latest-url.txt"));
//    if (latestUrlRes.code()) {
//        qDebug() << latestUrlRes.message();
//        return;
//    }

//    auto latestUrl = latestUrlRes.responseText();

//    auto existsReq = curl.request();
//    existsReq.setNoBody(true);
//    auto existsRes = existsReq.perform("", latestUrl);
//    if (existsRes.code() == 0) // already exists;
//        return;
//    auto uploadRes = curl.put(latestUrl, fileStream);
//    if (uploadRes.code) {
//        qDebug() << uploadRes.message();
//        return;
//    }

//    auto logRes = curl.post("http://example.com/api/log",
//                            {{"uploadedAt", "2019-10-10T22:22:22Z"}},
//                            {{"Content-Type", "application/json"}});
//    if (logRes.code) {
//        qDebug() << logRes.message();
//        return;
//    }

//    auto expireCacheRes = curl.dele("http://example.com/api/cache/latest");
}

#endif // TEST_QCURL_H
