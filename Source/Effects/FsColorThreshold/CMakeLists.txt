project("colorThreshold")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  colorThreshold.cpp
  colorThresholdMain16.cpp
  colorThresholdMain32.cpp
  colorThresholdMain8.cpp
  colorThresholdSub.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
