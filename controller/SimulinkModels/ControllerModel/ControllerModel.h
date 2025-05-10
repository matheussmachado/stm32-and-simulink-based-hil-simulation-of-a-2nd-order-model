/*
 * File: ControllerModel.h
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

#ifndef RTW_HEADER_ControllerModel_h_
#define RTW_HEADER_ControllerModel_h_
#ifndef ControllerModel_COMMON_INCLUDES_
#define ControllerModel_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* ControllerModel_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_ControllerModel_T RT_MODEL_ControllerModel_T;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator;                   /* '<S33>/Integrator' */
  real_T Integrator_DSTATE;            /* '<S33>/Integrator' */
} DW_ControllerModel_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T e;                            /* '<Root>/e' */
} ExtU_ControllerModel_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T u;                            /* '<Root>/u' */
} ExtY_ControllerModel_T;

/* Real-time Model Data Structure */
struct tag_RTM_ControllerModel_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block signals and states (default storage) */
extern DW_ControllerModel_T ControllerModel_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_ControllerModel_T ControllerModel_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_ControllerModel_T ControllerModel_Y;

/* Model entry point functions */
extern void ControllerModel_initialize(void);
extern void ControllerModel_step(void);

/* Real-time Model object */
extern RT_MODEL_ControllerModel_T *const ControllerModel_M;

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
 * '<Root>' : 'ControllerModel'
 * '<S1>'   : 'ControllerModel/PID Controller'
 * '<S2>'   : 'ControllerModel/PID Controller/Anti-windup'
 * '<S3>'   : 'ControllerModel/PID Controller/D Gain'
 * '<S4>'   : 'ControllerModel/PID Controller/Filter'
 * '<S5>'   : 'ControllerModel/PID Controller/Filter ICs'
 * '<S6>'   : 'ControllerModel/PID Controller/I Gain'
 * '<S7>'   : 'ControllerModel/PID Controller/Ideal P Gain'
 * '<S8>'   : 'ControllerModel/PID Controller/Ideal P Gain Fdbk'
 * '<S9>'   : 'ControllerModel/PID Controller/Integrator'
 * '<S10>'  : 'ControllerModel/PID Controller/Integrator ICs'
 * '<S11>'  : 'ControllerModel/PID Controller/N Copy'
 * '<S12>'  : 'ControllerModel/PID Controller/N Gain'
 * '<S13>'  : 'ControllerModel/PID Controller/P Copy'
 * '<S14>'  : 'ControllerModel/PID Controller/Parallel P Gain'
 * '<S15>'  : 'ControllerModel/PID Controller/Reset Signal'
 * '<S16>'  : 'ControllerModel/PID Controller/Saturation'
 * '<S17>'  : 'ControllerModel/PID Controller/Saturation Fdbk'
 * '<S18>'  : 'ControllerModel/PID Controller/Sum'
 * '<S19>'  : 'ControllerModel/PID Controller/Sum Fdbk'
 * '<S20>'  : 'ControllerModel/PID Controller/Tracking Mode'
 * '<S21>'  : 'ControllerModel/PID Controller/Tracking Mode Sum'
 * '<S22>'  : 'ControllerModel/PID Controller/Tsamp - Integral'
 * '<S23>'  : 'ControllerModel/PID Controller/Tsamp - Ngain'
 * '<S24>'  : 'ControllerModel/PID Controller/postSat Signal'
 * '<S25>'  : 'ControllerModel/PID Controller/preSat Signal'
 * '<S26>'  : 'ControllerModel/PID Controller/Anti-windup/Passthrough'
 * '<S27>'  : 'ControllerModel/PID Controller/D Gain/Disabled'
 * '<S28>'  : 'ControllerModel/PID Controller/Filter/Disabled'
 * '<S29>'  : 'ControllerModel/PID Controller/Filter ICs/Disabled'
 * '<S30>'  : 'ControllerModel/PID Controller/I Gain/Internal Parameters'
 * '<S31>'  : 'ControllerModel/PID Controller/Ideal P Gain/Passthrough'
 * '<S32>'  : 'ControllerModel/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S33>'  : 'ControllerModel/PID Controller/Integrator/Discrete'
 * '<S34>'  : 'ControllerModel/PID Controller/Integrator ICs/Internal IC'
 * '<S35>'  : 'ControllerModel/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S36>'  : 'ControllerModel/PID Controller/N Gain/Disabled'
 * '<S37>'  : 'ControllerModel/PID Controller/P Copy/Disabled'
 * '<S38>'  : 'ControllerModel/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S39>'  : 'ControllerModel/PID Controller/Reset Signal/Disabled'
 * '<S40>'  : 'ControllerModel/PID Controller/Saturation/Passthrough'
 * '<S41>'  : 'ControllerModel/PID Controller/Saturation Fdbk/Disabled'
 * '<S42>'  : 'ControllerModel/PID Controller/Sum/Sum_PI'
 * '<S43>'  : 'ControllerModel/PID Controller/Sum Fdbk/Disabled'
 * '<S44>'  : 'ControllerModel/PID Controller/Tracking Mode/Disabled'
 * '<S45>'  : 'ControllerModel/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S46>'  : 'ControllerModel/PID Controller/Tsamp - Integral/Passthrough'
 * '<S47>'  : 'ControllerModel/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S48>'  : 'ControllerModel/PID Controller/postSat Signal/Forward_Path'
 * '<S49>'  : 'ControllerModel/PID Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_ControllerModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
