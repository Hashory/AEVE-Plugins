project("EdgeBlur")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  EdgeBlur.cpp
  EdgeBlurSub16.cpp
  EdgeBlurSub32.cpp
  EdgeBlurSub8.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
