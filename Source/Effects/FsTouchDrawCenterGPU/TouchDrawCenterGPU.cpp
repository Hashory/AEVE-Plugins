// clang-format off
#if HAS_CUDA
  #include <cuda_runtime.h>
  // SDK_Invert_ProcAmp.h defines these and are needed whereas the cuda_runtime ones are not.
  #undef MAJOR_VERSION
  #undef MINOR_VERSION
#endif

#include "TouchDrawCenterGPU.h"
#include <iostream>

// brings in M_PI on Windows
#define _USE_MATH_DEFINES
#include <math.h>
// clang-format on

inline PF_Err CL2Err(cl_int cl_result) {
  if (cl_result == CL_SUCCESS) {
    return PF_Err_NONE;
  } else {
    // set a breakpoint here to pick up OpenCL errors.
    return PF_Err_INTERNAL_STRUCT_DAMAGED;
  }
}

#define CL_ERR(FUNC) ERR(CL2Err(FUNC))

//  CUDA kernel; see TouchDrawCenterGPU.cu.
extern void TouchDrawCenter_CUDA(float const *src, float *dst,
                                 unsigned int srcPitch, unsigned int dstPitch,
                                 int is16f, unsigned int width,
                                 unsigned int height,
                                 const TouchDrawCenterParams *params);

static PF_Err About(PF_InData *in_data, PF_OutData *out_data,
                    PF_ParamDef *params[], PF_LayerDef *output) {
  PF_SPRINTF(out_data->return_msg, "%s, v%d.%d\r%s", NAME, MAJOR_VERSION,
             MINOR_VERSION, DESCRIPTION);

  return PF_Err_NONE;
}

static PF_Err GlobalSetup(PF_InData *in_dataP, PF_OutData *out_data,
                          PF_ParamDef *params[], PF_LayerDef *output) {
  PF_Err err = PF_Err_NONE;

  out_data->my_version = PF_VERSION(MAJOR_VERSION, MINOR_VERSION, BUG_VERSION,
                                    STAGE_VERSION, BUILD_VERSION);

  out_data->out_flags =
      PF_OutFlag_PIX_INDEPENDENT | PF_OutFlag_DEEP_COLOR_AWARE;

  out_data->out_flags2 = PF_OutFlag2_FLOAT_COLOR_AWARE |
                         PF_OutFlag2_SUPPORTS_SMART_RENDER |
                         PF_OutFlag2_SUPPORTS_THREADED_RENDERING;

  // For Premiere - declare supported pixel formats
  if (in_dataP->appl_id == 'PrMr') {
    AEFX_SuiteScoper<PF_PixelFormatSuite1> pixelFormatSuite =
        AEFX_SuiteScoper<PF_PixelFormatSuite1>(in_dataP, kPFPixelFormatSuite,
                                               kPFPixelFormatSuiteVersion1,
                                               out_data);

    //	Add the pixel formats we support in order of preference.
    (*pixelFormatSuite->ClearSupportedPixelFormats)(in_dataP->effect_ref);
    (*pixelFormatSuite->AddSupportedPixelFormat)(in_dataP->effect_ref,
                                                 PrPixelFormat_VUYA_4444_32f);
  } else {
    out_data->out_flags2 |= PF_OutFlag2_SUPPORTS_GPU_RENDER_F32 |
                            PF_OutFlag2_SUPPORTS_DIRECTX_RENDERING;
  }

  return err;
}

static PF_Err ParamsSetup(PF_InData *in_data, PF_OutData *out_data,
                          PF_ParamDef *params[], PF_LayerDef *output) {
  PF_Err err = PF_Err_NONE;
  PF_ParamDef def;

  // Integer slider
  AEFX_CLR_STRUCT(def);
  PF_ADD_SLIDER("RandomSeed",  // Parameter name
                0,             // Minimum value for numeric input
                32000,         // Maximum value for numeric input
                0,             // Minimum value for slider
                144,           // Maximum value for slider
                0,             // Default value
                ID_SEED);

  // Position specification
  AEFX_CLR_STRUCT(def);
  PF_ADD_POINT("Center",  // Parameter name
               50,        // X
               50,        // Y
               0,         // Flag
               ID_CENTER);

  // Fixed-point decimal slider
  AEFX_CLR_STRUCT(def);
  PF_ADD_FIXED("Length",  // Parameter name
               0,         // Minimum value for numeric input
               200,       // Maximum value for numeric input
               0,         // Minimum value for slider
               100,       // Maximum value for slider
               100,       // Default value
               1,         // Flag for numeric display
               0, 0, ID_LENGTH_MAX);

  // Fixed-point decimal slider
  AEFX_CLR_STRUCT(def);
  PF_ADD_FIXED("Length_Random",  // Parameter name
               0,                // Minimum value for numeric input
               200,              // Maximum value for numeric input
               0,                // Minimum value for slider
               100,              // Maximum value for slider
               50,               // Default value
               1,                // Flag for numeric display
               0, 0, ID_LENGTH_RND);

  // Integer slider
  AEFX_CLR_STRUCT(def);
  PF_ADD_SLIDER("Value",  // Parameter name
                0,        // Minimum value for numeric input
                3000,     // Maximum value for numeric input
                0,        // Minimum value for slider
                100,      // Maximum value for slider
                30,       // Default value
                ID_Y);

  // Color specification
  AEFX_CLR_STRUCT(def);
  PF_ADD_COLOR("Color", 0x00, 0x00, 0x00, ID_COLOR);

  // Fixed-point decimal slider
  AEFX_CLR_STRUCT(def);
  PF_ADD_FIXED("Opacity",  // Parameter name
               0,          // Minimum value for numeric input
               200,        // Maximum value for numeric input
               0,          // Minimum value for slider
               100,        // Maximum value for slider
               100,        // Default value
               1,          // Flag for numeric display
               0, 0, ID_OPACITY);

  // Fixed-point decimal slider
  AEFX_CLR_STRUCT(def);
  PF_ADD_FIXED("Opacity_Random",  // Parameter name
               0,                 // Minimum value for numeric input
               200,               // Maximum value for numeric input
               0,                 // Minimum value for slider
               100,               // Maximum value for slider
               50,                // Default value
               1,                 // Flag for numeric display
               0, 0, ID_OPACITY_RND);

  // Integer slider
  AEFX_CLR_STRUCT(def);
  PF_ADD_SLIDER("Point_Count",  // Parameter name
                0,              // Minimum value for numeric input
                100,            // Maximum value for numeric input
                0,              // Minimum value for slider
                10,             // Maximum value for slider
                5,              // Default value
                ID_POINT_COUNT);

  // Fixed-point decimal slider
  AEFX_CLR_STRUCT(def);
  PF_ADD_FIXED("Point_Length",  // Parameter name
               0,               // Minimum value for numeric input
               300,             // Maximum value for numeric input
               0,               // Minimum value for slider
               30,              // Maximum value for slider
               10,              // Default value
               1,               // Flag for numeric display
               0, 0, ID_POINT_LENGTH);

  // Checkbox
  AEFX_CLR_STRUCT(def);
  PF_ADD_CHECKBOX("Original_Blend", "ON", TRUE, 0, ID_ORG);

  out_data->num_params = ID_NUM_PARAMS;

  return err;
}

