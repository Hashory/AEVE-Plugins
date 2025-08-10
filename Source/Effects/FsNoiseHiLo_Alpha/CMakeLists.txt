project("NoiseHiLo_Alpha")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  NoiseHiLo_Alpha.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
