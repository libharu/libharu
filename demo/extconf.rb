require 'mkmf'
$CPPFLAGS = $CPPFLAGS + " -I../../include"
$LDFLAGS = $LDFLAGS + " -L../../"
$LIBS = $LIBS + " -lhpdf -lz -lpng"
create_makefile 'hpdf'

