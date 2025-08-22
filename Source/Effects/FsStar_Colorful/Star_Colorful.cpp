// F's Plugins for VS2010/VS2012

// clang-format off
#include "Star_Colorful.h"
// clang-format on

// Pass parameters to After Effects
// See Param_Utils.h
static PF_Err ParamsSetup(PF_InData* in_data, PF_OutData* out_data,
                          PF_ParamDef* params[], PF_LayerDef* output) {
  PF_Err err = PF_Err_NONE;
  PF_ParamDef def;

  AEFX_CLR_STRUCT(def);
  PF_ADD_TOPIC(STR_TOPIC0, ID_TOPIC0);
  // Popup menu
  AEFX_CLR_STRUCT(def);
  PF_ADD_POPUP(STR_TARGET_KIND,
               STR_TARGET_COUNT,  // Number of menus
               STR_TARGET_DFLT,   // Default
               STR_TARGET_ITEMS, ID_TAGET_KIND);

  AEFX_CLR_STRUCT(def);
  PF_ADD_FLOAT_SLIDER(STR_TAGET_BORDER,  // Name
                      50,                // VALID_MIN
                      100,               // VALID_MAX
                      50,                // SLIDER_MIN
                      100,               // SLIDER_MAX
                      1,                 // CURVE_TOLERANCE
                      100,               // DFLT
                      1,                 // PREC
                      0,                 // DISP
                      0,                 // WANT_PHASE
                      ID_TAGET_BORDER);
  AEFX_CLR_STRUCT(def);
  PF_ADD_FLOAT_SLIDER(STR_TAGET_SOFT,  // Name
                      0,               // VALID_MIN
                      100,             // VALID_MAX
                      0,               // SLIDER_MIN
                      100,             // SLIDER_MAX
                      1,               // CURVE_TOLERANCE
                      100,             // DFLT
                      1,               // PREC
                      0,               // DISP
                      0,               // WANT_PHASE
                      ID_TAGET_SOFT);
  // Color specification
  AEFX_CLR_STRUCT(def);
  PF_ADD_COLOR(STR_TARGET_COLOR, 0xFF, 0x00, 0x00, ID_TARGET_COLOR);
  AEFX_CLR_STRUCT(def);
  PF_ADD_CHECKBOX(STR_TARGET_MASK, STR_ON, FALSE, 0, ID_TARGET_MASK);

  AEFX_CLR_STRUCT(def);
  PF_END_TOPIC(ID_TOPIC0_END);
  AEFX_CLR_STRUCT(def);
  PF_ADD_TOPIC(STR_TOPICA, ID_TOPICA);
  AEFX_CLR_STRUCT(def);
  PF_ADD_FLOAT_SLIDER(STR_LENGTH,  // Name
                      0,           // VALID_MIN
                      600,         // VALID_MAX
                      0,           // SLIDER_MIN
                      200,         // SLIDER_MAX
                      1,           // CURVE_TOLERANCE
                      100,         // DFLT
                      1,           // PREC
                      0,           // DISP
                      0,           // WANT_PHASE
                      ID_LENGTH);
  AEFX_CLR_STRUCT(def);
  PF_ADD_FLOAT_SLIDER(STR_OPACITY,  // Name
                      0,            // VALID_MIN
                      100,          // VALID_MAX
                      0,            // SLIDER_MIN
                      100,          // SLIDER_MAX
                      1,            // CURVE_TOLERANCE
                      20,           // DFLT
                      1,            // PREC
                      0,            // DISP
                      0,            // WANT_PHASE
                      ID_OPACITY);

  // Angle
  AEFX_CLR_STRUCT(def);
  PF_ADD_ANGLE(STR_ROT, 0, ID_ROT);
  AEFX_CLR_STRUCT(def);
  PF_ADD_CHECKBOX(STR_AUTOROLLING, STR_ON, FALSE, 0, ID_AUTOROLLING);
  AEFX_CLR_STRUCT(def);
  PF_ADD_FLOAT_SLIDER(STR_ROLLINGSPEED,  // Name
                      -720,              // VALID_MIN
                      720,               // VALID_MAX
                      -180,              // SLIDER_MIN
                      180,               // SLIDER_MAX
                      1,                 // CURVE_TOLERANCE
                      90,                // DFLT
                      1,                 // PREC
                      0,                 // DISP
                      0,                 // WANT_PHASE
                      ID_ROLLINGDPEED);

  AEFX_CLR_STRUCT(def);
  PF_END_TOPIC(ID_TOPICA_END);

  AEFX_CLR_STRUCT(def);
  PF_ADD_TOPIC(STR_TOPIC1, ID_TOPIC1);
  // Popup menu
  AEFX_CLR_STRUCT(def);
  PF_ADD_POPUP(STR_COLOR_KIND,
               STR_COLOR_COUNT,  // Number of menus
               STR_COLOR_DFLT,   // Default
               STR_COLOR_ITEMS, ID_COLOR_KIND);
  // Color specification
  AEFX_CLR_STRUCT(def);
  PF_ADD_COLOR(STR_COLOR, 0xFF, 0xFF, 0x00, ID_COLOR);
  AEFX_CLR_STRUCT(def);
  PF_ADD_FLOAT_SLIDER(STR_BRIGHT,  // Name
                      0,           // VALID_MIN
                      100,         // VALID_MAX
                      0,           // SLIDER_MIN
                      20,          // SLIDER_MAX
                      1,           // CURVE_TOLERANCE
                      5,           // DFLT
                      1,           // PREC
                      0,           // DISP
                      0,           // WANT_PHASE
                      ID_BRIGHTNESS);

  AEFX_CLR_STRUCT(def);
  PF_ADD_FLOAT_SLIDER(STR_RAINBOW_OFFSET,  // Name
                      -30000,              // VALID_MIN
                      +30000,              // VALID_MAX
                      -1,                  // SLIDER_MIN
                      1,                   // SLIDER_MAX
                      1,                   // CURVE_TOLERANCE
                      0,                   // DFLT
                      1,                   // PREC
                      0,                   // DISP
                      0,                   // WANT_PHASE
                      ID_RAINBOW_OFFSET);
  AEFX_CLR_STRUCT(def);
  PF_ADD_FLOAT_SLIDER(STR_RAINBOW_DELTA,  // Name
                      0,                  // VALID_MIN
                      100,                // VALID_MAX
                      0,                  // SLIDER_MIN
                      5,                  // SLIDER_MAX
                      1,                  // CURVE_TOLERANCE
                      1,                  // DFLT
                      1,                  // PREC
                      0,                  // DISP
                      0,                  // WANT_PHASE
                      ID_RAINBOW_DELTA);
  AEFX_CLR_STRUCT(def);
  PF_END_TOPIC(ID_TOPIC1_END);
  AEFX_CLR_STRUCT(def);
  PF_ADD_TOPIC(STR_TOPIC2, ID_TOPIC2);
  AEFX_CLR_STRUCT(def);
  PF_ADD_SLIDER(STR_VER_LEN,  // Parameter name
                0,            // Minimum value for numerical input
                300,          // Maximum value for numerical input
                0,            // Slider minimum
                150,          // Slider maximum
                70,           // Default value
                ID_VER_LEN);
  // Angle
  AEFX_CLR_STRUCT(def);
  PF_ADD_ANGLE(STR_VER_ROT, 0, ID_VER_ROT);
  AEFX_CLR_STRUCT(def);
  PF_ADD_FLOAT_SLIDER(STR_VER_OPACITY,  // Name
                      0,                // VALID_MIN
                      100,              // VALID_MAX
                      0,                // SLIDER_MIN
                      100,              // SLIDER_MAX
                      0,                // CURVE_TOLERANCE
                      100,              // DFLT
                      1,                // PREC
                      0,                // DISP
                      0,                // WANT_PHASE
                      ID_VER_OPACITY);
  AEFX_CLR_STRUCT(def);
  PF_ADD_SLIDER(STR_HOR_LEN,  // Parameter name
                0,            // Minimum value for numerical input
                300,          // Maximum value for numerical input
                0,            // Slider minimum
                150,          // Slider maximum
                70,           // Default value
                ID_HOR_LEN);
  // Angle
  AEFX_CLR_STRUCT(def);
  PF_ADD_ANGLE(STR_HOR_ROT, 90, ID_HOR_ROT);
  AEFX_CLR_STRUCT(def);
  PF_ADD_FLOAT_SLIDER(STR_HOR_OPACITY,  // Name
                      0,                // VALID_MIN
                      100,              // VALID_MAX
                      0,                // SLIDER_MIN
                      100,              // SLIDER_MAX
                      0,                // CURVE_TOLERANCE
                      100,              // DFLT
                      1,                // PREC
                      0,                // DISP
                      0,                // WANT_PHASE
                      ID_HOR_OPACITY);
  AEFX_CLR_STRUCT(def);
  PF_ADD_SLIDER(STR_DIA_LEN,  // Parameter name
                0,            // Minimum value for numerical input
                300,          // Maximum value for numerical input
                0,            // Slider minimum
                150,          // Slider maximum
                50,           // Default value
                ID_DIA_LEN);
  // Angle
  AEFX_CLR_STRUCT(def);
  PF_ADD_ANGLE(STR_DIA_ROT, 45, ID_DIA_ROT);
  // Angle
  AEFX_CLR_STRUCT(def);
  PF_ADD_ANGLE(STR_DIA_ROT2, -45, ID_DIA_ROT2);
  AEFX_CLR_STRUCT(def);
  PF_ADD_FLOAT_SLIDER(STR_DIA_OPACITY,  // Name
                      0,                // VALID_MIN
                      100,              // VALID_MAX
                      0,                // SLIDER_MIN
                      100,              // SLIDER_MAX
                      0,                // CURVE_TOLERANCE
                      75,               // DFLT
                      1,                // PREC
                      0,                // DISP
                      0,                // WANT_PHASE
                      ID_DIA_OPACITY);

  AEFX_CLR_STRUCT(def);
  PF_END_TOPIC(ID_TOPIC2_END);

  // Popup menu
  AEFX_CLR_STRUCT(def);
  PF_ADD_POPUP(STR_BLEND,
               STR_BLEND_COUNT,  // Number of menus
               STR_BLEND_DFLT,   // Default
               STR_BLEND_ITEMS, ID_BLEND);
  out_data->num_params = ID_NUM_PARAMS;

  return err;
}

