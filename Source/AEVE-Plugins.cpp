#include "AEVE-Plugins.h"

extern "C" {

// #pragma region PluginDataEntryFunction2

__declspec(dllexport) PF_Err PluginDataEntryFunction2(
    PF_PluginDataPtr inPtr, PF_PluginDataCB2 inPluginDataCallBackPtr,
    SPBasicSuite *inSPBasicSuitePtr, const char *inHostName,
    const char *inHostVersion) {
  PF_Err result = PF_Err_INVALID_CALLBACK;

  // Register the effect using PF_REGISTER_EFFECT_EXT2.
  // Arguments:
  //   inPtr                   - Plugin data pointer
  //   inPluginDataCallBackPtr - Plugin data callback pointer
  //   "Name"                  - Display name in the Effects panel
  //   "Match Name"            - Unique match name for scripting
  //   "Category"              - Category in the Effects menu
  //   AE_RESERVED_INFO        - Reserved (use AE_RESERVED_INFO)
  //   "Entry point"           - Effect entry function name
  //   "Support URL"           - URL for support or documentation
  // Example:
  // result = PF_REGISTER_EFFECT_EXT2(
  //     inPtr,
  //     inPluginDataCallBackPtr,
  //     "EffectName",
  //     "AEVE-Plugins-EffectName",
  //     "AEVE-Plugins",
  //     AE_RESERVED_INFO,
  //     "EffectMain_EffectName",
  //     "https://AEVE-Plugins.hashory.app"
  // );
  // if (result != PF_Err_NONE) {
  //   return result;
  // }

  // Set the effects below

  return result;
}

// #pragma endregion PluginDataEntryFunction2

// #pragma region EffectMain functions

// Declares the main entry point for the effect
// __declspec(dllexport) PF_Err EffectMain_EffectName(PF_Cmd cmd,
//                                                    PF_InData *in_data,
//                                                    PF_OutData *out_data,
//                                                    PF_ParamDef *params[],
//                                                    PF_LayerDef *output) {
//   return AEVE_Plugins::EffectName::EffectMain(cmd, in_data, out_data, params,
//                                               output);
// }

// set the effects entry points below

// #pragma endregion EffectMain functions

}  // extern "C"
