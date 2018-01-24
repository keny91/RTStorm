/*-----------------------------------------------------------------------------
* File:
*   ds.h
*
* Description:
*  Include file for the Dacolian Standardization (DS-module). The purpose of
*  this module is to hide any platform (hardware and/or operation system) 
*  specific behavior from the rest of the Intrada modules.
*
*  The routines supplied by DS are supposed to have a well defined behavior on
*  all the supported platforms. Many of the functions will default to an empty
*  implementation if the platform is not supported. If is therefore important
*  to check the return values for each routine!
*
*  Currently supported platforms are:
*   DS_OS_WIN32
*   DS_OS_WIN64
*   DS_OS_LINUX
*   DS_OS_LINUX64
*   PLATFORM_C6400p
*
* 
* DsSlXXX
*  These functions provide a portable way to dynamically load object files. To
*  use them you must first determine whether dynamic loading is supported on
*  the platform by calling DsModulesSupported(). If it is, you can open a
*  module with DsModuleOpen(), find the module's symbols with DsModuleSymbol(),
*  and later close the module with DsModuleClose(). DsModuleName() will return
*  the name of a currently opened module.
*
* DsMutexXXX
*  These function provide a portable way to make programs multi threaded.
*
* DsStrXXXX
*  These functions provide additional routines for handling '\0' terminated
*  character strings.
*
* Modification history:
*  2014-12-09: Solved bug in CreateDir [DS_OS_WIN64] (3.0.3)
*  2014-11-25: Bump version number to be in line with external ds (3.0.2)
*  2013-12-09: Included various improvements (3.0.0)
*  2009-02-19: Made thread-safe (2.2.19)
*  2008-10-06: Ported to ppc603 platform (2.2.17)
*  2007-06-18: Ported to linux platform (2.2.16)
*  2007-06-05: Added clock() functions (2.2.15)
*  2007-05-21: Created parachute for DS_OS_WIN32 (2.2.14)
*  2007-05-18: Fixed bug in parachute (2.2.13)
*  2007-05-18: Added parachute (2.2.12)
*  2007-04-27: Fixed NULL pointer bug in 32 bit callstack (2.2.11)
*  2007-04-27: Fixed bug in diskid32 due to 64 bit porting
*  2007-04-27: Removed debug printf 
*  2007-04-27: Fixed problems with 64 bit defines
*  2007-04-27:  Ported to 64 bit platform
*  2007-04-23: change return type of DsDiffTime to long to allow <0
*              DSP prepare (2.2.6)
*  2007-03-27: Updated DS_SL_EXPORT for Windows CE
*              Fixed unresolved Quit (2.2.5)
*  2007-02-23: Added timing functions and ARM platform (2.2.4)
*  2007-01-31: Added Gordian specific precompiler flags (PowerPC)
*  2007-01-26: jpeg,tiff and hasp are not automatically set by DS (2.2.1)
*  2006-11-23: Added <limits.h> under linux (2.1.1)
*  2006-09-20: Added DsGetProcessId() (jn) (2.1.0)
*  2006-06-06: Removed type warnings in callstack routines (2.0.2)
*  2006-04-25: Added Callstack routines. (2.0.1).
*  2006-02-09: Clean separation of platform dependent/independent code
*               in Ds and Du (2.0.0)
*  2005-06-21: Addition of SlGetFilename routine (1.1.1)
*  2005-04-19: Addition of MAC address routines (1.1.0)
*  2003-08-08: Original coding (1.0.0)
*
* Copyright notice:
*   Copyright (c) 1998-2013  Dacolian B.V. All rights reserved
*-----------------------------------------------------------------------------*/

#ifndef  __DS_H__
#define  __DS_H__

/*-----------------------------------------------------------------------------
 * Macros:
 *   DS_SUPPORT_OBSOLETE
 *
 * DESCRIPTION:
 *   This define can be turned on and off to specify whether or not obsolete
 *   routines should be supported by Ds. If this variable is turned of, an
 *   application that uses Ds should be compliant with the new Ds standard
 *   (introduced in version 2.0.0).
 *---------------------------------------------------------------------------*/
#define DS_SUPPORT_OBSOLETE


/*-----------------------------------------------------------------------------
 * DS_LIB_MAJOR, DS_LIB_MINOR, DS_LIB_MAINTENANCE, DS_LIB_DOTTED_VERSION
 *
 * Description:
 *  These defines give the current version of this library. The version numbers 
 *  of the library and include file must match for the major and minor part of
 *  the version number. Any mismatch will result in an error during the 
 *  DuInstall() call.
 *----------------------------------------------------------------------------*/
#define DS_LIB_MAJOR       "3"
#define DS_LIB_MINOR       "0"
#define DS_LIB_MAINTENANCE "7"
#define DS_LIB_DOTTED_VERSION \
  DS_LIB_MAJOR "." DS_LIB_MINOR "." DS_LIB_MAINTENANCE


/*-----------------------------------------------------------------------------
 * Library return codes
 *----------------------------------------------------------------------------*/
#define DS_RETURN_OK                                    0
#define DS_RETURN_NULL_POINTER                          1
#define DS_RETURN_ILLEGAL_SYMBOL_NAME                   2
#define DS_RETURN_OUT_OF_MEMORY                         3
#define DS_RETURN_MODULE_INITIALIZATION_FAILED          4
#define DS_RETURN_ILLEGAL_VERSION                       5
#define DS_RETURN_NOT_INSTALLED                         6
#define DS_RETURN_ILLEGAL_NULL_POINTER                  7
#define DS_RETURN_SL_CANNOT_OPEN_LIBRARY                8
#define DS_RETURN_SL_CANNOT_CLOSE_LIBRARY               9
#define DS_RETURN_SL_CANNOT_FIND_PROC_ADDRESS          10
#define DS_RETURN_ILLEGAL_DRIVE_INDEX                  11
#define DS_RETURN_DISK_INFO_NOT_SUPPORTED              12
#define DS_RETURN_HOST_ID_NOT_SUPPORTED                13
#define DS_RETURN_MAC_ADDRESS_RETRIEVAL_NOT_SUPPORTED  14
#define DS_RETURN_ILLEGAL_MAC_ADDRESS_INDEX            15
#define DS_RETURN_SL_CANNOT_GET_FILENAME               16
#define DS_RETURN_TIMER_NOT_INITIALIZED                17
#define DS_RETURN_UNSUPPORTED_FEATURE                  18
#define DS_RETURN_ILLEGAL_FILENAME                     19
#define DS_RETURN_PROCESS_ID_NOT_SUPPORTED             20
#define DS_RETURN_ILLEGAL_LOCAL_TIME                   21
#define DS_RETURN_SYSTEM_ERROR                         22



