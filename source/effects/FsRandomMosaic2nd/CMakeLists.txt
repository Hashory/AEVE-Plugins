project("RandomMosaic2nd")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  RandomMosaic2nd.cpp
  RandomMosaic2nd.h
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
