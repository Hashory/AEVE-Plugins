
project(FsLibrary)

add_library(FsLibrary)

target_sources(FsLibrary PRIVATE
  "FsBlur.cpp"
  "FsGraphics.cpp"
  "FsGraphicsBlend.cpp"
  "FsGraphicsBox.cpp"
  "FsGraphicsCircle.cpp"
  "FsGraphicsLine.cpp"
  "FsGraphicsPaint.cpp"
  "FsMat.cpp"
  "FsMiniMax8.cpp"
  "FsMiniMax16.cpp"
  "FsMiniMax32.cpp"
  "FsMosaic.cpp"
)

target_link_libraries(FsLibrary PRIVATE AfterEffectsSDK)

target_include_directories(FsLibrary 
  PUBLIC 
    # FILE_SET HEADERS
    #   BASE_DIRS
    #     "./"
    #   FILES
        "FBlend.h"
        "FBlendSelected.h"
        "FGrad.h"
        "Fs.h"
        "FsAE.h"
        "FsBuffer.h"
        "FsDebug.h"
        "FsGraphics.h"
        "FsHLS.h"
        "FsRandom.h"
        "FsScreenShake.h"
        "FsSputtering.h"
        "FsUtils.h"
        "FsVersion.h"
        "FWorld.h"
        "FWorldTranst.h"
)