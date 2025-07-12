project(FsLibrary)

set(SOURCE_FILES
  FsBlur.cpp
  FsGraphics.cpp
  FsGraphicsBlend.cpp
  FsGraphicsBox.cpp
  FsGraphicsCircle.cpp
  FsGraphicsLine.cpp
  FsGraphicsPaint.cpp
  FsMat.cpp
  FsMiniMax8.cpp
  FsMiniMax16.cpp
  FsMiniMax32.cpp
  FsMosaic.cpp
)

add_library(FsLibrary STATIC
  ${SOURCE_FILES}
)

target_link_libraries(FsLibrary PRIVATE AfterEffectsSDK)

target_include_directories(FsLibrary PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)