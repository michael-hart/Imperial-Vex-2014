/* Include files */

#include <stddef.h>
#include "blas.h"
#include "read_uart_sfun.h"
#include "c3_read_uart.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "read_uart_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c3_debug_family_names[4] = { "nargin", "nargout", "u", "y" };

/* Function Declarations */
static void initialize_c3_read_uart(SFc3_read_uartInstanceStruct *chartInstance);
static void initialize_params_c3_read_uart(SFc3_read_uartInstanceStruct
  *chartInstance);
static void enable_c3_read_uart(SFc3_read_uartInstanceStruct *chartInstance);
static void disable_c3_read_uart(SFc3_read_uartInstanceStruct *chartInstance);
static void c3_update_debugger_state_c3_read_uart(SFc3_read_uartInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c3_read_uart(SFc3_read_uartInstanceStruct
  *chartInstance);
static void set_sim_state_c3_read_uart(SFc3_read_uartInstanceStruct
  *chartInstance, const mxArray *c3_st);
static void finalize_c3_read_uart(SFc3_read_uartInstanceStruct *chartInstance);
static void sf_gateway_c3_read_uart(SFc3_read_uartInstanceStruct *chartInstance);
static void mdl_start_c3_read_uart(SFc3_read_uartInstanceStruct *chartInstance);
static void initSimStructsc3_read_uart(SFc3_read_uartInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber);
static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData);
static void c3_emlrt_marshallIn(SFc3_read_uartInstanceStruct *chartInstance,
  const mxArray *c3_b_y, const char_T *c3_identifier, uint8_T c3_c_y[5]);
static void c3_b_emlrt_marshallIn(SFc3_read_uartInstanceStruct *chartInstance,
  const mxArray *c3_b_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_b_y[5]);
