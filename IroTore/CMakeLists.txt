project("IroTore")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  IroTore.cpp
  IroToreSub16.cpp
  IroToreSub32.cpp
  IroToreSub8.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
