/*
 * File: ControllerModel.c
 *
 * Code generated for Simulink model 'ControllerModel'.
 *
 * Model version                  : 1.10
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Sat May 10 19:51:55 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "ControllerModel.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

/* Block signals and states (default storage) */
DW_ControllerModel_T ControllerModel_DW;

/* External inputs (root inport signals with default storage) */
ExtU_ControllerModel_T ControllerModel_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_ControllerModel_T ControllerModel_Y;

/* Real-time model */
static RT_MODEL_ControllerModel_T ControllerModel_M_;
RT_MODEL_ControllerModel_T *const ControllerModel_M = &ControllerModel_M_;

/* Model step function */
void ControllerModel_step(void)
{
  /* local block i/o variables */
  real_T rtb_IntegralGain;

  /* Gain: '<S30>/Integral Gain' incorporates:
   *  Inport: '<Root>/e'
   */
  rtb_IntegralGain = 1.91054639755173 * ControllerModel_U.e;

  /* DiscreteIntegrator: '<S33>/Integrator' */
  ControllerModel_DW.Integrator = 0.025 * rtb_IntegralGain +
    ControllerModel_DW.Integrator_DSTATE;

  /* Outport: '<Root>/u' incorporates:
   *  Gain: '<S38>/Proportional Gain'
   *  Inport: '<Root>/e'
   *  Sum: '<S42>/Sum'
   */
  ControllerModel_Y.u = 0.21484784713862 * ControllerModel_U.e +
    ControllerModel_DW.Integrator;

  /* Update for DiscreteIntegrator: '<S33>/Integrator' */
  ControllerModel_DW.Integrator_DSTATE = 0.025 * rtb_IntegralGain +
    ControllerModel_DW.Integrator;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  ControllerModel_M->Timing.t[0] =
    ((time_T)(++ControllerModel_M->Timing.clockTick0)) *
    ControllerModel_M->Timing.stepSize0;

  {
    /* Update absolute timer for sample time: [0.05s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.05, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    ControllerModel_M->Timing.clockTick1++;
  }
}

/* Model initialize function */
void ControllerModel_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&ControllerModel_M->solverInfo,
                          &ControllerModel_M->Timing.simTimeStep);
    rtsiSetTPtr(&ControllerModel_M->solverInfo, &rtmGetTPtr(ControllerModel_M));
    rtsiSetStepSizePtr(&ControllerModel_M->solverInfo,
                       &ControllerModel_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&ControllerModel_M->solverInfo, (&rtmGetErrorStatus
      (ControllerModel_M)));
    rtsiSetRTModelPtr(&ControllerModel_M->solverInfo, ControllerModel_M);
  }

  rtsiSetSimTimeStep(&ControllerModel_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&ControllerModel_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(ControllerModel_M, &ControllerModel_M->Timing.tArray[0]);
  ControllerModel_M->Timing.stepSize0 = 0.05;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
