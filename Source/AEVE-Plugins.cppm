module;

#include "AE_Effect.h"

export module AEVE_Plugins;

import AEVE_Plugins.FsAlphaFix;

extern "C" {
__declspec(dllexport)
PF_Err PluginDataEntryFunction2(
	PF_PluginDataPtr inPtr,
	PF_PluginDataCB2 inPluginDataCallBackPtr,
	SPBasicSuite* inSPBasicSuitePtr,
	const char* inHostName,
	const char* inHostVersion)
{
	PF_Err result = PF_Err_INVALID_CALLBACK;

	result = PF_REGISTER_EFFECT_EXT2(
		inPtr,
		inPluginDataCallBackPtr,
		"Gamma (Table)", // Name
		"ADBE Gamma", // Match Name
		"Sample Plug-ins", // Category
		AE_RESERVED_INFO, // Reserved Info
		"EffectMain",    // Entry point
		"https://www.adobe.com");    // support URL

	return result;
}

__declspec(dllexport)
PF_Err EntryPointFunc(PF_Cmd cmd, PF_InData *in_data,
					  PF_OutData *out_data,
					  PF_ParamDef *params[],
					  PF_LayerDef *output, void *extraP) {
  return AEVE_Plugins.FsAlphaFix.EntryPointFunc(cmd, in_data, out_data, params, output, extraP);
}
}