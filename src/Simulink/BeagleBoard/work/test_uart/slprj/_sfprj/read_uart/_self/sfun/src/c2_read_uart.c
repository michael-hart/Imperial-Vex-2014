/* Include files */

#include <stddef.h>
#include "blas.h"
#include "read_uart_sfun.h"
#include "c2_read_uart.h"
#include "mwmathutil.h"
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
static const char * c2_debug_family_names[9] = { "current_buffer", "rows",
  "index", "nargin", "nargout", "u", "y", "buffer", "buf_len" };

/* Function Declarations */
static void initialize_c2_read_uart(SFc2_read_uartInstanceStruct *chartInstance);
static void initialize_params_c2_read_uart(SFc2_read_uartInstanceStruct
  *chartInstance);
static void enable_c2_read_uart(SFc2_read_uartInstanceStruct *chartInstance);
static void disable_c2_read_uart(SFc2_read_uartInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_read_uart(SFc2_read_uartInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_read_uart(SFc2_read_uartInstanceStruct
  *chartInstance);
static void set_sim_state_c2_read_uart(SFc2_read_uartInstanceStruct
  *chartInstance, const mxArray *c2_st);
static void finalize_c2_read_uart(SFc2_read_uartInstanceStruct *chartInstance);
static void sf_gateway_c2_read_uart(SFc2_read_uartInstanceStruct *chartInstance);
static void mdl_start_c2_read_uart(SFc2_read_uartInstanceStruct *chartInstance);
static void c2_chartstep_c2_read_uart(SFc2_read_uartInstanceStruct
  *chartInstance);
static void initSimStructsc2_read_uart(SFc2_read_uartInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static real_T c2_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_buf_len, const char_T *c2_identifier);
static real_T c2_b_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_c_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_buffer, const char_T *c2_identifier, uint8_T c2_y[4]);
static void c2_d_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, uint8_T c2_y[4]);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, c2_PacketsBus
  *c2_inData_data, c2_PacketsBus_size *c2_inData_elems_sizes);
static void c2_e_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_y, const char_T *c2_identifier, c2_PacketsBus *c2_b_y_data,
  c2_PacketsBus_size *c2_b_y_elems_sizes);
static void c2_f_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, c2_PacketsBus
  *c2_b_y_data, c2_PacketsBus_size *c2_b_y_elems_sizes);
static void c2_g_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, uint8_T
  c2_b_y_data[], int32_T c2_y_sizes[2]);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, c2_PacketsBus *c2_outData_data,
  c2_PacketsBus_size *c2_outData_elems_sizes);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_h_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, uint8_T
  c2_inData_data[], int32_T c2_inData_sizes[2]);
static void c2_i_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, uint8_T
  c2_b_y_data[], int32_T c2_y_sizes[2]);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, uint8_T c2_outData_data[],
  int32_T c2_outData_sizes[2]);
static void c2_info_helper(const mxArray **c2_info);
static const mxArray *c2_emlrt_marshallOut(const char * c2_b_u);
static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_b_u);
static int32_T c2_intlength(SFc2_read_uartInstanceStruct *chartInstance, uint8_T
  c2_x_data[], int32_T c2_x_sizes[2]);
static real_T c2_floor(SFc2_read_uartInstanceStruct *chartInstance, real_T c2_x);
static real_T c2_mod(SFc2_read_uartInstanceStruct *chartInstance, real_T c2_x,
                     real_T c2_y);
static void c2_eml_scalar_eg(SFc2_read_uartInstanceStruct *chartInstance);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_j_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_y_bus_io(void *chartInstanceVoid, void *c2_pData);
static const mxArray *c2_sf_marshall_unsupported(void *chartInstanceVoid);
static const mxArray *c2_c_emlrt_marshallOut(SFc2_read_uartInstanceStruct
  *chartInstance, const char * c2_b_u);
