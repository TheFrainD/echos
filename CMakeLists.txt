cmake_minimum_required(VERSION 3.15)
project(echos)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_BINARY_DIR})

include(conan)

set(CMAKE_CXX_STANDARD 20)

conan_cmake_configure(
        REQUIRES
        entt/3.11.1
        glfw/3.3.8
        glad/0.1.36
        glm/0.9.5.4
        spdlog/1.11.0
        OPTIONS
        glad:gl_profile=core
        glad:gl_version=4.6
        GENERATORS cmake_find_package)

conan_cmake_autodetect(settings)
conan_cmake_install(PATH_OR_REFERENCE .
        BUILD missing
        REMOTE conancenter
        SETTINGS ${settings})

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(EnTT REQUIRED)
find_package(glm REQUIRED)
find_package(spdlog REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_compile_definitions(${PROJECT_NAME} PUBLIC GLFW_INCLUDE_NONE)
target_link_libraries(${PROJECT_NAME} glfw glad::glad EnTT::EnTT glm::glm spdlog::spdlog)

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
