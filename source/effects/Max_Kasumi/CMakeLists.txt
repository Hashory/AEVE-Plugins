project("Max_Kasumi")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  Max_Kasumi.cpp
  Max_KasumiSub16.cpp
  Max_KasumiSub32.cpp
  Max_KasumiSub8.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
