QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    tst_http.cpp

DEPENDPATH += ../../libqcurl
INCLUDEPATH += ../../libqcurl/include \
               ../../deps/win32/include

unix {
    LIBS += -L$$PWD/../../builds/debug/libqcurl \
            -lqcurl -lcurl
}

win32 {
    LIBS += -L$$PWD/../../builds/libqcurl/debug -llibqcurl\
            -L$$PWD/../../deps/win32/lib  -llibcurl -llibssh2.dll -llibcrypto.dll -llibssl.dll \
            -lWs2_32 -lAdvapi32 -lCrypt32 -lWldap32 -lNormaliz -lUser32
    dlls.path = $$PWD/../../builds/tests/test_http/debug
    dlls.files = $$PWD/../../deps/win32/bin/*.dll
    INSTALLS += dlls
}
