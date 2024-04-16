###########################################################################
# CMakeLists.txt generated for component HT08_CASE
# Product type: executable
###########################################################################
cmake_minimum_required(VERSION 3.12)
project(HT08_CASE)

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
get_filename_component(START_DIR .. ABSOLUTE)

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
if(NOT TARGET BasicVehicleMath_rtwlib)
    add_subdirectory(../slprj/ert/BasicVehicleMath ${BINARY_START_DIR}/slprj/ert/BasicVehicleMath)
endif()
if(NOT TARGET NORMAL_FORCE_TV_rtwlib)
    add_subdirectory(../slprj/ert/NORMAL_FORCE_TV ${BINARY_START_DIR}/slprj/ert/NORMAL_FORCE_TV)
endif()
if(NOT TARGET PID_TV_rtwlib)
    add_subdirectory(../slprj/ert/PID_TV ${BINARY_START_DIR}/slprj/ert/PID_TV)
endif()
if(NOT TARGET POWER_LIMIT_rtwlib)
    add_subdirectory(../slprj/ert/POWER_LIMIT ${BINARY_START_DIR}/slprj/ert/POWER_LIMIT)
endif()
if(NOT TARGET TRACTION_CONTROL_rtwlib)
    add_subdirectory(../slprj/ert/TRACTION_CONTROL ${BINARY_START_DIR}/slprj/ert/TRACTION_CONTROL)
endif()
if(NOT TARGET rtwshared)
    add_subdirectory(../slprj/ert/_sharedutils ${BINARY_START_DIR}/slprj/ert/_sharedutils)
endif()

# Definition of target "HT08_CASE".
add_executable(HT08_CASE  ${START_DIR}/HT08_CASE_ert_rtw/HT08_CASE.cpp
    ${START_DIR}/HT08_CASE_ert_rtw/HT08_CASE_capi.cpp
    ${START_DIR}/HT08_CASE_ert_rtw/ert_main.cpp)

# Set properties for target "HT08_CASE".
set_target_properties(HT08_CASE PROPERTIES PREFIX ""
    POSITION_INDEPENDENT_CODE ON
    RUNTIME_OUTPUT_DIRECTORY "${BINARY_START_DIR}/./$<0:>"
    LIBRARY_OUTPUT_DIRECTORY "${BINARY_START_DIR}/./$<0:>"
    ARCHIVE_OUTPUT_DIRECTORY "${BINARY_START_DIR}/./$<0:>")

# Specify language features required for target "HT08_CASE".
target_compile_features(HT08_CASE PUBLIC cxx_std_11)

# Specify compiler preprocessor definitions for target "HT08_CASE".
target_compile_definitions(HT08_CASE PRIVATE -DMODEL=HT08_CASE
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

# Specify include directories for target "HT08_CASE".
target_include_directories(HT08_CASE PRIVATE ${START_DIR}/slprj/ert/TRACTION_CONTROL
    ${START_DIR}/slprj/ert/POWER_LIMIT
    ${START_DIR}/slprj/ert/PID_TV
    ${START_DIR}/slprj/ert/NORMAL_FORCE_TV
    ${START_DIR}/slprj/ert/BasicVehicleMath
    ${START_DIR}
    ${START_DIR}/HT08_CASE_ert_rtw
    ${MATLAB_ROOT}/extern/include
    ${MATLAB_ROOT}/simulink/include
    ${MATLAB_ROOT}/rtw/c/src
    ${MATLAB_ROOT}/rtw/c/src/ext_mode/common
    ${MATLAB_ROOT}/rtw/c/ert
    ${MATLAB_ROOT}/toolbox/shared/can/src/scanutil
    ${START_DIR}/slprj/ert/_sharedutils)

# Specify library link dependencies for target "HT08_CASE".  CMake 
# generator expressions are used to create a CMakeLists.txt file that 
# supports multiple platforms with differently named system library 
# dependencies.
target_link_libraries(HT08_CASE PRIVATE BasicVehicleMath_rtwlib
    NORMAL_FORCE_TV_rtwlib
    PID_TV_rtwlib
    POWER_LIMIT_rtwlib
    TRACTION_CONTROL_rtwlib
    rtwshared
    $<$<BOOL:${FOUND_LIBM}>:m>
    $<$<BOOL:${WIN32}>:kernel32>
    $<$<BOOL:${WIN32}>:ws2_32>
    $<$<BOOL:${WIN32}>:mswsock>
    $<$<BOOL:${WIN32}>:advapi32>)

# Extract DWARF debug symbols into a separate file when building 
# executable programs for Apple platforms.
if(APPLE AND (CMAKE_C_COMPILER_ID STREQUAL "AppleClang"))
    string(APPEND _dsymutilcmd "$<IF:$<CONFIG:DEBUG,RELWITHDEBINFO>,"
                "xcrun;dsymutil;$<TARGET_FILE:HT08_CASE>;--flat,"
                "true"
        >)
    add_custom_command(TARGET HT08_CASE
            POST_BUILD
            COMMAND "${_dsymutilcmd}"
            COMMAND_EXPAND_LISTS
            BYPRODUCTS HT08_CASE.dwarf)
endif()


###########################################################################
## Build success message
###########################################################################
add_custom_command(TARGET HT08_CASE POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "\\#\\#\\# Created executable: $<TARGET_FILE:HT08_CASE>")

###########################################################################
## Call toolchain hook function if defined
###########################################################################
if(COMMAND toolchain_target_hook)
    toolchain_target_hook(HT08_CASE)
endif()
