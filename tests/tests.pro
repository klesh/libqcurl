QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    tst_http.cpp

DEPENDPATH += ../libqcurl
INCLUDEPATH += ../libqcurl/include
LIBS += -L/home/klesh/Projects/study/qcurl/builds/debug/libqcurl \
        -lqcurl -lcurl
