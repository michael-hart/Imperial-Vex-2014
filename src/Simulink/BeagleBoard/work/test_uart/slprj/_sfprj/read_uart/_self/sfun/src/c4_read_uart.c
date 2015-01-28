/* Include files */

#include <stddef.h>
#include "blas.h"
#include "read_uart_sfun.h"
#include "c4_read_uart.h"
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
static const char * c4_debug_family_names[6] = { "nargin", "nargout", "packets",
  "itt", "singlePack", "terminate" };

/* Function Declarations */
static void initialize_c4_read_uart(SFc4_read_uartInstanceStruct *chartInstance);
static void initialize_params_c4_read_uart(SFc4_read_uartInstanceStruct
  *chartInstance);
static void enable_c4_read_uart(SFc4_read_uartInstanceStruct *chartInstance);
static void disable_c4_read_uart(SFc4_read_uartInstanceStruct *chartInstance);
static void c4_update_debugger_state_c4_read_uart(SFc4_read_uartInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c4_read_uart(SFc4_read_uartInstanceStruct
  *chartInstance);
static void set_sim_state_c4_read_uart(SFc4_read_uartInstanceStruct
  *chartInstance, const mxArray *c4_st);
static void finalize_c4_read_uart(SFc4_read_uartInstanceStruct *chartInstance);
static void sf_gateway_c4_read_uart(SFc4_read_uartInstanceStruct *chartInstance);
static void mdl_start_c4_read_uart(SFc4_read_uartInstanceStruct *chartInstance);
static void initSimStructsc4_read_uart(SFc4_read_uartInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber, uint32_T c4_instanceNumber);
static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData);
static boolean_T c4_emlrt_marshallIn(SFc4_read_uartInstanceStruct *chartInstance,
  const mxArray *c4_b_terminate, const char_T *c4_identifier);
static boolean_T c4_b_emlrt_marshallIn(SFc4_read_uartInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_c_emlrt_marshallIn(SFc4_read_uartInstanceStruct *chartInstance,
  const mxArray *c4_b_singlePack, const char_T *c4_identifier, uint8_T c4_y[5]);
static void c4_d_emlrt_marshallIn(SFc4_read_uartInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, uint8_T c4_y[5]);
static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, c4_PacketsBus
  *c4_inData_data, c4_PacketsBus_size *c4_inData_elems_sizes);
static const mxArray *c4_e_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static real_T c4_e_emlrt_marshallIn(SFc4_read_uartInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static void c4_info_helper(const mxArray **c4_info);
static const mxArray *c4_emlrt_marshallOut(const char * c4_u);
static const mxArray *c4_b_emlrt_marshallOut(const uint32_T c4_u);
static int32_T c4_intlength(SFc4_read_uartInstanceStruct *chartInstance, uint8_T
  c4_x_data[], int32_T c4_x_sizes[2]);
static const mxArray *c4_f_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static int32_T c4_f_emlrt_marshallIn(SFc4_read_uartInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_packets_bus_io(void *chartInstanceVoid, void *c4_pData);
static const mxArray *c4_sf_marshall_unsupported(void *chartInstanceVoid);
static const mxArray *c4_c_emlrt_marshallOut(SFc4_read_uartInstanceStruct
  *chartInstance, const char * c4_u);
static uint8_T c4_g_emlrt_marshallIn(SFc4_read_uartInstanceStruct *chartInstance,
  const mxArray *c4_b_is_active_c4_read_uart, const char_T *c4_identifier);
static uint8_T c4_h_emlrt_marshallIn(SFc4_read_uartInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void init_dsm_address_info(SFc4_read_uartInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc4_read_uartInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c4_read_uart(SFc4_read_uartInstanceStruct *chartInstance)
{
  chartInstance->c4_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c4_is_active_c4_read_uart = 0U;
}

static void initialize_params_c4_read_uart(SFc4_read_uartInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c4_read_uart(SFc4_read_uartInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c4_read_uart(SFc4_read_uartInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c4_update_debugger_state_c4_read_uart(SFc4_read_uartInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c4_read_uart(SFc4_read_uartInstanceStruct
  *chartInstance)
{
  const mxArray *c4_st;
  const mxArray *c4_y = NULL;
  int32_T c4_i0;
  uint8_T c4_u[5];
  const mxArray *c4_b_y = NULL;
  boolean_T c4_hoistedGlobal;
  boolean_T c4_b_u;
  const mxArray *c4_c_y = NULL;
  uint8_T c4_b_hoistedGlobal;
  uint8_T c4_c_u;
  const mxArray *c4_d_y = NULL;
  c4_st = NULL;
  c4_st = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createcellmatrix(3, 1), false);
  for (c4_i0 = 0; c4_i0 < 5; c4_i0++) {
    c4_u[c4_i0] = (*chartInstance->c4_singlePack)[c4_i0];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_u, 3, 0U, 1U, 0U, 2, 5, 1), false);
  sf_mex_setcell(c4_y, 0, c4_b_y);
  c4_hoistedGlobal = *chartInstance->c4_terminate;
  c4_b_u = c4_hoistedGlobal;
  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", &c4_b_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 1, c4_c_y);
  c4_b_hoistedGlobal = chartInstance->c4_is_active_c4_read_uart;
  c4_c_u = c4_b_hoistedGlobal;
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", &c4_c_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 2, c4_d_y);
  sf_mex_assign(&c4_st, c4_y, false);
  return c4_st;
}

static void set_sim_state_c4_read_uart(SFc4_read_uartInstanceStruct
  *chartInstance, const mxArray *c4_st)
{
  const mxArray *c4_u;
  uint8_T c4_uv0[5];
  int32_T c4_i1;
  chartInstance->c4_doneDoubleBufferReInit = true;
  c4_u = sf_mex_dup(c4_st);
  c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 0)),
                        "singlePack", c4_uv0);
  for (c4_i1 = 0; c4_i1 < 5; c4_i1++) {
    (*chartInstance->c4_singlePack)[c4_i1] = c4_uv0[c4_i1];
  }

  *chartInstance->c4_terminate = c4_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c4_u, 1)), "terminate");
  chartInstance->c4_is_active_c4_read_uart = c4_g_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c4_u, 2)), "is_active_c4_read_uart");
  sf_mex_destroy(&c4_u);
  c4_update_debugger_state_c4_read_uart(chartInstance);
  sf_mex_destroy(&c4_st);
}

