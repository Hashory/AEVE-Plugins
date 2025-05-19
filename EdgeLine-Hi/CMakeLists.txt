project("EdgeLine-Hi")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  EdgeLine-Hi.cpp
  EdgeLine-Hi_sub08.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
