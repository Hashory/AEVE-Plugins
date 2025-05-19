project("IroToreAdjacent")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  IroToreAdjacent.cpp
  IroToreAdjacentSub16.cpp
  IroToreAdjacentSub8.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
