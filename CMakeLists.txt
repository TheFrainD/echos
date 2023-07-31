cmake_minimum_required(VERSION 3.14)
project(echos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            TLS_VERIFY ON)
endif ()

include(${CMAKE_BINARY_DIR}/conan.cmake)

set(CMAKE_CXX_STANDARD 20)

conan_cmake_configure(
        REQUIRES
        entt/3.11.1
        glfw/3.3.8
        glad/0.1.36
        glm/0.9.5.4
        spdlog/1.11.0
        stb/cci.20220909
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
find_package(stb REQUIRED)

add_subdirectory(src)