static void finalize_c4_read_uart(SFc4_read_uartInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c4_read_uart(SFc4_read_uartInstanceStruct *chartInstance)
{
  int8_T c4_hoistedGlobal;
  c4_PacketsBus_size c4_b_packets_elems_sizes;
  int32_T c4_loop_ub;
  int32_T c4_i2;
  int32_T c4_b_loop_ub;
  int32_T c4_i3;
  c4_PacketsBus c4_b_packets_data;
  int32_T c4_c_loop_ub;
  int32_T c4_i4;
  int32_T c4_d_loop_ub;
  int32_T c4_i5;
  int32_T c4_e_loop_ub;
  int32_T c4_i6;
  int32_T c4_f_loop_ub;
  int32_T c4_i7;
  int32_T c4_g_loop_ub;
  int32_T c4_i8;
  int32_T c4_h_loop_ub;
  int32_T c4_i9;
  int32_T c4_i_loop_ub;
  int32_T c4_i10;
  int32_T c4_j_loop_ub;
  int32_T c4_i11;
  int8_T c4_b_itt;
  uint32_T c4_debug_family_var_map[6];
  real_T c4_nargin = 2.0;
  real_T c4_nargout = 2.0;
  uint8_T c4_b_singlePack[5];
  boolean_T c4_b_terminate;
  int32_T c4_i12;
  int32_T c4_x_sizes[2];
  int32_T c4_x;
  int32_T c4_b_x;
  int32_T c4_k_loop_ub;
  int32_T c4_i13;
  uint8_T c4_x_data[255];
  int32_T c4_b_x_sizes[2];
  int32_T c4_c_x;
  int32_T c4_d_x;
  int32_T c4_l_loop_ub;
  int32_T c4_i14;
  uint8_T c4_b_x_data[255];
  real_T c4_d0;
  int32_T c4_packets[1];
  int32_T c4_b_packets[1];
  int32_T c4_c_packets[1];
  int32_T c4_d_packets[1];
  int32_T c4_e_packets[1];
  int32_T c4_i15;
  int32_T c4_i16;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_itt, 1U);
  chartInstance->c4_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  c4_hoistedGlobal = *chartInstance->c4_itt;
  c4_b_packets_elems_sizes.cmd[0] = chartInstance->c4_packets_elems_sizes->cmd[0];
  c4_b_packets_elems_sizes.cmd[1] = chartInstance->c4_packets_elems_sizes->cmd[1];
  c4_loop_ub = chartInstance->c4_packets_elems_sizes->cmd[1] - 1;
  for (c4_i2 = 0; c4_i2 <= c4_loop_ub; c4_i2++) {
    c4_b_loop_ub = chartInstance->c4_packets_elems_sizes->cmd[0] - 1;
    for (c4_i3 = 0; c4_i3 <= c4_b_loop_ub; c4_i3++) {
      c4_b_packets_data.cmd[c4_i3 + c4_b_packets_elems_sizes.cmd[0] * c4_i2] =
        ((uint8_T *)&((char_T *)chartInstance->c4_packets_data)[0])[c4_i3 +
        chartInstance->c4_packets_elems_sizes->cmd[0] * c4_i2];
    }
  }

  c4_b_packets_elems_sizes.id[0] = chartInstance->c4_packets_elems_sizes->id[0];
  c4_b_packets_elems_sizes.id[1] = chartInstance->c4_packets_elems_sizes->id[1];
  c4_c_loop_ub = chartInstance->c4_packets_elems_sizes->id[1] - 1;
  for (c4_i4 = 0; c4_i4 <= c4_c_loop_ub; c4_i4++) {
    c4_d_loop_ub = chartInstance->c4_packets_elems_sizes->id[0] - 1;
    for (c4_i5 = 0; c4_i5 <= c4_d_loop_ub; c4_i5++) {
      c4_b_packets_data.id[c4_i5 + c4_b_packets_elems_sizes.id[0] * c4_i4] =
        ((uint8_T *)&((char_T *)chartInstance->c4_packets_data)[255])[c4_i5 +
        chartInstance->c4_packets_elems_sizes->id[0] * c4_i4];
    }
  }

  c4_b_packets_elems_sizes.data[0] = chartInstance->c4_packets_elems_sizes->
    data[0];
  c4_b_packets_elems_sizes.data[1] = chartInstance->c4_packets_elems_sizes->
    data[1];
  c4_e_loop_ub = chartInstance->c4_packets_elems_sizes->data[1] - 1;
  for (c4_i6 = 0; c4_i6 <= c4_e_loop_ub; c4_i6++) {
    c4_f_loop_ub = chartInstance->c4_packets_elems_sizes->data[0] - 1;
    for (c4_i7 = 0; c4_i7 <= c4_f_loop_ub; c4_i7++) {
      c4_b_packets_data.data[c4_i7 + c4_b_packets_elems_sizes.data[0] * c4_i6] =
        ((uint8_T *)&((char_T *)chartInstance->c4_packets_data)[510])[c4_i7 +
        chartInstance->c4_packets_elems_sizes->data[0] * c4_i6];
    }
  }

  c4_b_packets_elems_sizes.c0[0] = chartInstance->c4_packets_elems_sizes->c0[0];
  c4_b_packets_elems_sizes.c0[1] = chartInstance->c4_packets_elems_sizes->c0[1];
  c4_g_loop_ub = chartInstance->c4_packets_elems_sizes->c0[1] - 1;
  for (c4_i8 = 0; c4_i8 <= c4_g_loop_ub; c4_i8++) {
    c4_h_loop_ub = chartInstance->c4_packets_elems_sizes->c0[0] - 1;
    for (c4_i9 = 0; c4_i9 <= c4_h_loop_ub; c4_i9++) {
      c4_b_packets_data.c0[c4_i9 + c4_b_packets_elems_sizes.c0[0] * c4_i8] =
        ((uint8_T *)&((char_T *)chartInstance->c4_packets_data)[765])[c4_i9 +
        chartInstance->c4_packets_elems_sizes->c0[0] * c4_i8];
    }
  }

  c4_b_packets_elems_sizes.c1[0] = chartInstance->c4_packets_elems_sizes->c1[0];
  c4_b_packets_elems_sizes.c1[1] = chartInstance->c4_packets_elems_sizes->c1[1];
  c4_i_loop_ub = chartInstance->c4_packets_elems_sizes->c1[1] - 1;
  for (c4_i10 = 0; c4_i10 <= c4_i_loop_ub; c4_i10++) {
    c4_j_loop_ub = chartInstance->c4_packets_elems_sizes->c1[0] - 1;
    for (c4_i11 = 0; c4_i11 <= c4_j_loop_ub; c4_i11++) {
      c4_b_packets_data.c1[c4_i11 + c4_b_packets_elems_sizes.c1[0] * c4_i10] =
        ((uint8_T *)&((char_T *)chartInstance->c4_packets_data)[1020])[c4_i11 +
        chartInstance->c4_packets_elems_sizes->c1[0] * c4_i10];
    }
  }

  c4_b_itt = c4_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 6U, 6U, c4_debug_family_names,
    c4_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargin, 0U, c4_e_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargout, 1U, c4_e_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN(&c4_b_packets_data, NULL,
    &c4_b_packets_elems_sizes, 1, 2, (void *)c4_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_b_itt, 3U, c4_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_b_singlePack, 4U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b_terminate, 5U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 3);
  c4_b_terminate = true;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 4);
  for (c4_i12 = 0; c4_i12 < 5; c4_i12++) {
    c4_b_singlePack[c4_i12] = 0U;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 6);
  c4_x_sizes[0] = c4_b_packets_elems_sizes.cmd[0];
  c4_x_sizes[1] = c4_b_packets_elems_sizes.cmd[1];
  c4_x = c4_x_sizes[0];
  c4_b_x = c4_x_sizes[1];
  c4_k_loop_ub = c4_b_packets_elems_sizes.cmd[0] * c4_b_packets_elems_sizes.cmd
    [1] - 1;
  for (c4_i13 = 0; c4_i13 <= c4_k_loop_ub; c4_i13++) {
    c4_x_data[c4_i13] = c4_b_packets_data.cmd[c4_i13];
  }

  c4_b_x_sizes[0] = c4_x_sizes[0];
  c4_b_x_sizes[1] = c4_x_sizes[1];
  c4_c_x = c4_b_x_sizes[0];
  c4_d_x = c4_b_x_sizes[1];
  c4_l_loop_ub = c4_x_sizes[0] * c4_x_sizes[1] - 1;
  for (c4_i14 = 0; c4_i14 <= c4_l_loop_ub; c4_i14++) {
    c4_b_x_data[c4_i14] = c4_x_data[c4_i14];
  }

  c4_d0 = (real_T)c4_intlength(chartInstance, c4_b_x_data, c4_b_x_sizes);
  if (CV_EML_IF(0, 1, 0, CV_RELATIONAL_EVAL(4U, 0U, 0, c4_d0, (real_T)c4_b_itt,
        -1, 2U, c4_d0 < (real_T)c4_b_itt))) {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 7);
    c4_b_terminate = false;
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 8);
  } else {
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 11);
    (int8_T)_SFD_EML_ARRAY_BOUNDS_CHECK("packets.cmd", (int32_T)c4_b_itt, 1,
      c4_b_packets_elems_sizes.cmd[0] * c4_b_packets_elems_sizes.cmd[1], 1, 0);
    CV_EML_COND(0, 1, 0, false);
    CV_EML_MCDC(0, 1, 0, true);
    CV_EML_IF(0, 1, 1, true);
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 12);
    c4_packets[0] = c4_b_packets_elems_sizes.cmd[0] *
      c4_b_packets_elems_sizes.cmd[1];
    c4_b_packets[0] = c4_b_packets_elems_sizes.id[0] *
      c4_b_packets_elems_sizes.id[1];
    c4_c_packets[0] = c4_b_packets_elems_sizes.data[0] *
      c4_b_packets_elems_sizes.data[1];
    c4_d_packets[0] = c4_b_packets_elems_sizes.c0[0] *
      c4_b_packets_elems_sizes.c0[1];
    c4_e_packets[0] = c4_b_packets_elems_sizes.c1[0] *
      c4_b_packets_elems_sizes.c1[1];
    c4_b_singlePack[0] = c4_b_packets_data.cmd[(int8_T)
      _SFD_EML_ARRAY_BOUNDS_CHECK("packets.cmd", (int32_T)c4_b_itt, 1,
      c4_b_packets_elems_sizes.cmd[0] * c4_b_packets_elems_sizes.cmd[1], 1, 0) -
      1];
    c4_b_singlePack[1] = c4_b_packets_data.id[(int8_T)
      _SFD_EML_ARRAY_BOUNDS_CHECK("packets.id", (int32_T)c4_b_itt, 1,
      c4_b_packets_elems_sizes.id[0] * c4_b_packets_elems_sizes.id[1], 1, 0) - 1];
    c4_b_singlePack[2] = c4_b_packets_data.data[(int8_T)
      _SFD_EML_ARRAY_BOUNDS_CHECK("packets.data", (int32_T)c4_b_itt, 1,
      c4_b_packets_elems_sizes.data[0] * c4_b_packets_elems_sizes.data[1], 1, 0)
      - 1];
    c4_b_singlePack[3] = c4_b_packets_data.c0[(int8_T)
      _SFD_EML_ARRAY_BOUNDS_CHECK("packets.c0", (int32_T)c4_b_itt, 1,
      c4_b_packets_elems_sizes.c0[0] * c4_b_packets_elems_sizes.c0[1], 1, 0) - 1];
    c4_b_singlePack[4] = c4_b_packets_data.c1[(int8_T)
      _SFD_EML_ARRAY_BOUNDS_CHECK("packets.c1", (int32_T)c4_b_itt, 1,
      c4_b_packets_elems_sizes.c1[0] * c4_b_packets_elems_sizes.c1[1], 1, 0) - 1];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, -12);
  _SFD_SYMBOL_SCOPE_POP();
  for (c4_i15 = 0; c4_i15 < 5; c4_i15++) {
    (*chartInstance->c4_singlePack)[c4_i15] = c4_b_singlePack[c4_i15];
  }

  *chartInstance->c4_terminate = c4_b_terminate;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_read_uartMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c4_i16 = 0; c4_i16 < 5; c4_i16++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c4_singlePack)[c4_i16], 2U);
  }

  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c4_terminate, 3U);
}

