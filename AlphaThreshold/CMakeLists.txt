project("AlphaThreshold")

# -------------------- Common build configuration --------------------

# Bundle identifier and copyright variable definitions
set(MY_BUNDLE_GUI_IDENTIFIER "io.github.hashory.AEVE-Plugins.${PROJECT_NAME}")
string(TIMESTAMP BUILD_YEAR "%Y")
set(MY_BUNDLE_COPYRIGHT "MIT LICENSED ${BUILD_YEAR}.")


# PiPL resource filenames
set(PIPL_RSRC ${PROJECT_NAME}PiPL.rsrc)
set(PIPL_R ${PROJECT_NAME}PiPL.r)

# Set the plugin files
set(PROJECT_SOURCE_FILES
  alphaThreshold.cpp
)
add_library(${PROJECT_NAME} MODULE ${PROJECT_SOURCE_FILES})

# Link the library
target_link_libraries(${PROJECT_NAME} PRIVATE AfterEffectsSDK)
target_link_libraries(${PROJECT_NAME} PRIVATE FsLibrary)

# -------------------- Platform-specific build logic --------------------

# Xcode(macOS) logic
if(MAC_PLATFORM)
  target_link_libraries(${PROJECT_NAME} "-framework Cocoa")

  set_target_properties(${PROJECT_NAME} PROPERTIES
      XCODE_ATTRIBUTE_ENABLE_HARDENED_RUNTIME YES
  )

  find_program(AFX_REZ rez /Developer/Tools)

  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${PIPL_RSRC}
    COMMAND ${AFX_REZ}
    ARGS ${CMAKE_CURRENT_SOURCE_DIR}/${PIPL_R}
      -o ${CMAKE_CURRENT_BINARY_DIR}/${PIPL_RSRC}
      -useDF
      -i "${AE_SDK_PATH_ABS}/Headers"
      -i "${AE_SDK_PATH_ABS}/Headers/SP"
      -i "${AE_SDK_PATH_ABS}/Util"
      -i "${AE_SDK_PATH_ABS}/Resources"
      -D __MACH__
  )

  set_source_files_properties(
    ${CMAKE_CURRENT_BINARY_DIR}/${PIPL_RSRC}
    PROPERTIES
    MACOSX_PACKAGE_LOCATION Resources/
  )

  target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${PIPL_RSRC})

  set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
  set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX "")
  set_target_properties(${PROJECT_NAME} PROPERTIES
    BUNDLE True
    MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
    BUNDLE_EXTENSION "plugin"
    MACOSX_BUNDLE_INFO_STRING "${PROJECT_NAME}"
    MACOSX_BUNDLE_GUI_IDENTIFIER "${MY_BUNDLE_GUI_IDENTIFIER}"
    MACOSX_BUNDLE_COPYRIGHT "${MY_BUNDLE_COPYRIGHT}"
  )

  # PkgInfo
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/PkgInfo
    COMMAND echo "eFKTFXTC" >> ${CMAKE_CURRENT_BINARY_DIR}/PkgInfo
  )

  set_source_files_properties(
    ${CMAKE_CURRENT_BINARY_DIR}/PkgInfo
    PROPERTIES
    MACOSX_PACKAGE_LOCATION ""
  )

  target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/PkgInfo)
endif()

# Windows logic
if(WIN_PLATFORM)
  set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".aex")
  get_filename_component(
    AFX_REZ
    "${AE_SDK_PATH_ABS}/Resources/PiPLtool.exe"
    ABSOLUTE
    CACHE
  )

  message(STATUS "DEBUG: AFX_REZ is set to: ${AFX_REZ}")

  set(RR_FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rr")
  set(RRC_FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rrc")
  set(RC_FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.rc")

  add_custom_command(
    OUTPUT ${RR_FILE}
    COMMAND
    cl /utf-8
      /I "${AE_SDK_PATH_ABS}/Headers"
      /I "${AE_SDK_PATH_ABS}/Headers/SP"
      /I "${AE_SDK_PATH_ABS}/Util"
      /I "${AE_SDK_PATH_ABS}/Resources"
      /EP "${CMAKE_CURRENT_SOURCE_DIR}/${PIPL_R}" > "${RR_FILE}"
  )

  add_custom_command(
    DEPENDS ${RR_FILE}
    OUTPUT ${RRC_FILE}
    COMMAND ${AFX_REZ} "${RR_FILE}" "${RRC_FILE}"
  )

  add_custom_command(
    DEPENDS ${RRC_FILE}
    OUTPUT ${RC_FILE}
    COMMAND cl /utf-8 /D "MSWindows" /EP "${RRC_FILE}" > "${RC_FILE}"
  )

  target_sources(
    ${PROJECT_NAME} PRIVATE
    "${RC_FILE}"
  )
endif()