static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static real_T c3_c_emlrt_marshallIn(SFc3_read_uartInstanceStruct *chartInstance,
  const mxArray *c3_b_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int32_T c3_d_emlrt_marshallIn(SFc3_read_uartInstanceStruct *chartInstance,
  const mxArray *c3_b_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static uint8_T c3_e_emlrt_marshallIn(SFc3_read_uartInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_read_uart, const char_T *c3_identifier);
static uint8_T c3_f_emlrt_marshallIn(SFc3_read_uartInstanceStruct *chartInstance,
  const mxArray *c3_b_u, const emlrtMsgIdentifier *c3_parentId);
static void init_dsm_address_info(SFc3_read_uartInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc3_read_uartInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c3_read_uart(SFc3_read_uartInstanceStruct *chartInstance)
{
  chartInstance->c3_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c3_is_active_c3_read_uart = 0U;
}

static void initialize_params_c3_read_uart(SFc3_read_uartInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c3_read_uart(SFc3_read_uartInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c3_read_uart(SFc3_read_uartInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c3_update_debugger_state_c3_read_uart(SFc3_read_uartInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c3_read_uart(SFc3_read_uartInstanceStruct
  *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_b_y = NULL;
  int32_T c3_i0;
  uint8_T c3_b_u[5];
  const mxArray *c3_c_y = NULL;
  uint8_T c3_hoistedGlobal;
  uint8_T c3_c_u;
  const mxArray *c3_d_y = NULL;
  c3_st = NULL;
  c3_st = NULL;
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_createcellmatrix(2, 1), false);
  for (c3_i0 = 0; c3_i0 < 5; c3_i0++) {
    c3_b_u[c3_i0] = (*chartInstance->c3_y)[c3_i0];
  }

  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_b_u, 3, 0U, 1U, 0U, 1, 5), false);
  sf_mex_setcell(c3_b_y, 0, c3_c_y);
  c3_hoistedGlobal = chartInstance->c3_is_active_c3_read_uart;
  c3_c_u = c3_hoistedGlobal;
  c3_d_y = NULL;
  sf_mex_assign(&c3_d_y, sf_mex_create("y", &c3_c_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c3_b_y, 1, c3_d_y);
  sf_mex_assign(&c3_st, c3_b_y, false);
  return c3_st;
}

static void set_sim_state_c3_read_uart(SFc3_read_uartInstanceStruct
  *chartInstance, const mxArray *c3_st)
{
  const mxArray *c3_b_u;
  uint8_T c3_uv0[5];
  int32_T c3_i1;
  chartInstance->c3_doneDoubleBufferReInit = true;
  c3_b_u = sf_mex_dup(c3_st);
  c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_b_u, 0)), "y",
                      c3_uv0);
  for (c3_i1 = 0; c3_i1 < 5; c3_i1++) {
    (*chartInstance->c3_y)[c3_i1] = c3_uv0[c3_i1];
  }

  chartInstance->c3_is_active_c3_read_uart = c3_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_b_u, 1)), "is_active_c3_read_uart");
  sf_mex_destroy(&c3_b_u);
  c3_update_debugger_state_c3_read_uart(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_read_uart(SFc3_read_uartInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c3_read_uart(SFc3_read_uartInstanceStruct *chartInstance)
{
  int32_T c3_i2;
  int32_T c3_i3;
  uint8_T c3_b_u[3];
  uint32_T c3_debug_family_var_map[4];
  real_T c3_nargin = 1.0;
  real_T c3_nargout = 1.0;
  uint8_T c3_b_y[5];
  int32_T c3_i4;
  int32_T c3_i5;
  int32_T c3_i6;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
  for (c3_i2 = 0; c3_i2 < 3; c3_i2++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c3_u)[c3_i2], 0U);
  }

  chartInstance->c3_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
  for (c3_i3 = 0; c3_i3 < 3; c3_i3++) {
    c3_b_u[c3_i3] = (*chartInstance->c3_u)[c3_i3];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c3_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 0U, c3_c_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 1U, c3_c_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_u, 2U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_b_y, 3U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 5);
  for (c3_i4 = 0; c3_i4 < 5; c3_i4++) {
    c3_b_y[c3_i4] = 0U;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 8);
  switch (c3_b_u[0]) {
   case 1U:
    CV_EML_SWITCH(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 11);
    c3_b_y[0] = c3_b_u[1];
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 12);
    break;

   case 2U:
    CV_EML_SWITCH(0, 1, 0, 2);
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 15);
    c3_b_y[1] = c3_b_u[2];
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 16);
    c3_b_y[3] = c3_b_u[1];
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 17);
    break;

   case 4U:
    CV_EML_SWITCH(0, 1, 0, 3);
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 20);
    c3_b_y[2] = c3_b_u[2];
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 21);
    c3_b_y[3] = c3_b_u[1];
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 22);
    break;

   case 16U:
    CV_EML_SWITCH(0, 1, 0, 4);
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 25);
    c3_b_y[4] = c3_b_u[1];
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 26);
    break;

   case 8U:
    CV_EML_SWITCH(0, 1, 0, 5);
    _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 29);
    break;

   default:
    CV_EML_SWITCH(0, 1, 0, 0);
    break;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, -29);
  _SFD_SYMBOL_SCOPE_POP();
  for (c3_i5 = 0; c3_i5 < 5; c3_i5++) {
    (*chartInstance->c3_y)[c3_i5] = c3_b_y[c3_i5];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c3_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_read_uartMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c3_i6 = 0; c3_i6 < 5; c3_i6++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c3_y)[c3_i6], 1U);
  }
}

static void mdl_start_c3_read_uart(SFc3_read_uartInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void initSimStructsc3_read_uart(SFc3_read_uartInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber)
{
  (void)c3_machineNumber;
  (void)c3_chartNumber;
  (void)c3_instanceNumber;
}

static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i7;
  uint8_T c3_b_inData[5];
  int32_T c3_i8;
  uint8_T c3_b_u[5];
  const mxArray *c3_b_y = NULL;
  SFc3_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc3_read_uartInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i7 = 0; c3_i7 < 5; c3_i7++) {
    c3_b_inData[c3_i7] = (*(uint8_T (*)[5])c3_inData)[c3_i7];
  }

  for (c3_i8 = 0; c3_i8 < 5; c3_i8++) {
    c3_b_u[c3_i8] = c3_b_inData[c3_i8];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 3, 0U, 1U, 0U, 1, 5), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_b_y, false);
  return c3_mxArrayOutData;
}

static void c3_emlrt_marshallIn(SFc3_read_uartInstanceStruct *chartInstance,
  const mxArray *c3_b_y, const char_T *c3_identifier, uint8_T c3_c_y[5])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_y), &c3_thisId, c3_c_y);
  sf_mex_destroy(&c3_b_y);
}

