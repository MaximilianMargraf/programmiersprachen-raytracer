add_executable(example example.cpp)

target_link_libraries(example ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(example glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS example DESTINATION .)

add_executable(raytracer
  ../framework/material.cpp
  ../framework/light.cpp
  ../framework/camera.cpp
  ../framework/scene.cpp
  ../framework/sdfloader.hpp
  ../framework/shape.cpp
  ../framework/sphere.cpp
  ../framework/box.cpp
  ../framework/ray.hpp
  ../framework/hitpoint.hpp
  ../framework
  raytracer.cpp)

target_link_libraries(raytracer ${FRAMEWORK_NAME} ${LIBRARIES}
  glfw
  ${GLFW_LIBRARIES}
  )
add_dependencies(raytracer glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer DESTINATION .)

# Build tests
add_executable(tests
  ../framework/material.cpp
  ../framework/light.cpp
  ../framework/camera.cpp
  ../framework/scene.cpp
  ../framework/sdfloader.hpp
  ../framework/shape.cpp
  ../framework/sphere.cpp
  ../framework/box.cpp
  ../framework/ray.hpp
  ../framework/hitpoint.hpp
  tests.cpp)
target_link_libraries(tests
  ${GLFW_LIBRARIES}
  )

