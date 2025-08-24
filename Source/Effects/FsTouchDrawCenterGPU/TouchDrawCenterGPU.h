#pragma once

// clang-format off
#include "TouchDrawCenterGPU_Kernel.cl.h"
#include "AEConfig.h"
#include "entry.h"
#include "AEFX_SuiteHelper.h"
#include "PrSDKAESupport.h"
#include "AE_Effect.h"
#include "AE_EffectCB.h"
#include "AE_EffectCBSuites.h"
#include "AE_EffectGPUSuites.h"
#include "AE_Macros.h"
#include "AEGP_SuiteHandler.h"
#include "String_Utils.h"
#include "Param_Utils.h"
#include "Smart_Utils.h"


#if _WIN32
#include <CL/cl.h>
#define HAS_HLSL 1
#define HAS_METAL 0
#else
#include <OpenCL/cl.h>
#define HAS_HLSL 0
#define HAS_METAL 1
#include <Metal/Metal.h>
#include "TouchDrawCenterGPU_Kernel.metal.h"
#endif
#include <math.h>

#ifdef AE_OS_WIN
  #include <Windows.h>
#endif

#define DESCRIPTION	"\nExperimental* \rDraws concentration lines from the surroundings"

#define NAME			"AEVE FsTouchDrawCenterGPU"
#define	MAJOR_VERSION	1
#define	MINOR_VERSION	1
#define	BUG_VERSION		0
#define	STAGE_VERSION	PF_Stage_DEVELOP
#define	BUILD_VERSION	1
// clang-format on

enum {
  ID_INPUT = 0,

  ID_SEED,        // Random seed
  ID_CENTER,      // Center point
  ID_LENGTH_MAX,  // Max length of the touch line
  ID_LENGTH_RND,  // Randomness of the length

  ID_Y,            // Number of touches
  ID_COLOR,        // Color of the touch line
  ID_OPACITY,      // Opacity of the touch line
  ID_OPACITY_RND,  // Randomness of the opacity

  ID_POINT_COUNT,   // Number of points to generate
  ID_POINT_LENGTH,  // Range of points to generate
  ID_ORG,           // Original image blend

  ID_NUM_PARAMS
};

extern "C" {

DllExport PF_Err EffectMain(PF_Cmd cmd, PF_InData *in_data,
                            PF_OutData *out_data, PF_ParamDef *params[],
                            PF_LayerDef *output, void *extra);
}

#if HAS_METAL
/*
 ** Plugins must not rely on a host autorelease pool.
 ** Create a pool if autorelease is used, or Cocoa convention calls, such as
 *Metal, might internally autorelease.
 */
struct ScopedAutoreleasePool {
  ScopedAutoreleasePool() : mPool([[NSAutoreleasePool alloc] init]) {}

  ~ScopedAutoreleasePool() { [mPool release]; }

  NSAutoreleasePool *mPool;
};
#endif

typedef struct {
  A_long mSeed;
  PF_Fixed mCenterX;
  PF_Fixed mCenterY;
  PF_Fixed mLengthMax;
  PF_Fixed mLengthRnd;
  A_long mValueY;
  PF_PixelFloat mColor;
  PF_Fixed mOpacity;
  PF_Fixed mOpacityRnd;
  A_long mPointCount;
  PF_Fixed mPointLength;
  PF_Boolean mOrgBlend;
} TouchDrawCenterParams;