/*-----------------------------------------------------------------------------
 * DS_OS_###
 *
 * DESCRIPTION:
 *   Define the platforms supported by Ds. Currently, the following platforms
 *   are supported:
 *     DS_OS_WIN32
 *     DS_OS_LINUX
 *     DS_OS_SUN
 *---------------------------------------------------------------------------*/
#if defined (_WIN32_WCE) /* For the near future */
#define DS_OS_WINCE
#elif defined (_WIN64)
#define DS_OS_WIN64
#elif defined (_WIN32)
#define DS_OS_WIN32
#elif defined (__linux__)
#define DS_OS_LINUX
#elif defined (sun)
#define DS_OS_SUN
#endif

/*-----------------------------------------------------------------------------
 * Platform specific includes.
 *---------------------------------------------------------------------------*/
#if defined (GORDIAN)
#include "types.h"
#include "eictime.h"
#endif

#if defined (DS_OS_WIN32) || defined (DS_OS_WIN64)
#include <string.h>
#include <limits.h>

#elif defined (DS_OS_LINUX) || defined (DS_OS_LINUX64)
#include <limits.h>

#elif defined (DS_OS_SUN)

#elif defined (PLATFORM_C6400p)
#include <limits.h>
#include <math.h>
#endif

/*-----------------------------------------------------------------------------
 * Platform independent includes. We assume these header files exist on every
 * platform untill proved differently. In the latter case we have to move the
 * header file to the platform specific includes section.
 *
 * time.h   : required for clock_t
 *---------------------------------------------------------------------------*/
#include <time.h>
#include <stdio.h>
/*-----------------------------------------------------------------------------
 * Ignore certain irrelevant warnings 
 *
 * In Microsoft VC++, ignore the following warnings:
 *   4100 : unreferenced formal parameter
 *          We often have unused function parameters.
 *   4115 : named type definition in parentheses
 *          A weird warning in rpcasync.h (a VC++ header file)
 *   4127 : conditional expression is constant.
 *          We use a lot of constant conditional expression like while(1)
 *          loops.
 *   4505 : unreferenced local function has been removed
 *          This warning occurs in case of unused static routines.
 *---------------------------------------------------------------------------*/
#if defined (DS_OS_WIN32) || defined (DS_OS_WIN64)
#pragma warning (disable : 4100 4115 4127 4505 )
#endif


/*-----------------------------------------------------------------------------
 * DS_INLINE_FUNCTION
 *
 * DESCRIPTION:
 *   Putting DS_INLINE_FUNCTION in front of a routine will define it as an
 *   in-line routine, which improves execuion speed of the program but
 *   increases the size of the code.
 *---------------------------------------------------------------------------*/

#if defined (DS_OS_WIN32) || defined (DS_OS_WIN64)
#define DS_INLINE_FUNCTION __forceinline
#elif defined (DS_OS_LINUX) || defined (DS_OS_LINUX64)
#define DS_INLINE_FUNCTION __inline
#elif defined (DS_OS_SUN)
#define DS_INLINE_FUNCTION __inline
#else
#define DS_INLINE_FUNCTION
#endif


/*-----------------------------------------------------------------------------
 * Macro:
 *   NULL
 *
 * DESCRIPTION:
 *   Define NULL, if not already defined by the platform. This is a tricky 
 *   one, since we must not make the define before the header file that defines
 *   NULL does (most likely malloc.h does). Therefore include malloc.h in
 *   this header file.
 *---------------------------------------------------------------------------*/
#ifndef NULL
#  ifdef __cplusplus
#    define NULL        (0L)
#  else /* !__cplusplus */
#    define NULL        ((void*) 0)
#  endif /* !__cplusplus */
#endif


/*-----------------------------------------------------------------------------
 * DS_DIR_SEPARATOR, DS_DIR_SEPARATOR_S, DS_SEARCHPATH_SEPARATOR,
 * DS_SEARCHPATH_SEPARATOR_S
 *
 * Description:
 *  Defines that handle the difference between the directory separator and
 *  search path separator on windows and unix platforms.
 *---------------------------------------------------------------------------*/
#if defined (DS_OS_WIN32) || defined(DS_OS_WINCE) || defined (DS_OS_WIN64)
#define DS_DIR_SEPARATOR '\\'
#define DS_DIR_SEPARATOR_S "\\"
#define DS_SEARCHPATH_SEPARATOR ';'
#define DS_SEARCHPATH_SEPARATOR_S ";"
#elif defined (DS_OS_LINUX) || defined (DS_OS_LINUX64) || defined (DS_OS_SUN)
#define DS_DIR_SEPARATOR '/'
#define DS_DIR_SEPARATOR_S "/"
#define DS_SEARCHPATH_SEPARATOR ':'
#define DS_SEARCHPATH_SEPARATOR_S ":"
#endif


/*-----------------------------------------------------------------------------
* DS_N_ELEMENTS(), 
*
* Description:
*  Count the number of elements in an array. The array must be defined as such;
*  using this with a dynamically allocated array will give incorrect results.
*----------------------------------------------------------------------------*/
#define DS_N_ELEMENTS(arr)		(sizeof (arr) / sizeof ((arr)[0]))



