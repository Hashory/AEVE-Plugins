project("OpticalDiffusion")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  DF16.cpp
  DF32.cpp
  DF8.cpp
  odf_noise.cpp
  OpticalDiffusion.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