#if HAS_METAL
PF_Err NSError2PFErr(NSError *inError) {
  if (inError) {
    return PF_Err_INTERNAL_STRUCT_DAMAGED;  // For debugging, uncomment above
                                            // line and set breakpoint here
  }
  return PF_Err_NONE;
}
#endif  // HAS_METAL

// GPU data initialized at GPU setup and used during render.
struct OpenCLGPUData {
  cl_kernel touch_draw_kernel;
};

#if HAS_HLSL
inline PF_Err DXErr(bool inSuccess) {
  if (inSuccess) {
    return PF_Err_NONE;
  } else {
    return PF_Err_INTERNAL_STRUCT_DAMAGED;
  }
}
#define DX_ERR(FUNC) ERR(DXErr(FUNC))
#include "DirectXUtils.h"
struct DirectXGPUData {
  DXContextPtr mContext;
  ShaderObjectPtr mTouchDrawShader;
};
#endif

#if HAS_METAL
struct MetalGPUData {
  id<MTLComputePipelineState> touch_draw_pipeline;
};
#endif

static PF_Err GPUDeviceSetup(PF_InData *in_dataP, PF_OutData *out_dataP,
                             PF_GPUDeviceSetupExtra *extraP) {
  PF_Err err = PF_Err_NONE;

  PF_GPUDeviceInfo device_info;
  AEFX_CLR_STRUCT(device_info);

  AEFX_SuiteScoper<PF_HandleSuite1> handle_suite =
      AEFX_SuiteScoper<PF_HandleSuite1>(in_dataP, kPFHandleSuite,
                                        kPFHandleSuiteVersion1, out_dataP);

  AEFX_SuiteScoper<PF_GPUDeviceSuite1> gpuDeviceSuite =
      AEFX_SuiteScoper<PF_GPUDeviceSuite1>(
          in_dataP, kPFGPUDeviceSuite, kPFGPUDeviceSuiteVersion1, out_dataP);

  gpuDeviceSuite->GetDeviceInfo(in_dataP->effect_ref,
                                extraP->input->device_index, &device_info);

  // Load and compile the kernel - a real plugin would cache binaries to disk

  if (extraP->input->what_gpu == PF_GPU_Framework_CUDA) {
    // Nothing to do here. CUDA Kernel statically linked
    out_dataP->out_flags2 = PF_OutFlag2_SUPPORTS_GPU_RENDER_F32;
  } else if (extraP->input->what_gpu == PF_GPU_Framework_OPENCL) {
    PF_Handle gpu_dataH = handle_suite->host_new_handle(sizeof(OpenCLGPUData));
    OpenCLGPUData *cl_gpu_data = reinterpret_cast<OpenCLGPUData *>(*gpu_dataH);

    cl_int result = CL_SUCCESS;

    char const *k16fString = "#define GF_OPENCL_SUPPORTS_16F 0\n";

    size_t sizes[] = {strlen(k16fString),
                      strlen(kSDK_Invert_ProcAmp_Kernel_OpenCLString)};
    char const *strings[] = {k16fString,
                             kSDK_Invert_ProcAmp_Kernel_OpenCLString};
    cl_context context = (cl_context)device_info.contextPV;
    cl_device_id device = (cl_device_id)device_info.devicePV;

    cl_program program;
    if (!err) {
      program = clCreateProgramWithSource(context, 2, &strings[0], &sizes[0],
                                          &result);
      CL_ERR(result);
    }

    CL_ERR(clBuildProgram(program, 1, &device,
                          "-cl-single-precision-constant -cl-fast-relaxed-math",
                          0, 0));

    if (!err) {
      cl_gpu_data->touch_draw_kernel =
          clCreateKernel(program, "TouchDrawCenterKernel", &result);
      CL_ERR(result);
    }

    extraP->output->gpu_data = gpu_dataH;

    out_dataP->out_flags2 = PF_OutFlag2_SUPPORTS_GPU_RENDER_F32;
  }
#if HAS_HLSL
  else if (extraP->input->what_gpu == PF_GPU_Framework_DIRECTX) {
    PF_Handle gpu_dataH = handle_suite->host_new_handle(sizeof(DirectXGPUData));
    DirectXGPUData *dx_gpu_data =
        reinterpret_cast<DirectXGPUData *>(*gpu_dataH);
    memset(dx_gpu_data, 0, sizeof(DirectXGPUData));

    // Create objects
    dx_gpu_data->mContext = std::make_shared<DXContext>();
    dx_gpu_data->mInvertShader = std::make_shared<ShaderObject>();
    dx_gpu_data->mProcAmpShader = std::make_shared<ShaderObject>();

    // Create the DXContext
    DX_ERR(dx_gpu_data->mContext->Initialize(
        (ID3D12Device *)device_info.devicePV,
        (ID3D12CommandQueue *)device_info.command_queuePV));

    std::wstring csoPath, sigPath;

    DX_ERR(GetShaderPath(L"TouchDrawCenterKernel", csoPath, sigPath));
    DX_ERR(dx_gpu_data->mContext->LoadShader(csoPath.c_str(), sigPath.c_str(),
                                             dx_gpu_data->mTouchDrawShader));

    extraP->output->gpu_data = gpu_dataH;
    out_dataP->out_flags2 = PF_OutFlag2_SUPPORTS_GPU_RENDER_F32;
  }
#endif
#if HAS_METAL
  else if (extraP->input->what_gpu == PF_GPU_Framework_METAL) {
    ScopedAutoreleasePool pool;

    // Create a library from source
    NSString *source =
        [NSString stringWithCString:kSDK_Invert_ProcAmp_Kernel_MetalString
                           encoding:NSUTF8StringEncoding];
    id<MTLDevice> device = (id<MTLDevice>)device_info.devicePV;

    NSError *error = nil;
    id<MTLLibrary> library =
        [[device newLibraryWithSource:source options:nil error:&error]
            autorelease];

    // An error code is set for Metal compile warnings, so use nil library as
    // the error signal
    if (!err && !library) {
      err = NSError2PFErr(error);
    }

    // For debugging only. This will contain Metal compile warnings and erorrs.
    NSString *getError = error.localizedDescription;

    PF_Handle metal_handle =
        handle_suite->host_new_handle(sizeof(MetalGPUData));
    MetalGPUData *metal_data = reinterpret_cast<MetalGPUData *>(*metal_handle);

    // Create pipeline state from function extracted from library
    if (err == PF_Err_NONE) {
      id<MTLFunction> touch_draw_function = nil;
      NSString *kernel_name =
          [NSString stringWithCString:"TouchDrawCenterKernel"
                             encoding:NSUTF8StringEncoding];
      touch_draw_function =
          [[library newFunctionWithName:kernel_name] autorelease];

      if (!touch_draw_function) {
        err = PF_Err_INTERNAL_STRUCT_DAMAGED;
      }

      if (!err) {
        metal_data->touch_draw_pipeline =
            [device newComputePipelineStateWithFunction:touch_draw_function
                                                  error:&error];
        err = NSError2PFErr(error);
      }

      if (!err) {
        extraP->output->gpu_data = metal_handle;
        out_dataP->out_flags2 = PF_OutFlag2_SUPPORTS_GPU_RENDER_F32;
      }
    }
  }
#endif
  return err;
}

