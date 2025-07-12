project(AfterEffectsSDK)

add_library(AfterEffectsSDK)

# Suppress warnings for this library across different compilers
if(MSVC)
  # For Microsoft Visual C++
  target_compile_options(AfterEffectsSDK PRIVATE /W0)
else()
  # For GCC, Clang, etc.
  target_compile_options(AfterEffectsSDK PRIVATE -w)
endif()

# source files
set(SOURCE_FILES
  "Util/AEFX_ArbParseHelper.c"
  "Util/AEFX_SuiteHelper.c"
  "Util/AEGP_SuiteHandler.cpp"
  "Util/AEGP_Utils.cpp"
  "Util/MissingSuiteError.cpp"
  "Util/Smart_Utils.cpp"

  # Don't need to include these files
  # "Util/DirectXUtils.cpp"
  # "Util/String_Utils.c"
)

add_library(AfterEffectsSDK STATIC ${SOURCE_FILES})

# headers
target_include_directories(AfterEffectsSDK SYSTEM PUBLIC FILE_SET HEADERS
  BASE_DIRS
    "Headers"
    "Headers/SP"
    "Util"
    "Resources"
    "GPUUtils"
    "GPUUtils/PrGPU/KernelSupport"
  FILES
    "Headers/AEConfig.h"
    "Headers/AE_Effect.h"
    "Headers/AE_EffectCB.h"
    "Headers/AE_EffectCBSuites.h"
    "Headers/AE_Macros.h"
    "Util/entry.h"
    "Util/AEGP_SuiteHandler.h"
    "Util/Param_Utils.h"
    "Util/Smart_Utils.h"
    # "Util/String_Utils.h"
)