static uint8_T c2_k_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_read_uart, const char_T *c2_identifier);
static uint8_T c2_l_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_floor(SFc2_read_uartInstanceStruct *chartInstance, real_T *c2_x);
static void init_dsm_address_info(SFc2_read_uartInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc2_read_uartInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_read_uart(SFc2_read_uartInstanceStruct *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_buffer_not_empty = false;
  chartInstance->c2_buf_len_not_empty = false;
  chartInstance->c2_is_active_c2_read_uart = 0U;
}

static void initialize_params_c2_read_uart(SFc2_read_uartInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c2_read_uart(SFc2_read_uartInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_read_uart(SFc2_read_uartInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_read_uart(SFc2_read_uartInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_read_uart(SFc2_read_uartInstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  const mxArray *c2_b_y = NULL;
  int32_T c2_u_sizes[2];
  int32_T c2_b_u;
  int32_T c2_c_u;
  int32_T c2_loop_ub;
  int32_T c2_i0;
  uint8_T c2_u_data[255];
  const mxArray *c2_c_y = NULL;
  int32_T c2_b_u_sizes[2];
  int32_T c2_d_u;
  int32_T c2_e_u;
  int32_T c2_b_loop_ub;
  int32_T c2_i1;
  uint8_T c2_b_u_data[255];
  const mxArray *c2_d_y = NULL;
  int32_T c2_c_u_sizes[2];
  int32_T c2_f_u;
  int32_T c2_g_u;
  int32_T c2_c_loop_ub;
  int32_T c2_i2;
  uint8_T c2_c_u_data[255];
  const mxArray *c2_e_y = NULL;
  int32_T c2_d_u_sizes[2];
  int32_T c2_h_u;
  int32_T c2_i_u;
  int32_T c2_d_loop_ub;
  int32_T c2_i3;
  uint8_T c2_d_u_data[255];
  const mxArray *c2_f_y = NULL;
  int32_T c2_e_u_sizes[2];
  int32_T c2_j_u;
  int32_T c2_k_u;
  int32_T c2_e_loop_ub;
  int32_T c2_i4;
  uint8_T c2_e_u_data[255];
  const mxArray *c2_g_y = NULL;
  real_T c2_hoistedGlobal;
  real_T c2_l_u;
  const mxArray *c2_h_y = NULL;
  int32_T c2_i5;
  uint8_T c2_m_u[4];
  const mxArray *c2_i_y = NULL;
  uint8_T c2_b_hoistedGlobal;
  uint8_T c2_n_u;
  const mxArray *c2_j_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(4, 1), false);
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c2_u_sizes[0] = chartInstance->c2_y_elems_sizes->cmd[0];
  c2_u_sizes[1] = chartInstance->c2_y_elems_sizes->cmd[1];
  c2_b_u = c2_u_sizes[0];
  c2_c_u = c2_u_sizes[1];
  c2_loop_ub = chartInstance->c2_y_elems_sizes->cmd[0] *
    chartInstance->c2_y_elems_sizes->cmd[1] - 1;
  for (c2_i0 = 0; c2_i0 <= c2_loop_ub; c2_i0++) {
    c2_u_data[c2_i0] = ((uint8_T *)&((char_T *)chartInstance->c2_y_data)[0])
      [c2_i0];
  }

  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_u_data, 3, 0U, 1U, 0U, 2,
    c2_u_sizes[0], c2_u_sizes[1]), false);
  sf_mex_addfield(c2_b_y, c2_c_y, "cmd", "cmd", 0);
  c2_b_u_sizes[0] = chartInstance->c2_y_elems_sizes->id[0];
  c2_b_u_sizes[1] = chartInstance->c2_y_elems_sizes->id[1];
  c2_d_u = c2_b_u_sizes[0];
  c2_e_u = c2_b_u_sizes[1];
  c2_b_loop_ub = chartInstance->c2_y_elems_sizes->id[0] *
    chartInstance->c2_y_elems_sizes->id[1] - 1;
  for (c2_i1 = 0; c2_i1 <= c2_b_loop_ub; c2_i1++) {
    c2_b_u_data[c2_i1] = ((uint8_T *)&((char_T *)chartInstance->c2_y_data)[255])
      [c2_i1];
  }

  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_b_u_data, 3, 0U, 1U, 0U, 2,
    c2_b_u_sizes[0], c2_b_u_sizes[1]), false);
  sf_mex_addfield(c2_b_y, c2_d_y, "id", "id", 0);
  c2_c_u_sizes[0] = chartInstance->c2_y_elems_sizes->data[0];
  c2_c_u_sizes[1] = chartInstance->c2_y_elems_sizes->data[1];
  c2_f_u = c2_c_u_sizes[0];
  c2_g_u = c2_c_u_sizes[1];
  c2_c_loop_ub = chartInstance->c2_y_elems_sizes->data[0] *
    chartInstance->c2_y_elems_sizes->data[1] - 1;
  for (c2_i2 = 0; c2_i2 <= c2_c_loop_ub; c2_i2++) {
    c2_c_u_data[c2_i2] = ((uint8_T *)&((char_T *)chartInstance->c2_y_data)[510])
      [c2_i2];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_c_u_data, 3, 0U, 1U, 0U, 2,
    c2_c_u_sizes[0], c2_c_u_sizes[1]), false);
  sf_mex_addfield(c2_b_y, c2_e_y, "data", "data", 0);
  c2_d_u_sizes[0] = chartInstance->c2_y_elems_sizes->c0[0];
  c2_d_u_sizes[1] = chartInstance->c2_y_elems_sizes->c0[1];
  c2_h_u = c2_d_u_sizes[0];
  c2_i_u = c2_d_u_sizes[1];
  c2_d_loop_ub = chartInstance->c2_y_elems_sizes->c0[0] *
    chartInstance->c2_y_elems_sizes->c0[1] - 1;
  for (c2_i3 = 0; c2_i3 <= c2_d_loop_ub; c2_i3++) {
    c2_d_u_data[c2_i3] = ((uint8_T *)&((char_T *)chartInstance->c2_y_data)[765])
      [c2_i3];
  }

  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", c2_d_u_data, 3, 0U, 1U, 0U, 2,
    c2_d_u_sizes[0], c2_d_u_sizes[1]), false);
  sf_mex_addfield(c2_b_y, c2_f_y, "c0", "c0", 0);
  c2_e_u_sizes[0] = chartInstance->c2_y_elems_sizes->c1[0];
  c2_e_u_sizes[1] = chartInstance->c2_y_elems_sizes->c1[1];
  c2_j_u = c2_e_u_sizes[0];
  c2_k_u = c2_e_u_sizes[1];
  c2_e_loop_ub = chartInstance->c2_y_elems_sizes->c1[0] *
    chartInstance->c2_y_elems_sizes->c1[1] - 1;
  for (c2_i4 = 0; c2_i4 <= c2_e_loop_ub; c2_i4++) {
    c2_e_u_data[c2_i4] = ((uint8_T *)&((char_T *)chartInstance->c2_y_data)[1020])
      [c2_i4];
  }

  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", c2_e_u_data, 3, 0U, 1U, 0U, 2,
    c2_e_u_sizes[0], c2_e_u_sizes[1]), false);
  sf_mex_addfield(c2_b_y, c2_g_y, "c1", "c1", 0);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_hoistedGlobal = chartInstance->c2_buf_len;
  c2_l_u = c2_hoistedGlobal;
  c2_h_y = NULL;
  if (!chartInstance->c2_buf_len_not_empty) {
    sf_mex_assign(&c2_h_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_h_y, sf_mex_create("y", &c2_l_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c2_y, 1, c2_h_y);
  for (c2_i5 = 0; c2_i5 < 4; c2_i5++) {
    c2_m_u[c2_i5] = chartInstance->c2_buffer[c2_i5];
  }

  c2_i_y = NULL;
  if (!chartInstance->c2_buffer_not_empty) {
    sf_mex_assign(&c2_i_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_i_y, sf_mex_create("y", c2_m_u, 3, 0U, 1U, 0U, 1, 4),
                  false);
  }

  sf_mex_setcell(c2_y, 2, c2_i_y);
  c2_b_hoistedGlobal = chartInstance->c2_is_active_c2_read_uart;
  c2_n_u = c2_b_hoistedGlobal;
  c2_j_y = NULL;
  sf_mex_assign(&c2_j_y, sf_mex_create("y", &c2_n_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 3, c2_j_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_read_uart(SFc2_read_uartInstanceStruct
  *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_b_u;
  c2_PacketsBus_size c2_tmp_elems_sizes;
  c2_PacketsBus c2_tmp_data;
  int32_T c2_loop_ub;
  int32_T c2_i6;
  int32_T c2_b_loop_ub;
  int32_T c2_i7;
  int32_T c2_c_loop_ub;
  int32_T c2_i8;
  int32_T c2_d_loop_ub;
  int32_T c2_i9;
  int32_T c2_e_loop_ub;
  int32_T c2_i10;
  int32_T c2_f_loop_ub;
  int32_T c2_i11;
  int32_T c2_g_loop_ub;
  int32_T c2_i12;
  int32_T c2_h_loop_ub;
  int32_T c2_i13;
  int32_T c2_i_loop_ub;
  int32_T c2_i14;
  int32_T c2_j_loop_ub;
  int32_T c2_i15;
  uint8_T c2_uv0[4];
  int32_T c2_i16;
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_b_u = sf_mex_dup(c2_st);
  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_b_u, 0)),
                        "y", &c2_tmp_data, &c2_tmp_elems_sizes);
  chartInstance->c2_y_elems_sizes->cmd[0] = c2_tmp_elems_sizes.cmd[0];
  chartInstance->c2_y_elems_sizes->cmd[1] = c2_tmp_elems_sizes.cmd[1];
  c2_loop_ub = c2_tmp_elems_sizes.cmd[1] - 1;
  for (c2_i6 = 0; c2_i6 <= c2_loop_ub; c2_i6++) {
    c2_b_loop_ub = c2_tmp_elems_sizes.cmd[0] - 1;
    for (c2_i7 = 0; c2_i7 <= c2_b_loop_ub; c2_i7++) {
      ((uint8_T *)&((char_T *)chartInstance->c2_y_data)[0])[c2_i7 +
        chartInstance->c2_y_elems_sizes->cmd[0] * c2_i6] = c2_tmp_data.cmd[c2_i7
        + c2_tmp_elems_sizes.cmd[0] * c2_i6];
    }
  }

  chartInstance->c2_y_elems_sizes->id[0] = c2_tmp_elems_sizes.id[0];
  chartInstance->c2_y_elems_sizes->id[1] = c2_tmp_elems_sizes.id[1];
  c2_c_loop_ub = c2_tmp_elems_sizes.id[1] - 1;
  for (c2_i8 = 0; c2_i8 <= c2_c_loop_ub; c2_i8++) {
    c2_d_loop_ub = c2_tmp_elems_sizes.id[0] - 1;
    for (c2_i9 = 0; c2_i9 <= c2_d_loop_ub; c2_i9++) {
      ((uint8_T *)&((char_T *)chartInstance->c2_y_data)[255])[c2_i9 +
        chartInstance->c2_y_elems_sizes->id[0] * c2_i8] = c2_tmp_data.id[c2_i9 +
        c2_tmp_elems_sizes.id[0] * c2_i8];
    }
  }

  chartInstance->c2_y_elems_sizes->data[0] = c2_tmp_elems_sizes.data[0];
  chartInstance->c2_y_elems_sizes->data[1] = c2_tmp_elems_sizes.data[1];
  c2_e_loop_ub = c2_tmp_elems_sizes.data[1] - 1;
  for (c2_i10 = 0; c2_i10 <= c2_e_loop_ub; c2_i10++) {
    c2_f_loop_ub = c2_tmp_elems_sizes.data[0] - 1;
    for (c2_i11 = 0; c2_i11 <= c2_f_loop_ub; c2_i11++) {
      ((uint8_T *)&((char_T *)chartInstance->c2_y_data)[510])[c2_i11 +
        chartInstance->c2_y_elems_sizes->data[0] * c2_i10] =
        c2_tmp_data.data[c2_i11 + c2_tmp_elems_sizes.data[0] * c2_i10];
    }
  }

  chartInstance->c2_y_elems_sizes->c0[0] = c2_tmp_elems_sizes.c0[0];
  chartInstance->c2_y_elems_sizes->c0[1] = c2_tmp_elems_sizes.c0[1];
  c2_g_loop_ub = c2_tmp_elems_sizes.c0[1] - 1;
  for (c2_i12 = 0; c2_i12 <= c2_g_loop_ub; c2_i12++) {
    c2_h_loop_ub = c2_tmp_elems_sizes.c0[0] - 1;
    for (c2_i13 = 0; c2_i13 <= c2_h_loop_ub; c2_i13++) {
      ((uint8_T *)&((char_T *)chartInstance->c2_y_data)[765])[c2_i13 +
        chartInstance->c2_y_elems_sizes->c0[0] * c2_i12] = c2_tmp_data.c0[c2_i13
        + c2_tmp_elems_sizes.c0[0] * c2_i12];
    }
  }

  chartInstance->c2_y_elems_sizes->c1[0] = c2_tmp_elems_sizes.c1[0];
  chartInstance->c2_y_elems_sizes->c1[1] = c2_tmp_elems_sizes.c1[1];
  c2_i_loop_ub = c2_tmp_elems_sizes.c1[1] - 1;
  for (c2_i14 = 0; c2_i14 <= c2_i_loop_ub; c2_i14++) {
    c2_j_loop_ub = c2_tmp_elems_sizes.c1[0] - 1;
    for (c2_i15 = 0; c2_i15 <= c2_j_loop_ub; c2_i15++) {
      ((uint8_T *)&((char_T *)chartInstance->c2_y_data)[1020])[c2_i15 +
        chartInstance->c2_y_elems_sizes->c1[0] * c2_i14] = c2_tmp_data.c1[c2_i15
        + c2_tmp_elems_sizes.c1[0] * c2_i14];
    }
  }

  chartInstance->c2_buf_len = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_b_u, 1)), "buf_len");
  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_b_u, 2)),
                        "buffer", c2_uv0);
  for (c2_i16 = 0; c2_i16 < 4; c2_i16++) {
    chartInstance->c2_buffer[c2_i16] = c2_uv0[c2_i16];
  }

  chartInstance->c2_is_active_c2_read_uart = c2_k_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_b_u, 3)), "is_active_c2_read_uart");
  sf_mex_destroy(&c2_b_u);
  c2_update_debugger_state_c2_read_uart(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_read_uart(SFc2_read_uartInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c2_read_uart(SFc2_read_uartInstanceStruct *chartInstance)
{
  int32_T c2_i17;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  for (c2_i17 = 0; c2_i17 < 255; c2_i17++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c2_u)[c2_i17], 0U);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_read_uart(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_read_uartMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c2_read_uart(SFc2_read_uartInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_chartstep_c2_read_uart(SFc2_read_uartInstanceStruct
  *chartInstance)
{
  int32_T c2_i18;
  uint8_T c2_b_u[255];
  uint32_T c2_debug_family_var_map[9];
  int32_T c2_current_buffer_sizes[2];
  real_T c2_rows;
  real_T c2_index;
  real_T c2_nargin = 1.0;
  real_T c2_nargout = 1.0;
  c2_PacketsBus_size c2_b_y_elems_sizes;
  c2_PacketsBus c2_b_y_data;
  int32_T c2_i19;
  boolean_T c2_b0;
  boolean_T c2_b1;
  boolean_T c2_b2;
  int32_T c2_i20;
  int32_T c2_tmp_sizes[2];
  int32_T c2_loop_ub;
  int32_T c2_i21;
  uint8_T c2_tmp_data[4];
  int32_T c2_b_tmp_sizes;
  int32_T c2_b_loop_ub;
  int32_T c2_i22;
  uint8_T c2_b_tmp_data[4];
  int32_T c2_iv0[2];
  int32_T c2_c_tmp_sizes[2];
  int32_T c2_i23;
  int32_T c2_i24;
  int32_T c2_c_loop_ub;
  int32_T c2_i25;
  uint8_T c2_c_tmp_data[4];
  int32_T c2_d_loop_ub;
  int32_T c2_i26;
  uint8_T c2_uv1[256];
  int32_T c2_i27;
  int32_T c2_current_buffer;
  int32_T c2_b_current_buffer;
  int32_T c2_i28;
  int32_T c2_c_current_buffer;
  int32_T c2_d_current_buffer;
  int32_T c2_i29;
  int32_T c2_x_sizes[2];
  int32_T c2_x;
  int32_T c2_b_x;
  int32_T c2_e_loop_ub;
  int32_T c2_i30;
  uint8_T c2_x_data[65280];
  int32_T c2_b_x_sizes[2];
  int32_T c2_c_x;
  int32_T c2_d_x;
  int32_T c2_f_loop_ub;
  int32_T c2_i31;
  uint8_T c2_b_x_data[65280];
  real_T c2_n;
  real_T c2_A;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_g_x;
  real_T c2_y;
  real_T c2_d0;
  int32_T c2_d_tmp_sizes;
  int32_T c2_g_loop_ub;
  int32_T c2_i32;
  uint8_T c2_d_tmp_data[6];
  int32_T c2_iv1[2];
  int32_T c2_iv2[2];
  int32_T c2_b_y;
  int32_T c2_c_y;
  int32_T c2_h_loop_ub;
  int32_T c2_i33;
  int32_T c2_i_loop_ub;
  int32_T c2_i34;
  int32_T c2_iv3[2];
  int32_T c2_iv4[2];
  int32_T c2_d_y;
  int32_T c2_e_y;
  int32_T c2_j_loop_ub;
  int32_T c2_i35;
  int32_T c2_k_loop_ub;
  int32_T c2_i36;
  int32_T c2_iv5[2];
  int32_T c2_iv6[2];
  int32_T c2_f_y;
  int32_T c2_g_y;
  int32_T c2_l_loop_ub;
  int32_T c2_i37;
  int32_T c2_m_loop_ub;
  int32_T c2_i38;
  int32_T c2_iv7[2];
  int32_T c2_iv8[2];
  int32_T c2_h_y;
  int32_T c2_i_y;
  int32_T c2_n_loop_ub;
  int32_T c2_i39;
  int32_T c2_o_loop_ub;
  int32_T c2_i40;
  int32_T c2_iv9[2];
  int32_T c2_iv10[2];
  int32_T c2_j_y;
  int32_T c2_k_y;
  int32_T c2_p_loop_ub;
  int32_T c2_i41;
  real_T c2_b_rows;
  int32_T c2_i42;
  int32_T c2_b_index;
  int32_T c2_h_x;
  int32_T c2_i_x;
  int32_T c2_q_loop_ub;
  int32_T c2_i43;
  int32_T c2_c_x_sizes[2];
  int32_T c2_j_x;
  int32_T c2_k_x;
  int32_T c2_r_loop_ub;
  int32_T c2_i44;
  uint8_T c2_c_x_data[65280];
  real_T c2_b_n;
  real_T c2_d1;
  boolean_T c2_b3;
  boolean_T c2_b4;
  boolean_T c2_b5;
  int32_T c2_i45;
  int32_T c2_i46;
  boolean_T c2_b6;
  boolean_T c2_b7;
  boolean_T c2_b8;
  int32_T c2_i47;
  int32_T c2_e_tmp_sizes;
  int32_T c2_s_loop_ub;
  int32_T c2_i48;
  int32_T c2_e_tmp_data[4];
  int32_T c2_f_tmp_sizes[2];
  int32_T c2_t_loop_ub;
  int32_T c2_i49;
  uint8_T c2_f_tmp_data[255];
  int32_T c2_u_loop_ub;
  int32_T c2_i50;
  int32_T c2_v_loop_ub;
  int32_T c2_i51;
  int32_T c2_w_loop_ub;
  int32_T c2_i52;
  int32_T c2_x_loop_ub;
  int32_T c2_i53;
  int32_T c2_y_loop_ub;
  int32_T c2_i54;
  int32_T c2_ab_loop_ub;
  int32_T c2_i55;
  int32_T c2_bb_loop_ub;
  int32_T c2_i56;
  int32_T c2_cb_loop_ub;
  int32_T c2_i57;
  int32_T c2_db_loop_ub;
  int32_T c2_i58;
  int32_T c2_eb_loop_ub;
  int32_T c2_i59;
  int32_T c2_fb_loop_ub;
  int32_T c2_i60;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  for (c2_i18 = 0; c2_i18 < 255; c2_i18++) {
    c2_b_u[c2_i18] = (*chartInstance->c2_u)[c2_i18];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 9U, 9U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(chartInstance->c2_current_buffer_data,
    (const int32_T *)&c2_current_buffer_sizes, NULL, 0, 0, (void *)
    c2_f_sf_marshallOut, (void *)c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_rows, 1U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_index, 2U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 3U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 4U, c2_e_sf_marshallOut,
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_b_u, 5U, c2_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(&c2_b_y_data, NULL,
    &c2_b_y_elems_sizes, 0, 6, (void *)c2_c_sf_marshallOut, (void *)
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c2_buffer, 7U,
    c2_b_sf_marshallOut, c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c2_buf_len, 8U,
    c2_sf_marshallOut, c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 3);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 5);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 10);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c2_buffer_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 11);
    for (c2_i19 = 0; c2_i19 < 4; c2_i19++) {
      chartInstance->c2_buffer[c2_i19] = 0U;
    }

    chartInstance->c2_buffer_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 14);
  if (CV_EML_IF(0, 1, 1, !chartInstance->c2_buf_len_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 15);
    chartInstance->c2_buf_len = 0.0;
    chartInstance->c2_buf_len_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 19);
  if (CV_EML_IF(0, 1, 2, CV_RELATIONAL_EVAL(4U, 0U, 0, chartInstance->c2_buf_len,
        0.0, -1, 4U, chartInstance->c2_buf_len > 0.0))) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 20);
    c2_b0 = (1.0 > chartInstance->c2_buf_len);
    c2_b1 = c2_b0;
    c2_b2 = c2_b1;
    if (c2_b2) {
      c2_i20 = 0;
    } else {
      c2_i20 = _SFD_EML_ARRAY_BOUNDS_CHECK("buffer", (int32_T)_SFD_INTEGER_CHECK
        ("buf_len", chartInstance->c2_buf_len), 1, 4, 0, 0);
    }

    c2_tmp_sizes[0] = 1;
    c2_tmp_sizes[1] = c2_i20;
    c2_loop_ub = c2_i20 - 1;
    for (c2_i21 = 0; c2_i21 <= c2_loop_ub; c2_i21++) {
      c2_tmp_data[c2_tmp_sizes[0] * c2_i21] = chartInstance->c2_buffer[c2_i21];
    }

    c2_b_tmp_sizes = c2_tmp_sizes[1];
    c2_b_loop_ub = c2_tmp_sizes[1] - 1;
    for (c2_i22 = 0; c2_i22 <= c2_b_loop_ub; c2_i22++) {
      c2_b_tmp_data[c2_i22] = c2_tmp_data[c2_tmp_sizes[0] * c2_i22];
    }

    c2_iv0[0] = c2_tmp_sizes[1];
    c2_iv0[1] = 1;
    c2_c_tmp_sizes[0] = c2_iv0[0];
    c2_c_tmp_sizes[1] = 1;
    c2_i23 = c2_c_tmp_sizes[0];
    c2_i24 = c2_c_tmp_sizes[1];
    c2_c_loop_ub = c2_tmp_sizes[1] - 1;
    for (c2_i25 = 0; c2_i25 <= c2_c_loop_ub; c2_i25++) {
      c2_c_tmp_data[c2_i25] = c2_b_tmp_data[c2_i25];
    }

    _SFD_DIM_SIZE_EQ_CHECK(1, c2_c_tmp_sizes[0], 1);
    c2_d_loop_ub = c2_c_tmp_sizes[0] - 1;
    for (c2_i26 = 0; c2_i26 <= c2_d_loop_ub; c2_i26++) {
      c2_uv1[c2_i26] = c2_c_tmp_data[c2_i26];
    }

    for (c2_i27 = 0; c2_i27 < 255; c2_i27++) {
      c2_uv1[c2_i27 + 1] = c2_b_u[c2_i27];
    }

    c2_current_buffer_sizes[0] = 1;
    c2_current_buffer_sizes[1] = 256;
    c2_current_buffer = c2_current_buffer_sizes[0];
    c2_b_current_buffer = c2_current_buffer_sizes[1];
    for (c2_i28 = 0; c2_i28 < 256; c2_i28++) {
      chartInstance->c2_current_buffer_data[c2_i28] = c2_uv1[c2_i28];
    }
  } else {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 22);
    c2_current_buffer_sizes[0] = 255;
    c2_current_buffer_sizes[1] = 1;
    c2_c_current_buffer = c2_current_buffer_sizes[0];
    c2_d_current_buffer = c2_current_buffer_sizes[1];
    for (c2_i29 = 0; c2_i29 < 255; c2_i29++) {
      chartInstance->c2_current_buffer_data[c2_i29] = c2_b_u[c2_i29];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 25);
  c2_x_sizes[0] = c2_current_buffer_sizes[0];
  c2_x_sizes[1] = c2_current_buffer_sizes[1];
  c2_x = c2_x_sizes[0];
  c2_b_x = c2_x_sizes[1];
  c2_e_loop_ub = c2_current_buffer_sizes[0] * c2_current_buffer_sizes[1] - 1;
  for (c2_i30 = 0; c2_i30 <= c2_e_loop_ub; c2_i30++) {
    c2_x_data[c2_i30] = chartInstance->c2_current_buffer_data[c2_i30];
  }

  c2_b_x_sizes[0] = c2_x_sizes[0];
  c2_b_x_sizes[1] = c2_x_sizes[1];
  c2_c_x = c2_b_x_sizes[0];
  c2_d_x = c2_b_x_sizes[1];
  c2_f_loop_ub = c2_x_sizes[0] * c2_x_sizes[1] - 1;
  for (c2_i31 = 0; c2_i31 <= c2_f_loop_ub; c2_i31++) {
    c2_b_x_data[c2_i31] = c2_x_data[c2_i31];
  }

  c2_n = (real_T)c2_intlength(chartInstance, c2_b_x_data, c2_b_x_sizes);
  c2_A = c2_n;
  c2_e_x = c2_A;
  c2_f_x = c2_e_x;
  c2_g_x = c2_f_x;
  c2_y = c2_g_x / 40.0;
  c2_d0 = c2_y;
  c2_b_floor(chartInstance, &c2_d0);
  c2_rows = c2_d0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 26);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
  c2_d_tmp_sizes = (int32_T)c2_rows;
  c2_g_loop_ub = (int32_T)c2_rows - 1;
  for (c2_i32 = 0; c2_i32 <= c2_g_loop_ub; c2_i32++) {
    c2_d_tmp_data[c2_i32] = 0U;
  }

  _SFD_DIM_SIZE_GEQ_CHECK(255, c2_d_tmp_sizes, 1);
  c2_iv1[0] = c2_d_tmp_sizes;
  c2_iv1[1] = 1;
  c2_b_y_elems_sizes.cmd[0] = c2_iv1[0];
  c2_iv2[0] = c2_d_tmp_sizes;
  c2_iv2[1] = 1;
  c2_b_y_elems_sizes.cmd[1] = c2_iv2[1];
  c2_b_y = c2_b_y_elems_sizes.cmd[0];
  c2_c_y = c2_b_y_elems_sizes.cmd[1];
  c2_h_loop_ub = c2_d_tmp_sizes - 1;
  for (c2_i33 = 0; c2_i33 <= c2_h_loop_ub; c2_i33++) {
    c2_b_y_data.cmd[c2_i33] = c2_d_tmp_data[c2_i33];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 29);
  c2_d_tmp_sizes = (int32_T)c2_rows;
  c2_i_loop_ub = (int32_T)c2_rows - 1;
  for (c2_i34 = 0; c2_i34 <= c2_i_loop_ub; c2_i34++) {
    c2_d_tmp_data[c2_i34] = 0U;
  }

  _SFD_DIM_SIZE_GEQ_CHECK(255, c2_d_tmp_sizes, 1);
  c2_iv3[0] = c2_d_tmp_sizes;
  c2_iv3[1] = 1;
  c2_b_y_elems_sizes.id[0] = c2_iv3[0];
  c2_iv4[0] = c2_d_tmp_sizes;
  c2_iv4[1] = 1;
  c2_b_y_elems_sizes.id[1] = c2_iv4[1];
  c2_d_y = c2_b_y_elems_sizes.id[0];
  c2_e_y = c2_b_y_elems_sizes.id[1];
  c2_j_loop_ub = c2_d_tmp_sizes - 1;
  for (c2_i35 = 0; c2_i35 <= c2_j_loop_ub; c2_i35++) {
    c2_b_y_data.id[c2_i35] = c2_d_tmp_data[c2_i35];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 30);
  c2_d_tmp_sizes = (int32_T)c2_rows;
  c2_k_loop_ub = (int32_T)c2_rows - 1;
  for (c2_i36 = 0; c2_i36 <= c2_k_loop_ub; c2_i36++) {
    c2_d_tmp_data[c2_i36] = 0U;
  }

  _SFD_DIM_SIZE_GEQ_CHECK(255, c2_d_tmp_sizes, 1);
  c2_iv5[0] = c2_d_tmp_sizes;
  c2_iv5[1] = 1;
  c2_b_y_elems_sizes.data[0] = c2_iv5[0];
  c2_iv6[0] = c2_d_tmp_sizes;
  c2_iv6[1] = 1;
  c2_b_y_elems_sizes.data[1] = c2_iv6[1];
  c2_f_y = c2_b_y_elems_sizes.data[0];
  c2_g_y = c2_b_y_elems_sizes.data[1];
  c2_l_loop_ub = c2_d_tmp_sizes - 1;
  for (c2_i37 = 0; c2_i37 <= c2_l_loop_ub; c2_i37++) {
    c2_b_y_data.data[c2_i37] = c2_d_tmp_data[c2_i37];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 31);
  c2_d_tmp_sizes = (int32_T)c2_rows;
  c2_m_loop_ub = (int32_T)c2_rows - 1;
  for (c2_i38 = 0; c2_i38 <= c2_m_loop_ub; c2_i38++) {
    c2_d_tmp_data[c2_i38] = 0U;
  }

  _SFD_DIM_SIZE_GEQ_CHECK(255, c2_d_tmp_sizes, 1);
  c2_iv7[0] = c2_d_tmp_sizes;
  c2_iv7[1] = 1;
  c2_b_y_elems_sizes.c0[0] = c2_iv7[0];
  c2_iv8[0] = c2_d_tmp_sizes;
  c2_iv8[1] = 1;
  c2_b_y_elems_sizes.c0[1] = c2_iv8[1];
  c2_h_y = c2_b_y_elems_sizes.c0[0];
  c2_i_y = c2_b_y_elems_sizes.c0[1];
  c2_n_loop_ub = c2_d_tmp_sizes - 1;
  for (c2_i39 = 0; c2_i39 <= c2_n_loop_ub; c2_i39++) {
    c2_b_y_data.c0[c2_i39] = c2_d_tmp_data[c2_i39];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 32);
  c2_d_tmp_sizes = (int32_T)c2_rows;
  c2_o_loop_ub = (int32_T)c2_rows - 1;
  for (c2_i40 = 0; c2_i40 <= c2_o_loop_ub; c2_i40++) {
    c2_d_tmp_data[c2_i40] = 0U;
  }

  _SFD_DIM_SIZE_GEQ_CHECK(255, c2_d_tmp_sizes, 1);
  c2_iv9[0] = c2_d_tmp_sizes;
  c2_iv9[1] = 1;
  c2_b_y_elems_sizes.c1[0] = c2_iv9[0];
  c2_iv10[0] = c2_d_tmp_sizes;
  c2_iv10[1] = 1;
  c2_b_y_elems_sizes.c1[1] = c2_iv10[1];
  c2_j_y = c2_b_y_elems_sizes.c1[0];
  c2_k_y = c2_b_y_elems_sizes.c1[1];
  c2_p_loop_ub = c2_d_tmp_sizes - 1;
  for (c2_i41 = 0; c2_i41 <= c2_p_loop_ub; c2_i41++) {
    c2_b_y_data.c1[c2_i41] = c2_d_tmp_data[c2_i41];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 34);
  c2_b_rows = c2_rows;
  c2_i42 = (int32_T)c2_b_rows - 1;
  c2_index = 1.0;
  c2_b_index = 0;
  while (c2_b_index <= c2_i42) {
    c2_index = 1.0 + (real_T)c2_b_index;
    CV_EML_FOR(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 35);
    c2_b_y_data.cmd[_SFD_EML_ARRAY_BOUNDS_CHECK("y.cmd", (int32_T)c2_index, 1,
      c2_b_y_elems_sizes.cmd[0], 1, 0) - 1] = c2_b_u[(int32_T)((c2_index - 1.0) *
      5.0 + 1.0) - 1];
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 36);
    c2_b_y_data.id[_SFD_EML_ARRAY_BOUNDS_CHECK("y.id", (int32_T)c2_index, 1,
      c2_b_y_elems_sizes.id[0], 1, 0) - 1] = c2_b_u[(int32_T)((c2_index - 1.0) *
      5.0 + 2.0) - 1];
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 37);
    c2_b_y_data.data[_SFD_EML_ARRAY_BOUNDS_CHECK("y.data", (int32_T)c2_index, 1,
      c2_b_y_elems_sizes.data[0], 1, 0) - 1] = c2_b_u[(int32_T)((c2_index - 1.0)
      * 5.0 + 3.0) - 1];
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 38);
    c2_b_y_data.c0[_SFD_EML_ARRAY_BOUNDS_CHECK("y.c0", (int32_T)c2_index, 1,
      c2_b_y_elems_sizes.c0[0], 1, 0) - 1] = c2_b_u[(int32_T)((c2_index - 1.0) *
      5.0 + 4.0) - 1];
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 39);
    c2_b_y_data.c1[_SFD_EML_ARRAY_BOUNDS_CHECK("y.c1", (int32_T)c2_index, 1,
      c2_b_y_elems_sizes.c1[0], 1, 0) - 1] = c2_b_u[(int32_T)((c2_index - 1.0) *
      5.0 + 5.0) - 1];
    c2_b_index++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 42);
  c2_x_sizes[0] = c2_current_buffer_sizes[0];
  c2_x_sizes[1] = c2_current_buffer_sizes[1];
  c2_h_x = c2_x_sizes[0];
  c2_i_x = c2_x_sizes[1];
  c2_q_loop_ub = c2_current_buffer_sizes[0] * c2_current_buffer_sizes[1] - 1;
  for (c2_i43 = 0; c2_i43 <= c2_q_loop_ub; c2_i43++) {
    c2_x_data[c2_i43] = chartInstance->c2_current_buffer_data[c2_i43];
  }

  c2_c_x_sizes[0] = c2_x_sizes[0];
  c2_c_x_sizes[1] = c2_x_sizes[1];
  c2_j_x = c2_c_x_sizes[0];
  c2_k_x = c2_c_x_sizes[1];
  c2_r_loop_ub = c2_x_sizes[0] * c2_x_sizes[1] - 1;
  for (c2_i44 = 0; c2_i44 <= c2_r_loop_ub; c2_i44++) {
    c2_c_x_data[c2_i44] = c2_x_data[c2_i44];
  }

  c2_b_n = (real_T)c2_intlength(chartInstance, c2_c_x_data, c2_c_x_sizes);
  chartInstance->c2_buf_len = c2_mod(chartInstance, c2_b_n, 5.0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 43);
  if (CV_EML_IF(0, 1, 3, CV_RELATIONAL_EVAL(4U, 0U, 1, chartInstance->c2_buf_len,
        0.0, -1, 4U, chartInstance->c2_buf_len > 0.0))) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 44);
    c2_d1 = 256.0 - chartInstance->c2_buf_len;
    c2_b3 = (c2_d1 > 255.0);
    c2_b4 = c2_b3;
    c2_b5 = c2_b4;
    if (c2_b5) {
      c2_i45 = 1;
      c2_i46 = 0;
    } else {
      c2_i45 = _SFD_EML_ARRAY_BOUNDS_CHECK("u", (int32_T)_SFD_INTEGER_CHECK(
        "length(u)+1-buf_len", c2_d1), 1, 255, 0, 0);
      c2_i46 = 255;
    }

    c2_b6 = (1.0 > chartInstance->c2_buf_len);
    c2_b7 = c2_b6;
    c2_b8 = c2_b7;
    if (c2_b8) {
      c2_i47 = 0;
    } else {
      c2_i47 = _SFD_EML_ARRAY_BOUNDS_CHECK("buffer", (int32_T)_SFD_INTEGER_CHECK
        ("buf_len", chartInstance->c2_buf_len), 1, 4, 0, 0);
    }

    c2_e_tmp_sizes = c2_i47;
    c2_s_loop_ub = c2_i47 - 1;
    for (c2_i48 = 0; c2_i48 <= c2_s_loop_ub; c2_i48++) {
      c2_e_tmp_data[c2_i48] = 1 + c2_i48;
    }

    c2_f_tmp_sizes[0] = 1;
    c2_f_tmp_sizes[1] = (c2_i46 - c2_i45) + 1;
    c2_t_loop_ub = c2_i46 - c2_i45;
    for (c2_i49 = 0; c2_i49 <= c2_t_loop_ub; c2_i49++) {
      c2_f_tmp_data[c2_f_tmp_sizes[0] * c2_i49] = c2_b_u[(c2_i45 + c2_i49) - 1];
    }

    _SFD_SIZE_EQ_CHECK_1D(c2_e_tmp_sizes, c2_f_tmp_sizes[1]);
    c2_u_loop_ub = c2_f_tmp_sizes[1] - 1;
    for (c2_i50 = 0; c2_i50 <= c2_u_loop_ub; c2_i50++) {
      chartInstance->c2_buffer[c2_e_tmp_data[c2_i50] - 1] =
        c2_f_tmp_data[c2_f_tmp_sizes[0] * c2_i50];
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -44);
  _SFD_SYMBOL_SCOPE_POP();
  chartInstance->c2_y_elems_sizes->cmd[0] = c2_b_y_elems_sizes.cmd[0];
  chartInstance->c2_y_elems_sizes->cmd[1] = c2_b_y_elems_sizes.cmd[1];
  c2_v_loop_ub = c2_b_y_elems_sizes.cmd[1] - 1;
  for (c2_i51 = 0; c2_i51 <= c2_v_loop_ub; c2_i51++) {
    c2_w_loop_ub = c2_b_y_elems_sizes.cmd[0] - 1;
    for (c2_i52 = 0; c2_i52 <= c2_w_loop_ub; c2_i52++) {
      ((uint8_T *)&((char_T *)chartInstance->c2_y_data)[0])[c2_i52 +
        chartInstance->c2_y_elems_sizes->cmd[0] * c2_i51] =
        c2_b_y_data.cmd[c2_i52 + c2_b_y_elems_sizes.cmd[0] * c2_i51];
    }
  }

  chartInstance->c2_y_elems_sizes->id[0] = c2_b_y_elems_sizes.id[0];
  chartInstance->c2_y_elems_sizes->id[1] = c2_b_y_elems_sizes.id[1];
  c2_x_loop_ub = c2_b_y_elems_sizes.id[1] - 1;
  for (c2_i53 = 0; c2_i53 <= c2_x_loop_ub; c2_i53++) {
    c2_y_loop_ub = c2_b_y_elems_sizes.id[0] - 1;
    for (c2_i54 = 0; c2_i54 <= c2_y_loop_ub; c2_i54++) {
      ((uint8_T *)&((char_T *)chartInstance->c2_y_data)[255])[c2_i54 +
        chartInstance->c2_y_elems_sizes->id[0] * c2_i53] = c2_b_y_data.id[c2_i54
        + c2_b_y_elems_sizes.id[0] * c2_i53];
    }
  }

  chartInstance->c2_y_elems_sizes->data[0] = c2_b_y_elems_sizes.data[0];
  chartInstance->c2_y_elems_sizes->data[1] = c2_b_y_elems_sizes.data[1];
  c2_ab_loop_ub = c2_b_y_elems_sizes.data[1] - 1;
  for (c2_i55 = 0; c2_i55 <= c2_ab_loop_ub; c2_i55++) {
    c2_bb_loop_ub = c2_b_y_elems_sizes.data[0] - 1;
    for (c2_i56 = 0; c2_i56 <= c2_bb_loop_ub; c2_i56++) {
      ((uint8_T *)&((char_T *)chartInstance->c2_y_data)[510])[c2_i56 +
        chartInstance->c2_y_elems_sizes->data[0] * c2_i55] =
        c2_b_y_data.data[c2_i56 + c2_b_y_elems_sizes.data[0] * c2_i55];
    }
  }

  chartInstance->c2_y_elems_sizes->c0[0] = c2_b_y_elems_sizes.c0[0];
  chartInstance->c2_y_elems_sizes->c0[1] = c2_b_y_elems_sizes.c0[1];
  c2_cb_loop_ub = c2_b_y_elems_sizes.c0[1] - 1;
  for (c2_i57 = 0; c2_i57 <= c2_cb_loop_ub; c2_i57++) {
    c2_db_loop_ub = c2_b_y_elems_sizes.c0[0] - 1;
    for (c2_i58 = 0; c2_i58 <= c2_db_loop_ub; c2_i58++) {
      ((uint8_T *)&((char_T *)chartInstance->c2_y_data)[765])[c2_i58 +
        chartInstance->c2_y_elems_sizes->c0[0] * c2_i57] = c2_b_y_data.c0[c2_i58
        + c2_b_y_elems_sizes.c0[0] * c2_i57];
    }
  }

  chartInstance->c2_y_elems_sizes->c1[0] = c2_b_y_elems_sizes.c1[0];
  chartInstance->c2_y_elems_sizes->c1[1] = c2_b_y_elems_sizes.c1[1];
  c2_eb_loop_ub = c2_b_y_elems_sizes.c1[1] - 1;
  for (c2_i59 = 0; c2_i59 <= c2_eb_loop_ub; c2_i59++) {
    c2_fb_loop_ub = c2_b_y_elems_sizes.c1[0] - 1;
    for (c2_i60 = 0; c2_i60 <= c2_fb_loop_ub; c2_i60++) {
      ((uint8_T *)&((char_T *)chartInstance->c2_y_data)[1020])[c2_i60 +
        chartInstance->c2_y_elems_sizes->c1[0] * c2_i59] = c2_b_y_data.c1[c2_i60
        + c2_b_y_elems_sizes.c1[0] * c2_i59];
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_read_uart(SFc2_read_uartInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)c2_machineNumber;
  (void)c2_chartNumber;
  (void)c2_instanceNumber;
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_b_u;
  const mxArray *c2_y = NULL;
  SFc2_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc2_read_uartInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_b_u = *(real_T *)c2_inData;
  c2_y = NULL;
  if (!chartInstance->c2_buf_len_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_buf_len, const char_T *c2_identifier)
{
  real_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_buf_len),
    &c2_thisId);
  sf_mex_destroy(&c2_b_buf_len);
  return c2_y;
}

