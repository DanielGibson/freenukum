#!/bin/sh
for pkg in pkg-config libtool automake aclocal autoreconf:autoconf autopoint:gettext
do
  if ! ${pkg%%:*} --version >/dev/null
  then
    echo "You need to install ${pgk##*:}"
    exit 1
  fi
done

aclocal -I m4 --force
automake --foreign --add-missing
autoreconf --force --install

