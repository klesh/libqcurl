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
    void testMkdirP();
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
    curl.setPrivateKeyPath(ID_RSA_PATH);
    curl.setPublicKeyPath(ID_RSA_PUB_PATH);
    curl.setKeyPassword("pass");
    qDebug() << ID_RSA_PATH << ID_RSA_PUB_PATH;
    auto res = curl.get();
    qDebug() << "res" << res.code();
    QCOMPARE(res.responseText().trimmed(), "hello world");
}

void Sftp::testMkdirP()
{
    QCurl curl(QUrl("sftp://sftpuser:sftppass@localhost:7882/"));
    QByteArray bytes = QString("this is a test").toUtf8();
    QBuffer buffer(&bytes);
    auto putRes = curl.put("/home/sftpuser/somefolder/hello.txt", buffer);
    QCOMPARE(putRes.code(), 0);
    auto getRes = curl.get("/home/sftpuser/somefolder/hello.txt");
    QCOMPARE(getRes.responseText(), "this is a test");
}

void Sftp::testExists()
{
    QCurl curl(QUrl("sftp://sftpuser:sftppass@localhost:7882/"));
    int foobarExists, notfoundExists;
    curl.exists(foobarExists, "/home/sftpuser/foobar.txt");
    curl.exists(notfoundExists, "/home/sftpuser/notfound.txt");
    QCOMPARE(foobarExists, 1);
    QCOMPARE(notfoundExists, 0);

//    QCurl curl(QUrl("sftp://sftpuser:sftppass@localhost:2222/"));
//    curl.setVerbose(true);
//    int helloExists, notfoundExists;
//    auto res = curl.exists(helloExists, "/home/sftpuser/hello.txt");
//    qDebug() << res.code() << res.message();
//    QCOMPARE(helloExists, 1);
//    curl.exists(notfoundExists, "/home/ftpuser/notfound.txt");
//    QCOMPARE(notfoundExists, 0);


//    QByteArray bytes = QString("this is a test").toUtf8();
//    QBuffer buffer(&bytes);
//    QFile file("C:/Users/Klesh Wong/Desktop/ImageSets/rotd/diamondskull.bmp");
//    auto putRes = curl.put("/home/ftpuser/hello.txt", file);
//    QCOMPARE(putRes.code(), 0);

//    auto getRes = curl.get("/home/sftpuser/hello.txt");
//    QCOMPARE(getRes.responseText(), "this is a test");

//    auto delRes = curl.dele("/home/sftpuser/hello.txt");

//    QCOMPARE(curl.exists("foobar.txt"), 0);
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

    int foobarExists;
    curl.exists(foobarExists, "foobar.txt");
    QCOMPARE(foobarExists, 0);
}


QTEST_APPLESS_MAIN(Sftp)

#include "tst_sftp.moc"