static real_T c2_b_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d2;
  if (mxIsEmpty(c2_b_u)) {
    chartInstance->c2_buf_len_not_empty = false;
  } else {
    chartInstance->c2_buf_len_not_empty = true;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), &c2_d2, 1, 0, 0U, 0, 0U, 0);
    c2_y = c2_d2;
  }

  sf_mex_destroy(&c2_b_u);
  return c2_y;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_buf_len;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc2_read_uartInstanceStruct *)chartInstanceVoid;
  c2_b_buf_len = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_buf_len),
    &c2_thisId);
  sf_mex_destroy(&c2_b_buf_len);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i61;
  uint8_T c2_b_inData[4];
  int32_T c2_i62;
  uint8_T c2_b_u[4];
  const mxArray *c2_y = NULL;
  SFc2_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc2_read_uartInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i61 = 0; c2_i61 < 4; c2_i61++) {
    c2_b_inData[c2_i61] = (*(uint8_T (*)[4])c2_inData)[c2_i61];
  }

  for (c2_i62 = 0; c2_i62 < 4; c2_i62++) {
    c2_b_u[c2_i62] = c2_b_inData[c2_i62];
  }

  c2_y = NULL;
  if (!chartInstance->c2_buffer_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", c2_b_u, 3, 0U, 1U, 0U, 1, 4), false);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_c_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_buffer, const char_T *c2_identifier, uint8_T c2_y[4])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_buffer), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_buffer);
}

