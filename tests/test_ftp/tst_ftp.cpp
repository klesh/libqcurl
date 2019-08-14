#include <QtTest>
#include "qcurl.h"

// add necessary includes here
// should run `mockserver` first

class Ftp : public QObject
{
    Q_OBJECT

public:
    Ftp();
    ~Ftp();

private slots:
    void testSimpleGet();
    void testExists();
    void testPutAndDelete();
};

Ftp::Ftp()
{

}

Ftp::~Ftp()
{

}

void Ftp::testSimpleGet()
{
    auto res = QCurl::get(QUrl("ftp://ftpuser:ftppass@localhost:7881/hello.txt"));
    QCOMPARE(res.responseText().trimmed(), "helloworld");
}

void Ftp::testExists()
{
    QCurl curl(QUrl("ftp://ftpuser:ftppass@localhost:7881/"));
    int helloExists, notfoundExists;
    curl.exists(helloExists, "hello.txt");
    auto res = curl.exists(notfoundExists, "notfound.txt");
    QCOMPARE(helloExists, 1);
    QCOMPARE(notfoundExists, 0);
    QVERIFY(!res.message().isEmpty());
}

void Ftp::testPutAndDelete()
{
    QCurl curl(QUrl("ftp://ftpuser:ftppass@localhost:7881/"));
//    auto req = curl.request();
//    req.setRange("0-0");
//    req.setVerbose(true);
//    auto res = req.perform("GET", "foobar.txt");
//    qDebug() << res.code();

    QByteArray bytes = QString("this is a test").toUtf8();
    QBuffer buffer(&bytes);
    auto putRes = curl.put("foobar.txt", buffer);
    QCOMPARE(putRes.code(), 0);

    auto getRes = curl.get("foobar.txt");
    QCOMPARE(getRes.responseText(), "this is a test");

    auto delRes = curl.dele("foobar.txt");

    int foobarExists;
    curl.exists(foobarExists, "foobar.txt");
    QCOMPARE(foobarExists, 0);
}


QTEST_APPLESS_MAIN(Ftp)

#include "tst_ftp.moc"
