#!/bin/sh
for pkg in pkg-config libtool automake aclocal autoreconf:autoconf autopoint:gettext
do
  if ! ${pkg%%:*} --version >/dev/null
  then
    echo "You need to install ${pgk##*:}"
    exit 1
  fi
done

autoreconf --force --install