static void c2_d_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, uint8_T c2_y[4])
{
  uint8_T c2_uv2[4];
  int32_T c2_i63;
  if (mxIsEmpty(c2_b_u)) {
    chartInstance->c2_buffer_not_empty = false;
  } else {
    chartInstance->c2_buffer_not_empty = true;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), c2_uv2, 1, 3, 0U, 1, 0U, 1, 4);
    for (c2_i63 = 0; c2_i63 < 4; c2_i63++) {
      c2_y[c2_i63] = c2_uv2[c2_i63];
    }
  }

  sf_mex_destroy(&c2_b_u);
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_buffer;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y[4];
  int32_T c2_i64;
  SFc2_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc2_read_uartInstanceStruct *)chartInstanceVoid;
  c2_b_buffer = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_buffer), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_buffer);
  for (c2_i64 = 0; c2_i64 < 4; c2_i64++) {
    (*(uint8_T (*)[4])c2_outData)[c2_i64] = c2_y[c2_i64];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, c2_PacketsBus
  *c2_inData_data, c2_PacketsBus_size *c2_inData_elems_sizes)
{
  const mxArray *c2_mxArrayOutData = NULL;
  c2_PacketsBus_size c2_u_elems_sizes;
  c2_PacketsBus c2_u_data;
  const mxArray *c2_y = NULL;
  int32_T c2_u_sizes[2];
  int32_T c2_b_u;
  int32_T c2_c_u;
  int32_T c2_loop_ub;
  int32_T c2_i65;
  uint8_T c2_b_u_data[255];
  const mxArray *c2_b_y = NULL;
  int32_T c2_b_u_sizes[2];
  int32_T c2_d_u;
  int32_T c2_e_u;
  int32_T c2_b_loop_ub;
  int32_T c2_i66;
  uint8_T c2_c_u_data[255];
  const mxArray *c2_c_y = NULL;
  int32_T c2_c_u_sizes[2];
  int32_T c2_f_u;
  int32_T c2_g_u;
  int32_T c2_c_loop_ub;
  int32_T c2_i67;
  uint8_T c2_d_u_data[255];
  const mxArray *c2_d_y = NULL;
  int32_T c2_d_u_sizes[2];
  int32_T c2_h_u;
  int32_T c2_i_u;
  int32_T c2_d_loop_ub;
  int32_T c2_i68;
  uint8_T c2_e_u_data[255];
  const mxArray *c2_e_y = NULL;
  int32_T c2_e_u_sizes[2];
  int32_T c2_j_u;
  int32_T c2_k_u;
  int32_T c2_e_loop_ub;
  int32_T c2_i69;
  uint8_T c2_f_u_data[255];
  const mxArray *c2_f_y = NULL;
  SFc2_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc2_read_uartInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u_elems_sizes = *c2_inData_elems_sizes;
  c2_u_data = *c2_inData_data;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c2_u_sizes[0] = c2_u_elems_sizes.cmd[0];
  c2_u_sizes[1] = c2_u_elems_sizes.cmd[1];
  c2_b_u = c2_u_sizes[0];
  c2_c_u = c2_u_sizes[1];
  c2_loop_ub = c2_u_elems_sizes.cmd[0] * c2_u_elems_sizes.cmd[1] - 1;
  for (c2_i65 = 0; c2_i65 <= c2_loop_ub; c2_i65++) {
    c2_b_u_data[c2_i65] = c2_u_data.cmd[c2_i65];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u_data, 3, 0U, 1U, 0U, 2,
    c2_u_sizes[0], c2_u_sizes[1]), false);
  sf_mex_addfield(c2_y, c2_b_y, "cmd", "cmd", 0);
  c2_b_u_sizes[0] = c2_u_elems_sizes.id[0];
  c2_b_u_sizes[1] = c2_u_elems_sizes.id[1];
  c2_d_u = c2_b_u_sizes[0];
  c2_e_u = c2_b_u_sizes[1];
  c2_b_loop_ub = c2_u_elems_sizes.id[0] * c2_u_elems_sizes.id[1] - 1;
  for (c2_i66 = 0; c2_i66 <= c2_b_loop_ub; c2_i66++) {
    c2_c_u_data[c2_i66] = c2_u_data.id[c2_i66];
  }

  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_c_u_data, 3, 0U, 1U, 0U, 2,
    c2_b_u_sizes[0], c2_b_u_sizes[1]), false);
  sf_mex_addfield(c2_y, c2_c_y, "id", "id", 0);
  c2_c_u_sizes[0] = c2_u_elems_sizes.data[0];
  c2_c_u_sizes[1] = c2_u_elems_sizes.data[1];
  c2_f_u = c2_c_u_sizes[0];
  c2_g_u = c2_c_u_sizes[1];
  c2_c_loop_ub = c2_u_elems_sizes.data[0] * c2_u_elems_sizes.data[1] - 1;
  for (c2_i67 = 0; c2_i67 <= c2_c_loop_ub; c2_i67++) {
    c2_d_u_data[c2_i67] = c2_u_data.data[c2_i67];
  }

  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_d_u_data, 3, 0U, 1U, 0U, 2,
    c2_c_u_sizes[0], c2_c_u_sizes[1]), false);
  sf_mex_addfield(c2_y, c2_d_y, "data", "data", 0);
  c2_d_u_sizes[0] = c2_u_elems_sizes.c0[0];
  c2_d_u_sizes[1] = c2_u_elems_sizes.c0[1];
  c2_h_u = c2_d_u_sizes[0];
  c2_i_u = c2_d_u_sizes[1];
  c2_d_loop_ub = c2_u_elems_sizes.c0[0] * c2_u_elems_sizes.c0[1] - 1;
  for (c2_i68 = 0; c2_i68 <= c2_d_loop_ub; c2_i68++) {
    c2_e_u_data[c2_i68] = c2_u_data.c0[c2_i68];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u_data, 3, 0U, 1U, 0U, 2,
    c2_d_u_sizes[0], c2_d_u_sizes[1]), false);
  sf_mex_addfield(c2_y, c2_e_y, "c0", "c0", 0);
  c2_e_u_sizes[0] = c2_u_elems_sizes.c1[0];
  c2_e_u_sizes[1] = c2_u_elems_sizes.c1[1];
  c2_j_u = c2_e_u_sizes[0];
  c2_k_u = c2_e_u_sizes[1];
  c2_e_loop_ub = c2_u_elems_sizes.c1[0] * c2_u_elems_sizes.c1[1] - 1;
  for (c2_i69 = 0; c2_i69 <= c2_e_loop_ub; c2_i69++) {
    c2_f_u_data[c2_i69] = c2_u_data.c1[c2_i69];
  }

  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", c2_f_u_data, 3, 0U, 1U, 0U, 2,
    c2_e_u_sizes[0], c2_e_u_sizes[1]), false);
  sf_mex_addfield(c2_y, c2_f_y, "c1", "c1", 0);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_e_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_y, const char_T *c2_identifier, c2_PacketsBus *c2_b_y_data,
  c2_PacketsBus_size *c2_b_y_elems_sizes)
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_y), &c2_thisId, c2_b_y_data,
                        c2_b_y_elems_sizes);
  sf_mex_destroy(&c2_y);
}

