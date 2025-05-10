/*
 * File: PlantModel.c
 *
 * Code generated for Simulink model 'PlantModel'.
 *
 * Model version                  : 1.10
 * Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
 * C/C++ source code generated on : Sat May 10 19:46:09 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "PlantModel.h"

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

/* Continuous states */
X_PlantModel_T PlantModel_X;

/* External inputs (root inport signals with default storage) */
ExtU_PlantModel_T PlantModel_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_PlantModel_T PlantModel_Y;

/* Real-time model */
static RT_MODEL_PlantModel_T PlantModel_M_;
RT_MODEL_PlantModel_T *const PlantModel_M = &PlantModel_M_;

/* private model entry point functions */
extern void PlantModel_derivatives(void);

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  PlantModel_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  PlantModel_step();
  PlantModel_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  PlantModel_step();
  PlantModel_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void PlantModel_step(void)
{
  if (rtmIsMajorTimeStep(PlantModel_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&PlantModel_M->solverInfo,
                          ((PlantModel_M->Timing.clockTick0+1)*
      PlantModel_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(PlantModel_M)) {
    PlantModel_M->Timing.t[0] = rtsiGetT(&PlantModel_M->solverInfo);
  }

  /* Outport: '<Root>/y' incorporates:
   *  TransferFcn: '<Root>/Transfer Fcn'
   */
  PlantModel_Y.y = 0.0 * PlantModel_X.TransferFcn_CSTATE[0] + 25.0 *
    PlantModel_X.TransferFcn_CSTATE[1];
  if (rtmIsMajorTimeStep(PlantModel_M)) {
    rt_ertODEUpdateContinuousStates(&PlantModel_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++PlantModel_M->Timing.clockTick0;
    PlantModel_M->Timing.t[0] = rtsiGetSolverStopTime(&PlantModel_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.05s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.05, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      PlantModel_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void PlantModel_derivatives(void)
{
  XDot_PlantModel_T *_rtXdot;
  _rtXdot = ((XDot_PlantModel_T *) PlantModel_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' incorporates:
   *  Inport: '<Root>/u'
   */
  _rtXdot->TransferFcn_CSTATE[0] = 0.0;
  _rtXdot->TransferFcn_CSTATE[0] += -7.5000000000000009 *
    PlantModel_X.TransferFcn_CSTATE[0];
  _rtXdot->TransferFcn_CSTATE[1] = 0.0;
  _rtXdot->TransferFcn_CSTATE[0] += -25.0 * PlantModel_X.TransferFcn_CSTATE[1];
  _rtXdot->TransferFcn_CSTATE[1] += PlantModel_X.TransferFcn_CSTATE[0];
  _rtXdot->TransferFcn_CSTATE[0] += PlantModel_U.u;
}

/* Model initialize function */
void PlantModel_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&PlantModel_M->solverInfo,
                          &PlantModel_M->Timing.simTimeStep);
    rtsiSetTPtr(&PlantModel_M->solverInfo, &rtmGetTPtr(PlantModel_M));
    rtsiSetStepSizePtr(&PlantModel_M->solverInfo,
                       &PlantModel_M->Timing.stepSize0);
    rtsiSetdXPtr(&PlantModel_M->solverInfo, &PlantModel_M->derivs);
    rtsiSetContStatesPtr(&PlantModel_M->solverInfo, (real_T **)
                         &PlantModel_M->contStates);
    rtsiSetNumContStatesPtr(&PlantModel_M->solverInfo,
      &PlantModel_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&PlantModel_M->solverInfo,
      &PlantModel_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&PlantModel_M->solverInfo,
      &PlantModel_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&PlantModel_M->solverInfo,
      &PlantModel_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&PlantModel_M->solverInfo, (&rtmGetErrorStatus
      (PlantModel_M)));
    rtsiSetRTModelPtr(&PlantModel_M->solverInfo, PlantModel_M);
  }

  rtsiSetSimTimeStep(&PlantModel_M->solverInfo, MAJOR_TIME_STEP);
  PlantModel_M->intgData.y = PlantModel_M->odeY;
  PlantModel_M->intgData.f[0] = PlantModel_M->odeF[0];
  PlantModel_M->intgData.f[1] = PlantModel_M->odeF[1];
  PlantModel_M->intgData.f[2] = PlantModel_M->odeF[2];
  PlantModel_M->contStates = ((X_PlantModel_T *) &PlantModel_X);
  rtsiSetSolverData(&PlantModel_M->solverInfo, (void *)&PlantModel_M->intgData);
  rtsiSetSolverName(&PlantModel_M->solverInfo,"ode3");
  rtmSetTPtr(PlantModel_M, &PlantModel_M->Timing.tArray[0]);
  PlantModel_M->Timing.stepSize0 = 0.05;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  PlantModel_X.TransferFcn_CSTATE[0] = 0.0;
  PlantModel_X.TransferFcn_CSTATE[1] = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
