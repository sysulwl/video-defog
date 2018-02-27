/*
 * MATLAB Compiler: 4.17 (R2012a)
 * Date: Fri Feb 23 16:03:57 2018
 * Arguments: "-B" "macro_default" "-B" "csharedlib:Defog" "-W" "lib:Defog"
 * "-T" "link:lib" "Defog.m" 
 */

#ifndef __Defog_h
#define __Defog_h 1

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

#ifdef EXPORTING_Defog
#define PUBLIC_Defog_C_API __global
#else
#define PUBLIC_Defog_C_API /* No import statement needed. */
#endif

#define LIB_Defog_C_API PUBLIC_Defog_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_Defog
#define PUBLIC_Defog_C_API __declspec(dllexport)
#else
#define PUBLIC_Defog_C_API __declspec(dllimport)
#endif

#define LIB_Defog_C_API PUBLIC_Defog_C_API


#else

#define LIB_Defog_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_Defog_C_API 
#define LIB_Defog_C_API /* No special import/export declaration */
#endif

extern LIB_Defog_C_API 
bool MW_CALL_CONV DefogInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_Defog_C_API 
bool MW_CALL_CONV DefogInitialize(void);

extern LIB_Defog_C_API 
void MW_CALL_CONV DefogTerminate(void);



extern LIB_Defog_C_API 
void MW_CALL_CONV DefogPrintStackTrace(void);

extern LIB_Defog_C_API 
bool MW_CALL_CONV mlxDefog(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);



extern LIB_Defog_C_API bool MW_CALL_CONV mlfDefog(mxArray* StrFilePath, mxArray* StrFileName);

#ifdef __cplusplus
}
#endif
#endif