static PF_Err GPUDeviceSetdown(PF_InData *in_dataP, PF_OutData *out_dataP,
                               PF_GPUDeviceSetdownExtra *extraP) {
  PF_Err err = PF_Err_NONE;

  if (extraP->input->what_gpu == PF_GPU_Framework_OPENCL) {
    PF_Handle gpu_dataH = (PF_Handle)extraP->input->gpu_data;
    OpenCLGPUData *cl_gpu_dataP = reinterpret_cast<OpenCLGPUData *>(*gpu_dataH);

    (void)clReleaseKernel(cl_gpu_dataP->invert_kernel);
    (void)clReleaseKernel(cl_gpu_dataP->procamp_kernel);

    AEFX_SuiteScoper<PF_HandleSuite1> handle_suite =
        AEFX_SuiteScoper<PF_HandleSuite1>(in_dataP, kPFHandleSuite,
                                          kPFHandleSuiteVersion1, out_dataP);

    handle_suite->host_dispose_handle(gpu_dataH);
  }
#if HAS_HLSL
  else if (extraP->input->what_gpu == PF_GPU_Framework_DIRECTX) {
    PF_Handle gpu_dataH = (PF_Handle)extraP->input->gpu_data;
    DirectXGPUData *dx_gpu_dataP =
        reinterpret_cast<DirectXGPUData *>(*gpu_dataH);

    // Note: DirectX: If deferred execution is implemented, a GPU sync is
    // necessary before the plugin shutdown.
    dx_gpu_dataP->mContext.reset();
    dx_gpu_dataP->mInvertShader.reset();
    dx_gpu_dataP->mProcAmpShader.reset();

    AEFX_SuiteScoper<PF_HandleSuite1> handle_suite =
        AEFX_SuiteScoper<PF_HandleSuite1>(in_dataP, kPFHandleSuite,
                                          kPFHandleSuiteVersion1, out_dataP);

    handle_suite->host_dispose_handle(gpu_dataH);
  }
#endif

  return err;
}

