project("MainLineRepaint_old")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  MainLineRepaint_old.cpp
  MainLineRepaint_old_Strings.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
