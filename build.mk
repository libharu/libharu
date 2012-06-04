
SUPPRESS_WARNINGS = 2>&1 | (egrep -v '(AC_TRY_RUN called without default to allow cross compiling|AC_PROG_CXXCPP was called before AC_PROG_CXX|defined in acinclude.m4 but never used|AC_PROG_LEX invoked multiple times|AC_DECL_YYTEXT is expanded from...|the top level)'||true)

AUTOCONF ?= 'autoconf'
ACLOCAL ?= 'aclocal'
AUTOHEADER ?= 'autoheader'
AUTOMAKE ?= 'automake'
LIBTOOLIZE ?= $(shell uname -s | grep Darwin >/dev/null && echo 'glibtoolize' || echo 'libtoolize')

config_h_in = src/hpdf_config.h.in
targets = $(config_h_in) configure makefiles

all: $(targets)

ltmain:
	$(LIBTOOLIZE) --force --copy >/dev/null 2>&1

aclocal.m4:
	$(ACLOCAL)

$(config_h_in): configure
	@echo rebuilding $@
	@rm -f $@
	$(AUTOHEADER) $(SUPPRESS_WARNINGS)

configure: aclocal.m4 configure.in ltmain
	@echo rebuilding $@
	$(AUTOCONF) $(SUPPRESS_WARNINGS)

makefiles: configure Makefile.am src/Makefile.am
	@echo rebuilding Makefile.in files
	$(AUTOMAKE) --add-missing --copy 2>/dev/null

cvsclean:
	@rm -rf src/*.lo src/*.la src/*.o src/*.a src/.libs src/Makefile src/Makefile.in include/Makefile include/Makefile.in 
	rm -rf src/stamp-h1 src/test include/hpdf_config.h.in include/stamp-h1
	rm -rf aclocal.m4 autom4te.cache install.sh libtool Makefile Makefile.in 'configure.in~' missing config.h* configure
	rm -f config.guess config.log config.status config.sub cscope.out install-sh ltmain.sh

