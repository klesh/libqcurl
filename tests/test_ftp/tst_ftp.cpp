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
    void testWhole();
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
//    QCOMPARE(res.statusCode(), 200);
    QCOMPARE(res.responseText(), "helloworld");
}

void Ftp::testWhole()
{
    QCurl curl(QUrl("ftp://ftpuser:ftppass@localhost:7881/"));
    auto head1 = curl.head("hello.txt");
    qDebug() << "head1 response" << head1.responseText() << "code" << head1.code();

    qDebug() << "start head 2";
    auto head2 = curl.head("notfound.txt");
    qDebug() << "head2 response" << head2.responseText() << "code" << head2.code();

    qDebug() << "start head 3";
    auto head3 = curl.get("hello.txt");
    qDebug() << "head3 response" << head3.responseText() << "code" << head3.code();

    qDebug() << "start range notfound";
    auto req = curl.request();
    req.setRange("0-0");
    auto res = req.perform("GET", QUrl("notfound.txt"));
    qDebug() << "notfound.txt response" << res.responseText() << "code" << res.code();
    QCOMPARE(res.code(), CURLE_REMOTE_FILE_NOT_FOUND);

    qDebug() << "start range hello.txt";
    auto req1 = curl.request();
    req1.setRange("0-0");
    auto res1 = req1.perform("GET", QUrl("hello.txt"));
    qDebug() << "hello.txt response" << res1.responseText() << "code" << res1.code();
}


QTEST_APPLESS_MAIN(Ftp)

#include "tst_ftp.moc"