static void mdl_start_c4_read_uart(SFc4_read_uartInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void initSimStructsc4_read_uart(SFc4_read_uartInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber, uint32_T c4_instanceNumber)
{
  (void)c4_machineNumber;
  (void)c4_chartNumber;
  (void)c4_instanceNumber;
}

static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  boolean_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc4_read_uartInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(boolean_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static boolean_T c4_emlrt_marshallIn(SFc4_read_uartInstanceStruct *chartInstance,
  const mxArray *c4_b_terminate, const char_T *c4_identifier)
{
  boolean_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_terminate),
    &c4_thisId);
  sf_mex_destroy(&c4_b_terminate);
  return c4_y;
}

static boolean_T c4_b_emlrt_marshallIn(SFc4_read_uartInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  boolean_T c4_y;
  boolean_T c4_b0;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_b0, 1, 11, 0U, 0, 0U, 0);
  c4_y = c4_b0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_terminate;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  boolean_T c4_y;
  SFc4_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc4_read_uartInstanceStruct *)chartInstanceVoid;
  c4_b_terminate = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_terminate),
    &c4_thisId);
  sf_mex_destroy(&c4_b_terminate);
  *(boolean_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i17;
  uint8_T c4_b_inData[5];
  int32_T c4_i18;
  uint8_T c4_u[5];
  const mxArray *c4_y = NULL;
  SFc4_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc4_read_uartInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i17 = 0; c4_i17 < 5; c4_i17++) {
    c4_b_inData[c4_i17] = (*(uint8_T (*)[5])c4_inData)[c4_i17];
  }

  for (c4_i18 = 0; c4_i18 < 5; c4_i18++) {
    c4_u[c4_i18] = c4_b_inData[c4_i18];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 3, 0U, 1U, 0U, 2, 5, 1), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static void c4_c_emlrt_marshallIn(SFc4_read_uartInstanceStruct *chartInstance,
  const mxArray *c4_b_singlePack, const char_T *c4_identifier, uint8_T c4_y[5])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_singlePack), &c4_thisId,
                        c4_y);
  sf_mex_destroy(&c4_b_singlePack);
}

