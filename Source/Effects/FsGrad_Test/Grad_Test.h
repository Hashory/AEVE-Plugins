#pragma once

// clang-format off
#include "../FsLibrary/Fs.h"
#include "Fs_Target.h"
#include "../FsLibrary/FGrad.h"
#include "../FsLibrary/FsAE.h"
// clang-format on

// IDs for User Interface
// Used as IDs for the 'params' parameter in ParamsSetup and Render functions.
enum {
  ID_INPUT = 0,  // default input layer

  ID_START_POS,
  ID_LAST_POS,

  ID_START_COL,
  ID_LAST_COL,

  ID_NUM_PARAMS
};

// UI display strings
#define STR_START_POS "startPos"
#define STR_LAST_POS "lastPos"

#define STR_START_COL "startCol"
#define STR_LAST_COL "lastCol"

// UI parameters
typedef struct ParamInfo {
  A_FloatPoint startPos;
  A_FloatPoint lastPos;

  PF_Pixel startCol;
  PF_Pixel lastCol;

} ParamInfo, *ParamInfoP, **ParamInfoH;

extern "C" {

DllExport PF_Err EntryPointFunc(PF_Cmd cmd, PF_InData *in_data,
                                PF_OutData *out_data, PF_ParamDef *params[],
                                PF_LayerDef *output, void *extra);
}
