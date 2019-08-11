QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    tst_ftp.cpp

include(../../config.pri)

DEPENDPATH += ../../libqcurl
INCLUDEPATH += $$QCURL_DESTDIR/include

win32 {
#            -L$$PWD/../../deps/win32/lib  -llibcurl -llibssh2.dll -llibcrypto.dll -llibssl.dll \
    LIBS += -L$$QCURL_DESTDIR -llibqcurl1 \
            -lWs2_32 -lAdvapi32 -lCrypt32 -lWldap32 -lNormaliz -lUser32
    dlls.path = $$PROJECT_ROOT/builds/tests/test_ftp/debug
    dlls.files = $$PROJECT_ROOT/deps/win32/bin/*.dll
    INSTALLS += dlls
}

unix {
    LIBS += -L$$PWD/../../builds/debug/libqcurl \
            -lqcurl -lcurl
}

