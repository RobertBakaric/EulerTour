#Initialize AC: ACINIT(toolkit_name, version, bug_report_add)
AC_INIT([EulerTour], [1.0])

#Initialize Automake
AC_PREREQ([2.68])
AM_INIT_AUTOMAKE


## AC - autoconf executes this AM automake executes this
AC_PROG_RANLIB

#Check for c
AC_LANG(C)
AC_PROG_CC


#Check for g++
AC_LANG(C++)
AC_PROG_CXX

# Where make files should be produced
AC_CONFIG_FILES([Makefile src/apps/Makefile])
#CXXFLAGS=-O3

AC_CONFIG_MACRO_DIR([m4])

AX_BOOST_BASE([1.46],,[AC_MSG_ERROR([Boost is necessary, but it was not found in your system])])
AX_BOOST_SYSTEM
AX_BOOST_FILESYSTEM
AX_BOOST_PROGRAM_OPTIONS


AC_OUTPUT
