cmake_minimum_required(VERSION 3.15)
project(echos)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_BINARY_DIR})

include(conan)

set(CMAKE_CXX_STANDARD 20)

conan_cmake_configure(
        REQUIRES
        entt/3.11.1
        glfw/3.3.8
        glew/2.2.0
        glm/0.9.5.4
        GENERATORS cmake_find_package)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
        BUILD missing
        REMOTE conancenter
        SETTINGS ${settings})

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3.8 REQUIRED)
find_package(EnTT 3.11.1 REQUIRED)
find_package(GLEW 2.2.0 REQUIRED)
find_package(glm REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include ${GLEW_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PUBLIC GLFW_INCLUDE_NONE)
target_link_libraries(${PROJECT_NAME} glfw ${GLEW_LIBRARIES} EnTT::EnTT glm::glm)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif ()

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "$<TARGET_PROPERTY:${PROJECT_NAME},SOURCE_DIR>/assets"
    "$<TARGET_PROPERTY:${PROJECT_NAME},BINARY_DIR>/assets"
)
