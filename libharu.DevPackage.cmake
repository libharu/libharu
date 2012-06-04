[Setup]
Version=2
AppName=libHaru
AppVerName=libHaru Version ${LIBHPDF_VERSION}
AppVersion=${LIBHPDF_VERSION}
MenuName=libHaru ${LIBHPDF_VERSION}
Description=${LIBHPDF_DESCRIPTION}
Url=http://www.libharu.org
Readme=README
Dependencies=zlib libpng
Reboot=0

[Files]
lib=<app>\lib\
include=<app>\include\
bin=<app>\bin\

[Icons]
libharu Website=http://www.libharu.org