static void c4_d_emlrt_marshallIn(SFc4_read_uartInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, uint8_T c4_y[5])
{
  uint8_T c4_uv1[5];
  int32_T c4_i19;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_uv1, 1, 3, 0U, 1, 0U, 2, 5, 1);
  for (c4_i19 = 0; c4_i19 < 5; c4_i19++) {
    c4_y[c4_i19] = c4_uv1[c4_i19];
  }

  sf_mex_destroy(&c4_u);
}

static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_singlePack;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  uint8_T c4_y[5];
  int32_T c4_i20;
  SFc4_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc4_read_uartInstanceStruct *)chartInstanceVoid;
  c4_b_singlePack = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_singlePack), &c4_thisId,
                        c4_y);
  sf_mex_destroy(&c4_b_singlePack);
  for (c4_i20 = 0; c4_i20 < 5; c4_i20++) {
    (*(uint8_T (*)[5])c4_outData)[c4_i20] = c4_y[c4_i20];
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int8_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc4_read_uartInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(int8_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 2, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, c4_PacketsBus
  *c4_inData_data, c4_PacketsBus_size *c4_inData_elems_sizes)
{
  const mxArray *c4_mxArrayOutData = NULL;
  c4_PacketsBus_size c4_u_elems_sizes;
  c4_PacketsBus c4_u_data;
  const mxArray *c4_y = NULL;
  int32_T c4_u_sizes[2];
  int32_T c4_u;
  int32_T c4_b_u;
  int32_T c4_loop_ub;
  int32_T c4_i21;
  uint8_T c4_b_u_data[255];
  const mxArray *c4_b_y = NULL;
  int32_T c4_b_u_sizes[2];
  int32_T c4_c_u;
  int32_T c4_d_u;
  int32_T c4_b_loop_ub;
  int32_T c4_i22;
  uint8_T c4_c_u_data[255];
  const mxArray *c4_c_y = NULL;
  int32_T c4_c_u_sizes[2];
  int32_T c4_e_u;
  int32_T c4_f_u;
  int32_T c4_c_loop_ub;
  int32_T c4_i23;
  uint8_T c4_d_u_data[255];
  const mxArray *c4_d_y = NULL;
  int32_T c4_d_u_sizes[2];
  int32_T c4_g_u;
  int32_T c4_h_u;
  int32_T c4_d_loop_ub;
  int32_T c4_i24;
  uint8_T c4_e_u_data[255];
  const mxArray *c4_e_y = NULL;
  int32_T c4_e_u_sizes[2];
  int32_T c4_i_u;
  int32_T c4_j_u;
  int32_T c4_e_loop_ub;
  int32_T c4_i25;
  uint8_T c4_f_u_data[255];
  const mxArray *c4_f_y = NULL;
  SFc4_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc4_read_uartInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u_elems_sizes = *c4_inData_elems_sizes;
  c4_u_data = *c4_inData_data;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c4_u_sizes[0] = c4_u_elems_sizes.cmd[0];
  c4_u_sizes[1] = c4_u_elems_sizes.cmd[1];
  c4_u = c4_u_sizes[0];
  c4_b_u = c4_u_sizes[1];
  c4_loop_ub = c4_u_elems_sizes.cmd[0] * c4_u_elems_sizes.cmd[1] - 1;
  for (c4_i21 = 0; c4_i21 <= c4_loop_ub; c4_i21++) {
    c4_b_u_data[c4_i21] = c4_u_data.cmd[c4_i21];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_b_u_data, 3, 0U, 1U, 0U, 2,
    c4_u_sizes[0], c4_u_sizes[1]), false);
  sf_mex_addfield(c4_y, c4_b_y, "cmd", "cmd", 0);
  c4_b_u_sizes[0] = c4_u_elems_sizes.id[0];
  c4_b_u_sizes[1] = c4_u_elems_sizes.id[1];
  c4_c_u = c4_b_u_sizes[0];
  c4_d_u = c4_b_u_sizes[1];
  c4_b_loop_ub = c4_u_elems_sizes.id[0] * c4_u_elems_sizes.id[1] - 1;
  for (c4_i22 = 0; c4_i22 <= c4_b_loop_ub; c4_i22++) {
    c4_c_u_data[c4_i22] = c4_u_data.id[c4_i22];
  }

  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", c4_c_u_data, 3, 0U, 1U, 0U, 2,
    c4_b_u_sizes[0], c4_b_u_sizes[1]), false);
  sf_mex_addfield(c4_y, c4_c_y, "id", "id", 0);
  c4_c_u_sizes[0] = c4_u_elems_sizes.data[0];
  c4_c_u_sizes[1] = c4_u_elems_sizes.data[1];
  c4_e_u = c4_c_u_sizes[0];
  c4_f_u = c4_c_u_sizes[1];
  c4_c_loop_ub = c4_u_elems_sizes.data[0] * c4_u_elems_sizes.data[1] - 1;
  for (c4_i23 = 0; c4_i23 <= c4_c_loop_ub; c4_i23++) {
    c4_d_u_data[c4_i23] = c4_u_data.data[c4_i23];
  }

  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", c4_d_u_data, 3, 0U, 1U, 0U, 2,
    c4_c_u_sizes[0], c4_c_u_sizes[1]), false);
  sf_mex_addfield(c4_y, c4_d_y, "data", "data", 0);
  c4_d_u_sizes[0] = c4_u_elems_sizes.c0[0];
  c4_d_u_sizes[1] = c4_u_elems_sizes.c0[1];
  c4_g_u = c4_d_u_sizes[0];
  c4_h_u = c4_d_u_sizes[1];
  c4_d_loop_ub = c4_u_elems_sizes.c0[0] * c4_u_elems_sizes.c0[1] - 1;
  for (c4_i24 = 0; c4_i24 <= c4_d_loop_ub; c4_i24++) {
    c4_e_u_data[c4_i24] = c4_u_data.c0[c4_i24];
  }

  c4_e_y = NULL;
  sf_mex_assign(&c4_e_y, sf_mex_create("y", c4_e_u_data, 3, 0U, 1U, 0U, 2,
    c4_d_u_sizes[0], c4_d_u_sizes[1]), false);
  sf_mex_addfield(c4_y, c4_e_y, "c0", "c0", 0);
  c4_e_u_sizes[0] = c4_u_elems_sizes.c1[0];
  c4_e_u_sizes[1] = c4_u_elems_sizes.c1[1];
  c4_i_u = c4_e_u_sizes[0];
  c4_j_u = c4_e_u_sizes[1];
  c4_e_loop_ub = c4_u_elems_sizes.c1[0] * c4_u_elems_sizes.c1[1] - 1;
  for (c4_i25 = 0; c4_i25 <= c4_e_loop_ub; c4_i25++) {
    c4_f_u_data[c4_i25] = c4_u_data.c1[c4_i25];
  }

  c4_f_y = NULL;
  sf_mex_assign(&c4_f_y, sf_mex_create("y", c4_f_u_data, 3, 0U, 1U, 0U, 2,
    c4_e_u_sizes[0], c4_e_u_sizes[1]), false);
  sf_mex_addfield(c4_y, c4_f_y, "c1", "c1", 0);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static const mxArray *c4_e_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc4_read_uartInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static real_T c4_e_emlrt_marshallIn(SFc4_read_uartInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d1;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d1, 1, 0, 0U, 0, 0U, 0);
  c4_y = c4_d1;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_nargout;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc4_read_uartInstanceStruct *)chartInstanceVoid;
  c4_nargout = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_nargout), &c4_thisId);
  sf_mex_destroy(&c4_nargout);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

