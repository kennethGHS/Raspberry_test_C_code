lib_LTLIBRARIES = librpigpio.la
include_HEADERS = $(top_srcdir)/include/ManualGPIO.h $(top_srcdir)/include/Monitoring.h
AM_CPPFLAGS = -I$(top_srcdir)/include
librpigpio_la_SOURCES = ManualGPIO.c Monitoring.c
librpigpio_la_LIBADD = -lrt -lpthread
