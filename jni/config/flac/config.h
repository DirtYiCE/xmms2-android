/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Target processor is big endian. */
#define CPU_IS_BIG_ENDIAN 0

/* Target processor is little endian. */
#define CPU_IS_LITTLE_ENDIAN 1

/* define to align allocated memory on 32-byte boundaries */
/* #undef FLAC__ALIGN_MALLOC_DATA */

/* define if building for ia32/i386 */
/* #undef FLAC__CPU_IA32 */

/* define if building for PowerPC */
/* #undef FLAC__CPU_PPC */

/* define if building for PowerPC with SPE ABI */
/* #undef FLAC__CPU_PPC_SPE */

/* define if building for SPARC */
/* #undef FLAC__CPU_SPARC */

/* define if you are compiling for PowerPC and have the 'as' assembler */
/* #undef FLAC__HAS_AS */

/* define if you have docbook-to-man or docbook2man */
#define FLAC__HAS_DOCBOOK_TO_MAN 1

/* define if you are compiling for PowerPC and have the 'gas' assembler */
#define FLAC__HAS_GAS 1

/* define if you are compiling for x86 and have the NASM assembler */
/* #undef FLAC__HAS_NASM */

/* define if you have the ogg library */
/* #undef FLAC__HAS_OGG */

/* define to disable use of assembly code */
/* #undef FLAC__NO_ASM */

/* define if your operating system supports SSE instructions */
/* #undef FLAC__SSE_OS */

/* define if building for Darwin / MacOS X */
/* #undef FLAC__SYS_DARWIN */

/* define if building for Linux */
/* #undef FLAC__SYS_LINUX */

/* define to enable use of 3Dnow! instructions */
/* #undef FLAC__USE_3DNOW */

/* define to enable use of Altivec instructions */
/* #undef FLAC__USE_ALTIVEC */

/* Compiler has the __builtin_bswap32 intrinsic */
#define HAVE_BSWAP32 1

/* Define to 1 if you have the <byteswap.h> header file. */
#define HAVE_BYTESWAP_H 1

/* Define to 1 if C++ supports variable-length arrays. */
#define HAVE_CXX_VARARRAYS 1

/* Define to 1 if C supports variable-length arrays. */
#define HAVE_C_VARARRAYS 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if fseeko (and presumably ftello) exists and is declared. */
#define HAVE_FSEEKO 1

/* Define to 1 if you have the `getopt_long' function. */
#define HAVE_GETOPT_LONG 1

/* Define if you have the iconv() function and it works. */
#define HAVE_ICONV 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define if you have <langinfo.h> and nl_langinfo(CODESET). */
#define HAVE_LANGINFO_CODESET 1

/* lround support */
#define HAVE_LROUND 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if the system has the type `socklen_t'. */
#define HAVE_SOCKLEN_T 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if typeof works with your compiler. */
#define HAVE_TYPEOF 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define as const if the declaration of iconv() needs const. */
#define ICONV_CONST 

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
/* #undef NO_MINUS_C_MINUS_O */

/* Name of package */
#define PACKAGE "flac"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME "flac"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "flac 1.2.1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "flac"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.2.1"

/* The size of `void*', as computed by sizeof. */
#define SIZEOF_VOIDP 8

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Version number of package */
#define VERSION "1.2.1"

/* Target processor is big endian. */
#define WORDS_BIGENDIAN 0

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define to 1 to make fseeko visible on some hosts (e.g. glibc 2.2). */
/* #undef _LARGEFILE_SOURCE */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to __typeof__ if your compiler spells it that way. */
/* #undef typeof */
