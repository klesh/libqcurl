
# Introduction

`QNetworkAccessManager` can not be used in a `QThread` by design, that is where `qcurl` comes in handy. You can use do Network Access in a intuitive way.

# Installation

## Linux
```
$ git clone https://github.com/klesh/libqcurl.git
$ cd libqcurl
& mkdir builds && cd builds
$ qmake .. && make && sudo make install
$ pkg-config --libs libqcurl
```

# Usage

## Simple cases

```cpp
#include <QtTest>
#include "qcurl.h"

int main() {
    // post empty body
    auto res = QCurl::post(QUrl("http://localhost:7880/echo"));
    QCOMPARE(res.statusCode(), 200);

    // post plain text
    auto res2 = QCurl::post(QUrl("http://localhost:7880/echo"), "foobar");
    QCOMPARE(res2.statusCode(), 200);
    QCOMPARE(res2.responseText(), "foobar");

    // post regular form
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

    QByteArray bytes = QString("hello world").toUtf8();
    QBuffer buffer(&bytes);
    buffer.setProperty("filename", "plaintextfile.txt");
    parts.append({"file", QVariant::fromValue(&buffer)});
    auto res5 = QCurl::post(QUrl("http://localhost:7880/parts"), parts);
    QCOMPARE(res5.statusCode(), 200);
    QCOMPARE(res5.responseText(), "plaintextfile.txt\nhello world");

    QBuffer buffer2(&bytes);
    auto res6 = QCurl::post(QUrl("http://localhost:7880/raw"), buffer2);
    QCOMPARE(res6.statusCode(), 200);
    QCOMPARE(res6.responseText(), "hello world");

    return 0;
}
```

## Download as file

```cpp
#include <QtTest>
#include "qcurl.h"

int main() {
    QCurl curl(QUrl("http://localhost:7880/"));
    QTemporaryFile file;
    auto req = curl.request();
    auto res = req.perform("GET", "hello.txt", &file);
    file.seek(0);
    QCOMPARE(file.readAll(), "hello world");
}
```

## Calling on APIs
```cpp
#include <QtTest>
#include "qcurl.h"

int main() {
    QCurl apiClient(QUrl("http://localhost:7880/api/")); // ending with slash is essential
    apiClient.setHeader("Authorization", "Bearer xxxx");

    auto usersRes = apiClient.get("users");
    auto users = usersRes.responseJson();
    // do sth with users

    auto userDetailRes = apiClient.get("users/123");
    auto userDetail = userDetailRes.responseJson(); 
    // do sth with userDetail
}
```

## FTP/SFTP

```cpp
#include <QtTest>
#include "qcurl.h"

int main() {
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
```


# How to run compile/test on Windows with MinGW
1. Download `curl` source code from https://curl.haxx.se/windows/
2. Download `deps` you need (`openssl`, `libssh2` is required) from https://windows.php.net/downloads/php-sdk/deps/vs16
3. Extract `curl` to some place , e.g. `D:\Projects\curl`, so all `curl` source code should be in `D:\Projects\curl\curl-7.65.3` or something like that.
4. Create folder `D:\Projects\curl\deps`, and extract deps of your choice into it. This folder should contains `bin` `include` and `lib` folders. beware `openssl` might have its `DLLs` in its root folder while others have them in `bin` folder, you'd better copy those `DLLs` to `bin` as well.
5. Open `Developer Command Prompt for VS` and go to `D:\Projects\curl\curl-7.65.3\winbuild` to build. For test I suggest follwing command: `nmake /f Makefile.vc mode=dll WITH_SSH2=dll WITH_ZLIB=static MACHINE=x86`
6. Some folder like `D:\Projects\curl\curl-7.65.3\builds\libcurl-vc-x86-release-dll-zlib-static-ssh2-dll-ipv6-sspi-winssl` should be created. Now, copy `bin` `include` `lib` to `D:\Projects\curl\deps`. So it becomes the `deps` folder we need for our `tests`
7. Clone `libqcurl` into some directory, Copy `deps\*` folder to `somedirectory\deps\selfbuild\i386` folder, along side with `libqcurl` and `tests` folder.  The project directory structure should look like:
```
   somedirectory\
    |_doc
    |_libqcurl
    |_test
    |
    |_deps
      |_selfbuild
        |_i386
          |_ lib
          |_ include
          |_ bin
        |_x86_64
          |_ lib
          |_ include
          |_ bin
```
8. Build and run `libqcurl` with `Qt Creator`

