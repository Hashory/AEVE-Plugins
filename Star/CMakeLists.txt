project("Star")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  Star.cpp
  StarBuf.cpp
  StarDraw.cpp
  StarMask.cpp
  StarTargetCopy.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
