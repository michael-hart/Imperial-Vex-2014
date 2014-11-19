/*
 * File: feedback_control.h
 *
 * Code generated for Simulink model 'feedback_control'.
 *
 * Model version                  : 1.39
 * Simulink Coder version         : 8.7 (R2014b) 08-Sep-2014
 * C/C++ source code generated on : Wed Nov 19 13:46:01 2014
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_feedback_control_h_
#define RTW_HEADER_feedback_control_h_
#ifndef feedback_control_COMMON_INCLUDES_
# define feedback_control_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* feedback_control_COMMON_INCLUDES_ */

#include "feedback_control_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S1>/Integrator' */
  real_T Filter_DSTATE;                /* '<S1>/Filter' */
} D_Work_feedback_control;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real_T control_input;                /* '<Root>/u' */
} ExternalInputs_feedback_control;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real_T y;                            /* '<Root>/y' */
} ExternalOutputs_feedback_contro;

/* Parameters (auto storage) */
struct Parameters_feedback_control_ {
  pid_param pid;                       /* Variable: pid
                                        * Referenced by:
                                        *   '<S1>/Derivative Gain'
                                        *   '<S1>/Filter Coefficient'
                                        *   '<S1>/Integral Gain'
                                        *   '<S1>/Proportional Gain'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_feedback_control {
  const char_T * volatile errorStatus;
};

/* Block parameters (auto storage) */
extern Parameters_feedback_control feedback_control_P;

/* Block states (auto storage) */
extern D_Work_feedback_control feedback_control_DWork;

/* External inputs (root inport signals with auto storage) */
extern ExternalInputs_feedback_control feedback_control_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExternalOutputs_feedback_contro feedback_control_Y;

/* Model entry point functions */
extern void feedback_control_initialize(void);
extern void feedback_control_step(void);
extern void feedback_control_terminate(void);

/* Real-time Model object */
extern RT_MODEL_feedback_control *const feedback_control_M;

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
 * '<Root>' : 'feedback_control'
 * '<S1>'   : 'feedback_control/Discrete PID Controller'
 */
#endif                                 /* RTW_HEADER_feedback_control_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
