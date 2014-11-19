/*
 * File: feedback_control_types.h
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

#ifndef RTW_HEADER_feedback_control_types_h_
#define RTW_HEADER_feedback_control_types_h_
#include "rtwtypes.h"
#ifndef _DEFINED_TYPEDEF_FOR_pid_param_
#define _DEFINED_TYPEDEF_FOR_pid_param_

typedef struct {
  real_T P;
  real_T I;
  real_T D;
  real_T N;
} pid_param;

#endif

/* Parameters (auto storage) */
typedef struct Parameters_feedback_control_ Parameters_feedback_control;

/* Forward declaration for rtModel */
typedef struct tag_RTM_feedback_control RT_MODEL_feedback_control;

#endif                                 /* RTW_HEADER_feedback_control_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
