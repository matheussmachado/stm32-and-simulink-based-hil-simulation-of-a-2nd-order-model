/*
 * File: ReferenceInputModel.c
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

#include "ReferenceInputModel.h"

/* Block signals and states (default storage) */
DW_ReferenceInputModel_T ReferenceInputModel_DW;

/* External outputs (root outports fed by signals with default storage) */
ExtY_ReferenceInputModel_T ReferenceInputModel_Y;

/* Model step function */
void ReferenceInputModel_step(void)
{
  real_T rtb_PulseGenerator;

  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  rtb_PulseGenerator = (ReferenceInputModel_DW.clockTickCounter < 80) &&
    (ReferenceInputModel_DW.clockTickCounter >= 0) ? 0.5 : 0.0;
  if (ReferenceInputModel_DW.clockTickCounter >= 159) {
    ReferenceInputModel_DW.clockTickCounter = 0;
  } else {
    ReferenceInputModel_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<Root>/Pulse Generator' */

  /* Outport: '<Root>/r' incorporates:
   *  Constant: '<Root>/Constant'
   *  Sum: '<Root>/Subtract'
   */
  ReferenceInputModel_Y.r = 1.5 - rtb_PulseGenerator;
}

/* Model initialize function */
void ReferenceInputModel_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
