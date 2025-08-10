project("ShitsuKanBlur")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  ShitsuKanBlur.cpp
  ShitsuKanBlurSub16.cpp
  ShitsuKanBlurSub32.cpp
  ShitsuKanBlurSub8.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
