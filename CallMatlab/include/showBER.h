/*
 * MATLAB Compiler: 4.17 (R2012a)
 * Date: Wed Feb 14 19:24:57 2018
 * Arguments: "-B" "macro_default" "-B" "csharedlib:showBER" "-W" "lib:showBER"
 * "-T" "link:lib" "showBER.m" 
 */

#ifndef __showBER_h
#define __showBER_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_showBER
#define PUBLIC_showBER_C_API __global
#else
#define PUBLIC_showBER_C_API /* No import statement needed. */
#endif

#define LIB_showBER_C_API PUBLIC_showBER_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_showBER
#define PUBLIC_showBER_C_API __declspec(dllexport)
#else
#define PUBLIC_showBER_C_API __declspec(dllimport)
#endif

#define LIB_showBER_C_API PUBLIC_showBER_C_API


#else

#define LIB_showBER_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_showBER_C_API 
#define LIB_showBER_C_API /* No special import/export declaration */
#endif

extern LIB_showBER_C_API 
bool MW_CALL_CONV showBERInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_showBER_C_API 
bool MW_CALL_CONV showBERInitialize(void);

extern LIB_showBER_C_API 
void MW_CALL_CONV showBERTerminate(void);



extern LIB_showBER_C_API 
void MW_CALL_CONV showBERPrintStackTrace(void);

extern LIB_showBER_C_API 
bool MW_CALL_CONV mlxShowBER(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);



extern LIB_showBER_C_API bool MW_CALL_CONV mlfShowBER(mxArray* SNR_indB, mxArray* BER);

#ifdef __cplusplus
}
#endif
#endif
