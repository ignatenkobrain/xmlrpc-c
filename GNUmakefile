include Makefile.srcdir

BLDDIR = $(CURDIR)
SUBDIR =

export SRCDIR
export BLDDIR

include $(BLDDIR)/Makefile.version
include $(BLDDIR)/Makefile.config

SUBDIRS = include lib src tools examples

# The reason we don't build tools and examples by default is that they
# contain executables, which require significantly more from the
# environment to build than libraries.  Ergo, they are signficantly
# more likely to fail to build.  Indeed, when 'tools' was built by
# default, the majority of the reported build problems were with that.
# Since they are ancillary to the package, building them by default is
# not worth causing the whole build to fail.

# As with any subdirectory, to build 'tools' or 'examples', cd to the
# subdirectory and make there.

DEFAULT_SUBDIRS = include lib src

PROGRAMS_TO_INSTALL = xmlrpc-c-config

default: xmlrpc-c-config xmlrpc-c-config.test $(DEFAULT_SUBDIRS:%=%/all)

.PHONY: all
all: xmlrpc-c-config xmlrpc-c-config.test $(SUBDIRS:%=%/all)

# The examples subdirectory is special, because even the make file in there
# is designed to be an example.  So it has to be simple and as close as
# possible to something a person could use outside of the Xmlrpc-c source
# tree.  One ramification of that is that it does not specify dependencies
# on other parts of the Xmlrpc-c build.  That means we must separately
# ensure that the Xmlrpc-c libraries are built before making the example
# programs.
#
# It also means that you have to manually clean the examples directory
# in order to get the examples rebuilt after you modify the Xmlrpc-c
# libraries.

examples/all: xmlrpc-c-config.test lib/all src/all include/all

# Parallel make (make --jobs) is not smart enough to coordinate builds
# between submakes, so a naive parallel make would cause certain
# targets to get built multiple times simultaneously.  That is usually
# unacceptable.  So we introduce extra dependencies here just to make
# sure such targets are already up to date before the submake starts,
# for the benefit of parallel make.  Note that we ensure that parallel
# make works for 'make all' in the top directory, but it may still fail
# for the aforementioned reason for other invocations.

tools/all: include/all lib/all src/all
src/all lib/all: include/all
src/all: lib/all

MAJOR := $(XMLRPC_MAJOR_RELEASE)
MINOR := $(XMLRPC_MINOR_RELEASE)
POINT := $(XMLRPC_POINT_RELEASE)
version.h: $(SRCDIR)/Makefile.version
	rm -f $@
	echo "/* Generated by make file rule */" >>$@
	echo "#define XMLRPC_C_VERSION" \
	  \"Xmlrpc-c $(MAJOR).$(MINOR).$(POINT)"\"" >>$@
	echo "#define XMLRPC_VERSION_MAJOR $(MAJOR)" >>$@
	echo "#define XMLRPC_VERSION_MINOR $(MINOR)" >>$@
	echo "#define XMLRPC_VERSION_POINT $(POINT)" >>$@

# We don't want Makefile.common's rule for version.h
OMIT_VERSION_H = Y

# We don't want Makefile.common's rule for transport_config.h
OMIT_TRANSPORT_CONFIG_H = Y

include transport_config.make

# shell_config is a fragment to place inside a Bourne shell program that
# sets variables that tell how the build is configured.

