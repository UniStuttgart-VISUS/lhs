﻿# CMakeLists.txt
# Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
# Licensed under the MIT licence. See LICENCE file for details.

cmake_minimum_required(VERSION 3.21.0)

project(test)

# First-class hack adapted from https://jslav.livejournal.com/13059.html to get
# access to the VC installation directory.
string(TOLOWER ${CMAKE_MAKE_PROGRAM} MakeProgramme)
if (NOT ${MakeProgramme} MATCHES "/msbuild.+")
    message(FATAL_ERROR "An MSBuild-based process is required for building the tests.")
endif ()
string(REGEX REPLACE "/msbuild.+" "/VC" VcInstallDir ${MakeProgramme})

# Collect source files.
file(GLOB_RECURSE HeaderFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.h" "*.inl")
file(GLOB_RECURSE SourceFiles RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.cpp")

# Define the output.
add_library(${PROJECT_NAME} SHARED ${HeaderFiles} ${SourceFiles})

# Configure the compiler.
target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE _UNICODE)

# Configure the linker: besides the library to test, we also need to link the
# Visual Studio testing framework.
target_link_directories(${PROJECT_NAME} PRIVATE "${VcInstallDir}/Auxiliary/VS/UnitTest/lib/$(LibrariesArchitecture)")
target_link_libraries(${PROJECT_NAME} PRIVATE
    Microsoft.VisualStudio.TestTools.CppUnitTestFramework.lib
    liblhs)

# Grab the DLLs to be tested and copy them to the output directory such that
# the Visual Studio test driver finds everything.
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
#    COMMAND_EXPAND_LISTS)