const mxArray *sf_c4_read_uart_get_eml_resolved_functions_info(void)
{
  const mxArray *c4_nameCaptureInfo = NULL;
  c4_nameCaptureInfo = NULL;
  sf_mex_assign(&c4_nameCaptureInfo, sf_mex_createstruct("structure", 2, 7, 1),
                false);
  c4_info_helper(&c4_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c4_nameCaptureInfo);
  return c4_nameCaptureInfo;
}

static void c4_info_helper(const mxArray **c4_info)
{
  const mxArray *c4_rhs0 = NULL;
  const mxArray *c4_lhs0 = NULL;
  const mxArray *c4_rhs1 = NULL;
  const mxArray *c4_lhs1 = NULL;
  const mxArray *c4_rhs2 = NULL;
  const mxArray *c4_lhs2 = NULL;
  const mxArray *c4_rhs3 = NULL;
  const mxArray *c4_lhs3 = NULL;
  const mxArray *c4_rhs4 = NULL;
  const mxArray *c4_lhs4 = NULL;
  const mxArray *c4_rhs5 = NULL;
  const mxArray *c4_lhs5 = NULL;
  const mxArray *c4_rhs6 = NULL;
  const mxArray *c4_lhs6 = NULL;
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("length"), "name", "name", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("uint8"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1303149806U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c4_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m!intlength"),
                  "context", "context", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1323174178U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c4_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m!intlength"),
                  "context", "context", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexIntRelop"),
                  "name", "name", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1326731922U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c4_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!apply_float_relop"),
                  "context", "context", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1393334458U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c4_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!float_class_contains_indexIntClass"),
                  "context", "context", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1326731596U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c4_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!is_signed_indexIntClass"),
                  "context", "context", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("intmin"), "name", "name", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1362265482U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c4_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 6);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1393334458U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c4_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs6), "lhs", "lhs", 6);
  sf_mex_destroy(&c4_rhs0);
  sf_mex_destroy(&c4_lhs0);
  sf_mex_destroy(&c4_rhs1);
  sf_mex_destroy(&c4_lhs1);
  sf_mex_destroy(&c4_rhs2);
  sf_mex_destroy(&c4_lhs2);
  sf_mex_destroy(&c4_rhs3);
  sf_mex_destroy(&c4_lhs3);
  sf_mex_destroy(&c4_rhs4);
  sf_mex_destroy(&c4_lhs4);
  sf_mex_destroy(&c4_rhs5);
  sf_mex_destroy(&c4_lhs5);
  sf_mex_destroy(&c4_rhs6);
  sf_mex_destroy(&c4_lhs6);
}

