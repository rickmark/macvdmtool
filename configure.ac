AC_PREREQ(2.68)
AC_INIT([libmacvdm], [1.0])
AM_INIT_AUTOMAKE([no-dist])

AC_CONFIG_SRCDIR([src/])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CC
AC_PROG_CXX

LT_INIT

AC_TYPE_INT32_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

AC_CHECK_HEADERS([stdint.h stdlib.h string.h unistd.h])

AC_CHECK_HEADERS([CoreFoundation/CFString.h], [],
	[AC_MSG_ERROR([libmacvdm requires CoreFoundation])]
)

AC_CHECK_HEADERS([IOKit/IOCFPlugIn.h], [],
	[AC_MSG_ERROR([libmacvdm requires IOKit])]
)

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/libmacvdm-1.0.pc
    include/Makefile
    tools/Makefile
])

AC_OUTPUT