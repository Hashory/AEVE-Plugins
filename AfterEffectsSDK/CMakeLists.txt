project(AfterEffectsSDK)

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
target_include_directories(AfterEffectsSDK PUBLIC
  "Headers"
  "Headers/SP"
  "Util"
  "Resources"
  "GPUUtils"
  "GPUUtils/PrGPU/KernelSupport"
)
