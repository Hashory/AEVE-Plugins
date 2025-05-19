project("Unmult_KNSW_Fake")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  Unmult_KNSW_Fake.cpp
  Unmult_KNSW_FakeFX.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
