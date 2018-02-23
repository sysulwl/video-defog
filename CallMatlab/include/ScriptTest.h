/*
 * MATLAB Compiler: 4.17 (R2012a)
 * Date: Wed Feb 21 23:15:15 2018
 * Arguments: "-B" "macro_default" "-B" "csharedlib:ScriptTest" "-W"
 * "lib:ScriptTest" "-T" "link:lib" "ScriptTest.m" 
 */

#ifndef __ScriptTest_h
#define __ScriptTest_h 1

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

#ifdef EXPORTING_ScriptTest
#define PUBLIC_ScriptTest_C_API __global
#else
#define PUBLIC_ScriptTest_C_API /* No import statement needed. */
#endif

#define LIB_ScriptTest_C_API PUBLIC_ScriptTest_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_ScriptTest
#define PUBLIC_ScriptTest_C_API __declspec(dllexport)
#else
#define PUBLIC_ScriptTest_C_API __declspec(dllimport)
#endif

#define LIB_ScriptTest_C_API PUBLIC_ScriptTest_C_API


#else

#define LIB_ScriptTest_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_ScriptTest_C_API 
#define LIB_ScriptTest_C_API /* No special import/export declaration */
#endif

extern LIB_ScriptTest_C_API 
bool MW_CALL_CONV ScriptTestInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_ScriptTest_C_API 
bool MW_CALL_CONV ScriptTestInitialize(void);

extern LIB_ScriptTest_C_API 
void MW_CALL_CONV ScriptTestTerminate(void);



extern LIB_ScriptTest_C_API 
void MW_CALL_CONV ScriptTestPrintStackTrace(void);

extern LIB_ScriptTest_C_API 
bool MW_CALL_CONV mlxScriptTest(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);



extern LIB_ScriptTest_C_API bool MW_CALL_CONV mlfScriptTest();

#ifdef __cplusplus
}
#endif
#endif
