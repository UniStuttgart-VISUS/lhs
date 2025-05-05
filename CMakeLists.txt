# CMakeLists.txt
# Copyright © 2025 Visualisierungsinstitut der Universität Stuttgart.
# Licensed under the MIT licence. See LICENCE file for details.

cmake_minimum_required(VERSION 3.21.0)

project(lhs)

include(CMakeDependentOption)
include(GNUInstallDirs)

# User-configurable options.
cmake_dependent_option(LHS_BuildTests "Build unit tests." ON WIN32 OFF)

# Global options
set (CXX_STANDARD 14)

# The library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lhs)

# Unit tests
if (LHS_BuildTests)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif ()
