project("TouchDraw")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  TouchDraw.cpp
  ToutchDraw16.cpp
  ToutchDraw32.cpp
  ToutchDraw8.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