static PF_Err FilterImage16(void *refcon, A_long xL, A_long yL, PF_Pixel16 *inP,
                            PF_Pixel16 *outP) {
  PF_Err err = PF_Err_NONE;

  InvertProcAmpParams *infoP = reinterpret_cast<InvertProcAmpParams *>(refcon);

  PF_Pixel16 tmp;
  tmp.red = 32768 - inP->red;
  tmp.green = 32768 - inP->green;
  tmp.blue = 32768 - inP->blue;

  /* RGB -> YUV */
  A_u_short srcY((((int32_t)(tmp.red) * 9798 + (int32_t)(tmp.green) * 19235 +
                   (int32_t)(tmp.blue) * 3735) +
                  16384) >>
                 15);
  A_short srcU((((int32_t)(tmp.red) * -5529 + (int32_t)(tmp.green) * -10855 +
                 (int32_t)(tmp.blue) * 16384) +
                16384) >>
               15);
  A_short srcV((((int32_t)(tmp.red) * 16384 + (int32_t)(tmp.green) * -13720 +
                 (int32_t)(tmp.blue) * -2664) +
                16384) >>
               15);

  /* Render ProcAmp */
  int32_t contrast = (int32_t)(infoP->mContrast * 32768.0f + 0.5f);
  int32_t brightness = (int32_t)(infoP->mBrightness * 32768.0f + 0.5f);
  int32_t cosSat = (int32_t)(infoP->mHueCosSaturation * 32768.0f + 0.5f);
  int32_t sinHue = (int32_t)(infoP->mHueSinSaturation * 32768.0f + 0.5f);

  int32_t dstY = ((contrast * srcY) + brightness * 32768 + 16384) >> 15;
  int32_t dstU = ((srcU * cosSat) + (srcV * -sinHue) + 16384) >> 15;
  int32_t dstV = ((srcV * cosSat) + (srcU * sinHue) + 16384) >> 15;

  /* YUV -> RGB */
  int32_t dstR = (dstY * 32768 + dstV * 45940 + 16384) >> 15;
  int32_t dstG = (dstY * 32768 + dstU * -11277 + dstV * -23401 + 16384) >> 15;
  int32_t dstB = (dstY * 32768 + dstU * 58065 + 16384) >> 15;

  outP->red = MIN(MAX(0, dstR), 32768);
  outP->green = MIN(MAX(0, dstG), 32768);
  outP->blue = MIN(MAX(0, dstB), 32768);
  outP->alpha = inP->alpha;

  return err;
}

static PF_Err FilterImage8(void *refcon, A_long xL, A_long yL, PF_Pixel8 *inP,
                           PF_Pixel8 *outP) {
  PF_Err err = PF_Err_NONE;

  // Rescale and call the 16-bit version.
  PF_Pixel16 tmpSrc;

  // rescale [0..255] -> [0..32768]
  tmpSrc.red = (int32_t)((inP->red * 257) >> 1) + (inP->red & 0x1);
  tmpSrc.green = (int32_t)((inP->green * 257) >> 1) + (inP->green & 0x1);
  tmpSrc.blue = (int32_t)((inP->blue * 257) >> 1) + (inP->blue & 0x1);
  tmpSrc.alpha = (int32_t)((inP->alpha * 257) >> 1) + (inP->alpha & 0x1);

  PF_Pixel16 tmpDst;
  err = FilterImage16(refcon, xL, yL, &tmpSrc, &tmpDst);

  if (!err) {
    outP->red = (A_u_char)((tmpDst.red >> 7) - ((tmpDst.red - 1) >> 14));
    outP->green = (A_u_char)((tmpDst.green >> 7) - ((tmpDst.green - 1) >> 14));
    outP->blue = (A_u_char)((tmpDst.blue >> 7) - ((tmpDst.blue - 1) >> 14));
    outP->alpha = inP->alpha;
  }

  return err;
}

static PF_Err FilterImage32(void *refcon, A_long xL, A_long yL,
                            PF_PixelFloat *inP, PF_PixelFloat *outP) {
  PF_Err err = PF_Err_NONE;

  InvertProcAmpParams *infoP = reinterpret_cast<InvertProcAmpParams *>(refcon);

  PF_PixelFloat tmp;
  tmp.red = 1.0f - inP->red;
  tmp.green = 1.0f - inP->green;
  tmp.blue = 1.0f - inP->blue;

  /* RGB -> YUV */
  float srcY = tmp.red * 0.299f + tmp.green * 0.587f + tmp.blue * 0.114f;
  float srcU = tmp.red * -0.168736f + tmp.green * -0.331264f + tmp.blue * 0.5f;
  float srcV = tmp.red * 0.5f + tmp.green * -0.418688f + tmp.blue * -0.081312f;

  /* Render ProcAmp */
  float dstY = (infoP->mContrast * srcY) + infoP->mBrightness;
  float dstU =
      (srcU * infoP->mHueCosSaturation) + (srcV * -infoP->mHueSinSaturation);
  float dstV =
      (srcV * infoP->mHueCosSaturation) + (srcU * infoP->mHueSinSaturation);

  /* YUV -> RGB */
  outP->red = dstY * 1.0f + dstU * 0.0f + dstV * 1.402f;
  outP->green = dstY * 1.0f + dstU * -0.344136f + dstV * -0.714136f;
  outP->blue = dstY * 1.0f + dstU * 1.772f + dstV * 0.0f;
  outP->alpha = inP->alpha;

  return err;
}

static PF_Err Render(PF_InData *in_dataP, PF_OutData *out_dataP,
                     PF_ParamDef *params[], PF_LayerDef *output) {
  if (in_dataP->appl_id == 'PrMr') {
    PF_LayerDef *src = &params[0]->u.ld;
    PF_LayerDef *dest = output;

    const char *srcData = (const char *)src->data;
    char *destData = (char *)dest->data;

    float brightness =
        (float)FIX_2_FLOAT(params[SDK_INVERT_PROCAMP_BRIGHTNESS]->u.fd.value) /
        100.0f;
    float contrast =
        (float)FIX_2_FLOAT(params[SDK_INVERT_PROCAMP_CONTRAST]->u.fd.value) /
        100.0f;
    float hue = (float)FIX_2_FLOAT(params[SDK_INVERT_PROCAMP_HUE]->u.ad.value);
    float saturation =
        (float)FIX_2_FLOAT(params[SDK_INVERT_PROCAMP_SATURATION]->u.fd.value) /
        100.0f;

    float hueRadians = (float)(M_PI / 180) * hue;
    float hueCosSaturation = (float)cos(hueRadians) * saturation;
    float hueSinSaturation = (float)sin(hueRadians) * saturation;

    for (int y = 0; y < output->height;
         ++y, srcData += src->rowbytes, destData += dest->rowbytes) {
      for (int x = 0; x < output->width; ++x) {
        float v = ((const float *)srcData)[x * 4 + 0];
        float u = ((const float *)srcData)[x * 4 + 1];
        float y = ((const float *)srcData)[x * 4 + 2];
        float a = ((const float *)srcData)[x * 4 + 3];

        // invert
        y = 1.0f - y;
        u *= -1.0f;
        v *= -1.0f;

        ((float *)destData)[x * 4 + 0] =
            (v * hueCosSaturation) + (u * hueSinSaturation);
        ((float *)destData)[x * 4 + 1] =
            (u * hueCosSaturation) + (v * -hueSinSaturation);
        ((float *)destData)[x * 4 + 2] = (contrast * y) + brightness;
        ((float *)destData)[x * 4 + 3] = a;
      }
    }
  }

  return PF_Err_NONE;
}