static const mxArray *c4_emlrt_marshallOut(const char * c4_u)
{
  const mxArray *c4_y = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c4_u)), false);
  return c4_y;
}

static const mxArray *c4_b_emlrt_marshallOut(const uint32_T c4_u)
{
  const mxArray *c4_y = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 7, 0U, 0U, 0U, 0), false);
  return c4_y;
}

static int32_T c4_intlength(SFc4_read_uartInstanceStruct *chartInstance, uint8_T
  c4_x_data[], int32_T c4_x_sizes[2])
{
  int32_T c4_n;
  real_T c4_a;
  real_T c4_b_a;
  real_T c4_flt;
  boolean_T c4_p;
  real_T c4_c_a;
  real_T c4_d_a;
  real_T c4_b_flt;
  boolean_T c4_b_p;
  boolean_T guard1 = false;
  (void)chartInstance;
  (void)c4_x_data;
  c4_a = (real_T)c4_x_sizes[0];
  c4_b_a = c4_a;
  c4_flt = c4_b_a;
  c4_p = (0.0 == c4_flt);
  guard1 = false;
  if (c4_p) {
    guard1 = true;
  } else {
    c4_c_a = (real_T)c4_x_sizes[1];
    c4_d_a = c4_c_a;
    c4_b_flt = c4_d_a;
    c4_b_p = (0.0 == c4_b_flt);
    if (c4_b_p) {
      guard1 = true;
    } else if ((real_T)c4_x_sizes[0] > (real_T)c4_x_sizes[1]) {
      c4_n = c4_x_sizes[0];
    } else {
      c4_n = c4_x_sizes[1];
    }
  }

  if (guard1 == true) {
    c4_n = 0;
  }

  return c4_n;
}

