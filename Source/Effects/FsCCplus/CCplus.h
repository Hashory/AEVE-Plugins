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

#define COLOR_TABLE_LENGTH8 (PF_MAX_CHAN8 + 1)
#define COLOR_TABLE_LENGTH16 (PF_MAX_CHAN16 + 1)

#define COLOR_TABLE_SIZE8 ((COLOR_TABLE_LENGTH8) * sizeof(PF_Pixel))
#define COLOR_TABLE_SIZE16 ((COLOR_TABLE_LENGTH16) * sizeof(PF_Pixel16))

#define StrName "CCplus"
#define StrDescription "CCplus bry-ful AfterEffects EffectPlugin"
#define StrMADEBY "bry-ful"

#define StrORG_REV1 "original_reverce"  // PF_Pixel
#define StrORG_REV2 "on"                // PF_Pixel

#define StrCOLOR_START "start_color"
#define StrCOLOR_CENTER "center_color"  // PF_Pixel
#define StrCOLOR_END "end_color"        // PF_Pixel
#define StrCOLOR_CENTER_POS "center_color_pos(%)"

#define StrALPHA_START "start_alpha(%)"  // Make transparent
#define StrALPHA_END "end_alpha(%)"      // Make transparent
#define StrNOISE_VALUE "noise_value"     // Noise strength

#define StrERR_getFsAEParams "Image buffer size error. Sorry."
#define StrERR_getParams "Parameter error. Sorry."

// Structure for After Effects information
typedef struct {
  PF_InData *in_data;
  PF_OutData *out_data;

  PF_EffectWorld *input;
  PF_EffectWorld *output;
  PF_PixelPtr inData;   // Address of the input image
  PF_PixelPtr outData;  // Address of the output image
  A_long width;         // Width of the target image (pixels)
  A_long height;        // Height of the target image (pixels)

  A_long inWidth;         // Actual width of the input image (pixels)
  A_long outWidth;        // Actual width of the output image (pixels)
  A_long offsetInWidth;   // inWidth - width Correction size
  A_long offsetOutWidth;  // outWidth - width
  A_long Frame;           // Current frame being rendered (0-indexed)
  PF_Boolean is16Bit;     // True if 16-bit mode
  A_u_char reserve1;
  A_u_short reserve2;
  A_long reserve3;
  A_long reserve4;
  /* Forcibly align to 64 bytes */
} FsAEParams;

// User interface IDs
// These become the IDs for the params parameter in the ParamsSetup and Render
// functions.
enum {
  ID_INPUT = 0,  // default input layer

  ID_ORG_REV,  // Invert the original image

  ID_COLOR_START,   // PF_Pixel
  ID_COLOR_CENTER,  // PF_Pixel
  ID_COLOR_END,     // PF_Pixel
  ID_COLOR_CENTER_POS,

  ID_ALPHA_START,  // Make transparent
  ID_ALPHA_END,    // Make transparent

  ID_NOISE_VALUE,  // Amount of noise
  ID_NUM_PARAMS

};

typedef struct CCPInfo {
  PF_Boolean org_rev;
  PF_Pixel color_start;
  PF_Pixel color_center;
  PF_Pixel color_end;

  A_u_char color_border;
  A_long alpha_start;
  A_long alpha_end;
  A_long noise_value;
  PF_Pixel *colorTbl;
} CCPInfo, *CCPInfoP, **CCPInfoH;

typedef struct CCPInfo16 {
  PF_Boolean org_rev;
  PF_Pixel16 color_start;
  PF_Pixel16 color_center;
  PF_Pixel16 color_end;

  A_u_short color_border;
  A_long alpha_start;
  A_long alpha_end;
  A_long noise_value;
  PF_Pixel16 *colorTbl;
} CCPInfo16, *CCPInfo16P, **CCPInfo16H;

typedef struct CCPInfo32 {
  PF_Boolean org_rev;
  PF_PixelFloat color_start;
  PF_PixelFloat color_center;
  PF_PixelFloat color_end;

  PF_FpShort color_border;

  PF_FpShort alpha_start;
  PF_FpShort alpha_end;
  A_long noise_value;
  PF_PixelFloat colorTbl;
} CCPInfo32, *CCPInfo32P, **CCPInfo32H;

typedef struct {
  PF_Fixed value;
  PF_ProgPtr ref;
  PF_SampPB samp_pb;
  PF_InData *in_data;
} CCplusInfo;

extern "C" {
DllExport PF_Err EntryPointFunc(PF_Cmd cmd, PF_InData *in_data,
                                PF_OutData *out_data, PF_ParamDef *params[],
                                PF_LayerDef *output, void *extraP);
}

// Create FsAEParams structure
PF_Err getFsAEParams(PF_InData *in_data, PF_OutData *out_data,
                     PF_ParamDef *params[], PF_LayerDef *output,
                     FsAEParams *aeprm);
