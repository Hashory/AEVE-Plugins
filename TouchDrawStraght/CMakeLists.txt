project("TouchDrawStraght")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  TouchDrawStraght.cpp
  ToutchDrawStraght16.cpp
  ToutchDrawStraght32.cpp
  ToutchDrawStraght8.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
