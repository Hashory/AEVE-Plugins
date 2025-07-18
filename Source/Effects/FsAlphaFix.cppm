#include <string_view>

constexpr std::string_view NAME = "Gamma_Table";
constexpr std::string_view DESCRIPTION = "Perform simple image gamma correction.";


constexpr int MAJOR_VERSION = 1;
constexpr int MINOR_VERSION = 0;
constexpr int BUG_VERSION = 0;
constexpr int STAGE_VERSION = PF_Stage_DEVELOP;
constexpr int BUILD_VERSION = 0;


#include "Gamma_Table.h"

static PF_Err About(PF_InData *in_data, PF_OutData *out_data,
                    PF_ParamDef *params[], PF_LayerDef *output) {
  PF_SPRINTF(out_data->return_msg, "%s, v%d.%d\r%s", NAME, MAJOR_VERSION,
             MINOR_VERSION, DESCRIPTION);

  return PF_Err_NONE;
}

static PF_Err GlobalSetup(PF_InData *in_data, PF_OutData *out_data,
                          PF_ParamDef *params[], PF_LayerDef *output) {
  PF_Err err = PF_Err_NONE;

  out_data->my_version = PF_VERSION(MAJOR_VERSION, MINOR_VERSION, BUG_VERSION,
                                    STAGE_VERSION, BUILD_VERSION);

  out_data->out_flags |=
      PF_OutFlag_PIX_INDEPENDENT | PF_OutFlag_USE_OUTPUT_EXTENT;

  out_data->out_flags2 = PF_OutFlag2_SUPPORTS_THREADED_RENDERING;

  return err;
}

static PF_Err ParamsSetup(PF_InData *in_data, PF_OutData *out_data,
                          PF_ParamDef *params[], PF_LayerDef *output) {
  PF_Err err = PF_Err_NONE;
  PF_ParamDef def;
  AEFX_CLR_STRUCT(def);

  PF_ADD_FIXED("Gamma", GAMMA_MIN, GAMMA_BIG_MAX, GAMMA_MIN, GAMMA_MAX,
               GAMMA_DFLT, 1, 0, 0, GAMMA_DISK_ID);

  out_data->num_params = GAMMA_NUM_PARAMS;

  return err;
}

static PF_Err SequenceSetup(PF_InData *in_data, PF_OutData *out_data,
                            PF_ParamDef *params[], PF_LayerDef *output) {
  Gamma_Table *g_tableP;
  A_long iL = 0;

  if (out_data->sequence_data) {
    PF_DISPOSE_HANDLE(out_data->sequence_data);
  }
  out_data->sequence_data = PF_NEW_HANDLE(sizeof(Gamma_Table));
  if (!out_data->sequence_data) {
    return PF_Err_INTERNAL_STRUCT_DAMAGED;
  }

  // generate base table

  g_tableP = *(Gamma_Table **)out_data->sequence_data;
  g_tableP->gamma_val = (1L << 16);

  for (iL = 0; iL <= PF_MAX_CHAN8; iL++) {
    g_tableP->lut[iL] = (A_u_char)iL;
  }

  return PF_Err_NONE;
}

static PF_Err SequenceSetdown(PF_InData *in_data, PF_OutData *out_data,
                              PF_ParamDef *params[], PF_LayerDef *output) {
  if (in_data->sequence_data) {
    PF_DISPOSE_HANDLE(in_data->sequence_data);
    out_data->sequence_data = NULL;
  }
  return PF_Err_NONE;
}

static PF_Err SequenceResetup(PF_InData *in_data, PF_OutData *out_data,
                              PF_ParamDef *params[], PF_LayerDef *output) {
  if (!in_data->sequence_data) {
    return SequenceSetup(in_data, out_data, params, output);
  }
  return PF_Err_NONE;
}

// Computes the gamma-corrected pixel given the lookup table.

