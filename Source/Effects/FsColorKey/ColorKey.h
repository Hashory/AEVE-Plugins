#pragma once

// clang-format off
#include "Fs_Target.h"
#include "AEConfig.h"
#include "entry.h"
#include "AE_Effect.h"
#include "AE_EffectCB.h"
#include "AE_EffectCBSuites.h"
#include "AE_Macros.h"
#include "AEGP_SuiteHandler.h"
#include "String_Utils.h"
#include "Param_Utils.h"
#include "Smart_Utils.h"
#if defined(PF_AE100_PLUG_IN_VERSION)
#include "AEFX_SuiteHelper.h"
#define refconType void*
#else
#include "PF_Suite_Helper.h"
#define refconType A_long
#endif
#ifdef AE_OS_WIN
#include <Windows.h>
#endif
#include "../FsLibrary/FsAE.h"
// clang-format on

// User interface ID
// Used as an ID for the params parameter in ParamsSetup and Render functions
enum {
  ID_INPUT = 0,  // default input layer

  ID_COLOR,
  ID_RANGE,
  ID_UNDERCOLOR,

  ID_NUM_PARAMS
};

// Display string for UI
#define STR_COLOR "color"
#define STR_RANGE "range"
#define STR_UNDER "Undercolor"

// UI parameters
typedef struct {
  PF_Pixel color;
  PF_Pixel under;
  A_u_char range;
} ParamInfo;

typedef struct {
  PF_Pixel color;
  PF_Pixel16 under;
  A_u_char range;
} ParamInfo16;
typedef struct {
  PF_Pixel color;
  PF_PixelFloat under;
  A_u_char range;
} ParamInfo32;

extern "C" {

DllExport PF_Err EntryPointFunc(PF_Cmd cmd, PF_InData *in_data,
                                PF_OutData *out_data, PF_ParamDef *params[],
                                PF_LayerDef *output, void *extra);
}
