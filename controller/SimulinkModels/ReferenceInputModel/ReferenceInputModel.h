/*
 * File: ReferenceInputModel.h
 *
 * Code generated for Simulink model 'ReferenceInputModel'.
 *
 * Model version                  : 1.11
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Sat May 10 19:54:49 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ReferenceInputModel_h_
#define RTW_HEADER_ReferenceInputModel_h_
#ifndef ReferenceInputModel_COMMON_INCLUDES_
#define ReferenceInputModel_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                /* ReferenceInputModel_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  int32_T clockTickCounter;            /* '<Root>/Pulse Generator' */
} DW_ReferenceInputModel_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T r;                            /* '<Root>/r' */
} ExtY_ReferenceInputModel_T;

/* Block signals and states (default storage) */
extern DW_ReferenceInputModel_T ReferenceInputModel_DW;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_ReferenceInputModel_T ReferenceInputModel_Y;

/* Model entry point functions */
extern void ReferenceInputModel_initialize(void);
extern void ReferenceInputModel_step(void);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'ReferenceInputModel'
 */
#endif                                 /* RTW_HEADER_ReferenceInputModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
