# Umicom Bits2Banking
# File: Makefile
# PURPOSE: Build the original status driver with MINIX 3.3.0 service rules.
# AUTHOR AND ORGANISATION: Sammy Hegab / Umicom Foundation
# LICENCE: MIT
PROG=umi_status
# The original source list is retained for review; read_reply now owns the
# portable transfer outcome and the driver remains a thin grant adapter.
# SRCS=status_driver.c read_window.c
SRCS=status_driver.c read_window.c read_reply.c
DPADD+=${LIBCHARDRIVER} ${LIBSYS}
LDADD+=-lchardriver -lsys
.include <minix.service.mk>