static PF_Err GetParams(CFsAE* ae, ParamInfo* infoP) {
  PF_Err err = PF_Err_NONE;

  ERR(ae->GetPOPUP(ID_TAGET_KIND, &infoP->target_kind));
  ERR(ae->GetFLOAT(ID_TAGET_BORDER, &infoP->target_border));
  infoP->target_border /= 100;
  ERR(ae->GetFLOAT(ID_TAGET_SOFT, &infoP->target_softness));
  infoP->target_softness /= 100;

  ERR(ae->GetCOLOR(ID_TARGET_COLOR, &infoP->target_color));
  ERR(ae->GetCHECKBOX(ID_TARGET_MASK, &infoP->target_maskDraw));

  ERR(ae->GetANGLE_FLT(ID_ROT, &infoP->rot));
  infoP->rot = CRot::RoundRot(infoP->rot);

  ERR(ae->GetCHECKBOX(ID_AUTOROLLING, &infoP->autoRolling));
  ERR(ae->GetFLOAT(ID_ROLLINGDPEED, &infoP->rollingSpeed));

  ERR(ae->GetFLOAT(ID_LENGTH, &infoP->length));
  infoP->length /= 100;
  ERR(ae->GetFLOAT(ID_OPACITY, &infoP->opacity));
  infoP->opacity /= 100;
  ERR(ae->GetFLOAT(ID_BRIGHTNESS, &infoP->brigthness));
  infoP->brigthness /= 100;

  ERR(ae->GetPOPUP(ID_COLOR_KIND, &infoP->color_kind));
  ERR(ae->GetCOLOR(ID_COLOR, &infoP->color));

  ERR(ae->GetFLOAT(ID_RAINBOW_OFFSET, &infoP->rainbowOffset));
  ERR(ae->GetFLOAT(ID_RAINBOW_DELTA, &infoP->rainbowDelta));
  infoP->rainbowDelta /= 100;
  infoP->rainbowDelta = ae->downSaleValue() * infoP->rainbowDelta;
  if (infoP->rainbowDelta == 0) infoP->rainbowDelta = 0.001;

  ERR(ae->GetADD(ID_VER_LEN, &infoP->verLength));
  infoP->verLength = ae->downScale(infoP->verLength);

  ERR(ae->GetANGLE_FLT(ID_VER_ROT, &infoP->verRot));
  infoP->verRot = CRot::RoundRot(infoP->verRot);

  ERR(ae->GetFLOAT(ID_VER_OPACITY, &infoP->verOpacity));
  infoP->verOpacity /= 100;

  ERR(ae->GetADD(ID_HOR_LEN, &infoP->horLength));
  infoP->horLength = ae->downScale(infoP->horLength);
  ERR(ae->GetANGLE_FLT(ID_HOR_ROT, &infoP->horRot));
  infoP->horRot = CRot::RoundRot(infoP->horRot);

  ERR(ae->GetFLOAT(ID_HOR_OPACITY, &infoP->horOpacity));
  infoP->horOpacity /= 100;

  ERR(ae->GetADD(ID_DIA_LEN, &infoP->diaLength));
  infoP->diaLength = ae->downScale(infoP->diaLength);
  ERR(ae->GetANGLE_FLT(ID_DIA_ROT, &infoP->diaRot));
  infoP->diaRot = CRot::RoundRot(infoP->diaRot);
  ERR(ae->GetANGLE_FLT(ID_DIA_ROT2, &infoP->diaRot2));
  infoP->diaRot2 = CRot::RoundRot(infoP->diaRot2);

  ERR(ae->GetFLOAT(ID_DIA_OPACITY, &infoP->diaOpacity));
  infoP->diaOpacity /= 100;

  ERR(ae->GetPOPUP(ID_BLEND, &infoP->blend));

  return err;
}
static PF_Err Exec(CFsAE* ae, ParamInfo* infoP) {
  PF_Err err = PF_Err_NONE;

  // Copy screen
  ERR(ae->CopyInToOut());

  switch (ae->pixelFormat()) {
    case PF_PixelFormat_ARGB128:
      ERR(StarExec32(ae, infoP));
      break;
    case PF_PixelFormat_ARGB64:
      ERR(StarExec16(ae, infoP));
      break;
    case PF_PixelFormat_ARGB32:
      ERR(StarExec8(ae, infoP));
      break;
  }
  return err;
}

