#!/bin/sh
test -n "$srcdir" || srcdir=`dirname "$0"`
test -n "$srcdir" || srcdir=.

autoreconf --force --install -I build --verbose
test -n "$NOCONFIGURE" || "$srcdir/configure"
