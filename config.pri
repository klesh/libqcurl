VERSION = 1.0.0
CONFIG(release, debug|release) {
    BUILD = release
}
CONFIG(debug, debug|release) {
    BUILD = debug
}

msvc:COMPILER=msvc
gcc:COMPILER=gcc

DEP = selfbuild

PROJECT_ROOT = $$PWD
QCURL_DESTDIR = $$PROJECT_ROOT/builds/libqcurl-$$COMPILER-$$QT_ARCH-$$BUILD-$$VERSION
QCURL_OUT_PWD = $$PROJECT_ROOT/builds/libqcurl-$$COMPILER-$$QT_ARCH-$$BUILD-$$VERSION-out
DEPSDIR = $$PROJECT_ROOT/deps/$$DEP/$$QT_ARCH
