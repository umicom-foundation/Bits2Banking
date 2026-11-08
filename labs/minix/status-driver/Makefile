# Umicom Bits2Banking
# File: Makefile
# PURPOSE: Build the original status driver with MINIX 3.3.0 service rules.
# AUTHOR AND ORGANISATION: Sammy Hegab / Umicom Foundation
# LICENCE: MIT
PROG=umi_status
SRCS=status_driver.c read_window.c
DPADD+=${LIBCHARDRIVER} ${LIBSYS}
LDADD+=-lchardriver -lsys
.include <minix.service.mk>