/*-----------------------------------------------------------------------------
* DS_STRUCT_OFFSET(), DS_STRUCT_MEMBER_P(), DS_STRUCT_MEMBER()
*
* Description:
*  Provide convenience macros for handling structure fields through their
*  offsets. DS_STRUCT_OFFSET() return the offset, in bytes of a member of a
*  struct. DS_STRUCT_MEMBER_P() returns an untyped pointer to a given offset of
*  a struct. DS_STRUCT_MEMBER() returns a member of a structure at a given
*  offset, using the given type.
*----------------------------------------------------------------------------*/
#define DS_STRUCT_OFFSET(struct_type, member)	\
    ((long)((unsigned char *) &((struct_type*) 0)->member))
#define DS_STRUCT_MEMBER_P(struct_p, struct_offset)   \
    ((void *)((unsigned char *) (struct_p) + (long) (struct_offset)))
#define DS_STRUCT_MEMBER(member_type, struct_p, struct_offset)   \
    (*(member_type*)DS_STRUCT_MEMBER_P ((struct_p), (struct_offset)))


/*-----------------------------------------------------------------------------
*  DS_STMT_START, DS_STMT_END
*
* Description:
*  Provide simple macro statement wrappers (adapted from Perl): DS_STMT_START
*  { statements; } DS_STMT_END; can be used as a single statement, as in if (x)
*  DS_STMT_START { ... } DS_STMT_END; else ...
*  For gcc we will wrap the statements within `({' and `})' braces. For SunOS
*  they will be wrapped within `if (1)' and `else (void) 0', and otherwise
*  within `do' and `while (0)'.
*----------------------------------------------------------------------------*/
#if defined (__GNUC__) && !defined (__STRICT_ANSI__) && !defined (__cplusplus)
#define DS_STMT_START	(void)(
#define DS_STMT_END		)

#elif defined (DS_OS_SUN)
#define DS_STMT_START	if (1)
#define DS_STMT_END	else (void)0

#else
#define DS_STMT_START	do
#define DS_STMT_END	while (0)
#endif

/*-----------------------------------------------------------------------------
 * DS_FILE_###
 *
 * DESCRIPTION:
 *   Defines for the DsFileTest() routine.
 *---------------------------------------------------------------------------*/
#define DS_FILE_IS_REGULAR    (1<<0)
#define DS_FILE_IS_SYMLINK    (1<<1)
#define DS_FILE_IS_DIR        (1<<2)
#define DS_FILE_IS_EXECUTABLE (1<<3)
#define DS_FILE_EXISTS        (1<<4)


/*-----------------------------------------------------------------------------
 * DS_SL_PREFIX:
 *   Expands to the proper shared library prefix for the current platform.
 *
 * DS_SL_SUFFIX:
 *   Expands to the proper shared library suffix for the current platform
 *   without the leading dot. For most Unix and Linux systems this 
 *   is "so", for some HP-UX this is "sl" and for Windows this is "dll".
 *---------------------------------------------------------------------------*/
#if defined(DS_OS_WIN32) || defined (DS_OS_WINCE) || defined (DS_OS_WIN64)
#define DS_SL_PREFIX      ""
#define DS_SL_SUFFIX      "dll"

#elif defined(DS_OS_LINUX) || defined(DS_OS_LINUX64) || defined(DS_OS_SUN)
#define DS_SL_PREFIX      "lib"
#define DS_SL_SUFFIX      "so"

#else
#define DS_SL_PREFIX      "DS_SL_PREFIX"
#define DS_SL_SUFFIX      "DS_SL_SUFFIX"
#endif

 
/*-----------------------------------------------------------------------------
 * DS_SL_BIND_LAZY:
 * DS_SL_BIND_NOW
 *  Flag passed to DsModuleOpen() specifying whether the symbols must be
 *  resolved at load time (DS_SL_BIN_NOW) or only when they are needed 
 *  (DS_SL_BIND_LAZY). DS_SL_BIND_LAYZ is not supported on all
 *  platforms. Deferred resolution sounds more attractive but it is risky.
 *  Failure usually results in an unrecoverable error. In contrast, failure to
 *  resolve at load time produces a NULL return value and (hopefully) a
 *  meaningful error message. 
 *---------------------------------------------------------------------------*/
#define DS_SL_BIND_LAZY   1
#define DS_SL_BIND_NOW    2



/*-----------------------------------------------------------------------------
 * DS_SL_EXPORT
 *   Used to declare functions exported by modules.
 *---------------------------------------------------------------------------*/
#if defined(DS_OS_WIN32) || defined (DS_OS_WINCE) || defined (DS_OS_WIN64)
#define DS_SL_EXPORT      __declspec(dllexport)

#elif defined(DS_OS_LINUX) || defined(DS_OS_LINUX64) || defined(DS_OS_SUN)
#define DS_SL_EXPORT      

#else
#define DS_SL_EXPORT
#endif



/*-----------------------------------------------------------------------------
 * DS_MUTEX_INIT
 *   Initialization value for MUTEX variable. 
 *---------------------------------------------------------------------------*/
#define DS_MUTEX_INIT 0


/*-----------------------------------------------------------------------------
 * Macros:
 *   DS_MIN_### / DS_MAX_###
 *
 * DESCRIPTION:
 *   Define limits for default types:
 *    float
 *    double
 *    short
 *    unsigned short
 *    int 
 *    unsigned int
 *    long
 *    unsigned long
 *---------------------------------------------------------------------------*/
#define DS_MIN_FLOAT    FLT_MIN
#define DS_MAX_FLOAT    FLT_MAX
#define DS_MIN_DOUBLE   DBL_MIN
#define DS_MAX_DOUBLE   DBL_MAX
#define DS_MIN_SHORT    SHRT_MIN
#define DS_MAX_SHORT    SHRT_MAX
#define DS_MAX_USHORT   USHRT_MAX
#define DS_MIN_INT      INT_MIN
#define DS_MAX_INT      INT_MAX
#define DS_MAX_UINT     UINT_MAX
#define DS_MIN_LONG     LONG_MIN
#define DS_MAX_LONG     LONG_MAX
#define DS_MAX_ULONG    ULONG_MAX

