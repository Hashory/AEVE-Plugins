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
#define refconType void *
#else
#include "PF_Suite_Helper.h"
#define refconType A_long
#endif
#ifdef AE_OS_WIN
#include <Windows.h>
#endif
#include "../FsLibrary/FsAE.h"
// clang-format on

// IDs for the user interface
// These will be the IDs for the params in the ParamsSetup and Render functions
enum {
  ID_INPUT = 0,  // default input layer
  ID_Highlights_COLOR,
  ID_Midtones_COLOR,
  ID_Shadows_COLOR,
  ID_Midtones_OFFSET,
  ID_Blend_w_Original_FIXED,

  ID_NUM_PARAMS
};

// A struct to hold the plugin's unique parameters
#define COLOR_TABLE_LENGTH8 256
#define COLOR_TABLE_LENGTH16 (32768 + 1)
#define COLOR_TABLE_SIZE8 ((COLOR_TABLE_LENGTH8) * sizeof(PF_Pixel))
#define COLOR_TABLE_SIZE16 ((COLOR_TABLE_LENGTH16) * sizeof(PF_Pixel16))
#define MID8 (COLOR_TABLE_LENGTH8 / 2 - 1)
#define LAST8 (COLOR_TABLE_LENGTH8 - 1)
#define MID16 (COLOR_TABLE_LENGTH16 / 2 - 1)
#define LAST16 (COLOR_TABLE_LENGTH16 - 1)

#define STR_Highlights_COLOR "Highlights"
#define STR_Midtones_COLOR "Midtones"
#define STR_Shadows_COLOR "Shadows"
#define STR_Midtones_OFFSET "MidtonesOffset"
#define STR_Blend_w_Original_FIXED "Blend w. Original"

// Initial parameter values
#define Highlights_def_red 0xFF
#define Highlights_def_green 0xFF
#define Highlights_def_blue 0xFF
#define Midtones_def_red 0x7F
#define Midtones_def_green 0x64
#define Midtones_def_blue 0x46
#define Midtones_def_offset 0x00
#define Shadows_def_red 0x00
#define Shadows_def_green 0x00
#define Shadows_def_blue 0x00
#define Blend_w_Original_def 0

typedef struct ToneParam {
  PF_PixelPtr colorTbl;
  PF_PixelFloat Highlights;
  PF_PixelFloat Midtones;
  PF_PixelFloat Shadows;
  PF_FpShort MidtonesBorder;
  PF_FpShort level;
  PF_FpShort Blend_w_Original;
} ToneParam;

extern "C" {
DllExport PF_Err EntryPointFunc(PF_Cmd cmd, PF_InData *in_data,
                                PF_OutData *out_data, PF_ParamDef *params[],
                                PF_LayerDef *output, void *extra);
}
