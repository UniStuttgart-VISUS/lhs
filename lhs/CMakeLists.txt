# CMakeLists.txt
# Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
# Licensed under the MIT licence. See LICENCE file for details.

project(liblhs)


# Collect source files.
set(IncludeDir "${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB_RECURSE HeaderFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${IncludeDir}/*.h" "${IncludeDir}/*.inl")

source_group("Header Files\\include" FILES  ${HeaderFiles})

# Define the output.
add_library(${PROJECT_NAME} INTERFACE ${HeaderFiles})

# Configure the compiler
target_include_directories(${PROJECT_NAME} INTERFACE ${IncludeDir})

# Install
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
