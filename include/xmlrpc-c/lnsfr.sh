#!/bin/sh -efu

if [ "$#" != 2 ]; then
  exit 1
fi

tgt="$1"; shift
src="$1"; shift
ln -sfr "${DESTDIR}${tgt}" "${DESTDIR}${src}"
