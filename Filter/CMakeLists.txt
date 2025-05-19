project("Filter")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  Filter.cpp
  FilterBlur16.cpp
  FilterExec08.cpp
  FilterExec16.cpp
  FilterMax16.cpp
  FilterSub16.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
