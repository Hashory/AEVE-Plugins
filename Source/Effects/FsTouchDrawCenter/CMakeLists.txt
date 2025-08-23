project("TouchDrawCenter")

# Set the plugin specific source files
set(${PROJECT_NAME}_SOURCES
  TouchDrawCenter.cpp
  ToutchDraw8.cpp
  ToutchDraw16.cpp
  ToutchDraw32.cpp
  alphaBlur8.cpp
  alphaBlur16.cpp
  alphaBlur32.cpp
  copyImage.cpp
)

# Call the common plugin build function
build_ae_plugin(${PROJECT_NAME})
