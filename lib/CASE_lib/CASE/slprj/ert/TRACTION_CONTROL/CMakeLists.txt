###########################################################################
# CMakeLists.txt generated for component TRACTION_CONTROL_rtwlib
# Product type: STATIC library
###########################################################################
cmake_minimum_required(VERSION 3.12)
project(TRACTION_CONTROL_rtwlib)

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

# Include upstream components that need to be built as part of the current 
# project using the add_subdirectory command.
if(NOT TARGET rtwshared)
    add_subdirectory(../../../slprj/ert/_sharedutils ${BINARY_START_DIR}/slprj/ert/_sharedutils)
endif()

# Definition of target "TRACTION_CONTROL_rtwlib".
add_library(TRACTION_CONTROL_rtwlib STATIC ${START_DIR}/slprj/ert/TRACTION_CONTROL/TRACTION_CONTROL.cpp
    ${START_DIR}/slprj/ert/TRACTION_CONTROL/TRACTION_CONTROL_capi.cpp)

# Set properties for target "TRACTION_CONTROL_rtwlib".
set_target_properties(TRACTION_CONTROL_rtwlib PROPERTIES PREFIX ""
    POSITION_INDEPENDENT_CODE ON
    RUNTIME_OUTPUT_DIRECTORY "${BINARY_START_DIR}/slprj/ert/TRACTION_CONTROL/$<0:>"
    LIBRARY_OUTPUT_DIRECTORY "${BINARY_START_DIR}/slprj/ert/TRACTION_CONTROL/$<0:>"
    ARCHIVE_OUTPUT_DIRECTORY "${BINARY_START_DIR}/slprj/ert/TRACTION_CONTROL/$<0:>")

# Specify language features required for target "TRACTION_CONTROL_rtwlib".
target_compile_features(TRACTION_CONTROL_rtwlib PUBLIC cxx_std_11)

# Specify compiler preprocessor definitions for target 
# "TRACTION_CONTROL_rtwlib".
target_compile_definitions(TRACTION_CONTROL_rtwlib PRIVATE -DMODEL=TRACTION_CONTROL
    -DNUMST=1
    -DNCSTATES=0
    -DHAVESTDIO
    -DMODEL_HAS_DYNAMICALLY_LOADED_SFCNS=0
    -DCLASSIC_INTERFACE=0
    -DALLOCATIONFCN=0
    -DTID01EQ=0
    -DTERMFCN=1
    -DONESTEPFCN=1
    -DMAT_FILE=0
    -DMULTI_INSTANCE_CODE=1
    -DINTEGER_CODE=0
    -DMT=0)

# Specify include directories for target "TRACTION_CONTROL_rtwlib".
target_include_directories(TRACTION_CONTROL_rtwlib PUBLIC $<BUILD_INTERFACE:${START_DIR}>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>>
    $<BUILD_INTERFACE:${START_DIR}/slprj/ert/TRACTION_CONTROL>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/slprj/ert/TRACTION_CONTROL>
    $<BUILD_INTERFACE:${MATLAB_ROOT}/extern/include>
    $<BUILD_INTERFACE:${MATLAB_ROOT}/simulink/include>
    $<BUILD_INTERFACE:${MATLAB_ROOT}/rtw/c/src>
    $<BUILD_INTERFACE:${MATLAB_ROOT}/rtw/c/src/ext_mode/common>
    $<BUILD_INTERFACE:${MATLAB_ROOT}/rtw/c/ert>
    $<BUILD_INTERFACE:${START_DIR}/slprj/ert/_sharedutils>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/slprj/ert/_sharedutils>)

# Specify library link dependencies for target "TRACTION_CONTROL_rtwlib".  
# CMake generator expressions are used to create a CMakeLists.txt file 
# that supports multiple platforms with differently named system library 
# dependencies.
target_link_libraries(TRACTION_CONTROL_rtwlib INTERFACE rtwshared
    $<$<BOOL:${FOUND_LIBM}>:m>)


###########################################################################
## Build success message
###########################################################################
add_custom_command(TARGET TRACTION_CONTROL_rtwlib POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "\\#\\#\\# Created STATIC library: $<TARGET_FILE:TRACTION_CONTROL_rtwlib>")

###########################################################################
## Call toolchain hook function if defined
###########################################################################
if(COMMAND toolchain_target_hook)
    toolchain_target_hook(TRACTION_CONTROL_rtwlib)
endif()