static void DisposePreRenderData(void *pre_render_dataPV) {
  if (pre_render_dataPV) {
    InvertProcAmpParams *infoP =
        reinterpret_cast<InvertProcAmpParams *>(pre_render_dataPV);
    free(infoP);
  }
}

static PF_Err PreRender(PF_InData *in_dataP, PF_OutData *out_dataP,
                        PF_PreRenderExtra *extraP) {
  PF_Err err = PF_Err_NONE;
  PF_RenderRequest req = extraP->input->output_request;
  PF_CheckoutResult in_result;

  extraP->output->flags |= PF_RenderOutputFlag_GPU_RENDER_POSSIBLE;

  // 新しいパラメータ構造体のメモリを確保
  TouchDrawCenterParams *infoP = reinterpret_cast<TouchDrawCenterParams *>(
      malloc(sizeof(TouchDrawCenterParams)));

  if (infoP) {
    PF_ParamDef cur_param;

    // 各UIの値を読み込んで構造体に格納
    ERR(PF_CHECKOUT_PARAM(in_dataP, ID_SEED, in_dataP->current_time,
                          in_dataP->time_step, in_dataP->time_scale,
                          &cur_param));
    infoP->mSeed = cur_param.u.sd.value;

    ERR(PF_CHECKOUT_PARAM(in_dataP, ID_CENTER, in_dataP->current_time,
                          in_dataP->time_step, in_dataP->time_scale,
                          &cur_param));
    infoP->mCenterX = cur_param.u.td.x_value;
    infoP->mCenterY = cur_param.u.td.y_value;

    ERR(PF_CHECKOUT_PARAM(in_dataP, ID_LENGTH_MAX, in_dataP->current_time,
                          in_dataP->time_step, in_dataP->time_scale,
                          &cur_param));
    infoP->mLengthMax = cur_param.u.fd.value;

    ERR(PF_CHECKOUT_PARAM(in_dataP, ID_LENGTH_RND, in_dataP->current_time,
                          in_dataP->time_step, in_dataP->time_scale,
                          &cur_param));
    infoP->mLengthRnd = cur_param.u.fd.value;

    ERR(PF_CHECKOUT_PARAM(in_dataP, ID_Y, in_dataP->current_time,
                          in_dataP->time_step, in_dataP->time_scale,
                          &cur_param));
    infoP->mValueY = cur_param.u.sd.value;

    ERR(PF_CHECKOUT_PARAM(in_dataP, ID_COLOR, in_dataP->current_time,
                          in_dataP->time_step, in_dataP->time_scale,
                          &cur_param));
    infoP->mColor.red = (float)cur_param.u.cd.value.red / PF_MAX_CHAN8;
    infoP->mColor.green = (float)cur_param.u.cd.value.green / PF_MAX_CHAN8;
    infoP->mColor.blue = (float)cur_param.u.cd.value.blue / PF_MAX_CHAN8;
    infoP->mColor.alpha = (float)cur_param.u.cd.value.alpha / PF_MAX_CHAN8;

    ERR(PF_CHECKOUT_PARAM(in_dataP, ID_OPACITY, in_dataP->current_time,
                          in_dataP->time_step, in_dataP->time_scale,
                          &cur_param));
    infoP->mOpacity = cur_param.u.fd.value;

    ERR(PF_CHECKOUT_PARAM(in_dataP, ID_OPACITY_RND, in_dataP->current_time,
                          in_dataP->time_step, in_dataP->time_scale,
                          &cur_param));
    infoP->mOpacityRnd = cur_param.u.fd.value;

    ERR(PF_CHECKOUT_PARAM(in_dataP, ID_POINT_COUNT, in_dataP->current_time,
                          in_dataP->time_step, in_dataP->time_scale,
                          &cur_param));
    infoP->mPointCount = cur_param.u.sd.value;

    ERR(PF_CHECKOUT_PARAM(in_dataP, ID_POINT_LENGTH, in_dataP->current_time,
                          in_dataP->time_step, in_dataP->time_scale,
                          &cur_param));
    infoP->mPointLength = cur_param.u.fd.value;

    ERR(PF_CHECKOUT_PARAM(in_dataP, ID_ORG, in_dataP->current_time,
                          in_dataP->time_step, in_dataP->time_scale,
                          &cur_param));
    infoP->mOrgBlend = cur_param.u.cd.value;

    extraP->output->pre_render_data = infoP;
    extraP->output->delete_pre_render_data_func = DisposePreRenderData;

    ERR(extraP->cb->checkout_layer(
        in_dataP->effect_ref, ID_INPUT, ID_INPUT, &req, in_dataP->current_time,
        in_dataP->time_step, in_dataP->time_scale, &in_result));

    UnionLRect(&in_result.result_rect, &extraP->output->result_rect);
    UnionLRect(&in_result.max_result_rect, &extraP->output->max_result_rect);
  } else {
    err = PF_Err_OUT_OF_MEMORY;
  }
  return err;
}

