
// clang-format off
#include "Frame.h"
#include "Fs_Entry.h"
// clang-format on

// Pass parameters to After Effects
// See Param_Utils.h
static PF_Err ParamsSetup(PF_InData *in_data, PF_OutData *out_data,
                          PF_ParamDef *params[], PF_LayerDef *output) {
  PF_Err err = PF_Err_NONE;
  PF_ParamDef def;

  AEFX_CLR_STRUCT(def);
  PF_ADD_SLIDER(Str_WIDTH_ADD,  // Parameter name
                50,             // Minimum value for numerical input
                4800,           // Maximum value for numerical input
                640,            // Minimum value of the slider
                1920,           // Maximum value of the slider
                1280,           // Default value
                ID_WIDTH_ADD);
  AEFX_CLR_STRUCT(def);
  PF_ADD_SLIDER(Str_HEIGHT_ADD,  // Parameter name
                50,              // Minimum value for numerical input
                4800,            // Maximum value for numerical input
                480,             // Minimum value of the slider
                1080,            // Maximum value of the slider
                720,             // Default value
                ID_HEIGHT_ADD);
  // Specify color
  AEFX_CLR_STRUCT(def);
  PF_ADD_COLOR(Str_LINE_COLOR, 0xFF, 0x00, 0x00, ID_LINE_COLOR);
  AEFX_CLR_STRUCT(def);
  PF_ADD_SLIDER(Str_SAFE_ADD,  // Parameter name
                0,             // Minimum value for numerical input
                100,           // Maximum value for numerical input
                50,            // Minimum value of the slider
                100,           // Maximum value of the slider
                80,            // Default value
                ID_SAFE_ADD);
  // Checkbox
  AEFX_CLR_STRUCT(def);
  PF_ADD_CHECKBOX(Str_CENTER_CB1, Str_CENTER_CB2, TRUE, 0, ID_CENTER_CB);
  // Specify color
  AEFX_CLR_STRUCT(def);
  PF_ADD_COLOR(Str_OUT_COLOR, 0xFF, 0x00, 0xFF, ID_OUT_COLOR);
  AEFX_CLR_STRUCT(def);
  PF_ADD_FIXED(Str_OUT_OPACITY,  // Parameter name
               0,                // Minimum value for numerical input
               100,              // Maximum value for numerical input
               0,                // Minimum value of the slider
               100,              // Maximum value of the slider
               50,               // Default value
               1,                // Flag for numerical display
               0, 0, ID_OUT_OPACITY);
  AEFX_CLR_STRUCT(def);
  PF_ADD_SLIDER(Str_LINE_HEIGHT,  // Parameter name
                1,                // Minimum value for numerical input
                10,               // Maximum value for numerical input
                1,                // Minimum value of the slider
                5,                // Maximum value of the slider
                2,                // Default value
                ID_LINE_HEIGHT);
  // 7th parameter
  // Popup menu
  AEFX_CLR_STRUCT(def);
  PF_ADD_POPUP(Str_SIZE_POP1,
               7,  // Number of menus
               1,  // Default
               Str_SIZE_POP2, ID_SIZE_POP);

  out_data->num_params = ID_NUM_PARAMS;

  return err;
}

