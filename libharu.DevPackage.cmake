[Setup]
Version=2
AppName=libHaru
AppVerName=libHaru Version ${LIBHARU_VERSION}
AppVersion=${LIBHARU_VERSION}
MenuName=libHaru ${LIBHARU_VERSION}
Description=${LIBHARU_DESCRIPTION}
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
