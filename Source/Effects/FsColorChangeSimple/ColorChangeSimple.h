#pragma once

// clang-format off
#include "Fs_Target.h"

#include "AEConfig.h"
#include "entry.h"

//#include "PrSDKAESupport.h"
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
// ID for the params parameter of ParamsSetup and Render functions
enum {
  ID_INPUT = 0,    // default input layer
  ID_LEVEL_FIXED,  // long
  ID_SRC_COLOR,    // PF_Pixel
  ID_DST_COLOR,    // PF_Pixel
  ID_NUM_PARAMS
};

#define STR_LEVEL "Tolerance"
#define STR_SRC "Source Color"
#define STR_DST "New Color"

typedef struct ParamInfo {
  A_u_char level;
  PF_Pixel src;
  PF_Pixel dst;
  PF_Pixel16 dst16;
  PF_PixelFloat dst32;
} ParamInfo, *ParamInfoP, **ParamInfoH;

//-------------
extern "C" {

DllExport PF_Err EntryPointFunc(PF_Cmd cmd, PF_InData *in_data,
                                PF_OutData *out_data, PF_ParamDef *params[],
                                PF_LayerDef *output, void *extra);
}
