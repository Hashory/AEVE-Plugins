#pragma once
#ifndef alphaThreshold_H
#define alphaThreshold_H

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
//#include "FsAE.h"

//User interface ID
//Becomes the ID for the params parameter of the ParamsSetup and Render functions
enum {
	ID_INPUT = 0,	// default input layer

	ID_A,
	ID_NUM_PARAMS
};

//UI display string
#define	STR_A				"AlphaThreshold"


//UI parameters
typedef struct ParamInfo {
	PF_FpLong	a;
	
} ParamInfo, *ParamInfoP, **ParamInfoH;

extern "C" {

DllExport 
PF_Err 
EntryPointFunc (	
	PF_Cmd			cmd,
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void			*extra);
}
#endif // alphaThreshold_H
