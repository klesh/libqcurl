QT += testlib core
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

DEFINES += TEST_IMG_PATH=\\\"$$PWD/1027.png\\\" \

TEMPLATE = app

SOURCES +=  \
    tst_http.cpp

include(../../config.pri)

DEPENDPATH += ../../libqcurl
INCLUDEPATH += ../../libqcurl/include

unix {
    LIBS += -L$$QCURL_DESTDIR \
            -lqcurl
}

win32 {
    LIBS += -L$$QCURL_DESTDIR \
            -lqcurl1
}
