#ifndef __c2_read_uart_h__
#define __c2_read_uart_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef struct_PacketsBus_tag
#define struct_PacketsBus_tag

struct PacketsBus_tag
{
  uint8_T cmd[255];
  uint8_T id[255];
  uint8_T data[255];
  uint8_T c0[255];
  uint8_T c1[255];
};

#endif                                 /*struct_PacketsBus_tag*/

#ifndef typedef_c2_PacketsBus
#define typedef_c2_PacketsBus

typedef struct PacketsBus_tag c2_PacketsBus;

#endif                                 /*typedef_c2_PacketsBus*/

#ifndef struct_PacketsBus_tag_size
#define struct_PacketsBus_tag_size

struct PacketsBus_tag_size
{
  int32_T cmd[2];
  int32_T id[2];
  int32_T data[2];
  int32_T c0[2];
  int32_T c1[2];
};

#endif                                 /*struct_PacketsBus_tag_size*/

#ifndef typedef_c2_PacketsBus_size
#define typedef_c2_PacketsBus_size

typedef struct PacketsBus_tag_size c2_PacketsBus_size;

#endif                                 /*typedef_c2_PacketsBus_size*/

#ifndef typedef_SFc2_read_uartInstanceStruct
#define typedef_SFc2_read_uartInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_isStable;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_read_uart;
  uint8_T c2_buffer[4];
  boolean_T c2_buffer_not_empty;
  real_T c2_buf_len;
  boolean_T c2_buf_len_not_empty;
  uint8_T c2_current_buffer_data[65280];
  uint8_T (*c2_u)[255];
  c2_PacketsBus *c2_y_data;
  c2_PacketsBus_size *c2_y_elems_sizes;
} SFc2_read_uartInstanceStruct;

#endif                                 /*typedef_SFc2_read_uartInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_read_uart_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_read_uart_get_check_sum(mxArray *plhs[]);
extern void c2_read_uart_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