/*-----------------------------------------------------------------------------
 * Macros:
 *   DS_MIN_### / DS_MAX_###
 *
 * DESCRIPTION:
 *   Define limits for fixed-number-of-bits types:
 *   INT8
 *   UINT8
 *   INT16
 *   UINT16
 *   INT32
 *   UINT32
 *---------------------------------------------------------------------------*/

#define DS_MIN_INT8    ((DS_INT8)  0x80)
#define DS_MAX_INT8    ((DS_INT8)  0x7f)
#define DS_MAX_UINT8   ((DS_UINT8) 0xff)

#define DS_MIN_INT16   ((DS_INT16)  0x8000)
#define DS_MAX_INT16   ((DS_INT16)  0x7fff)
#define DS_MAX_UINT16	 ((DS_UINT16) 0xffff)

#define DS_MIN_INT32   ((DS_INT32)  0x80000000)
#define DS_MAX_INT32   ((DS_INT32)  0x7fffffff)
#define DS_MAX_UINT32  ((DS_UINT32) 0xffffffff)


/*-----------------------------------------------------------------------------
 *
 * Define some mathematical constants that aren't available symbolically in 
 * some strict ISO C implementations.
 *
 *----------------------------------------------------------------------------*/

#define DS_E       2.7182818284590452353602874713526624977572470937000
#define DS_LN2     0.69314718055994530941723212145817656807550013436026
#define DS_LN10    2.3025850929940456840179914546843642076011014886288
#define DS_PI      3.1415926535897932384626433832795028841971693993751
#define DS_PI_2    1.5707963267948966192313216916397514420985846996876
#define DS_PI_4    0.78539816339744830961566084581987572104929234984378
#define DS_SQRT2   1.4142135623730950488016887242096980785696718753769

#define DS_EPSILON 0.0000000000000000000000000000000001


/*------------------------------------------------------------------------------
 * DS_DRIVE_TYPE_###
 *
 * Description:
 *   Defines different types of drives.
 *----------------------------------------------------------------------------*/
#define DS_DRIVE_TYPE_FIXED			  0
#define DS_DRIVE_TYPE_REMOVABLE		1
#define DS_DRIVE_TYPE_UNKNOWN			2

/*------------------------------------------------------------------------------
 * DS_DRIVE_CONTROL_###
 *
 * Description:
 *   Defines to indicate wheter a drive is master or slave.
 *----------------------------------------------------------------------------*/
#define DS_DRIVE_CONTROL_MASTER		0
#define DS_DRIVE_CONTROL_SLAVE	  1


/*------------------------------------------------------------------------------
 * DS_MAX_HOST_ID_SIZE
 *
 * Description:
 *   Define the maximum size of a host ID string. Such strings are used by the
 *   routine DsGetHostId().
 *----------------------------------------------------------------------------*/
#define DS_MAX_HOST_ID_SIZE 256

/*------------------------------------------------------------------------------
 * DS_MIN / DS_MAX
 *
 * Description:
 *   Defines of the min and max macros. Such macros are not defined on all
 *   platforms. Therefore we have defined our own.
 *----------------------------------------------------------------------------*/
#define DS_MIN(x,y) (((x)<(y))? (x) : (y))
#define DS_MAX(x,y) (((x)>(y))? (x) : (y))
#define DS_MIN3(x,y,z) DS_MIN((x),DS_MIN((y),(z)))
#define DS_MAX3(x,y,z) DS_MAX((x),DS_MAX((y),(z)))

/*------------------------------------------------------------------------------
 * DS_ABS
 *
 * Description:
 *   Absoloute value.
 *----------------------------------------------------------------------------*/
#define DS_ABS(f) (((f)>=0) ? (f) : -(f))



