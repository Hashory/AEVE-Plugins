project("AlphaFix")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  AlphaFix.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
