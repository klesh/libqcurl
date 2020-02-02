#-------------------------------------------------
#
# Project created by QtCreator 2019-07-22T22:50:56
#
#-------------------------------------------------

#QT       += core
QT       -= gui

TARGET = qcurl
TEMPLATE = lib

DEFINES += QTDLL_LIBRARY

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
    include/qcurlrequest.h \
    include/qcurlresponse.h

SOURCES += \
        src/qcurl.cpp \
        src/qcurlbase.cpp \
        src/qcurlrequest.cpp \
        src/qcurlresponse.cpp

include(../config.pri)

DESTDIR = $$QCURL_DESTDIR

win32 {
    INCLUDEPATH += $$DEPSDIR/include
    LIBS += -L$$DEPSDIR/lib -lws2_32 -lAdvapi32 -lCrypt32 -lWldap32 -lNormaliz -lUser32
    equals(DEP, "selfbuild") {
        PRE_TARGETDEPS += $$DEPSDIR/lib/libcurl.lib
        LIBS += -llibcurl
    } else {
        LIBS += -llibcurl.dll
    }

    bin.path = $$DESTDIR
    bin.files = $$DEPSDIR/bin/*.dll
    INSTALLS += bin

    distinc.path = $$DISTDIR/include
    distinc.files = $$PWD/include/*.h
    INSTALLS += distinc

    distbin.path = $$DISTDIR/bin
    distbin.files = $$DEPSDIR/bin/*.dll
    INSTALLS += distbin

    distlib.path = $$DISTDIR/lib
    distlib.files = $$DESTDIR/*.a
    INSTALLS += distlib

    dlltarget.path = $$DISTDIR/bin
    INSTALLS += dlltarget
}

unix {
    LIBS += -lcurl

    # generate pkg-config file
    CONFIG += create_pc create_prl no_install_prl
    QMAKE_PKGCONFIG_NAME = libqcurl
    QMAKE_PKGCONFIG_FILE = libqcurl
    QMAKE_PKGCONFIG_DESCRIPTION = Make Network Access easier on Qt with curl
#    QMAKE_PKGCONFIG_PREFIX = $$QMAKE_PKGCONFIG_PREFIX
    QMAKE_PKGCONFIG_PREFIX = /usr
    QMAKE_PKGCONFIG_LIBDIR = ${prefix}/lib
    QMAKE_PKGCONFIG_INCDIR = ${prefix}/include
    QMAKE_PKGCONFIG_VERSION = $$VERSION
    QMAKE_PKGCONFIG_REQUIRES = libcurl


    # install
    headers.path = $$QMAKE_PKGCONFIG_PREFIX/include
    headers.files = $$_PRO_FILE_PWD_/include/*.h
    INSTALLS += headers

    libs.path = $$QMAKE_PKGCONFIG_PREFIX/lib
    libs.files = $$DESTDIR/libqcurl.so*
    INSTALLS += libs

    pkgcfg.path = $$QMAKE_PKGCONFIG_PREFIX/lib/pkgconfig
    pkgcfg.files = $$DESTDIR/libqcurl.pc
    INSTALLS += pkgcfg
}
