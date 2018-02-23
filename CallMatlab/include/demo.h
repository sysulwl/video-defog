/*
 * MATLAB Compiler: 4.17 (R2012a)
 * Date: Fri Feb 23 00:24:06 2018
 * Arguments: "-B" "macro_default" "-B" "csharedlib:demo" "-W" "lib:demo" "-T"
 * "link:lib" "demo.m" 
 */

#ifndef __demo_h
#define __demo_h 1

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

#ifdef EXPORTING_demo
#define PUBLIC_demo_C_API __global
#else
#define PUBLIC_demo_C_API /* No import statement needed. */
#endif

#define LIB_demo_C_API PUBLIC_demo_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_demo
#define PUBLIC_demo_C_API __declspec(dllexport)
#else
#define PUBLIC_demo_C_API __declspec(dllimport)
#endif

#define LIB_demo_C_API PUBLIC_demo_C_API


#else

#define LIB_demo_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_demo_C_API 
#define LIB_demo_C_API /* No special import/export declaration */
#endif

extern LIB_demo_C_API 
bool MW_CALL_CONV demoInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_demo_C_API 
bool MW_CALL_CONV demoInitialize(void);

extern LIB_demo_C_API 
void MW_CALL_CONV demoTerminate(void);



extern LIB_demo_C_API 
void MW_CALL_CONV demoPrintStackTrace(void);

extern LIB_demo_C_API 
bool MW_CALL_CONV mlxDemo(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);



extern LIB_demo_C_API bool MW_CALL_CONV mlfDemo();

#ifdef __cplusplus
}
#endif
#endif