static void c3_b_emlrt_marshallIn(SFc3_read_uartInstanceStruct *chartInstance,
  const mxArray *c3_b_u, const emlrtMsgIdentifier *c3_parentId, uint8_T c3_b_y[5])
{
  uint8_T c3_uv1[5];
  int32_T c3_i9;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_b_u), c3_uv1, 1, 3, 0U, 1, 0U, 1, 5);
  for (c3_i9 = 0; c3_i9 < 5; c3_i9++) {
    c3_b_y[c3_i9] = c3_uv1[c3_i9];
  }

  sf_mex_destroy(&c3_b_u);
}

static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_y;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  uint8_T c3_c_y[5];
  int32_T c3_i10;
  SFc3_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc3_read_uartInstanceStruct *)chartInstanceVoid;
  c3_b_y = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_y), &c3_thisId, c3_c_y);
  sf_mex_destroy(&c3_b_y);
  for (c3_i10 = 0; c3_i10 < 5; c3_i10++) {
    (*(uint8_T (*)[5])c3_outData)[c3_i10] = c3_c_y[c3_i10];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i11;
  uint8_T c3_b_inData[3];
  int32_T c3_i12;
  uint8_T c3_b_u[3];
  const mxArray *c3_b_y = NULL;
  SFc3_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc3_read_uartInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i11 = 0; c3_i11 < 3; c3_i11++) {
    c3_b_inData[c3_i11] = (*(uint8_T (*)[3])c3_inData)[c3_i11];
  }

  for (c3_i12 = 0; c3_i12 < 3; c3_i12++) {
    c3_b_u[c3_i12] = c3_b_inData[c3_i12];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 3, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_b_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_b_u;
  const mxArray *c3_b_y = NULL;
  SFc3_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc3_read_uartInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_b_u = *(real_T *)c3_inData;
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_b_y, false);
  return c3_mxArrayOutData;
}

static real_T c3_c_emlrt_marshallIn(SFc3_read_uartInstanceStruct *chartInstance,
  const mxArray *c3_b_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_b_y;
  real_T c3_d0;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_b_u), &c3_d0, 1, 0, 0U, 0, 0U, 0);
  c3_b_y = c3_d0;
  sf_mex_destroy(&c3_b_u);
  return c3_b_y;
}

static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_nargout;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_b_y;
  SFc3_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc3_read_uartInstanceStruct *)chartInstanceVoid;
  c3_nargout = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_y = c3_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_nargout),
    &c3_thisId);
  sf_mex_destroy(&c3_nargout);
  *(real_T *)c3_outData = c3_b_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

const mxArray *sf_c3_read_uart_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo = NULL;
  c3_nameCaptureInfo = NULL;
  sf_mex_assign(&c3_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c3_nameCaptureInfo;
}

static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_b_u;
  const mxArray *c3_b_y = NULL;
  SFc3_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc3_read_uartInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_b_u = *(int32_T *)c3_inData;
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_b_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_b_y, false);
  return c3_mxArrayOutData;
}

static int32_T c3_d_emlrt_marshallIn(SFc3_read_uartInstanceStruct *chartInstance,
  const mxArray *c3_b_u, const emlrtMsgIdentifier *c3_parentId)
{
  int32_T c3_b_y;
  int32_T c3_i13;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_b_u), &c3_i13, 1, 6, 0U, 0, 0U, 0);
  c3_b_y = c3_i13;
  sf_mex_destroy(&c3_b_u);
  return c3_b_y;
}

static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_sfEvent;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  int32_T c3_b_y;
  SFc3_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc3_read_uartInstanceStruct *)chartInstanceVoid;
  c3_b_sfEvent = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_y = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sfEvent),
    &c3_thisId);
  sf_mex_destroy(&c3_b_sfEvent);
  *(int32_T *)c3_outData = c3_b_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static uint8_T c3_e_emlrt_marshallIn(SFc3_read_uartInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_read_uart, const char_T *c3_identifier)
{
  uint8_T c3_b_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_y = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_b_is_active_c3_read_uart), &c3_thisId);
  sf_mex_destroy(&c3_b_is_active_c3_read_uart);
  return c3_b_y;
}

