cmake_minimum_required(VERSION 3.16)
project(Orchestrator-Server LANGUAGES CXX VERSION 0.1.0)

# --- C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- (opcional) vcpkg toolchain já deve estar passado na linha de comando:
# cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-linux ..

# --- output dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# --- sources/headers
file(GLOB_RECURSE PROJECT_SOURCES
     CONFIGURE_DEPENDS
     "${CMAKE_SOURCE_DIR}/src/*.cpp")

file(GLOB_RECURSE PROJECT_HEADERS
     CONFIGURE_DEPENDS
     "${CMAKE_SOURCE_DIR}/include/*.h"
     "${CMAKE_SOURCE_DIR}/include/*.hpp")

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

# --- deps via vcpkg
find_package(nlohmann_json CONFIG REQUIRED)
find_package(MbedTLS CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        nlohmann_json::nlohmann_json
        # Base64 e crypto estão em mbedcrypto; mantemos os 3 alvos para cobrir variações do pacote
        MbedTLS::mbedcrypto
        MbedTLS::mbedtls
        MbedTLS::mbedx509
)

# (opcional) Warnings agradáveis
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