static const mxArray *c4_f_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc4_read_uartInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(int32_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static int32_T c4_f_emlrt_marshallIn(SFc4_read_uartInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int32_T c4_y;
  int32_T c4_i26;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_i26, 1, 6, 0U, 0, 0U, 0);
  c4_y = c4_i26;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_sfEvent;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int32_T c4_y;
  SFc4_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc4_read_uartInstanceStruct *)chartInstanceVoid;
  c4_b_sfEvent = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_sfEvent),
    &c4_thisId);
  sf_mex_destroy(&c4_b_sfEvent);
  *(int32_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_packets_bus_io(void *chartInstanceVoid, void *c4_pData)
{
  const mxArray *c4_mxVal = NULL;
  SFc4_read_uartInstanceStruct *chartInstance;
  (void)c4_pData;
  chartInstance = (SFc4_read_uartInstanceStruct *)chartInstanceVoid;
  c4_mxVal = NULL;
  sf_mex_assign(&c4_mxVal, c4_sf_marshall_unsupported(chartInstance), false);
  return c4_mxVal;
}

static const mxArray *c4_sf_marshall_unsupported(void *chartInstanceVoid)
{
  const mxArray *c4_y = NULL;
  SFc4_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc4_read_uartInstanceStruct *)chartInstanceVoid;
  c4_y = NULL;
  sf_mex_assign(&c4_y, c4_c_emlrt_marshallOut(chartInstance,
    "Structures with variable-sized fields unsupported for debugging."), false);
  return c4_y;
}

static const mxArray *c4_c_emlrt_marshallOut(SFc4_read_uartInstanceStruct
  *chartInstance, const char * c4_u)
{
  const mxArray *c4_y = NULL;
  (void)chartInstance;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c4_u)), false);
  return c4_y;
}

