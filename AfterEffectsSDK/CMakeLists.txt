project(AfterEffectsSDK)

add_library(${PROJECT_NAME} STATIC)

if(WIN32)
  target_compile_definitions(${PROJECT_NAME} PRIVATE _WINDOWS=1)
endif()

# Suppress warnings for this library across different compilers
if(MSVC)
  # For Microsoft Visual C++
  target_compile_options(${PROJECT_NAME} PRIVATE /W0)
else()
  # For GCC, Clang, etc.
  target_compile_options(${PROJECT_NAME} PRIVATE -w)
endif()

# source files
target_sources(${PROJECT_NAME} PRIVATE
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

# headers
target_include_directories(${PROJECT_NAME} 
  SYSTEM PUBLIC
    FILE_SET HEADERS
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

        # This header is not completed
        # "Util/String_Utils.h"
)
