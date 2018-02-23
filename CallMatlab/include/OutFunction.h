/*
 * MATLAB Compiler: 4.17 (R2012a)
 * Date: Thu Feb 22 23:48:32 2018
 * Arguments: "-B" "macro_default" "-B" "csharedlib:OutFunction" "-W"
 * "lib:OutFunction" "-T" "link:lib" "OutFunction.m" 
 */

#ifndef __OutFunction_h
#define __OutFunction_h 1

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

#ifdef EXPORTING_OutFunction
#define PUBLIC_OutFunction_C_API __global
#else
#define PUBLIC_OutFunction_C_API /* No import statement needed. */
#endif

#define LIB_OutFunction_C_API PUBLIC_OutFunction_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_OutFunction
#define PUBLIC_OutFunction_C_API __declspec(dllexport)
#else
#define PUBLIC_OutFunction_C_API __declspec(dllimport)
#endif

#define LIB_OutFunction_C_API PUBLIC_OutFunction_C_API


#else

#define LIB_OutFunction_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_OutFunction_C_API 
#define LIB_OutFunction_C_API /* No special import/export declaration */
#endif

extern LIB_OutFunction_C_API 
bool MW_CALL_CONV OutFunctionInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_OutFunction_C_API 
bool MW_CALL_CONV OutFunctionInitialize(void);

extern LIB_OutFunction_C_API 
void MW_CALL_CONV OutFunctionTerminate(void);



extern LIB_OutFunction_C_API 
void MW_CALL_CONV OutFunctionPrintStackTrace(void);

extern LIB_OutFunction_C_API 
bool MW_CALL_CONV mlxOutFunction(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);



extern LIB_OutFunction_C_API bool MW_CALL_CONV mlfOutFunction();

#ifdef __cplusplus
}
#endif
#endif
