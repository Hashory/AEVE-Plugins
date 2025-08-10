project("HLS_Reverse")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  HLS_Reverse.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
