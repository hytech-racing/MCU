###########################################################################
# CMakeLists.txt generated for component rtwshared
# Product type: STATIC library
###########################################################################
cmake_minimum_required(VERSION 3.12)
# Propagate the CMAKE_EXPORT_COMPILE_COMMANDS variable from the 
# environment if it is defined as an environment variable, but not as a 
# CMake variable. This is to work around a bug in CMake 3.19 when the 
# "NMake Makefiles" generator is selected.
if(DEFINED ENV{CMAKE_EXPORT_COMPILE_COMMANDS} AND NOT DEFINED CMAKE_EXPORT_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS $ENV{CMAKE_EXPORT_COMPILE_COMMANDS})
endif()

# Define common variables that are used within the whole project.
set(SYSLIB_PREFIX $<IF:$<AND:$<BOOL:${WIN32}>,$<NOT:$<BOOL:${MINGW}>>>,lib,>)

###########################################################################
## Path variables
###########################################################################
# Derive an absolute path to the code generation anchor folder.
get_filename_component(START_DIR ../../.. ABSOLUTE)

# Special directories defined by using CACHE variables can be overridden 
# by setting the variable from the command line, e.g.,
# 
# 	cmake . -DMATLAB_ROOT=/path/to/another/matlab/root
set(MATLAB_ROOT C:/Program\ Files/MATLAB/R2023b CACHE PATH "")

# Additional variables that are defined conditionally.
if("${CMAKE_CURRENT_BINARY_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    set(BINARY_START_DIR "${START_DIR}")
else()
    set(BINARY_START_DIR "${CMAKE_BINARY_DIR}")
endif()

###########################################################################
## System Libraries
###########################################################################
find_library(FOUND_LIBM m NO_SYSTEM_ENVIRONMENT_PATH PATHS ${CMAKE_C_IMPLICIT_LINK_DIRECTORIES} ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})

###########################################################################
## Target definition and commands
###########################################################################

# Definition of target "rtwshared".
add_library(rtwshared STATIC ${START_DIR}/slprj/ert/_sharedutils/const_params.cpp
    ${START_DIR}/slprj/ert/_sharedutils/look1_binlxpw.cpp
    ${START_DIR}/slprj/ert/_sharedutils/rtGetInf.cpp
    ${START_DIR}/slprj/ert/_sharedutils/rtGetNaN.cpp
    ${START_DIR}/slprj/ert/_sharedutils/rt_atan2d_snf.cpp
    ${START_DIR}/slprj/ert/_sharedutils/rt_nonfinite.cpp
    ${START_DIR}/slprj/ert/_sharedutils/interp1_fDh6ZCtI.cpp)

# Set properties for target "rtwshared".
set_target_properties(rtwshared PROPERTIES PREFIX ""
    POSITION_INDEPENDENT_CODE ON
    RUNTIME_OUTPUT_DIRECTORY "${BINARY_START_DIR}/slprj/ert/_sharedutils/$<0:>"
    LIBRARY_OUTPUT_DIRECTORY "${BINARY_START_DIR}/slprj/ert/_sharedutils/$<0:>"
    ARCHIVE_OUTPUT_DIRECTORY "${BINARY_START_DIR}/slprj/ert/_sharedutils/$<0:>")

# Specify language features required for target "rtwshared".
target_compile_features(rtwshared PUBLIC cxx_std_11)

# Specify compiler preprocessor definitions for target "rtwshared".
target_compile_definitions(rtwshared PRIVATE -DINTEGER_CODE=0)

# Specify include directories for target "rtwshared".
target_include_directories(rtwshared PUBLIC $<BUILD_INTERFACE:${START_DIR}>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>>
    $<BUILD_INTERFACE:${START_DIR}/slprj/ert/_sharedutils>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/slprj/ert/_sharedutils>
    $<BUILD_INTERFACE:${MATLAB_ROOT}/extern/include>
    $<BUILD_INTERFACE:${MATLAB_ROOT}/simulink/include>
    $<BUILD_INTERFACE:${MATLAB_ROOT}/rtw/c/src>
    $<BUILD_INTERFACE:${MATLAB_ROOT}/rtw/c/src/ext_mode/common>
    $<BUILD_INTERFACE:${MATLAB_ROOT}/rtw/c/ert>
    $<BUILD_INTERFACE:${MATLAB_ROOT}/toolbox/shared/can/src/scanutil>)

# Specify library link dependencies for target "rtwshared".  CMake 
# generator expressions are used to create a CMakeLists.txt file that 
# supports multiple platforms with differently named system library 
# dependencies.
target_link_libraries(rtwshared INTERFACE $<$<BOOL:${FOUND_LIBM}>:m>)


###########################################################################
## Build success message
###########################################################################
add_custom_command(TARGET rtwshared POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "\\#\\#\\# Created STATIC library: $<TARGET_FILE:rtwshared>")

###########################################################################
## Call toolchain hook function if defined
###########################################################################
if(COMMAND toolchain_target_hook)
    toolchain_target_hook(rtwshared)
endif()