// Main rendering function
/*
        Hosts that do not support SmartFX (those before After Effects 7) call
   this function to draw. If you write this function, it will be compatible with
   v6.5.
*/
static PF_Err Render(PF_InData* in_data, PF_OutData* out_data,
                     PF_ParamDef* params[], PF_LayerDef* output) {
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
        For SmartFX support, this function is called first to acquire
   parameters.
*/
#if defined(SUPPORT_SMARTFX)
static PF_Err PreRender(PF_InData* in_data, PF_OutData* out_data,
                        PF_PreRenderExtra* extraP) {
  PF_Err err = PF_Err_NONE;
  CFsAE ae(in_data, out_data, extraP, sizeof(ParamInfo), ID_NUM_PARAMS);
  err = ae.resultErr();
  if (!err) {
    ParamInfo* infoP = reinterpret_cast<ParamInfo*>(ae.LockPreRenderData());
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
static PF_Err SmartRender(PF_InData* in_data, PF_OutData* out_data,
                          PF_SmartRenderExtra* extraP) {
  PF_Err err = PF_Err_NONE, err2 = PF_Err_NONE;

  CFsAE ae(in_data, out_data, extraP, ID_NUM_PARAMS);
  err = ae.resultErr();
  if (!err) {
    ParamInfo* infoP = reinterpret_cast<ParamInfo*>(ae.LockPreRenderData());
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

// clang-format off
#include "Fs_Entry.h"
// clang-format on
