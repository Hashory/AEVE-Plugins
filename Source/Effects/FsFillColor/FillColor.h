#pragma once

// clang-format off
#include "Fs_Target.h"
#include "AEConfig.hh"
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
	#include "PF_Suite_Helper.hh"
	#define refconType A_long
#endif
#ifdef AE_OS_WIN
	#include <Windows.h>
#endif

#include "../FsLibrary/FsAE.h"
// clang-format on

#define STR_ENABLED_CB1 "Execute"
#define STR_ENABLED_CB2 "ON"
#define STR_COLOR "Color"
#define STR_OPA_FIXED "Opacity"

// User interface ID
// This will be the ID for the params parameter in the ParamsSetup and Render
// functions.
enum {
  ID_INPUT = 0,  // default input layer

  // For reference below
  ID_ENABLED_CB,  // boolean
  ID_FILL_COLOR,
  ID_OPA_COLOR_FIXED,
  ID_NUM_PARAMS
};

typedef struct ParamInfo8 {
  PF_Boolean enabled;
  PF_Pixel fill_color;
  PF_FpShort opa_color;
  PF_FpShort opa_color2;

} ParamInfo8, *ParamInfo8P, **ParamInfo8H;

typedef struct ParamInfo16 {
  PF_Boolean enabled;
  PF_Pixel16 fill_color;
  PF_FpShort opa_color;
  PF_FpShort opa_color2;

} ParamInfo16, *ParamInfo16P, **ParamInfo16H;

typedef struct ParamInfo32 {
  PF_Boolean enabled;
  PF_PixelFloat fill_color;
  PF_FpShort opa_color;
  PF_FpShort opa_color2;

} ParamInfo32, *ParamInfo32P, **ParamInfo32H;

extern "C" {

DllExport PF_Err EntryPointFunc(PF_Cmd cmd, PF_InData *in_data,
                                PF_OutData *out_data, PF_ParamDef *params[],
                                PF_LayerDef *output, void *extra);
}
