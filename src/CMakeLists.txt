set(LIBRARY_NAME dag)

# list all headers
set(MODULE_HEADERS
        node.h
        data.h
        utility.h)

# list all the code files
set(MODULE_SOURCES
        node.cpp
        data.cpp
        utility.cpp)

# build the module library
add_library(${LIBRARY_NAME} ${MODULE_HEADERS} ${MODULE_SOURCES})
add_library(lib::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

target_include_directories(
        ${LIBRARY_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

# require C++11
target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_11)

set_target_properties(${LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)