static PF_Err GetParams(CFsAE *ae, ParamInfo *infoP) {
  PF_Err err = PF_Err_NONE;
  if ((ae == NULL) || (infoP == NULL)) {
    err = PF_Err_BAD_CALLBACK_PARAM;
    return err;
  }
  ERR(ae->GetPOPUP(ID_SIZE_POP, &infoP->size_kind));
  if (!err) {
    switch (infoP->size_kind) {
      case SIZE_720_540:
        infoP->frame_Width = 720;
        infoP->frame_Height = 540;
        break;
      case SIZE_1024_576:
        infoP->frame_Width = 1024;
        infoP->frame_Height = 576;
        break;
      case SIZE_1024_768:
        infoP->frame_Width = 1024;
        infoP->frame_Height = 768;
        break;
      case SIZE_1280_720:
        infoP->frame_Width = 1280;
        infoP->frame_Height = 720;
        break;
      case SIZE_1440_810:
        infoP->frame_Width = 1440;
        infoP->frame_Height = 810;
        break;
      case SIZE_1920_1080:
        infoP->frame_Width = 1920;
        infoP->frame_Height = 1080;
        break;
      case SIZE_CUSTUM:
      default:
        ERR(ae->GetADD(ID_WIDTH_ADD, &infoP->frame_Width));
        ERR(ae->GetADD(ID_HEIGHT_ADD, &infoP->frame_Height));
        break;
    }
    // infoP->frame_Width = ae->downScale(infoP->frame_Width);
    // infoP->frame_Height = ae->downScale(infoP->frame_Height);

    ERR(ae->GetCOLOR(ID_LINE_COLOR, &infoP->line_color));
    ERR(ae->GetADD(ID_SAFE_ADD, &infoP->safe_frame));
    ERR(ae->GetCHECKBOX(ID_CENTER_CB, &infoP->center_line));
    ERR(ae->GetCOLOR(ID_OUT_COLOR, &infoP->out_color));
    ERR(ae->GetFIXED2FpShort(ID_OUT_OPACITY, &infoP->out_opacity));
    if (!err) {
      infoP->out_opacity /= 100;
      infoP->out_color.alpha =
          RoundByteFpShort(PF_MAX_CHAN8 * infoP->out_opacity);
    }
    ERR(ae->GetADD(ID_LINE_HEIGHT, &infoP->line_height));
    /*
    if ( !err) {
            infoP->line_height = ae->downScale(infoP->line_height);
            infoP->center_x		= ae->out->width() /2;
            infoP->center_y		= ae->out->height() /2;
            infoP->frm.top		= (A_short)(infoP->center_y -
    (infoP->frame_Height /2)); infoP->frm.bottom	=
    (A_short)(infoP->center_y + (infoP->frame_Height /2) -1); infoP->frm.left
    = (A_short)(infoP->center_x - (infoP->frame_Width /2)); infoP->frm.right
    = (A_short)(infoP->center_x + (infoP->frame_Width /2) -1);

            A_long sW			= infoP->frame_Width * infoP->safe_frame
    / 100; A_long sH			= infoP->frame_Height *
    infoP->safe_frame / 100; infoP->safe.top		=
    (A_short)(infoP->center_y - (sH /2)); infoP->safe.bottom	=
    (A_short)(infoP->center_y + (sH /2) -1); infoP->safe.left	=
    (A_short)(infoP->center_x - (sW /2)); infoP->safe.right	=
    (A_short)(infoP->center_x + (sW /2) -1);
    }
    */
  }
  return err;
}

static PF_Err Exec(CFsAE *ae, ParamInfo *infoP) {
  PF_Err err = PF_Err_NONE;

  infoP->frame_Width = ae->downScale(infoP->frame_Width);
  infoP->frame_Height = ae->downScale(infoP->frame_Height);

  infoP->line_height = ae->downScale(infoP->line_height);
  infoP->center_x = ae->out->width() / 2;
  infoP->center_y = ae->out->height() / 2;
  infoP->frm.top = (A_short)(infoP->center_y - (infoP->frame_Height / 2));
  infoP->frm.bottom =
      (A_short)(infoP->center_y + (infoP->frame_Height / 2) - 1);
  infoP->frm.left = (A_short)(infoP->center_x - (infoP->frame_Width / 2));
  infoP->frm.right = (A_short)(infoP->center_x + (infoP->frame_Width / 2) - 1);

  A_long sW = infoP->frame_Width * infoP->safe_frame / 100;
  A_long sH = infoP->frame_Height * infoP->safe_frame / 100;
  infoP->safe.top = (A_short)(infoP->center_y - (sH / 2));
  infoP->safe.bottom = (A_short)(infoP->center_y + (sH / 2) - 1);
  infoP->safe.left = (A_short)(infoP->center_x - (sW / 2));
  infoP->safe.right = (A_short)(infoP->center_x + (sW / 2) - 1);

  PF_InData *in_data;
  in_data = ae->in_data;

  ERR(PF_FILL(NULL, NULL, ae->output));
  ERR(PF_FILL(&infoP->out_color, NULL, ae->output));
  ERR(PF_FILL(NULL, &infoP->frm, ae->output));
  A_long bak = ae->out->lineHeiht;
  ae->out->lineHeiht = infoP->line_height;
  ae->out->box(infoP->frm.left, infoP->frm.top, infoP->frm.right,
               infoP->frm.bottom, infoP->line_color, infoP->line_color);
  if (infoP->center_line == TRUE) {
    A_long p = ae->out->lineHeiht / 2;
    ae->out->XLine(0, ae->out->width(), infoP->center_y - p, infoP->line_color);
    ae->out->YLine(infoP->center_x - p, 0, ae->out->height(),
                   infoP->line_color);
  }
  if ((infoP->safe_frame > 0) && (infoP->safe_frame < 100)) {
    ae->out->box(infoP->safe.left, infoP->safe.top, infoP->safe.right,
                 infoP->safe.bottom, infoP->line_color, infoP->line_color);
  }

  return err;
}

// Main rendering function
/*
        Hosts that do not support SmartFX (such as After Effects 7 and earlier)
   call this function to render. Writing this function makes it compatible with
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
        For SmartFX support, this function is called first to acquire
   parameters.
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