static uint8_T c3_f_emlrt_marshallIn(SFc3_read_uartInstanceStruct *chartInstance,
  const mxArray *c3_b_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_b_y;
  uint8_T c3_u0;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_b_u), &c3_u0, 1, 3, 0U, 0, 0U, 0);
  c3_b_y = c3_u0;
  sf_mex_destroy(&c3_b_u);
  return c3_b_y;
}

static void init_dsm_address_info(SFc3_read_uartInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc3_read_uartInstanceStruct *chartInstance)
{
  chartInstance->c3_u = (uint8_T (*)[3])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c3_y = (uint8_T (*)[5])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c3_read_uart_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1996005633U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(180832998U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2904869461U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2642836294U);
}

mxArray* sf_c3_read_uart_get_post_codegen_info(void);
mxArray *sf_c3_read_uart_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("f6V1c0L4gqdYeo1X118lsH");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(5);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c3_read_uart_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c3_read_uart_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c3_read_uart_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "incompatibleSymbol", };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 3, infoFields);
  mxArray *fallbackReason = mxCreateString("feature_off");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxArray *fallbackType = mxCreateString("early");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c3_read_uart_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c3_read_uart_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c3_read_uart(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"y\",},{M[8],M[0],T\"is_active_c3_read_uart\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_read_uart_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_read_uartInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc3_read_uartInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _read_uartMachineNumber_,
           3,
           1,
           1,
           0,
           2,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_read_uartMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_read_uartMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _read_uartMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"u");
          _SFD_SET_DATA_PROPS(1,2,0,1,"y");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,1,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,572);

        {
          static int caseStart[] = { -1, 205, 277, 371, 454, 532 };

          static int caseExprEnd[] = { 8, 211, 283, 377, 461, 538 };

          _SFD_CV_INIT_EML_SWITCH(0,1,0,172,184,571,6,&(caseStart[0]),
            &(caseExprEnd[0]));
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)
            c3_sf_marshallIn);
        }

        _SFD_SET_DATA_VALUE_PTR(0U, *chartInstance->c3_u);
        _SFD_SET_DATA_VALUE_PTR(1U, *chartInstance->c3_y);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _read_uartMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "QPbmUMZynm06XLWsJxW39D";
}

static void sf_opaque_initialize_c3_read_uart(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_read_uartInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c3_read_uart((SFc3_read_uartInstanceStruct*)
    chartInstanceVar);
  initialize_c3_read_uart((SFc3_read_uartInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c3_read_uart(void *chartInstanceVar)
{
  enable_c3_read_uart((SFc3_read_uartInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_read_uart(void *chartInstanceVar)
{
  disable_c3_read_uart((SFc3_read_uartInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c3_read_uart(void *chartInstanceVar)
{
  sf_gateway_c3_read_uart((SFc3_read_uartInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c3_read_uart(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c3_read_uart((SFc3_read_uartInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c3_read_uart(SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c3_read_uart((SFc3_read_uartInstanceStruct*)
    chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c3_read_uart(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_read_uartInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_read_uart_optimization_info();
    }

    finalize_c3_read_uart((SFc3_read_uartInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_read_uart((SFc3_read_uartInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_read_uart(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c3_read_uart((SFc3_read_uartInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_read_uart(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_read_uart_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,3,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,3,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,3);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,3,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,3,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1948041926U));
  ssSetChecksum1(S,(1455852777U));
  ssSetChecksum2(S,(3908704440U));
  ssSetChecksum3(S,(3861407374U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c3_read_uart(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_read_uart(SimStruct *S)
{
  SFc3_read_uartInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc3_read_uartInstanceStruct *)utMalloc(sizeof
    (SFc3_read_uartInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_read_uartInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c3_read_uart;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c3_read_uart;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c3_read_uart;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_read_uart;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_read_uart;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c3_read_uart;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c3_read_uart;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c3_read_uart;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_read_uart;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_read_uart;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_read_uart;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->checksum = SF_RUNTIME_INFO_CHECKSUM;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  crtInfo->compiledInfo = NULL;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c3_read_uart_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_read_uart(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_read_uart(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_read_uart(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_read_uart_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
