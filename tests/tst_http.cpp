#include <QtTest>
#include "qcurl.h"

// add necessary includes here
// should run `mockserver` first

class Http : public QObject
{
    Q_OBJECT

public:
    Http();
    ~Http();

private slots:
    void testSimpleGet();
    void testNotfound();
    void testPost();
};

Http::Http()
{

}

Http::~Http()
{

}

void Http::testSimpleGet()
{
    QCurlSession curl;
    auto res = curl.get(QUrl("http://localhost:7880"));
    QCOMPARE(res.statusCode(), 200);
    QCOMPARE(res.responseText(), "hello world");
}

void Http::testNotfound()
{
    QCurlSession curl;
    auto res = curl.get(QUrl("http://localhost:7880/notfound"));
    QCOMPARE(res.statusCode(), 404);
}

void Http::testPost()
{
    QCurlSession curl;
    auto res = curl.post(QUrl("http://localhost:7880/echo"));
    QCOMPARE(res.statusCode(), 200);

    auto res2 = curl.post(QUrl("http://localhost:7880/echo"), "foobar");
    QCOMPARE(res2.statusCode(), 200);
    QCOMPARE(res2.responseText(), "foobar");

    QCurlFormData form;
    form.append({"hello", "world"});
    auto res3 = curl.post(QUrl("http://localhost:7880/form"), form);
    QCOMPARE(res3.responseText(), "world");
}

QTEST_APPLESS_MAIN(Http)

#include "tst_http.moc"