#ifdef __cplusplus
extern "C" {
#endif


/*-----------------------------------------------------------------------------
 * Types:
 *   DS_INT8, DS_UINT8, DS_INT16, DS_UINT16, DS_INT32, DS_UINT32.
 *
 * DESCRIPTION:
 *   These types have to be defined for the different platforms to be exactly
 *   the number of bits (8/16/32) for signed and unsigned integer types.
 *---------------------------------------------------------------------------*/

/* TODO: Check this on all platforms we support. */
typedef signed char     DS_INT8;
typedef unsigned char   DS_UINT8;
typedef signed short    DS_INT16;
typedef unsigned short  DS_UINT16;
typedef signed int      DS_INT32;
typedef unsigned int    DS_UINT32;



typedef struct _DsLocalTimeStruct
{
	int tm_sec;                   /* Seconds after the minute.        [0-59] */
	int tm_min;                   /* Minutes after the hour.          [0-59] */
	int tm_hour;                  /* Hours since midnight.            [0-23] */
	int tm_mday;                  /* Day of the month.                [1-31] */
	int tm_mon;                   /* Months since January.            [0-11] */
	int tm_year;                  /* Years since 1900.                       */

	int tm_wday;                  /* Days since Sunday.                [0-6] */
	int tm_yday;                  /* Days since January 1.           [0-365] */

	int tm_isdst;                 /* Daylight Saving Time flag               */

	/* The Daylight Saving Time flag is greater than zero if Daylight Saving */
	/* Time is in effect, zero if Daylight Saving Time is not in effect, and */
	/* less than zero if the information is not available.                   */
} DsLocalTimeStruct;

typedef unsigned long ds_clock_t;


/*-----------------------------------------------------------------------------
 * DsClock()
 *
 * Description:
 *  Platform dependent system clock 
 * 
 * Returns:
 *   The current value of some system clock, or 0 if not implemented
 *----------------------------------------------------------------------------*/
ds_clock_t DsClock();

/*-----------------------------------------------------------------------------
 * DsTimerStruct
 *
 * Description:
 *   Structure containing timer information. The structure is initialized (or
 *   reset) by the routine DsResetTimer(). The elapsed time (in milliseconds) 
 *   after the last reset is returned by the routine DsGetElapsedTime().
 *
 * Fields:
 *        self : A self pointer that is used to check if the DsTimerStruct
 *               variable is initialized (by DsResetTimer()).
 *  reset_time : This field holds the time at which this variable was most
 *               recently  reset.
 *---------------------------------------------------------------------------*/
typedef struct _DsTimerStruct
{
	struct _DsTimerStruct *self;
	ds_clock_t             reset_time;
} DsTimerStruct, *DsTimer;


/*-----------------------------------------------------------------------------
 * DsResetTimer()
 *
 * Description:
 *   Resets the DsTimerStruct variable, or equivalently: defines a starting 
 *   point in time. Together with the routine DsGetElapsedTime(), the amount
 *   of elapsed time between two points in the code can be measured (see
 *   DsGetElapsedTime()).
 *
 * Arguments:
 *       timer : The DsTimer variable to reset.
 *
 * Returns:
 *   DS_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DS_RETURN_UNSUPPORTED_FEATURE.
 *----------------------------------------------------------------------------*/
int DsResetTimer(DsTimer timer);


/*-----------------------------------------------------------------------------
 * DsGetElapsedTime()
 *
 * Description:
 *   Determines the amount of elapsed time in milliseconds after the last time
 *   the DsTimerStruct variable was reset.
 *
 * Remarks:
 *   Note that this routine can only be used to measure 'relatively small'
 *   times due to the resolution of the clock variable and the limited amount
 *   of bits (clock_t is a long, thus 32 bits under WIN32/LINUX).
 *   Under WIN32, the 
 *
 * Arguments:
 *       timer : The DsTimer variable.
 *        msec : The number of milliseconds that have elapsed.
 *
 * Returns:
 *   DS_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DS_RETURN_UNSUPPORTED_FEATURE.
 *----------------------------------------------------------------------------*/
int DsGetElapsedTime(DsTimer timer, unsigned *msec);

/*-----------------------------------------------------------------------------
 * DsMutex
 *
 * Description:
 *   Variable type for mutual exclusion.
 *
 * Note:
 *   This is defined as a void pointer, equal to Windows' HANDLE type.
 *---------------------------------------------------------------------------*/
    typedef void* DsMutex;

/*-----------------------------------------------------------------------------
 * DsProc
 *
 * Description:
 *   DsProc is a pointer to a function. It's the base-type for a function-pointer
 *   and can be cast to any other type.
 *----------------------------------------------------------------------------*/
    typedef int (*DsSlProc)(void);



    typedef struct _DsDriveInfo
    {
	int			type;
	int			control;
	char		model_nr[256];
	char		serial_nr[256];
	char		revision_nr[256];
    } DsDriveInfo;

/*-----------------------------------------------------------------------------
 * DsGetVersion()
 *
 * Description:
 *   Delivers version information and compile date information of this library.
 *
 * Arguments:
 *         major : returns the major release number if not NULL.
 *         minor : returns the minor release number if not NULL.
 *   maintenance : returns the maintenance release number if not NULL.
 *   description : returns an informal description about the font library if
 *                 not NULL.
 *
 * Return value:
 *   pointer to a '\0' terminated character string that contains both the
 *   version number and compilation date and time.
 *---------------------------------------------------------------------------*/
    extern const char *DsGetVersion(const char **major,
                                    const char **minor,
                                    const char **maintenance,
                                    const char **description);

/*-----------------------------------------------------------------------------
* DsInitialize()
*
* Description:
*  Initialize this library. This routine must be called before any of the other
*  routines in this library are used. 
*
* Return value:
*  DS_RETURN_OK on successful completion or one of the following error 
*  codes: DS_RETURN_ILLEGAL_VERSION
*-----------------------------------------------------------------------------*/
#define DsInitialize() DsInitializeVersion(DS_LIB_MAJOR,DS_LIB_MINOR,NULL)
extern int DsInitializeVersion(const char *major, const char *minor,
                                const char *initialization_options);

/*-----------------------------------------------------------------------------
 * DsFinalize()
 *
 * Description:
 *  This routine will free all allocated resources for this library. Calling 
 *  this routine before DsInitialize() will have no effect.
 *
 * Return value:
 *  This routine will always return DS_RETURN_OK.
 *----------------------------------------------------------------------------*/
    extern int DsFinalize(void);


/*-----------------------------------------------------------------------------
 * DsGetErrorText()
 *
 * Description:
 *   Returns the string that corresponds to the specified error code. If the
 *   specified return code is invalid, the string "<INVALID RETURN CODE>" is
 *   returned. Note that only a reference to a string is returned, which
 *   means that the caller does not have to and is not allowed to deallocacte
 *   the string.
 *
 * Arguments:
 *    error : The error code.
 *     text : A reference to the error code string.
 *
 * Returns:
 *   DS_RETURN_OK.
 *---------------------------------------------------------------------------*/
    extern int DsGetErrorText (int error, const char **text);

/*-----------------------------------------------------------------------------
 * DsInstallParachute()
 *
 * Description:
 *
 * Arguments:
 *
 * Returns:
 *---------------------------------------------------------------------------*/
    extern void DsInstallParachute();

/*-----------------------------------------------------------------------------
 * DsUninstallParachute()
 *
 * Description:
 *
 * Arguments:
 *
 * Returns:
 *---------------------------------------------------------------------------*/
    extern void DsUninstallParachute();

/*-----------------------------------------------------------------------------
 * DsSlSupported
 *
 * Description:
 *   This function can be used to determine whether the platform the DS-module
 *   has been compiled for supports shared libraries. Default this is false, so
 *   when this function returns false it could be due to missing implementation.
 *
 * Input:
 *   -
 *
 * Return value:
 *   TRUE when the current platform supports shared libraries, FALSE otherwise.
 *----------------------------------------------------------------------------*/
    extern int DsSlSupported(void);


/*-----------------------------------------------------------------------------
 * DsSlSupported
 *
 * Description:
 *   With this function a shared library with the given filename can be loaded
 *   and a handle to the library is passed back. With the handle actions on the
 *   library can be made.
 *
 * Input:
 *   filename: The filename of the library
 *   flags:    Load flags for the library. Please note that these flags are not
 *             supported on all platforms
 *
 * Output:
 *   handle:   The handle to the library
 *
 * Return value:
 *   DS_RETURN_OK on success, DS_RETURN_SL_CANNOT_OPEN_LIBRARY when the library
 *   could not be opened.
 *----------------------------------------------------------------------------*/
    extern int DsSlLoadLibrary(const char* filename, int flags, void **handle);


/*-----------------------------------------------------------------------------
 * DsSlCloseLibrary
 *
 * Description:
 *   With this call the link (handle) to the shared library, opened with a call
 *   to DsSlLoadLibrary, can be closed. After this call the handle cannot be
 *   used anymore.
 *   For now the is_unref parameter isn't used.
 *
 * Input:
 *   handle:   Handle to be closed.
 *   is_unref: ?
 *
 * Return:
 *   DS_RETURN_OK on success, DS_RETURN_SL_CANNOT_CLOSE_LIBRARY when the library
 *   could not be closed.
 *----------------------------------------------------------------------------*/
    extern int DsSlCloseLibrary(void *handle, int is_unref);


/*-----------------------------------------------------------------------------
 * DsSlGetProcAddress
 *
 * Description:
 *   Retrieves the pointer to the function with the given name. For the win32
 *   version hooks have been placed which also look in some standard libraries.
 *
 * Input:
 *   handle:    Handle to the library containing the function.
 *   proc_name: Name of the function.
 *
 * Output:
 *   proc:      Pointer to the function
 *
 * Return:
 *   DS_RETURN_OK on success, DS_RETURN_OUT_OF_MEMORY, or
 *   DS_RETURN_SL_CANNOT_FIND_PROC_ADDRESS when the function could not be found.
 *
 * Note:
 *   Apparently this function can also be used to retrieve pointers to exported
 *   variables. This is still a rather undocumented feature and use of this
 *   behavior results in the penalty of a warning at the highest
 *   warning-level!
 *----------------------------------------------------------------------------*/
    extern int DsSlGetProcAddress(void *handle, const char *proc_name,
                                  DsSlProc *proc);


/*-----------------------------------------------------------------------------
 * DsSlGetFileName
 *
 * Description:
 *   Retrieves the filename of the 'handle'. This filename includes the 
 *   absolute path. The caller has to allocate the buffer 'filename'. If
 *   this buffer is not large enough to store the filename, the filename
 *   will be truncated.
 *
 * Input:
 *   handle:    Handle to the library.
 *   filename:  Buffer to store the filename in.
 *   bufsize:   Size of the buffer.
 *
 * Return:
 *   DS_RETURN_OK on success, DS_RETURN_SL_CANNOT_GET_FILENAME when the
 *   filename could not be retrieved, DS_RETURN_NULL_POINTER when the
 *   filename parameter is a null pointer.
 *----------------------------------------------------------------------------*/
    extern int DsSlGetFileName (void *handle, char *filename, 
                                unsigned long bufsize);


/*-----------------------------------------------------------------------------
 * DsSlSelf
 * 
 * Description:
 *   Retrieves a shared library handle to the library this is running.
 *
 * Input:
 *   -
 *
 * Return:
 *   A handle to the shared library.
 *----------------------------------------------------------------------------*/
    extern void *DsSlSelf(void);


/*------------------------------------------------------------------------------
 * DsMutexCreate, DsMutexDestroy, DsMutexLock, DsMutexUnlock
 *
 * Description:
 *   Create/destroy/lock/unlock a mutex.
 *----------------------------------------------------------------------------*/
    extern void DsMutexCreate(DsMutex* mutex);
    extern void DsMutexDestroy(DsMutex* mutex);
    extern void DsMutexLock(DsMutex* mutex);
    extern void DsMutexUnlock(DsMutex* mutex); 


/*------------------------------------------------------------------------------
 * getHardDriveName
 *
 * Description:
 *   Retrieves the name of the main harddrive, which is used in the licensing
 *   scheme.
 *----------------------------------------------------------------------------*/
    extern void getHardDriveName(char *buf, long buf_size);


/*------------------------------------------------------------------------------
 * DsFileTest
 *
 * Description:
 *   Test a file for a combination of the following properties:
 *     DS_FILE_IS_REGULAR
 *     DS_FILE_IS_SYMLINK
 *     DS_FILE_IS_DIR
 *     DS_FILE_IS_EXECUTABLE
 *     DS_FILE_EXISTS
 *   TODO: The implementation does not seem correct!!!
 *
 * Return value:
 *   1 if all of the specified file properties are satisfied and 0 if not.
 *----------------------------------------------------------------------------*/
    extern int DsFileTest (const char *file_name, int test);


/*------------------------------------------------------------------------------
 * DsGetDriveInfoSupported
 *
 * Description:
 *   Checks if drive info retrieval is supported on this platform. 
 *
 * Return value:
 *   1 if drive info retrieval is supported and 0 if not.
 *----------------------------------------------------------------------------*/
    extern int DsGetDriveInfoSupported ();

/*------------------------------------------------------------------------------
 * DsGetNumberOfDrives
 *
 * Description:
 *   Retrieves the nr of drives in the system.
 *
 * Arguments:
 *      nr_drives : returns the number of drives.
 *
 * Return value:
 *   DS_RETURN_OK in case of successful operation, or one of the following 
 *   error messages: DS_RETURN_DISK_INFO_NOT_SUPPORTED.
 *----------------------------------------------------------------------------*/
    extern int DsGetNumberOfDrives (int *nr_drives);

/*------------------------------------------------------------------------------
 * DsGetDriveInfo
 *
 * Description:
 *   Retrieves the info of the drive with index 'drive_index'. The index
 *   should be in the range 0..N-1, where N is the number of drives returned
 *   by the routine DsGetNumberOfDrives().
 *
 * Arguments:
 *      drive_index : returns the number of drives.
 *
 * Return value:
 *   DS_RETURN_OK in case of successful operation, or one of the following 
 *   error messages: DS_RETURN_DISK_INFO_NOT_SUPPORTED, 
 *   DS_RETURN_ILLEGAL_DRIVE_INDEX
 *----------------------------------------------------------------------------*/
    extern int DsGetDriveInfo (int drive_index, DsDriveInfo *drive_info);


/*------------------------------------------------------------------------------
 * DsGetHostIdSupported
 *
 * Description:
 *   Checks if host ID retrieval is supported on this platform. 
 *
 * Return value:
 *   1 if host ID retrieval is supported and 0 if not.
 *----------------------------------------------------------------------------*/
    extern int DsGetHostIdSupported ();

/*------------------------------------------------------------------------------
 * DsGetHostId
 *
 * Description:
 *   Retrieves the host ID. This is a string containing some system specific
 *   information.
 *
 * Return value:
 *   DS_RETURN_OK in case of succesful operation, or one of the following 
 *   error messages: DS_RETURN_HOST_ID_NOT_SUPPORTED.
 *----------------------------------------------------------------------------*/
    extern int DsGetHostId (char host_id[DS_MAX_HOST_ID_SIZE]);

/*------------------------------------------------------------------------------
 * DsGetMacAddress
 *
 * Description:
 *   Retrieves the mac address with index 'mac_index'. The index should be in
 *   the range 0..N-1, where N is the number of mac addresses returned by the
 *   routine DsGetNumberOfMacAddresses().
 *
 * Arguments:
 *      mac_index : the index of the mac adress to be returned.
 *
 * Return value:
 *   DS_RETURN_OK on success, or in case of any problem one of the errors
 *   DS_RETURN_SL_CANNOT_OPEN_LIBRARY, DS_RETURN_SL_CANNOT_FIND_PROC_ADDRESS,
 *   DS_RETURN_OUT_OF_MEMORY, DS_RETURN_MAC_ADDRESS_RETRIEVAL_NOT_SUPPORTED, 
 *   DS_RETURN_ILLEGAL_MAC_ADDRESS_INDEX.
 *----------------------------------------------------------------------------*/
    extern int DsGetMacAddress (int mac_index, unsigned char mac_address[6]);

/*------------------------------------------------------------------------------
 * DsGetMacInfoSupported()
 *
 * Description:
 *   Checks if mac address retrieval is supported on this platform. 
 *
 * Return value:
 *   1 if mac address retrieval is supported and 0 if not.
 *----------------------------------------------------------------------------*/
    extern int DsGetMacInfoSupported ();

/*------------------------------------------------------------------------------
 * DsGetNumberOfMacAddresses()
 *
 * Description:
 *   Retrieves the number of mac addresses that can be retrieved.
 *
 * Arguments:
 *      nr_adresses : returns the number of mac addresses.
 *
 * Return value:
 *   DS_RETURN_OK on success, or in case of any problem one of the errors
 *   DS_RETURN_SL_CANNOT_OPEN_LIBRARY, DS_RETURN_SL_CANNOT_FIND_PROC_ADDRESS,
 *   DS_RETURN_OUT_OF_MEMORY, DS_RETURN_MAC_ADDRESS_RETRIEVAL_NOT_SUPPORTED.
 *----------------------------------------------------------------------------*/
    extern int DsGetNumberOfMacAddresses (int *nr_adresses);


/*-----------------------------------------------------------------------------
 * DsGetProcessId()
 *
 * Description:
 *  Retrieves the process ID obtained from the system.
 *
 * Argumnets:
 *  proc_id: returns the process ID
 *
 * Return value:
 *  DS_RETURN_OK on success, or one of the following error codes:
 *  DS_RETURN_PROCESS_ID_NOT_SUPPORTED
 *----------------------------------------------------------------------------*/
    extern int DsGetProcessId(int *proc_id);

/*-----------------------------------------------------------------------------
 * DsPathSkipDrive()
 *
 * Description:
 *   Potentially skips a drive prefix from file_name. On UNIX systems the
 *   concept of drive letters does not exist. Therefore, there is nothing to
 *   skip, and tail will point to file_name upon return. Under WIN32, it is
 *   checked if file_name is preceded by a drive letter and ':'. If so, tail
 *   will point to the path behind the ':'. For example, for the file_name
 *   C:\book.txt, tail will point to the substring "\book.txt".
 *
 * Arguments:
 *    file_name : The filename to be checked.
 *         tail : Returns a reference in file_name after the drive prefix.
 *                 The value will be identical to file_name if file_name 
 *                contains no Drive letter prefix.
 *
 * Returns:
 *   DS_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DS_RETURN_ILLEGAL_FILENAME. 
 *---------------------------------------------------------------------------*/
    extern int DsPathSkipDrive (const char *file_name, const char **tail);

/*-----------------------------------------------------------------------------
 * DsPathSkipUnc()
 *
 * Description:
 *   Potentially skips a UNC prefix from file_name. On UNIX systems the
 *   concept of UNC prefixes does not exist. Therefore, there is nothing to
 *   skip, and tail will point to file_name upon return. Under WIN32, it is
 *   checked if file_name is preceded by a UNC prefix. If so, tail
 *   will point to the path behind the prefix. For example, for the file_name
 *   "\\server\share\file.txt", tail will point to the substring \
 *   "share\file.txt". Note that the UNC prefix together with the trailing
 *   separators are skipped.
 *
 * Arguments:
 *    file_name : The filename to be checked.
 *         tail : Returns a reference in file_name, after the UNC prefix.
 *                The value will be identical to file_name if file_name 
 *                contains no UNC prefix.
 *
 * Returns:
 *   DS_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DS_RETURN_ILLEGAL_FILENAME. 
 *---------------------------------------------------------------------------*/
extern int DsPathSkipUnc (const char *file_name, const char **tail);



extern void DsGetCallstack (unsigned long *CallStack, int count);
extern void DsCallstackPrintInit ();
extern void DsCallstackPrintDone ();
extern void DsCallstackPrint (FILE *f, unsigned long *callstack,int count);


/*-----------------------------------------------------------------------------
* DsGetCurrentPosixTime 
*
* Description:
*   Returns the POXIX time (or Unix time).  This time system is used for 
*   describing points in time, defined as the number of seconds elapsed since 
*   midnight Coordinated Universal Time (UTC) of January 1, 1970 (not counting 
*   leap seconds). DsGetCurrentPosixTime is similar to time() routine. The 
*   time() return value is a signed integer data type, traditionally of 32 bits  
*   directly encoding the Unix time number. We have explicitly defined it to be 
*   DS_INT32. This means that it covers a range of about 136 years in 
*   total. Note that negative values represent points in time before 
*   January 1, 1970 UTC. The minimum representable time is 1901-12-13, 
*   and the maximum representable time is 2038-01-19.
*---------------------------------------------------------------------------*/
extern void DsGetCurrentPosixTime (DS_INT32 *posix_time);


extern int DsPosixToLocalTime (DS_INT32 posix_time, DsLocalTimeStruct *local_time);
extern int DsLocalToPosixTime (DsLocalTimeStruct local_time, DS_INT32 *posix_time);

//extern void DsMkTime(struct ds_tm *timeptr);

//void DsLocalTime(const ds_time_t *timep, struct ds_tm *time_out);

//extern DS_UINT32 DsDiffTime (ds_time_t time1, ds_time_t time0);



extern ds_clock_t DsClock();


/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * File and filename routines
 * TODO: These routines should be transformed into clean Ds### routines !!!!
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/

#define MAX_FILENAME_SIZE 500
#define NO_MAX_DEPTH -1


    extern void DIR_WALK_NO_FUNCTION (char *str, int depth);

    extern void DirWalk (char *dir, int max_depth, 
      void (*dir_fun)(char *, int),
      void (*file_fun)(char *, int));

    extern int CheckFileNameAndExtension (const char *filename, 
                                          const char *extension);

    extern void ExtractFileName (const char *full_filename, 
                                 char *filename);

    extern void ExtractPath (const char *full_filename, 
                             char *pathname);

    extern void ExtractExtention (const char *full_filename, char *extention);

    extern void ExtractFileBase(const char *full_filename, char *base);

    extern void ChangeFileExtention (char *filename, 
                                     const char *extention);

    extern void ChangeFilePath (char *filename, 
                                const char *path);

    extern void ChangeFileBase (char *filename, const char *new_base);

    extern void AddPostfix (char *filename, 
                            const char *postfix);

    extern void AddPrefix (char *filename, 
                           const char *prefix);

    extern void CleanPath (char *path);

    extern int CreateDir (const char *dir_name);

    extern int FileExists (char *filename);





#if defined(DS_OS_WIN32) || defined(DS_OS_WCE) ||  defined (DS_OS_WIN64)

#define DS_DIR_SEPARATOR '\\'
#define DS_DIR_SEPARATOR_S "\\"
#define DS_IS_DIR_SEPARATOR(c) ((c) == DS_DIR_SEPARATOR || (c) == '/')
#define DS_SEARCHPATH_SEPARATOR ';'
#define DS_SEARCHPATH_SEPARATOR_S ";"

#elif defined(DS_OS_LINUX) || defined(DS_OS_LINUX64) || defined(DS_OS_SUN)

#define DS_DIR_SEPARATOR '/'
#define DS_DIR_SEPARATOR_S "/"
#define DS_IS_DIR_SEPARATOR(c) ((c) == DS_DIR_SEPARATOR)
#define DS_SEARCHPATH_SEPARATOR ':'
#define DS_SEARCHPATH_SEPARATOR_S ":"

#elif defined(PLATFORM_C6400p)
/* the PLATFORM_C6400p platform has no file system so any definition of the */
/* following macros is valid. */

#define DS_DIR_SEPARATOR '/'
#define DS_DIR_SEPARATOR_S "/"
#define DS_IS_DIR_SEPARATOR(c) ((c) == DS_DIR_SEPARATOR)
#define DS_SEARCHPATH_SEPARATOR ':'
#define DS_SEARCHPATH_SEPARATOR_S ":"

#endif









#ifdef DS_SUPPORT_OBSOLETE

/*
** Put all obsolete stuff here.
*/

#define CLOCK_FACTOR CLOCKS_PER_SEC

#define ResetClock(clock_par)						\
   clock_par = clock ()

#define GetClock(clock_par)						\
   (((float) clock() - clock_par)/CLOCKS_PER_SEC)

#define PrintClock(clock_par, s)					\
      printf ("%50s: %.2f\n", s, GetClock(clock_par));


#define DsPrintTimer(timer, s) \
{ \
  unsigned elapsed_msec; \
  DsGetElapsedTime(timer, &elapsed_msec); \
  printf ("%50s: %u\n", s, elapsed_msec); \
}



#define INLINE_FUNCTION DS_INLINE_FUNCTION

    typedef DS_UINT8 BYTE;
    typedef DS_UINT16 WORD;

    typedef int BOOL;

#ifndef FALSE
#define FALSE (0)
#endif
#ifndef TRUE
#define TRUE  (!FALSE)
#endif

#define EPSILON DS_EPSILON

#if defined (DS_OS_WIN32) || defined (DS_OS_WIN64)
#define M_PI DS_PI
#endif

#define ABS(f) (DS_ABS(f))
#define fast_abs(f) (DS_ABS(f))
#define MIN(x,y) DS_MIN(x,y)
#define MAX(x,y) DS_MAX(x,y)

#if defined (DS_OS_SUN) ||  defined (DS_OS_LINUX) || defined(DS_OS_LINUX64)
#define min(x,y) DS_MIN(x,y)
#define max(x,y) DS_MAX(x,y)
#endif


#endif /* DS_SUPPORT_OBSOLETE */


#ifdef __cplusplus
}  /* close scope of 'extern "C"' declaration which encloses file. */
#endif

#endif /* __DS_H__ */
/* DON'T ADD STUFF AFTER THIS #endif */