static PF_Err SmartRenderCPU(PF_InData *in_data, PF_OutData *out_data,
                             PF_PixelFormat pixel_format,
                             PF_EffectWorld *input_worldP,
                             PF_EffectWorld *output_worldP,
                             PF_SmartRenderExtra *extraP,
                             InvertProcAmpParams *infoP) {
  PF_Err err = PF_Err_NONE;

  if (!err) {
    switch (pixel_format) {
      case PF_PixelFormat_ARGB128: {
        AEFX_SuiteScoper<PF_iterateFloatSuite2> iterateFloatSuite =
            AEFX_SuiteScoper<PF_iterateFloatSuite2>(
                in_data, kPFIterateFloatSuite, kPFIterateFloatSuiteVersion2,
                out_data);
        iterateFloatSuite->iterate(in_data, 0, output_worldP->height,
                                   input_worldP, NULL, (void *)infoP,
                                   FilterImage32, output_worldP);
        break;
      }

      case PF_PixelFormat_ARGB64: {
        AEFX_SuiteScoper<PF_iterate16Suite2> iterate16Suite =
            AEFX_SuiteScoper<PF_iterate16Suite2>(in_data, kPFIterate16Suite,
                                                 kPFIterate16SuiteVersion2,
                                                 out_data);
        iterate16Suite->iterate(in_data, 0, output_worldP->height, input_worldP,
                                NULL, (void *)infoP, FilterImage16,
                                output_worldP);
        break;
      }

      case PF_PixelFormat_ARGB32: {
        AEFX_SuiteScoper<PF_Iterate8Suite2> iterate8Suite =
            AEFX_SuiteScoper<PF_Iterate8Suite2>(
                in_data, kPFIterate8Suite, kPFIterate8SuiteVersion2, out_data);

        iterate8Suite->iterate(in_data, 0, output_worldP->height, input_worldP,
                               NULL, (void *)infoP, FilterImage8,
                               output_worldP);
        break;
      }

      default:
        err = PF_Err_BAD_CALLBACK_PARAM;
        break;
    }
  }

  return err;
}

static size_t RoundUp(size_t inValue, size_t inMultiple) {
  return inValue ? ((inValue + inMultiple - 1) / inMultiple) * inMultiple : 0;
}

typedef struct {
  int mSrcPitch;
  int mDstPitch;
  int m16f;
  int mWidth;
  int mHeight;
} InvertColorParams;

size_t DivideRoundUp(size_t inValue, size_t inMultiple) {
  return inValue ? (inValue + inMultiple - 1) / inMultiple : 0;
}

/*
 **The ProcAmp2Params structure mirrors that used by the metal kernel.
 */
typedef struct {
  int mSrcPitch;
  int mDstPitch;
  int m16f;
  int mWidth;
  int mHeight;
  float mBrightness;
  float mContrast;
  float mHueCosSaturation;
  float mHueSinSaturation;
} ProcAmp2Params;

