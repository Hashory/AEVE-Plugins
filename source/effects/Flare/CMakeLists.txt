project("Flare")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  Flare.cpp
  FlareBlur08.cpp
  FlareBlur16.cpp
  FlareMax08.cpp
  FlareMax16.cpp
  FlareSub08.cpp
  FlareSub16.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
