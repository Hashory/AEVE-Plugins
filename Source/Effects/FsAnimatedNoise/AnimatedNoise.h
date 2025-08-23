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
// This will be the ID for the params parameter in the ParamsSetup and Render
// functions.
enum {
  ID_INPUT = 0,           // default input layer
  ID_ANIMATED_CB,         // motion
  ID_ANIMATED_ADD,        // motion
  ID_VALUE_ADD,           // amount of noise
  ID_LENGTH_FIXED,        // strength of noise
  ID_COLOR_CB,            // color or monochrome
  ID_BLOCK_VALUE_FIXED,   // amount of block noise
  ID_BLOCK_LENGTH_FIXED,  // strength of block noise
  ID_BLOCK_WIDTH_ADD,     // block noise width
  ID_BLOCK_HEIGHT_ADD,    // block noise height
  ID_BLOCK_COLOR_CB,      // color or monochrome

  ID_NUM_PARAMS
};
typedef struct PrmTbl {
  PF_PixelPtr data;  // image
  A_long width;      // image width
  A_long height;     // image height
  A_long w;          // target
  A_long h;
  A_long target;

  PF_Boolean animFlag;  //
  A_long anim;

  A_long frame;
  A_long seed;

  A_long value;
  PF_Fixed length;
  PF_Boolean colorFlag;

  PF_Fixed block_value;
  PF_Fixed block_length;
  A_long block_width;
  A_long block_height;
  PF_Boolean block_colorFlag;

} PrmTbl;
static void NoiseMain8(PrmTbl *prm);
static void NoiseMain16(PrmTbl *prm);
static void NoiseMain32(PrmTbl *prm);
static void NoiseBlock8(PrmTbl *prm);
static void NoiseBlock16(PrmTbl *prm);
static void NoiseBlock32(PrmTbl *prm);

extern "C" {
DllExport PF_Err EntryPointFunc(PF_Cmd cmd, PF_InData *in_data,
                                PF_OutData *out_data, PF_ParamDef *params[],
                                PF_LayerDef *output, void *extraP);
}