shell_config: $(BLDDIR)/Makefile.config
	rm -f $@
	@echo "Lots of echoes to '$@' suppressed here ..."
	@echo '#' >>$@
	@echo '#######################################################' >>$@
	@echo "# From '$@'"                                             >>$@
	@echo '#######################################################' >>$@
	@echo 'ENABLE_ABYSS_THREADS="$(ENABLE_ABYSS_THREADS)"'		>>$@
	@echo 'ENABLE_LIBXML2_BACKEND="$(ENABLE_LIBXML2_BACKEND)"'      >>$@
	@echo 'MUST_BUILD_WININET_CLIENT="$(MUST_BUILD_WININET_CLIENT)"'>>$@
	@echo 'MUST_BUILD_CURL_CLIENT="$(MUST_BUILD_CURL_CLIENT)"'	>>$@
	@echo 'MUST_BUILD_LIBWWW_CLIENT="$(MUST_BUILD_LIBWWW_CLIENT)"'	>>$@
	@echo 'NEED_RPATH="$(NEED_RPATH)"'				>>$@
	@echo 'NEED_WL_RPATH="$(NEED_WL)RPATH)"'			>>$@
	@echo 'LSOCKET="$(LSOCKET)"'					>>$@
	@echo 'WININET_LDADD="$(WININET_LDADD)"'			>>$@
	@echo 'WININET_RPATH="$(WININET_RPATH)"'			>>$@
	@echo 'WININET_WL_RPATH="$(WININET_WL_RPATH)"'			>>$@
	@echo 'CURL_LDADD="$(CURL_LDADD)"'				>>$@
	@echo 'CURL_RPATH="$(CURL_RPATH)"'				>>$@
	@echo 'CURL_WL_RPATH="$(CURL_WL_RPATH)"'			>>$@
	@echo 'LIBWWW_LDADD="$(LIBWWW_LDADD)"'				>>$@
	@echo 'LIBWWW_RPATH="$(LIBWWW_RPATH)"'				>>$@
	@echo 'LIBWWW_WL_RPATH="$(LIBWWW_WL_RPATH)"'			>>$@
	@echo 'XMLRPC_MAJOR_RELEASE="$(XMLRPC_MAJOR_RELEASE)"'		>>$@
	@echo 'XMLRPC_MINOR_RELEASE="$(XMLRPC_MINOR_RELEASE)"'		>>$@
	@echo 'XMLRPC_POINT_RELEASE="$(XMLRPC_POINT_RELEASE)"'		>>$@
	@echo 'FEATURE_LIST="$(FEATURE_LIST)"'				>>$@
	@echo 'PREFIX="$(PREFIX)"'					>>$@
	@echo 'HEADERINST_DIR="$(HEADERINST_DIR)"'                      >>$@
	@echo 'LIBINST_DIR="$(LIBINST_DIR)"'                            >>$@
	@echo 'BLDDIR="$(BLDDIR)"'                                      >>$@
	@echo 'ABS_SRCDIR="$(ABS_SRCDIR)"'                              >>$@
	@echo '#######################################################' >>$@

# We don't want Makefile.config's xmlrpc-c-config.test rule:
OMIT_XMLRPC_C_CONFIG_TEST = Y

xmlrpc-c-config xmlrpc-c-config.test:%: %.main shell_config
	rm -f $@
	@echo "Echoes to '$@' suppressed here ..."
	@echo '#! /bin/sh' >>$@
	@echo '#'                                                       >>$@
	@echo '# This file was generated by a make rule'                >>$@
	@echo '#'                                                       >>$@
	cat shell_config >>$@
	cat $< >>$@
	chmod a+rx $@

.PHONY: clean clean-local
clean: $(SUBDIRS:%=%/clean) clean-common clean-local

clean-local:
	rm -f transport_config.h version.h

.PHONY: distclean distclean-local
distclean: $(SUBDIRS:%=%/distclean) distclean-common distclean-local

distclean-local: clean-local
	rm -f config.log config.status Makefile.config Makefile.srcdir
	rm -f xmlrpc_config.h xmlrpc_amconfig.h stamp-h 
	rm -f shell_config xmlrpc-c-config xmlrpc-c-config.test

check: $(SUBDIRS:%=%/check)

.PHONY: tags
tags: $(SUBDIRS:%=%/tags) TAGS

DISTFILES = 

.PHONY: distdir
distdir: distdir-common

.PHONY: install
install: $(DEFAULT_SUBDIRS:%=%/install) install-common install-compat-hdr

.PHONY: install-compat-hdr
install-compat-hdr:
# Install old names of header files for backward compatibility
	cd $(DESTDIR)$(HEADERINST_DIR); \
	  rm -f xmlrpc.h xmlrpc_client.h xmlrpc_server.h xmlrpc_cgi.h \
                xmlrpc_server_abyss.h xmlrpc_server_w32httpsys.h \
	        XmlRpcCpp.h; \
	  $(LN_S) xmlrpc-c/oldxmlrpc.h         xmlrpc.h; \
	  $(LN_S) xmlrpc-c/client.h            xmlrpc_client.h; \
	  $(LN_S) xmlrpc-c/server.h            xmlrpc_server.h; \
	  $(LN_S) xmlrpc-c/server_cgi.h        xmlrpc_cgi.h; \
	  $(LN_S) xmlrpc-c/server_abyss.h      xmlrpc_server_abyss.h; \
	  $(LN_S) xmlrpc-c/server_w32httpsys.h xmlrpc_server_w32httpsys.h; \
	  $(LN_S) xmlrpc-c/oldcppwrapper.hpp   XmlRpcCpp.h ;\

.PHONY: dep
dep: version.h $(BLDDIR)/include/xmlrpc-c/config.h $(SUBDIRS:%=%/dep)

xmlrpc_config.h xmlrpc_amconfig.h \
	:%:%.in $(SRCDIR)/configure
	$(SRCDIR)/configure

include $(SRCDIR)/Makefile.common


# A trick to catch a common user error.  When you don't run 'configure',
# you don't have a Makefile.srcdir, which means $(SRCDIR) is null.

/Makefile.common:
	@echo =======================================
	@echo = You must run Configure before Make. =
	@echo =======================================
	false