static PF_Err GammaFunc(void *refcon, A_long x, A_long y, PF_Pixel *inP,
                        PF_Pixel *outP) {
  PF_Err err = PF_Err_NONE;
  GammaInfo *giP = (GammaInfo *)refcon;

  if (giP) {
    outP->alpha = inP->alpha;
    outP->red = giP->lut[inP->red];
    outP->green = giP->lut[inP->green];
    outP->blue = giP->lut[inP->blue];
  } else {
    err = PF_Err_BAD_CALLBACK_PARAM;
  }
  return err;
}

static PF_Err Render(PF_InData *in_data, PF_OutData *out_data,
                     PF_ParamDef *params[], PF_LayerDef *output) {
  PF_Err err = PF_Err_NONE;
  A_long xL = 0, progress_heightL = 0;
  Gamma_Table *g_tableP = NULL;
  GammaInfo gamma_info;

  AEFX_CLR_STRUCT(gamma_info);

  // If the gamma factor is exactly 1.0 just make a direct copy.

  if (params[GAMMA_GAMMA]->u.fd.value == (1L << 16)) {
    ERR(PF_COPY(&params[0]->u.ld, output, NULL, NULL));
  } else {
    // If no table exists, pop an error message.

    if (!out_data->sequence_data) {
      PF_STRCPY(out_data->return_msg,
                "Gamma effect invoked without lookup table");
      out_data->out_flags |= PF_OutFlag_DISPLAY_ERROR_MESSAGE;
      err = PF_Err_INTERNAL_STRUCT_DAMAGED;
    }

    if (!err) {
      g_tableP = *(Gamma_Table **)out_data->sequence_data;

      if (g_tableP->gamma_val != params[GAMMA_GAMMA]->u.fd.value) {
        // if the table values are bad, regenerate table contents.

        double temp, gamma;

        g_tableP->gamma_val = params[GAMMA_GAMMA]->u.fd.value;
        gamma = (PF_FpLong)g_tableP->gamma_val / (double)(1L << 16);
        gamma = 1.0 / gamma;

        for (xL = 0; xL <= PF_MAX_CHAN8; ++xL) {
          temp = PF_POW((PF_FpLong)xL / 255.0, gamma);
          g_tableP->lut[xL] = (A_u_char)(temp * 255.0);
        }
      }

      // clear all pixels outside extent_hint.

      if (in_data->extent_hint.left != output->extent_hint.left ||
          in_data->extent_hint.top != output->extent_hint.top ||
          in_data->extent_hint.right != output->extent_hint.right ||
          in_data->extent_hint.bottom != output->extent_hint.bottom) {
        ERR(PF_FILL(NULL, &output->extent_hint, output));
      }
    }
    if (!err) {
      // iterate over image data.

      progress_heightL = in_data->extent_hint.top - in_data->extent_hint.bottom;
      gamma_info.lut = g_tableP->lut;

      ERR(PF_ITERATE(0, progress_heightL, &params[GAMMA_INPUT]->u.ld,
                     &in_data->extent_hint, (void *)&gamma_info, GammaFunc,
                     output));
    }
  }
  return err;
}

PF_Err EffectMain(PF_Cmd cmd, PF_InData *in_data, PF_OutData *out_data,
                  PF_ParamDef *params[], PF_LayerDef *output) {
  PF_Err err = PF_Err_NONE;

  switch (cmd) {
    case PF_Cmd_ABOUT:
      err = About(in_data, out_data, params, output);
      break;
    case PF_Cmd_GLOBAL_SETUP:
      err = GlobalSetup(in_data, out_data, params, output);
      break;
    case PF_Cmd_PARAMS_SETUP:
      err = ParamsSetup(in_data, out_data, params, output);
      break;
    case PF_Cmd_SEQUENCE_SETUP:
      err = SequenceSetup(in_data, out_data, params, output);
      break;
    case PF_Cmd_SEQUENCE_SETDOWN:
      err = SequenceSetdown(in_data, out_data, params, output);
      break;
    case PF_Cmd_SEQUENCE_RESETUP:
      err = SequenceResetup(in_data, out_data, params, output);
      break;
    case PF_Cmd_RENDER:
      err = Render(in_data, out_data, params, output);
      break;
  }
  return err;
}
