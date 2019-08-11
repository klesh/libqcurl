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

INCLUDEPATH += ../../libqcurl/include \
               $$DEPSDIR/include

LIBS += -L$$QCURL_DESTDIR -lqcurl1

win32 {
#            -L$$PWD/../../deps/win32/lib  -llibcurl -llibssh2.dll -llibcrypto.dll -llibssl.dll \
#            -lWs2_32 -lAdvapi32 -lCrypt32 -lWldap32 -lNormaliz -lUser32
    dlls.path = $$PROJECT_ROOT/builds/tests/test_http/$$BUILD
    dlls.files = $$QCURL_DESTDIR/*.dll
    INSTALLS += dlls
}
