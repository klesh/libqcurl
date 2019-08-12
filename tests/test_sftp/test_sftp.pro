QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

DEFINES += ID_RSA_PATH=\\\"$$PWD/../mockserver/id_rsa_nopwd\\\" \
           ID_RSA_PUB_PATH=\\\"$$PWD/../mockserver/id_rsa_nopwd.pub\\\"

TEMPLATE = app

SOURCES +=  \
    tst_sftp.cpp

include(../../config.pri)

DEPENDPATH += ../../libqcurl
INCLUDEPATH += ../../libqcurl/include

unix {
    LIBS += -L$$QCURL_DESTDIR \
            -lqcurl
}
