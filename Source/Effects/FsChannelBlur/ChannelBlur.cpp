// clang-format off
#include "ChannelBlur.h"
#include "Fs_Entry.h"
// clang-format on

// Pass parameters to After Effects
// See Param_Utils.h for details
static PF_Err ParamsSetup(PF_InData *in_data, PF_OutData *out_data,
                          PF_ParamDef *params[], PF_LayerDef *output) {
  PF_Err err = PF_Err_NONE;
  PF_ParamDef def;

  // Popup menu
  AEFX_CLR_STRUCT(def);
  PF_ADD_POPUP(STR_MODE,
               STR_MODE_COUNT,  // Number of menus
               STR_MODE_DFLT,   // Default
               STR_MODE_ITEMS, ID_MODE);

  AEFX_CLR_STRUCT(def);
  PF_ADD_SLIDER(STR_0CH_R,  // Parameter name
                0,          // Minimum value for numerical input
                500,        // Maximum value for numerical input
                0,          // Minimum value for slider
                100,        // Maximum value for slider
                0,          // Default value
                ID_0CH_R);

  AEFX_CLR_STRUCT(def);
  PF_ADD_SLIDER(STR_1CH_G,  // Parameter name
                0,          // Minimum value for numerical input
                500,        // Maximum value for numerical input
                0,          // Minimum value for slider
                100,        // Maximum value for slider
                0,          // Default value
                ID_1CH_G);

  AEFX_CLR_STRUCT(def);
  PF_ADD_SLIDER(STR_2CH_B,  // Parameter name
                0,          // Minimum value for numerical input
                500,        // Maximum value for numerical input
                0,          // Minimum value for slider
                100,        // Maximum value for slider
                0,          // Default value
                ID_2CH_B);

  AEFX_CLR_STRUCT(def);
  PF_ADD_SLIDER(STR_3CH_A,  // Parameter name
                0,          // Minimum value for numerical input
                500,        // Maximum value for numerical input
                0,          // Minimum value for slider
                100,        // Maximum value for slider
                0,          // Default value
                ID_3CH_A);

  out_data->num_params = ID_NUM_PARAMS;

  return err;
}

static PF_Err HandleChangedParam(PF_InData *in_data, PF_OutData *out_data,
                                 PF_ParamDef *params[], PF_LayerDef *outputP,
                                 PF_UserChangedParamExtra *extraP) {
  PF_Err err = PF_Err_NONE;
  return err;
}

static PF_Err QueryDynamicFlags(PF_InData *in_data, PF_OutData *out_data,
                                PF_ParamDef *params[], void *extra) {
  PF_Err err = PF_Err_NONE;
  return err;
}

static PF_Err FilterImage8(refconType refcon, A_long xL, A_long yL,
                           PF_Pixel8 *inP, PF_Pixel8 *outP) {
  PF_Err err = PF_Err_NONE;
  ParamInfo *infoP = reinterpret_cast<ParamInfo *>(refcon);

  return err;
}

static PF_Err FilterImage16(refconType refcon, A_long xL, A_long yL,
                            PF_Pixel16 *inP, PF_Pixel16 *outP) {
  PF_Err err = PF_Err_NONE;
  ParamInfo *infoP = reinterpret_cast<ParamInfo *>(refcon);

  return err;
}

static PF_Err FilterImage32(refconType refcon, A_long xL, A_long yL,
                            PF_PixelFloat *inP, PF_PixelFloat *outP) {
  PF_Err err = PF_Err_NONE;
  ParamInfo *infoP = reinterpret_cast<ParamInfo *>(refcon);

  return err;
}

static PF_Err GetParams(CFsAE *ae, ParamInfo *infoP) {
  PF_Err err = PF_Err_NONE;

  ERR(ae->GetPOPUP(ID_MODE, &infoP->mode));
  ERR(ae->GetADD(ID_0CH_R, &infoP->r_blur));
  ERR(ae->GetADD(ID_1CH_G, &infoP->g_blur));
  ERR(ae->GetADD(ID_2CH_B, &infoP->b_blur));
  ERR(ae->GetADD(ID_3CH_A, &infoP->a_blur));

  return err;
}

static PF_Err Exec(CFsAE *ae, ParamInfo *infoP) {
  PF_Err err = PF_Err_NONE;

  // Copy screen
  ERR(ae->CopyInToOut());
  switch (ae->pixelFormat()) {
    case PF_PixelFormat_ARGB128:
      // ERR(ae->iterate32((refconType)infoP,FilterImage32));
      break;
    case PF_PixelFormat_ARGB64:
      // ERR(ae->iterate16((refconType)infoP,FilterImage16));
      break;
    case PF_PixelFormat_ARGB32:
      // ERR(ae->iterate8((refconType)infoP,FilterImage8));
      break;
  }
  return err;
}

// Main rendering function
/*
This function is called for rendering on hosts that do not support SmartFX
(After Effects 7 and earlier). Writing this function ensures compatibility with
v6.5.
*/
static PF_Err Render(PF_InData *in_data, PF_OutData *out_data,
                     PF_ParamDef *params[], PF_LayerDef *output) {
  PF_Err err = PF_Err_NONE;
  PF_Handle pixelTable = NULL;

  CFsAE ae(in_data, out_data, params, output, ID_NUM_PARAMS);
  err = ae.resultErr();
  if (!err) {
    ParamInfo info;
    ERR(GetParams(&ae, &info));
    ERR(Exec(&ae, &info));
  }
  return err;
}

/*
For SmartFX support, this function is called first to acquire parameters.
*/
#if defined(SUPPORT_SMARTFX)
static PF_Err PreRender(PF_InData *in_data, PF_OutData *out_data,
                        PF_PreRenderExtra *extraP) {
  PF_Err err = PF_Err_NONE;
  CFsAE ae(in_data, out_data, extraP, sizeof(ParamInfo), ID_NUM_PARAMS);
  err = ae.resultErr();
  if (!err) {
    ParamInfo *infoP = reinterpret_cast<ParamInfo *>(ae.LockPreRenderData());
    if (infoP) {
      ae.SetHostPreRenderData();
      ERR(GetParams(&ae, infoP));
      ERR(ae.UnSetPreRenderData());
      ae.UnlockPreRenderData();
    } else {
      err = PF_Err_OUT_OF_MEMORY;
    }
  }
  return err;
}
#endif

#if defined(SUPPORT_SMARTFX)
static PF_Err SmartRender(PF_InData *in_data, PF_OutData *out_data,
                          PF_SmartRenderExtra *extraP) {
  PF_Err err = PF_Err_NONE, err2 = PF_Err_NONE;

  CFsAE ae(in_data, out_data, extraP, ID_NUM_PARAMS);
  err = ae.resultErr();
  if (!err) {
    ParamInfo *infoP = reinterpret_cast<ParamInfo *>(ae.LockPreRenderData());
    if (infoP) {
      ERR(Exec(&ae, infoP));
      ERR2(ae.UnsetSmartRender());
      ae.UnlockPreRenderData();
    } else {
      err = PF_Err_OUT_OF_MEMORY;
    }
  }
  return err;
}
#endif