static void c2_f_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, c2_PacketsBus
  *c2_b_y_data, c2_PacketsBus_size *c2_b_y_elems_sizes)
{
  emlrtMsgIdentifier c2_thisId;
  static const char * c2_fieldNames[5] = { "cmd", "id", "data", "c0", "c1" };

  c2_thisId.fParent = c2_parentId;
  sf_mex_check_struct(c2_parentId, c2_b_u, 5, c2_fieldNames, 0U, NULL);
  c2_thisId.fIdentifier = "cmd";
  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_b_u, "cmd",
    "cmd", 0)), &c2_thisId, c2_b_y_data->cmd, c2_b_y_elems_sizes->cmd);
  c2_thisId.fIdentifier = "id";
  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_b_u, "id",
    "id", 0)), &c2_thisId, c2_b_y_data->id, c2_b_y_elems_sizes->id);
  c2_thisId.fIdentifier = "data";
  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_b_u, "data",
    "data", 0)), &c2_thisId, c2_b_y_data->data, c2_b_y_elems_sizes->data);
  c2_thisId.fIdentifier = "c0";
  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_b_u, "c0",
    "c0", 0)), &c2_thisId, c2_b_y_data->c0, c2_b_y_elems_sizes->c0);
  c2_thisId.fIdentifier = "c1";
  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_b_u, "c1",
    "c1", 0)), &c2_thisId, c2_b_y_data->c1, c2_b_y_elems_sizes->c1);
  sf_mex_destroy(&c2_b_u);
}

