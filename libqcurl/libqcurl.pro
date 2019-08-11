#-------------------------------------------------
#
# Project created by QtCreator 2019-07-22T22:50:56
#
#-------------------------------------------------

QT       += core

TARGET = qcurl
TEMPLATE = lib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

INCLUDEPATH += include

HEADERS += \
    include/qcurl.h \
    include/qcurlbase.h \
    include/qcurlinternal.h \
    include/qcurlrequest.h \
    include/qcurlresponse.h

SOURCES += \
        src/qcurl.cpp \
        src/qcurlrequest.cpp \
        src/qcurlresponse.cpp

include(../config.pri)

DESTDIR = $$QCURL_DESTDIR
#OUT_PWD = $$DESTDIR
#OUT_PWD = $$PROJECT_ROOT/builds/$$QT_ARCH/libqcurl

win32 {
    PRE_TARGETDEPS += $$DEPSDIR/lib/libcurl.lib
    INCLUDEPATH += $$DEPSDIR/include
    LIBS += -L$$DEPSDIR/lib -llibcurl \
            -lws2_32 -lAdvapi32 -lCrypt32 -lWldap32 -lNormaliz -lUser32

    inc.path = $$DESTDIR/include
    inc.files = $$PWD/include/*.h
    INSTALLS += inc

    bin.path = $$DESTDIR/
    bin.files = $$DEPSDIR/bin/*.dll
    INSTALLS += bin
}

unix {
    LIBS += -lcurl

    headers.path = /usr/include
    headers.files = $$PWD/include/*.h
    INSTALLS += headers

    libs.path = /usr/lib
    libs.files = $$PWD/../builds/release/libqcurl/libqcurl.so*
    INSTALLS += libs

    pkgcfg.path = /usr/lib/pkgconfig
    pkgcfg.files = $$PWD/libqcurl.pc
    INSTALLS += pkgcfg

    CONFIG += create_pc create_prl no_install_prl

    QMAKE_PKGCONFIG_NAME = libqcurl
    QMAKE_PKGCONFIG_DESCRIPTION = Make Network Access easier on Qt with curl
    QMAKE_PKGCONFIG_PREFIX = /usr
    QMAKE_PKGCONFIG_LIBDIR = $$QMAKE_PKGCONFIG_PREFIX/lib
    QMAKE_PKGCONFIG_INCDIR = $$QMAKE_PKGCONFIG_PREFIX/include
    QMAKE_PKGCONFIG_VERSION = $$VERSION
    QMAKE_PKGCONFIG_REQUIRES = libcurl
    QMAKE_PKGCONFIG_DESTDIR = $$QMAKE_PKGCONFIG_PREFIX/lib/pkgconfig
}
