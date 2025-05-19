project("Unmult_RG_Fake")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  Unmult_RG_Fake.cpp
  Unmult_RG_FakeFX.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
