#include <QtTest>
#include "qcurl.h"

// add necessary includes here

class headers : public QObject
{
    Q_OBJECT

public:
    headers();
    ~headers();

private slots:
    void test_case1();

};

headers::headers()
{

}

headers::~headers()
{

}

void headers::test_case1()
{
    QCurlSession curl;
    auto res = curl.get(QUrl("https://baidu.com"));
    QVERIFY(res.statusCode() == 200);
}

QTEST_APPLESS_MAIN(headers)

#include "tst_headers.moc"
