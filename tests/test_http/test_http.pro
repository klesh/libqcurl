QT += testlib core
QT -= gui

VERSION = 1.0.0

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

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
