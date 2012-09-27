#!/bin/sh

>ChangeLog
aclocal 
autoconf
libtoolize -f -c
automake -a 