static void c2_g_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, uint8_T
  c2_b_y_data[], int32_T c2_y_sizes[2])
{
  int32_T c2_i70;
  uint32_T c2_uv3[2];
  int32_T c2_i71;
  boolean_T c2_bv0[2];
  int32_T c2_tmp_sizes[2];
  uint8_T c2_tmp_data[255];
  int32_T c2_y;
  int32_T c2_b_y;
  int32_T c2_loop_ub;
  int32_T c2_i72;
  (void)chartInstance;
  for (c2_i70 = 0; c2_i70 < 2; c2_i70++) {
    c2_uv3[c2_i70] = 255U + (uint32_T)(-254 * c2_i70);
  }

  for (c2_i71 = 0; c2_i71 < 2; c2_i71++) {
    c2_bv0[c2_i71] = true;
  }

  sf_mex_import_vs(c2_parentId, sf_mex_dup(c2_b_u), c2_tmp_data, 1, 3, 0U, 1, 0U,
                   2, c2_bv0, c2_uv3, c2_tmp_sizes);
  c2_y_sizes[0] = c2_tmp_sizes[0];
  c2_y_sizes[1] = c2_tmp_sizes[1];
  c2_y = c2_y_sizes[0];
  c2_b_y = c2_y_sizes[1];
  c2_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
  for (c2_i72 = 0; c2_i72 <= c2_loop_ub; c2_i72++) {
    c2_b_y_data[c2_i72] = c2_tmp_data[c2_i72];
  }

  sf_mex_destroy(&c2_b_u);
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, c2_PacketsBus *c2_outData_data,
  c2_PacketsBus_size *c2_outData_elems_sizes)
{
  const mxArray *c2_y;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  c2_PacketsBus_size c2_b_y_elems_sizes;
  c2_PacketsBus c2_b_y_data;
  SFc2_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc2_read_uartInstanceStruct *)chartInstanceVoid;
  c2_y = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_y), &c2_thisId,
                        &c2_b_y_data, &c2_b_y_elems_sizes);
  sf_mex_destroy(&c2_y);
  *c2_outData_elems_sizes = c2_b_y_elems_sizes;
  *c2_outData_data = c2_b_y_data;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i73;
  uint8_T c2_b_inData[255];
  int32_T c2_i74;
  uint8_T c2_b_u[255];
  const mxArray *c2_y = NULL;
  SFc2_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc2_read_uartInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i73 = 0; c2_i73 < 255; c2_i73++) {
    c2_b_inData[c2_i73] = (*(uint8_T (*)[255])c2_inData)[c2_i73];
  }

  for (c2_i74 = 0; c2_i74 < 255; c2_i74++) {
    c2_b_u[c2_i74] = c2_b_inData[c2_i74];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_b_u, 3, 0U, 1U, 0U, 2, 255, 1),
                false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_b_u;
  const mxArray *c2_y = NULL;
  SFc2_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc2_read_uartInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_b_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_h_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d3;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), &c2_d3, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d3;
  sf_mex_destroy(&c2_b_u);
  return c2_y;
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc2_read_uartInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, uint8_T
  c2_inData_data[], int32_T c2_inData_sizes[2])
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u_sizes[2];
  int32_T c2_b_u;
  int32_T c2_c_u;
  int32_T c2_inData;
  int32_T c2_b_inData;
  int32_T c2_b_inData_sizes;
  int32_T c2_loop_ub;
  int32_T c2_i75;
  uint8_T c2_b_inData_data[65280];
  int32_T c2_b_loop_ub;
  int32_T c2_i76;
  uint8_T c2_u_data[65280];
  const mxArray *c2_y = NULL;
  SFc2_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc2_read_uartInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u_sizes[0] = c2_inData_sizes[0];
  c2_u_sizes[1] = c2_inData_sizes[1];
  c2_b_u = c2_u_sizes[0];
  c2_c_u = c2_u_sizes[1];
  c2_inData = c2_inData_sizes[0];
  c2_b_inData = c2_inData_sizes[1];
  c2_b_inData_sizes = c2_inData * c2_b_inData;
  c2_loop_ub = c2_inData * c2_b_inData - 1;
  for (c2_i75 = 0; c2_i75 <= c2_loop_ub; c2_i75++) {
    c2_b_inData_data[c2_i75] = c2_inData_data[c2_i75];
  }

  c2_b_loop_ub = c2_b_inData_sizes - 1;
  for (c2_i76 = 0; c2_i76 <= c2_b_loop_ub; c2_i76++) {
    c2_u_data[c2_i76] = c2_b_inData_data[c2_i76];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u_data, 3, 0U, 1U, 0U, 2,
    c2_u_sizes[0], c2_u_sizes[1]), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_i_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId, uint8_T
  c2_b_y_data[], int32_T c2_y_sizes[2])
{
  int32_T c2_i77;
  uint32_T c2_uv4[2];
  int32_T c2_i78;
  boolean_T c2_bv1[2];
  int32_T c2_tmp_sizes[2];
  uint8_T c2_tmp_data[65280];
  int32_T c2_y;
  int32_T c2_b_y;
  int32_T c2_loop_ub;
  int32_T c2_i79;
  (void)chartInstance;
  for (c2_i77 = 0; c2_i77 < 2; c2_i77++) {
    c2_uv4[c2_i77] = 255U + (uint32_T)c2_i77;
  }

  for (c2_i78 = 0; c2_i78 < 2; c2_i78++) {
    c2_bv1[c2_i78] = true;
  }

  sf_mex_import_vs(c2_parentId, sf_mex_dup(c2_b_u), c2_tmp_data, 1, 3, 0U, 1, 0U,
                   2, c2_bv1, c2_uv4, c2_tmp_sizes);
  c2_y_sizes[0] = c2_tmp_sizes[0];
  c2_y_sizes[1] = c2_tmp_sizes[1];
  c2_y = c2_y_sizes[0];
  c2_b_y = c2_y_sizes[1];
  c2_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
  for (c2_i79 = 0; c2_i79 <= c2_loop_ub; c2_i79++) {
    c2_b_y_data[c2_i79] = c2_tmp_data[c2_i79];
  }

  sf_mex_destroy(&c2_b_u);
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, uint8_T c2_outData_data[],
  int32_T c2_outData_sizes[2])
{
  const mxArray *c2_current_buffer;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y_sizes[2];
  uint8_T c2_b_y_data[65280];
  int32_T c2_loop_ub;
  int32_T c2_i80;
  int32_T c2_b_loop_ub;
  int32_T c2_i81;
  SFc2_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc2_read_uartInstanceStruct *)chartInstanceVoid;
  c2_current_buffer = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_current_buffer), &c2_thisId,
                        c2_b_y_data, c2_y_sizes);
  sf_mex_destroy(&c2_current_buffer);
  c2_outData_sizes[0] = c2_y_sizes[0];
  c2_outData_sizes[1] = c2_y_sizes[1];
  c2_loop_ub = c2_y_sizes[1] - 1;
  for (c2_i80 = 0; c2_i80 <= c2_loop_ub; c2_i80++) {
    c2_b_loop_ub = c2_y_sizes[0] - 1;
    for (c2_i81 = 0; c2_i81 <= c2_b_loop_ub; c2_i81++) {
      c2_outData_data[c2_i81 + c2_outData_sizes[0] * c2_i80] =
        c2_b_y_data[c2_i81 + c2_y_sizes[0] * c2_i80];
    }
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_read_uart_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_createstruct("structure", 2, 31, 1),
                false);
  c2_info_helper(&c2_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs0 = NULL;
  const mxArray *c2_lhs0 = NULL;
  const mxArray *c2_rhs1 = NULL;
  const mxArray *c2_lhs1 = NULL;
  const mxArray *c2_rhs2 = NULL;
  const mxArray *c2_lhs2 = NULL;
  const mxArray *c2_rhs3 = NULL;
  const mxArray *c2_lhs3 = NULL;
  const mxArray *c2_rhs4 = NULL;
  const mxArray *c2_lhs4 = NULL;
  const mxArray *c2_rhs5 = NULL;
  const mxArray *c2_lhs5 = NULL;
  const mxArray *c2_rhs6 = NULL;
  const mxArray *c2_lhs6 = NULL;
  const mxArray *c2_rhs7 = NULL;
  const mxArray *c2_lhs7 = NULL;
  const mxArray *c2_rhs8 = NULL;
  const mxArray *c2_lhs8 = NULL;
  const mxArray *c2_rhs9 = NULL;
  const mxArray *c2_lhs9 = NULL;
  const mxArray *c2_rhs10 = NULL;
  const mxArray *c2_lhs10 = NULL;
  const mxArray *c2_rhs11 = NULL;
  const mxArray *c2_lhs11 = NULL;
  const mxArray *c2_rhs12 = NULL;
  const mxArray *c2_lhs12 = NULL;
  const mxArray *c2_rhs13 = NULL;
  const mxArray *c2_lhs13 = NULL;
  const mxArray *c2_rhs14 = NULL;
  const mxArray *c2_lhs14 = NULL;
  const mxArray *c2_rhs15 = NULL;
  const mxArray *c2_lhs15 = NULL;
  const mxArray *c2_rhs16 = NULL;
  const mxArray *c2_lhs16 = NULL;
  const mxArray *c2_rhs17 = NULL;
  const mxArray *c2_lhs17 = NULL;
  const mxArray *c2_rhs18 = NULL;
  const mxArray *c2_lhs18 = NULL;
  const mxArray *c2_rhs19 = NULL;
  const mxArray *c2_lhs19 = NULL;
  const mxArray *c2_rhs20 = NULL;
  const mxArray *c2_lhs20 = NULL;
  const mxArray *c2_rhs21 = NULL;
  const mxArray *c2_lhs21 = NULL;
  const mxArray *c2_rhs22 = NULL;
  const mxArray *c2_lhs22 = NULL;
  const mxArray *c2_rhs23 = NULL;
  const mxArray *c2_lhs23 = NULL;
  const mxArray *c2_rhs24 = NULL;
  const mxArray *c2_lhs24 = NULL;
  const mxArray *c2_rhs25 = NULL;
  const mxArray *c2_lhs25 = NULL;
  const mxArray *c2_rhs26 = NULL;
  const mxArray *c2_lhs26 = NULL;
  const mxArray *c2_rhs27 = NULL;
  const mxArray *c2_lhs27 = NULL;
  const mxArray *c2_rhs28 = NULL;
  const mxArray *c2_lhs28 = NULL;
  const mxArray *c2_rhs29 = NULL;
  const mxArray *c2_lhs29 = NULL;
  const mxArray *c2_rhs30 = NULL;
  const mxArray *c2_lhs30 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("length"), "name", "name", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("uint8"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1303149806U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c2_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m!intlength"),
                  "context", "context", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323174178U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c2_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m!intlength"),
                  "context", "context", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexIntRelop"),
                  "name", "name", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326731922U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c2_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!apply_float_relop"),
                  "context", "context", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1393334458U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c2_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!float_class_contains_indexIntClass"),
                  "context", "context", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326731596U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c2_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!is_signed_indexIntClass"),
                  "context", "context", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmin"), "name", "name", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362265482U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c2_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1393334458U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c2_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mrdivide"), "name", "name", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410811248U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1370013486U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c2_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389721374U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c2_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("rdivide"), "name", "name", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363717480U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c2_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395935456U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c2_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286822396U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c2_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_div"), "name", "name", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1386427552U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c2_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "context",
                  "context", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.div"), "name",
                  "name", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/div.p"), "resolved",
                  "resolved", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410811370U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c2_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("floor"), "name", "name", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363717454U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c2_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395935456U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c2_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286822326U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c2_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("mod"), "name", "name", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m"), "resolved",
                  "resolved", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363717454U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c2_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m"), "context",
                  "context", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1395935456U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c2_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m"), "context",
                  "context", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375984288U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c2_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410811370U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c2_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m"), "context",
                  "context", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375984288U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c2_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1410811370U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c2_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod"), "context",
                  "context", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375984288U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c2_rhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod"), "context",
                  "context", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286822326U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c2_rhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod"), "context",
                  "context", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_round"), "name",
                  "name", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_round.m"),
                  "resolved", "resolved", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1307654838U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c2_rhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod"), "context",
                  "context", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_abs"), "name",
                  "name", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m"),
                  "resolved", "resolved", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286822312U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c2_rhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/mod.m!floatmod"), "context",
                  "context", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eps"), "name", "name", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "resolved",
                  "resolved", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326731596U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c2_rhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs27), "lhs", "lhs",
                  27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "context",
                  "context", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_is_float_class"), "name",
                  "name", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_float_class.m"),
                  "resolved", "resolved", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286822382U), "fileTimeLo",
                  "fileTimeLo", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 28);
  sf_mex_assign(&c2_rhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs28), "rhs", "rhs",
                  28);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs28), "lhs", "lhs",
                  28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "context",
                  "context", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_eps"), "name", "name", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m"), "resolved",
                  "resolved", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326731596U), "fileTimeLo",
                  "fileTimeLo", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 29);
  sf_mex_assign(&c2_rhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs29), "rhs", "rhs",
                  29);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs29), "lhs", "lhs",
                  29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_eps.m"), "context",
                  "context", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1326731596U), "fileTimeLo",
                  "fileTimeLo", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 30);
  sf_mex_assign(&c2_rhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs30), "rhs", "rhs",
                  30);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs30), "lhs", "lhs",
                  30);
  sf_mex_destroy(&c2_rhs0);
  sf_mex_destroy(&c2_lhs0);
  sf_mex_destroy(&c2_rhs1);
  sf_mex_destroy(&c2_lhs1);
  sf_mex_destroy(&c2_rhs2);
  sf_mex_destroy(&c2_lhs2);
  sf_mex_destroy(&c2_rhs3);
  sf_mex_destroy(&c2_lhs3);
  sf_mex_destroy(&c2_rhs4);
  sf_mex_destroy(&c2_lhs4);
  sf_mex_destroy(&c2_rhs5);
  sf_mex_destroy(&c2_lhs5);
  sf_mex_destroy(&c2_rhs6);
  sf_mex_destroy(&c2_lhs6);
  sf_mex_destroy(&c2_rhs7);
  sf_mex_destroy(&c2_lhs7);
  sf_mex_destroy(&c2_rhs8);
  sf_mex_destroy(&c2_lhs8);
  sf_mex_destroy(&c2_rhs9);
  sf_mex_destroy(&c2_lhs9);
  sf_mex_destroy(&c2_rhs10);
  sf_mex_destroy(&c2_lhs10);
  sf_mex_destroy(&c2_rhs11);
  sf_mex_destroy(&c2_lhs11);
  sf_mex_destroy(&c2_rhs12);
  sf_mex_destroy(&c2_lhs12);
  sf_mex_destroy(&c2_rhs13);
  sf_mex_destroy(&c2_lhs13);
  sf_mex_destroy(&c2_rhs14);
  sf_mex_destroy(&c2_lhs14);
  sf_mex_destroy(&c2_rhs15);
  sf_mex_destroy(&c2_lhs15);
  sf_mex_destroy(&c2_rhs16);
  sf_mex_destroy(&c2_lhs16);
  sf_mex_destroy(&c2_rhs17);
  sf_mex_destroy(&c2_lhs17);
  sf_mex_destroy(&c2_rhs18);
  sf_mex_destroy(&c2_lhs18);
  sf_mex_destroy(&c2_rhs19);
  sf_mex_destroy(&c2_lhs19);
  sf_mex_destroy(&c2_rhs20);
  sf_mex_destroy(&c2_lhs20);
  sf_mex_destroy(&c2_rhs21);
  sf_mex_destroy(&c2_lhs21);
  sf_mex_destroy(&c2_rhs22);
  sf_mex_destroy(&c2_lhs22);
  sf_mex_destroy(&c2_rhs23);
  sf_mex_destroy(&c2_lhs23);
  sf_mex_destroy(&c2_rhs24);
  sf_mex_destroy(&c2_lhs24);
  sf_mex_destroy(&c2_rhs25);
  sf_mex_destroy(&c2_lhs25);
  sf_mex_destroy(&c2_rhs26);
  sf_mex_destroy(&c2_lhs26);
  sf_mex_destroy(&c2_rhs27);
  sf_mex_destroy(&c2_lhs27);
  sf_mex_destroy(&c2_rhs28);
  sf_mex_destroy(&c2_lhs28);
  sf_mex_destroy(&c2_rhs29);
  sf_mex_destroy(&c2_lhs29);
  sf_mex_destroy(&c2_rhs30);
  sf_mex_destroy(&c2_lhs30);
}