static uint8_T c4_g_emlrt_marshallIn(SFc4_read_uartInstanceStruct *chartInstance,
  const mxArray *c4_b_is_active_c4_read_uart, const char_T *c4_identifier)
{
  uint8_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c4_b_is_active_c4_read_uart), &c4_thisId);
  sf_mex_destroy(&c4_b_is_active_c4_read_uart);
  return c4_y;
}

static uint8_T c4_h_emlrt_marshallIn(SFc4_read_uartInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  uint8_T c4_u0;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_u0, 1, 3, 0U, 0, 0U, 0);
  c4_y = c4_u0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void init_dsm_address_info(SFc4_read_uartInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc4_read_uartInstanceStruct *chartInstance)
{
  chartInstance->c4_packets_data = (c4_PacketsBus *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c4_packets_elems_sizes = (c4_PacketsBus_size *)
    ssGetCurrentInputPortDimensions_wrapper(chartInstance->S, 0);
  chartInstance->c4_itt = (int8_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c4_singlePack = (uint8_T (*)[5])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c4_terminate = (boolean_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
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

void sf_c4_read_uart_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(539258620U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2246818199U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(172949602U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2139344218U);
}

mxArray* sf_c4_read_uart_get_post_codegen_info(void);
mxArray *sf_c4_read_uart_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("pVxotXBYUvxth7DrQOgllG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(13));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(4));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c4_read_uart_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c4_read_uart_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c4_read_uart_jit_fallback_info(void)
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

mxArray *sf_c4_read_uart_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c4_read_uart_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c4_read_uart(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"singlePack\",},{M[1],M[7],T\"terminate\",},{M[8],M[0],T\"is_active_c4_read_uart\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c4_read_uart_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc4_read_uartInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc4_read_uartInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _read_uartMachineNumber_,
           4,
           1,
           1,
           0,
           4,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"packets");
          _SFD_SET_DATA_PROPS(1,1,1,0,"itt");
          _SFD_SET_DATA_PROPS(2,2,0,1,"singlePack");
          _SFD_SET_DATA_PROPS(3,2,0,1,"terminate");
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
        _SFD_CV_INIT_EML(0,1,1,2,0,0,0,0,0,1,1);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,338);
        _SFD_CV_INIT_EML_IF(0,1,0,124,152,198,337);
        _SFD_CV_INIT_EML_IF(0,1,1,198,227,-1,337);

        {
          static int condStart[] = { 202 };

          static int condEnd[] = { 227 };

          static int pfixExpr[] = { 0, -1 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,201,227,1,0,&(condStart[0]),&(condEnd[0]),
                                2,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML_RELATIONAL(0,1,0,127,152,-1,2);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_packets_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_INT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 5;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)
            c4_b_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(3,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)c4_sf_marshallIn);
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c4_packets_data);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c4_itt);
        _SFD_SET_DATA_VALUE_PTR(2U, *chartInstance->c4_singlePack);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c4_terminate);
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
  return "OHgJoa7qZzS5uRdmWbR49C";
}

static void sf_opaque_initialize_c4_read_uart(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc4_read_uartInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c4_read_uart((SFc4_read_uartInstanceStruct*)
    chartInstanceVar);
  initialize_c4_read_uart((SFc4_read_uartInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c4_read_uart(void *chartInstanceVar)
{
  enable_c4_read_uart((SFc4_read_uartInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c4_read_uart(void *chartInstanceVar)
{
  disable_c4_read_uart((SFc4_read_uartInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c4_read_uart(void *chartInstanceVar)
{
  sf_gateway_c4_read_uart((SFc4_read_uartInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c4_read_uart(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c4_read_uart((SFc4_read_uartInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c4_read_uart(SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c4_read_uart((SFc4_read_uartInstanceStruct*)
    chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c4_read_uart(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc4_read_uartInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_read_uart_optimization_info();
    }

    finalize_c4_read_uart((SFc4_read_uartInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc4_read_uart((SFc4_read_uartInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c4_read_uart(SimStruct *S)
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
    initialize_params_c4_read_uart((SFc4_read_uartInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c4_read_uart(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_read_uart_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,4);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,4,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,4,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,4);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,4,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,4,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,4);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(964168457U));
  ssSetChecksum1(S,(3580404329U));
  ssSetChecksum2(S,(2602307481U));
  ssSetChecksum3(S,(3697751240U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c4_read_uart(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c4_read_uart(SimStruct *S)
{
  SFc4_read_uartInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc4_read_uartInstanceStruct *)utMalloc(sizeof
    (SFc4_read_uartInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc4_read_uartInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c4_read_uart;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c4_read_uart;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c4_read_uart;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c4_read_uart;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c4_read_uart;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c4_read_uart;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c4_read_uart;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c4_read_uart;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c4_read_uart;
  chartInstance->chartInfo.mdlStart = mdlStart_c4_read_uart;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c4_read_uart;
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

void c4_read_uart_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c4_read_uart(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c4_read_uart(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c4_read_uart(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c4_read_uart_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
