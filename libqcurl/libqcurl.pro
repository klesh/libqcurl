#-------------------------------------------------
#
# Project created by QtCreator 2019-07-22T22:50:56
#
#-------------------------------------------------

QT       += core network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qcurl
TEMPLATE = lib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS  CURL_STATICLIB

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 staticlib

INCLUDEPATH += include

HEADERS += \
    include/qcurl.h \
    include/qcurlbase.h \
    include/qcurlrequest.h \
    include/qcurlresponse.h \

SOURCES += \
        src/qcurl.cpp \
        src/qcurlrequest.cpp \
        src/qcurlresponse.cpp

win32 {
    INCLUDEPATH += D:/Projects/curl/curl-7.65.3/builds/libcurl-vc-x86-release-static-ssh2-dll-ipv6-sspi-winssl/include
    LIBS += -LD:/Projects/curl/curl-7.65.3/builds/libcurl-vc-x86-release-static-ssh2-dll-ipv6-sspi-winssl/lib \
            -LD:/Projects/curl/deps/lib \
            -lws2_32 -lAdvapi32 -lCrypt32 -lWldap32 -lNormaliz -lUser32 -llibcurl_a -llibssh2
}

unix {
    LIBS += -lcurl
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
