TEMPLATE = subdirs

SUBDIRS = \
          libqcurl \
          test_ftp \
          test_http \
          test_sftp

libqcurl.subdir = libqcurl

test_ftp.subdir = tests/test_ftp
test_ftp.depends = libqcurl

test_http.subdir = tests/test_http
test_http.depends = libqcurl

test_sftp.subdir = tests/test_sftp
test_sftp.depends = libqcurl
