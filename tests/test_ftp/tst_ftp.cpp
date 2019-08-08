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
    QCOMPARE(curl.exists("hello.txt"), 1);
    QCOMPARE(curl.exists("notfound.txt"), 0);
}

void Ftp::testPutAndDelete()
{
    QCurl curl(QUrl("ftp://ftpuser:ftppass@localhost:7881/"));
    QByteArray bytes = QString("this is a test").toUtf8();
    QBuffer buffer(&bytes);
    auto putRes = curl.put("foobar.txt", buffer);
    QCOMPARE(putRes.code(), CURLE_OK);

    auto getRes = curl.get("foobar.txt");
    QCOMPARE(getRes.responseText(), "this is a test");

    auto delRes = curl.dele("foobar.txt");

    QCOMPARE(curl.exists("foobar.txt"), 0);
}


QTEST_APPLESS_MAIN(Ftp)

#include "tst_ftp.moc"