static PF_Err SmartRenderGPU(PF_InData *in_dataP, PF_OutData *out_dataP,
                             PF_PixelFormat pixel_format,
                             PF_EffectWorld *input_worldP,
                             PF_EffectWorld *output_worldP,
                             PF_SmartRenderExtra *extraP,
                             InvertProcAmpParams *infoP) {
  PF_Err err = PF_Err_NONE;

  AEFX_SuiteScoper<PF_GPUDeviceSuite1> gpu_suite =
      AEFX_SuiteScoper<PF_GPUDeviceSuite1>(
          in_dataP, kPFGPUDeviceSuite, kPFGPUDeviceSuiteVersion1, out_dataP);

  if (pixel_format != PF_PixelFormat_GPU_BGRA128) {
    err = PF_Err_UNRECOGNIZED_PARAM_TYPE;
  }

  PF_GPUDeviceInfo device_info;
  ERR(gpu_suite->GetDeviceInfo(in_dataP->effect_ref,
                               extraP->input->device_index, &device_info));

  // Allocate an intermediate buffer for extra kernel steps
  // Here we use this buffer to invert color in CUDA
  PF_EffectWorld *intermediate_buffer;

  ERR(gpu_suite->CreateGPUWorld(
      in_dataP->effect_ref, extraP->input->device_index, input_worldP->width,
      input_worldP->height, input_worldP->pix_aspect_ratio, in_dataP->field,
      pixel_format, false, &intermediate_buffer));

  void *src_mem = 0;
  ERR(gpu_suite->GetGPUWorldData(in_dataP->effect_ref, input_worldP, &src_mem));

  void *dst_mem = 0;
  ERR(gpu_suite->GetGPUWorldData(in_dataP->effect_ref, output_worldP,
                                 &dst_mem));

  struct KernelParams {
    int mSrcPitch;
    int mDstPitch;
    int m16f;
    int mWidth;
    int mHeight;
    TouchDrawCenterParams mTDParams;
  };

  KernelParams kernel_params;
  kernel_params.mWidth = input_worldP->width;
  kernel_params.mHeight = input_worldP->height;
  kernel_params.mSrcPitch = input_worldP->rowbytes / 16;
  kernel_params.mDstPitch = output_worldP->rowbytes / 16;
  kernel_params.m16f = (pixel_format != PF_PixelFormat_GPU_BGRA128);
  kernel_params.mTDParams = *infoP;

  if (!err && extraP->input->what_gpu == PF_GPU_Framework_OPENCL) {
    PF_Handle gpu_dataH = (PF_Handle)extraP->input->gpu_data;
    OpenCLGPUData *cl_gpu_dataP = reinterpret_cast<OpenCLGPUData *>(*gpu_dataH);

    cl_mem cl_src_mem = (cl_mem)src_mem;
    cl_mem cl_im_mem = (cl_mem)im_mem;
    cl_mem cl_dst_mem = (cl_mem)dst_mem;

    cl_uint invert_param_index = 0;
    cl_uint procamp_param_index = 0;

    // Set the arguments
    CL_ERR(clSetKernelArg(cl_gpu_dataP->invert_kernel, invert_param_index++,
                          sizeof(cl_mem), &cl_src_mem));
    CL_ERR(clSetKernelArg(cl_gpu_dataP->invert_kernel, invert_param_index++,
                          sizeof(cl_mem), &cl_im_mem));
    CL_ERR(clSetKernelArg(cl_gpu_dataP->invert_kernel, invert_param_index++,
                          sizeof(int), &kernel_params.mSrcPitch));
    CL_ERR(clSetKernelArg(cl_gpu_dataP->invert_kernel, invert_param_index++,
                          sizeof(int), &kernel_params.mDstPitch));
    CL_ERR(clSetKernelArg(cl_gpu_dataP->invert_kernel, invert_param_index++,
                          sizeof(int), &kernel_params.m16f));
    CL_ERR(clSetKernelArg(cl_gpu_dataP->invert_kernel, invert_param_index++,
                          sizeof(int), &kernel_params.mWidth));
    CL_ERR(clSetKernelArg(cl_gpu_dataP->invert_kernel, invert_param_index++,
                          sizeof(int), &kernel_params.mHeight));

    // Launch the kernel
    size_t threadBlock[2] = {16, 16};
    size_t grid[2] = {RoundUp(kernel_params.mWidth, threadBlock[0]),
                      RoundUp(kernel_params.mHeight, threadBlock[1])};

    CL_ERR(clEnqueueNDRangeKernel((cl_command_queue)device_info.command_queuePV,
                                  cl_gpu_dataP->invert_kernel, 2, 0, grid,
                                  threadBlock, 0, 0, 0));
  }
#if HAS_CUDA
  else if (!err && extraP->input->what_gpu == PF_GPU_Framework_CUDA) {

    TouchDrawCenter_CUDA((const float *)src_mem, (float *)im_mem,
                      kernel_params.mSrcPitch, kernel_params.mDstPitch,
                      kernel_params.m16f, kernel_params.mWidth,
                      kernel_params.mHeight, &kernel_params.mTDParams);

    if (cudaPeekAtLastError() != cudaSuccess) {
      err = PF_Err_INTERNAL_STRUCT_DAMAGED;
    }  
  }
#endif
#if HAS_HLSL
  else if (!err && extraP->input->what_gpu == PF_GPU_Framework_DIRECTX) {
    PF_Handle gpu_dataH = (PF_Handle)extraP->input->gpu_data;
    DirectXGPUData *dx_gpu_data =
        reinterpret_cast<DirectXGPUData *>(*gpu_dataH);

    {
      // Execute Invert
      DXShaderExecution shaderExecution(dx_gpu_data->mContext,
                                        dx_gpu_data->mInvertShader, 3);

      // Note: The order of elements in the param structure should be identical
      // to the order expected by the shader
      DX_ERR(shaderExecution.SetParamBuffer(&invert_params,
                                            sizeof(InvertColorParams)));
      DX_ERR(shaderExecution.SetUnorderedAccessView(
          (ID3D12Resource *)im_mem, invert_params.mHeight * tmp_row_bytes));
      DX_ERR(shaderExecution.SetShaderResourceView(
          (ID3D12Resource *)src_mem, invert_params.mHeight * src_row_bytes));
      DX_ERR(shaderExecution.Execute(
          (UINT)DivideRoundUp(invert_params.mWidth, 16),
          (UINT)DivideRoundUp(invert_params.mHeight, 16)));
    }
    if (!err) {
      // Execute ProcAmp
      DXShaderExecution shaderExecution(dx_gpu_data->mContext,
                                        dx_gpu_data->mProcAmpShader, 3);

      // Note: The order of elements in the param structure should be identical
      // to the order expected by the shader
      DX_ERR(shaderExecution.SetParamBuffer(&procamp_params,
                                            sizeof(ProcAmp2Params)));
      DX_ERR(shaderExecution.SetUnorderedAccessView(
          (ID3D12Resource *)dst_mem, procamp_params.mHeight * dst_row_bytes));
      DX_ERR(shaderExecution.SetShaderResourceView(
          (ID3D12Resource *)im_mem, procamp_params.mHeight * tmp_row_bytes));
      DX_ERR(shaderExecution.Execute(
          (UINT)DivideRoundUp(procamp_params.mWidth, 16),
          (UINT)DivideRoundUp(procamp_params.mHeight, 16)));
    }
  }
#endif
#if HAS_METAL
  else if (!err && extraP->input->what_gpu == PF_GPU_Framework_METAL) {
    ScopedAutoreleasePool pool;

    Handle metal_handle = (Handle)extraP->input->gpu_data;
    MetalGPUData *metal_dataP = reinterpret_cast<MetalGPUData *>(*metal_handle);

    // Set the arguments
    id<MTLDevice> device = (id<MTLDevice>)device_info.devicePV;
    id<MTLBuffer> procamp_param_buffer =
        [[device newBufferWithBytes:&procamp_params
                             length:sizeof(ProcAmp2Params)
                            options:MTLResourceStorageModeManaged] autorelease];

    id<MTLBuffer> invert_param_buffer =
        [[device newBufferWithBytes:&invert_params
                             length:sizeof(InvertColorParams)
                            options:MTLResourceStorageModeManaged] autorelease];

    // Launch the command
    id<MTLCommandQueue> queue =
        (id<MTLCommandQueue>)device_info.command_queuePV;
    id<MTLCommandBuffer> commandBuffer = [queue commandBuffer];
    id<MTLComputeCommandEncoder> computeEncoder =
        [commandBuffer computeCommandEncoder];
    id<MTLBuffer> src_metal_buffer = (id<MTLBuffer>)src_mem;
    id<MTLBuffer> im_metal_buffer = (id<MTLBuffer>)im_mem;
    id<MTLBuffer> dst_metal_buffer = (id<MTLBuffer>)dst_mem;

    MTLSize threadsPerGroup1 = {
        [metal_dataP->invert_pipeline threadExecutionWidth], 16, 1};
    MTLSize numThreadgroups1 = {
        DivideRoundUp(invert_params.mWidth, threadsPerGroup1.width),
        DivideRoundUp(invert_params.mHeight, threadsPerGroup1.height), 1};

    MTLSize threadsPerGroup2 = {
        [metal_dataP->procamp_pipeline threadExecutionWidth], 16, 1};
    MTLSize numThreadgroups2 = {
        DivideRoundUp(procamp_params.mWidth, threadsPerGroup2.width),
        DivideRoundUp(procamp_params.mHeight, threadsPerGroup2.height), 1};

    [computeEncoder setComputePipelineState:metal_dataP->invert_pipeline];
    [computeEncoder setBuffer:src_metal_buffer offset:0 atIndex:0];
    [computeEncoder setBuffer:im_metal_buffer offset:0 atIndex:1];
    [computeEncoder setBuffer:invert_param_buffer offset:0 atIndex:2];
    [computeEncoder dispatchThreadgroups:numThreadgroups1
                   threadsPerThreadgroup:threadsPerGroup1];

    err = NSError2PFErr([commandBuffer error]);

    if (!err) {
      [computeEncoder setComputePipelineState:metal_dataP->procamp_pipeline];
      [computeEncoder setBuffer:im_metal_buffer offset:0 atIndex:0];
      [computeEncoder setBuffer:dst_metal_buffer offset:0 atIndex:1];
      [computeEncoder setBuffer:procamp_param_buffer offset:0 atIndex:2];
      [computeEncoder dispatchThreadgroups:numThreadgroups2
                     threadsPerThreadgroup:threadsPerGroup2];
      [computeEncoder endEncoding];
      [commandBuffer commit];

      err = NSError2PFErr([commandBuffer error]);
    }
  }
#endif  // HAS_METAL

  // Must free up allocated intermediate buffer
  ERR(gpu_suite->DisposeGPUWorld(in_dataP->effect_ref, intermediate_buffer));
  return err;
}