static const mxArray *c2_emlrt_marshallOut(const char * c2_b_u)
{
  const mxArray *c2_y = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_b_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c2_b_u)), false);
  return c2_y;
}

static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_b_u)
{
  const mxArray *c2_y = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_b_u, 7, 0U, 0U, 0U, 0), false);
  return c2_y;
}

static int32_T c2_intlength(SFc2_read_uartInstanceStruct *chartInstance, uint8_T
  c2_x_data[], int32_T c2_x_sizes[2])
{
  int32_T c2_n;
  (void)chartInstance;
  (void)c2_x_data;
  if ((real_T)c2_x_sizes[0] > (real_T)c2_x_sizes[1]) {
    c2_n = c2_x_sizes[0];
  } else {
    c2_n = c2_x_sizes[1];
  }

  return c2_n;
}

static real_T c2_floor(SFc2_read_uartInstanceStruct *chartInstance, real_T c2_x)
{
  real_T c2_b_x;
  c2_b_x = c2_x;
  c2_b_floor(chartInstance, &c2_b_x);
  return c2_b_x;
}

static real_T c2_mod(SFc2_read_uartInstanceStruct *chartInstance, real_T c2_x,
                     real_T c2_y)
{
  real_T c2_xk;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_d_x;
  (void)c2_y;
  c2_eml_scalar_eg(chartInstance);
  c2_xk = c2_x;
  c2_b_x = c2_xk;
  c2_eml_scalar_eg(chartInstance);
  c2_c_x = c2_b_x / 5.0;
  c2_d_x = c2_c_x;
  c2_d_x = muDoubleScalarFloor(c2_d_x);
  return c2_b_x - c2_d_x * 5.0;
}

