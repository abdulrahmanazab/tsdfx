AM_CPPFLAGS = -I$(top_srcdir)/include
sbin_PROGRAMS = tsdfx
tsdfx_SOURCES =
tsdfx_SOURCES += main.c
tsdfx_SOURCES += tsdfx.c
tsdfx_SOURCES += copy.c
tsdfx_SOURCES += map.c
tsdfx_SOURCES += scan.c
tsdfx_LDADD = $(CRYPTO_LIBS) $(top_builddir)/lib/libtsd/libtsd.la
noinst_HEADERS =
noinst_HEADERS += tsdfx.h
noinst_HEADERS += tsdfx_copy.h
noinst_HEADERS += tsdfx_map.h
noinst_HEADERS += tsdfx_scan.h
dist_man8_MANS = tsdfx.8
