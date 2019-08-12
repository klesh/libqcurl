QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    tst_ftp.cpp

include(../../config.pri)

DEPENDPATH += ../../libqcurl
INCLUDEPATH += ../../libqcurl/include

unix {
    LIBS += -L$$QCURL_DESTDIR \
            -lqcurl
}

win32 {
    LIBS += -L$$QCURL_DESTDIR \
            -llibqcurl1
}
