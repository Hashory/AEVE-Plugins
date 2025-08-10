project("SelectedBlur")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  SelectedBlur.cpp
  SelectedBlurSub16.cpp
  SelectedBlurSub32.cpp
  SelectedBlurSub8.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
