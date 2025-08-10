# new-build-process.cmake

# Enable C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Project AEVE_Plugins
add_library(${PROJECT_NAME} MODULE)

# Plugin output directory settings
set(PLUGIN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/AEVE_Plugins)
file(MAKE_DIRECTORY ${PLUGIN_OUTPUT_DIR}) # Create the output directory if it doesn't exist
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_DIR})

# Windows specific settings
if(WIN32)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_compile_definitions(_WINDOWS=1)
  set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".aex")
  if(MSVC)
    add_compile_options(/utf-8)
  endif()
endif()

# AfterEffectsSDK
set(AE_SDK_PATH "./AfterEffectsSDK")
get_filename_component(AE_SDK_PATH_ABS "${CMAKE_CURRENT_SOURCE_DIR}/${AE_SDK_PATH}" ABSOLUTE)
add_subdirectory("AfterEffectsSDK")
target_link_libraries(${PROJECT_NAME} PRIVATE AfterEffectsSDK)

# AEVE_Plugins source file
target_sources(${PROJECT_NAME}
  PRIVATE
  "Source/AEVE-Plugins.cpp"
)
target_include_directories(${PROJECT_NAME}
  PRIVATE
  FILE_SET HEADERS
    BASE_DIRS
      # "Source/Effects/EffectsName"
    FILES
      # "EffectsName.h"
)

# AEVE_Plugins effects

# For example:
# add_subdirectory("Source/Effects/EffectsName")
# target_link_libraries(${PROJECT_NAME} PRIVATE EffectsName)
