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
    void testProxy();
    void testHttps();
    void testNotfound();
    void testPost();
    void testPutAndDelete();
    void testQVariant();
    void testExists();
    void testDownload();
    void testHeaders();
    void testUploadFile();
};

Http::Http()
{

}

Http::~Http()
{

}

void Http::testSimpleGet()
{
    auto res = QCurl::get(QUrl("http://localhost:7880"));
    QCOMPARE(res.statusCode(), 200);
    QCOMPARE(res.responseText(), "hello world");
}


void Http::testProxy()
{
    QCurl curl(QUrl("http://example.com"));
    curl.setVerbose(true);
    curl.setProxyUrl(QUrl("socks5://puser:ppass@localhost:7884"));
    auto res = curl.get();
    QCOMPARE(res.statusCode(), 200);
    QVERIFY(res.responseText().isEmpty() == false);
}

void Http::testHttps()
{
    auto res = QCurl::get(QUrl("https://example.com"));
    QCOMPARE(res.statusCode(), 200);
}

void Http::testNotfound()
{
    auto res = QCurl::get(QUrl("http://localhost:7880/notfound"));
    QCOMPARE(res.statusCode(), 404);
}

void Http::testPost()
{
    // post empty body
    auto res = QCurl::post(QUrl("http://localhost:7880/echo"));
    QCOMPARE(res.statusCode(), 200);

    // post plain text
    auto res2 = QCurl::post(QUrl("http://localhost:7880/echo"), "foobar");
    QCOMPARE(res2.statusCode(), 200);
    QCOMPARE(res2.responseText(), "foobar");

    // post ordinary form
    QCurlForm form;
    form.append({"hello", "world"});
    auto res3 = QCurl::post(QUrl("http://localhost:7880/form"), form);
    QCOMPARE(res3.responseText(), "world");

    // post and receive json
    QJsonObject postRoot;
    postRoot.insert("username", "foobar");
    postRoot.insert("password", "helloworld");
    QCurlJson postJson(postRoot);
    auto res4 = QCurl::post(QUrl("http://localhost:7880/json"), postJson);
    auto resJson = res4.responseJson();
    QCOMPARE(res4.statusCode(), 200);
    auto root = resJson.object();
    QCOMPARE(root["code"].toString(), "SUCCESS");
    auto data = root["data"].toObject();
    QCOMPARE(data["username"].toString(), "foobar");
    QCOMPARE(data["password"].toString(), "helloworld");

    // upload file by multipart
    QCurlMultipart parts;
    parts.append({"filename", "plaintextfile.txt"});

    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    const int randomStringLength = 1024 * 23; // assuming you want random strings of 12 characters

    QString randomString;
    for(int i=0; i<randomStringLength; ++i)
    {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }
    QByteArray bytes = randomString.toUtf8();
    QBuffer buffer(&bytes);
    buffer.setProperty("filename", "plaintextfile.txt");
    parts.append({"file", QVariant::fromValue(&buffer)});
    auto res5 = QCurl::post(QUrl("http://localhost:7880/parts"), parts);
    QCOMPARE(res5.statusCode(), 200);
    QCOMPARE(res5.responseText(), "plaintextfile.txt\n"+randomString);

    QBuffer buffer2(&bytes);
    auto res6 = QCurl::post(QUrl("http://localhost:7880/raw"), buffer2);
    QCOMPARE(res6.statusCode(), 200);
    QCOMPARE(res6.responseText(), randomString);
}

void Http::testPutAndDelete()
{
    auto res = QCurl::put(QUrl("http://localhost:7880/method"));
    QCOMPARE(res.statusCode(), 200);
    QCOMPARE(res.responseText(), "PUT");

    auto res2 = QCurl::dele(QUrl("http://localhost:7880/method"));
    QCOMPARE(res2.statusCode(), 200);
    QCOMPARE(res2.responseText(), "DELETE");
}

void Http::testQVariant()
{
    QByteArray bytes = QString("hello world").toUtf8();
    QBuffer buffer(&bytes);

    QVariant var = QVariant::fromValue(&buffer);

    QVERIFY(var.canConvert<QIODevice*>());

    QVariant var2 = QString("foobar");

    QCOMPARE(var2.canConvert<QIODevice*>(), false);

    QUrl url("HTTPs://example.com");
    QCOMPARE(url.scheme(), "https");
}

void Http::testExists()
{
    int echoExists, notfoundExists;
    QCurl::exists(echoExists, QUrl("http://localhost:7880/echo"));
    QCurl::exists(notfoundExists, QUrl("http://localhost:7880/notfound"));
    QCOMPARE(echoExists, 1);
    QCOMPARE(notfoundExists, 0);
}

void Http::testDownload()
{
    QCurl curl(QUrl("http://localhost:7880/"));
    QTemporaryFile file;
    auto req = curl.request();
    auto res = req.perform("GET", "", &file);
    file.seek(0);
    QCOMPARE(file.readAll(), "hello world");
}

void Http::testHeaders()
{
    QCurl curl(QUrl("http://localhost:7880/"));
    curl.setHeaders({{"auth", "haha"}});
    curl.setVerbose(true);
    auto res = curl.get("echo-header/auth");
    QCOMPARE(res.responseText(), "haha");
}

void Http::testUploadFile()
{
    QByteArray bytes1 = "abcd";
    QByteArray bytes2;
    bytes2.append("ab");
    bytes2.append("cd");
    QCOMPARE(bytes1, bytes2);

    QCurlMultipart parts;
    QFile img(TEST_IMG_PATH);
    parts.append({"file", QVariant::fromValue(&img)});
    QCurl curl(QUrl("http://localhost:7880/upload"));
//    curl.setVerbose(true);
    auto res = curl.post(parts);
    QFile img2(TEST_IMG_PATH);
    img2.open(QIODevice::ReadOnly);
    auto imgAll = img2.readAll();
    QVERIFY(imgAll.size());
    QCOMPARE(imgAll, res.device()->readAll());
}

QTEST_APPLESS_MAIN(Http)

#include "tst_http.moc"
