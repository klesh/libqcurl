#include <QtTest>
#include "qcurl.h"

// add necessary includes here
// should run `mockserver` first

class Sftp : public QObject
{
    Q_OBJECT

public:
    Sftp();
    ~Sftp();

private slots:
    void testSimpleGet();
    void testExists();
    void testPutAndDelete();
};

Sftp::Sftp()
{

}

Sftp::~Sftp()
{

}

void Sftp::testSimpleGet()
{
    auto res = QCurl::get(QUrl("sftp://ftpuser:ftppass@localhost:2222/home/ftpuser/hello.txt"));
    QCOMPARE(res.responseText().trimmed(), "hello");
}

void Sftp::testExists()
{
    QCurl curl(QUrl("sftp://ftpuser:ftppass@localhost:2222/"));
    QCOMPARE(curl.exists("/home/ftpuser/hello.txt"), 1);
    QCOMPARE(curl.exists("/home/ftpuser/notfound.txt"), 0);
}

void Sftp::testPutAndDelete()
{
    QCurl curl(QUrl("sftp://ftpuser:ftppass@localhost:2222/"));
    QByteArray bytes = QString("this is a test").toUtf8();
    QBuffer buffer(&bytes);
    auto putRes = curl.put("/home/ftpuser/foobar.txt", buffer);
    QCOMPARE(putRes.code(), CURLE_OK);

    auto getRes = curl.get("/home/ftpuser/foobar.txt");
    QCOMPARE(getRes.responseText(), "this is a test");

    auto delRes = curl.dele("/home/ftpuser/foobar.txt");

    QCOMPARE(curl.exists("foobar.txt"), 0);
}


QTEST_APPLESS_MAIN(Sftp)

#include "tst_sftp.moc"
