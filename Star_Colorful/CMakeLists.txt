project("Star_Colorful")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  Star_Colorful.cpp
  Star_ColorfulSub16.cpp
  Star_ColorfulSub32.cpp
  Star_ColorfulSub8.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
