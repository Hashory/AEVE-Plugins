project("Thin")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  Thin.cpp
  ThinSub16.cpp
  ThinSub32.cpp
  ThinSub8.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