static void c2_eml_scalar_eg(SFc2_read_uartInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_b_u;
  const mxArray *c2_y = NULL;
  SFc2_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc2_read_uartInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_b_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_b_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_j_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i82;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), &c2_i82, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i82;
  sf_mex_destroy(&c2_b_u);
  return c2_y;
}

static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc2_read_uartInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_y_bus_io(void *chartInstanceVoid, void *c2_pData)
{
  const mxArray *c2_mxVal = NULL;
  SFc2_read_uartInstanceStruct *chartInstance;
  (void)c2_pData;
  chartInstance = (SFc2_read_uartInstanceStruct *)chartInstanceVoid;
  c2_mxVal = NULL;
  sf_mex_assign(&c2_mxVal, c2_sf_marshall_unsupported(chartInstance), false);
  return c2_mxVal;
}

static const mxArray *c2_sf_marshall_unsupported(void *chartInstanceVoid)
{
  const mxArray *c2_y = NULL;
  SFc2_read_uartInstanceStruct *chartInstance;
  chartInstance = (SFc2_read_uartInstanceStruct *)chartInstanceVoid;
  c2_y = NULL;
  sf_mex_assign(&c2_y, c2_c_emlrt_marshallOut(chartInstance,
    "Structures with variable-sized fields unsupported for debugging."), false);
  return c2_y;
}

static const mxArray *c2_c_emlrt_marshallOut(SFc2_read_uartInstanceStruct
  *chartInstance, const char * c2_b_u)
{
  const mxArray *c2_y = NULL;
  (void)chartInstance;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_b_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c2_b_u)), false);
  return c2_y;
}

static uint8_T c2_k_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_read_uart, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_read_uart), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_read_uart);
  return c2_y;
}

static uint8_T c2_l_emlrt_marshallIn(SFc2_read_uartInstanceStruct *chartInstance,
  const mxArray *c2_b_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_b_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_b_u);
  return c2_y;
}

static void c2_b_floor(SFc2_read_uartInstanceStruct *chartInstance, real_T *c2_x)
{
  (void)chartInstance;
  *c2_x = muDoubleScalarFloor(*c2_x);
}

static void init_dsm_address_info(SFc2_read_uartInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc2_read_uartInstanceStruct *chartInstance)
{
  chartInstance->c2_u = (uint8_T (*)[255])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c2_y_data = (c2_PacketsBus *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_y_elems_sizes = (c2_PacketsBus_size *)
    ssGetCurrentOutputPortDimensions_wrapper(chartInstance->S, 1);
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

void sf_c2_read_uart_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(279760228U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4131342684U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2268772405U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1305853247U);
}

mxArray* sf_c2_read_uart_get_post_codegen_info(void);
mxArray *sf_c2_read_uart_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("5I1lK818H5259Qg9O93XxF");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(255);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c2_read_uart_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_read_uart_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_read_uart_jit_fallback_info(void)
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

mxArray *sf_c2_read_uart_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c2_read_uart_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c2_read_uart(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x4'type','srcId','name','auxInfo'{{M[1],M[5],T\"y\",},{M[4],M[0],T\"buf_len\",S'l','i','p'{{M1x2[95 102],M[0],}}},{M[4],M[0],T\"buffer\",S'l','i','p'{{M1x2[76 82],M[0],}}},{M[8],M[0],T\"is_active_c2_read_uart\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 4, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_read_uart_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_read_uartInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc2_read_uartInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _read_uartMachineNumber_,
           2,
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
        _SFD_CV_INIT_EML(0,1,1,4,0,0,0,1,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,932);
        _SFD_CV_INIT_EML_IF(0,1,0,151,169,-1,206);
        _SFD_CV_INIT_EML_IF(0,1,1,208,227,-1,248);
        _SFD_CV_INIT_EML_IF(0,1,2,298,312,365,404);
        _SFD_CV_INIT_EML_IF(0,1,3,851,865,-1,931);
        _SFD_CV_INIT_EML_FOR(0,1,0,612,631,807);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,0,301,312,-1,4);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,1,854,865,-1,4);

        {
          unsigned int dimVector[2];
          dimVector[0]= 255;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_y_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_VALUE_PTR(0U, *chartInstance->c2_u);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c2_y_data);
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
  return "HUN2HF38Ht6KqyS8a5mfQD";
}

static void sf_opaque_initialize_c2_read_uart(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_read_uartInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c2_read_uart((SFc2_read_uartInstanceStruct*)
    chartInstanceVar);
  initialize_c2_read_uart((SFc2_read_uartInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_read_uart(void *chartInstanceVar)
{
  enable_c2_read_uart((SFc2_read_uartInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_read_uart(void *chartInstanceVar)
{
  disable_c2_read_uart((SFc2_read_uartInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_read_uart(void *chartInstanceVar)
{
  sf_gateway_c2_read_uart((SFc2_read_uartInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_read_uart(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c2_read_uart((SFc2_read_uartInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_read_uart(SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c2_read_uart((SFc2_read_uartInstanceStruct*)
    chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c2_read_uart(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_read_uartInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_read_uart_optimization_info();
    }

    finalize_c2_read_uart((SFc2_read_uartInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_read_uart((SFc2_read_uartInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_read_uart(SimStruct *S)
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
    initialize_params_c2_read_uart((SFc2_read_uartInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_read_uart(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_read_uart_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1919634225U));
  ssSetChecksum1(S,(1215479784U));
  ssSetChecksum2(S,(3747118688U));
  ssSetChecksum3(S,(3402308279U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_read_uart(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_read_uart(SimStruct *S)
{
  SFc2_read_uartInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc2_read_uartInstanceStruct *)utMalloc(sizeof
    (SFc2_read_uartInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_read_uartInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_read_uart;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_read_uart;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_read_uart;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_read_uart;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_read_uart;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_read_uart;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_read_uart;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_read_uart;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_read_uart;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_read_uart;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_read_uart;
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

void c2_read_uart_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_read_uart(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_read_uart(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_read_uart(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_read_uart_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
