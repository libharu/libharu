require 'mkmf'
$CPPFLAGS = $CPPFLAGS + " -I../../include"
$LDFLAGS = $LDFLAGS + " -L../../"
$LIBS = $LIBS + " -lhpdf -lpng -lz"
create_makefile 'hpdf'

