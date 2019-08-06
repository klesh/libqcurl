TEMPLATE = subdirs

SUBDIRS = \
          libqcurl \
          tests

libqcurl.subdir = libqcurl
tests.subdir = tests

tests.depends = libqcurl
