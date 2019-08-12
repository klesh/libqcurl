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
    void testPrivateKeySimpleGet();
};

Sftp::Sftp()
{

}

Sftp::~Sftp()
{

}

void Sftp::testSimpleGet()
{
    auto res = QCurl::get(QUrl("sftp://sftpuser:sftppass@localhost:7882/home/sftpuser/foobar.txt"));
    QCOMPARE(res.responseText().trimmed(), "foobar");
}

void Sftp::testPrivateKeySimpleGet()
{
    QCurl curl(QUrl("sftp://sftpkey@localhost:7882/home/sftpkey/hello.txt"));
    curl.setVerbose(true);
    curl.setSshKeyFiles(ID_RSA_PATH, ID_RSA_PUB_PATH, "pass");
    qDebug() << ID_RSA_PATH << ID_RSA_PUB_PATH;
    auto res = curl.get();
    qDebug() << "res" << res.code();
    QCOMPARE(res.responseText().trimmed(), "hello world");
}

void Sftp::testExists()
{
    QCurl curl(QUrl("sftp://sftpuser:sftppass@localhost:7882/"));
    QCOMPARE(curl.exists("/home/sftpuser/foobar.txt"), 1);
    QCOMPARE(curl.exists("/home/sftpuser/notfound.txt"), 0);
}

void Sftp::testPutAndDelete()
{
    QCurl curl(QUrl("sftp://sftpuser:sftppass@localhost:7882/"));
    QByteArray bytes = QString("this is a test").toUtf8();
    QBuffer buffer(&bytes);
    auto putRes = curl.put("/home/sftpuser/hello.txt", buffer);
    QCOMPARE(putRes.code(), 0);

    auto getRes = curl.get("/home/sftpuser/hello.txt");
    QCOMPARE(getRes.responseText(), "this is a test");

    auto delRes = curl.dele("/home/sftpuser/hello.txt");

    QCOMPARE(curl.exists("foobar.txt"), 0);
}


QTEST_APPLESS_MAIN(Sftp)

#include "tst_sftp.moc"
