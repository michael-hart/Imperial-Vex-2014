#ifndef __c4_read_uart_h__
#define __c4_read_uart_h__

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

#ifndef typedef_c4_PacketsBus
#define typedef_c4_PacketsBus

typedef struct PacketsBus_tag c4_PacketsBus;

#endif                                 /*typedef_c4_PacketsBus*/

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

#ifndef typedef_c4_PacketsBus_size
#define typedef_c4_PacketsBus_size

typedef struct PacketsBus_tag_size c4_PacketsBus_size;

#endif                                 /*typedef_c4_PacketsBus_size*/

#ifndef typedef_SFc4_read_uartInstanceStruct
#define typedef_SFc4_read_uartInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c4_sfEvent;
  boolean_T c4_isStable;
  boolean_T c4_doneDoubleBufferReInit;
  uint8_T c4_is_active_c4_read_uart;
  c4_PacketsBus *c4_packets_data;
  c4_PacketsBus_size *c4_packets_elems_sizes;
  int8_T *c4_itt;
  uint8_T (*c4_singlePack)[5];
  boolean_T *c4_terminate;
} SFc4_read_uartInstanceStruct;

#endif                                 /*typedef_SFc4_read_uartInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c4_read_uart_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c4_read_uart_get_check_sum(mxArray *plhs[]);
extern void c4_read_uart_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
