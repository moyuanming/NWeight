

#/bin/bash!

Values=$(date +%y%m%d%H%M)
sed  -i  "s/\#define BUILDDATA \".\{0,30\}\"/\#define BUILDDATA \"$Values\"/" global/include/Version.h
