cmake_minimum_required(VERSION 3.30)
project(threaded-signals VERSION 0.1.0)

set(THREADED_SIGNALS_BUILD_EXAMPLES ON CACHE BOOL "Build Examples")

file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS include/*.hpp)
add_library(${PROJECT_NAME} INTERFACE)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

target_include_directories(
    ${PROJECT_NAME}
    INTERFACE 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/thread-signals>
)

install(
    TARGETS ${UTILS_LIB_NAME} 
    EXPORT utils_Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(${THREADED_SIGNALS_BUILD_EXAMPLES})
    add_subdirectory(examples)
endif()