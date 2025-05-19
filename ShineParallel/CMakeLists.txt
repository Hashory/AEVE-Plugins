project("ShineParallel")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  ShineParallel.cpp
  ShineParallelFX.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
