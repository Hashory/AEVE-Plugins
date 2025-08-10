project("Extract_Edge")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  Extract_Edge.cpp
  Extract_EdgeSub8.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