static PF_Err SmartRender(PF_InData *in_data, PF_OutData *out_data,
                          PF_SmartRenderExtra *extraP, bool isGPU) {
  PF_Err err = PF_Err_NONE, err2 = PF_Err_NONE;
  PF_EffectWorld *input_worldP = NULL, *output_worldP = NULL;

  TouchDrawCenterParams *infoP =
      reinterpret_cast<TouchDrawCenterParams *>(extraP->input->pre_render_data);

  if (infoP) {
    ERR((extraP->cb->checkout_layer_pixels(in_data->effect_ref, ID_INPUT,
                                           &input_worldP)));
    ERR(extraP->cb->checkout_output(in_data->effect_ref, &output_worldP));

    AEFX_SuiteScoper<PF_WorldSuite2> world_suite =
        AEFX_SuiteScoper<PF_WorldSuite2>(in_data, kPFWorldSuite,
                                         kPFWorldSuiteVersion2, out_data);
    PF_PixelFormat pixel_format = PF_PixelFormat_INVALID;
    ERR(world_suite->PF_GetPixelFormat(input_worldP, &pixel_format));

    if (isGPU) {
      ERR(SmartRenderGPU(in_data, out_data, pixel_format, input_worldP,
                         output_worldP, extraP, infoP));
    } else {
      // CPU版は今回は実装しない
      // ERR(SmartRenderCPU(...));
    }
    ERR2(extraP->cb->checkin_layer_pixels(in_data->effect_ref, ID_INPUT));
  } else {
    return PF_Err_INTERNAL_STRUCT_DAMAGED;
  }
  return err;
}

extern "C" DllExport PF_Err PluginDataEntryFunction2(
    PF_PluginDataPtr inPtr, PF_PluginDataCB2 inPluginDataCallBackPtr,
    SPBasicSuite *inSPBasicSuitePtr, const char *inHostName,
    const char *inHostVersion) {
  PF_Err result = PF_Err_INVALID_CALLBACK;

  result = PF_REGISTER_EFFECT_EXT2(
      inPtr, inPluginDataCallBackPtr,
      "AEVE FsTouchDrawCenter",              // Name
      "ADBE SDK_Invert_ProcAmp",             // Match Name
      "AEVE Plugins",                        // Category
      AE_RESERVED_INFO,                      // Reserved Info
      "EffectMain",                          // Entry point
      "https://aeve-plugins.hashory.app/");  // support URL

  return result;
}

PF_Err EffectMain(PF_Cmd cmd, PF_InData *in_dataP, PF_OutData *out_data,
                  PF_ParamDef *params[], PF_LayerDef *output, void *extra) {
  PF_Err err = PF_Err_NONE;

  try {
    switch (cmd) {
      case PF_Cmd_ABOUT:
        err = About(in_dataP, out_data, params, output);
        break;
      case PF_Cmd_GLOBAL_SETUP:
        err = GlobalSetup(in_dataP, out_data, params, output);
        break;
      case PF_Cmd_PARAMS_SETUP:
        err = ParamsSetup(in_dataP, out_data, params, output);
        break;
      case PF_Cmd_GPU_DEVICE_SETUP:
        err =
            GPUDeviceSetup(in_dataP, out_data, (PF_GPUDeviceSetupExtra *)extra);
        break;
      case PF_Cmd_GPU_DEVICE_SETDOWN:
        err = GPUDeviceSetdown(in_dataP, out_data,
                               (PF_GPUDeviceSetdownExtra *)extra);
        break;
      case PF_Cmd_RENDER:
        err = Render(in_dataP, out_data, params, output);
        break;
      case PF_Cmd_SMART_PRE_RENDER:
        err = PreRender(in_dataP, out_data, (PF_PreRenderExtra *)extra);
        break;
      case PF_Cmd_SMART_RENDER:
        err = SmartRender(in_dataP, out_data, (PF_SmartRenderExtra *)extra,
                          false);
        break;
      case PF_Cmd_SMART_RENDER_GPU:
        err =
            SmartRender(in_dataP, out_data, (PF_SmartRenderExtra *)extra, true);
        break;
    }
  } catch (PF_Err &thrown_err) {
    // Never EVER throw exceptions into AE.
    err = thrown_err;
  }
  return err;
}
