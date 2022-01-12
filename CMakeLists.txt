cmake_minimum_required (VERSION 3.0)

project(raytracer)
set(CMAKE_CXX_STANDARD 14)


#IMPORTANT COMPILING DIRECTIVES

# 1
# Enable this when you start working on your solution and you add the file RayTracer.h 
# in the src folder; Without this file the code base will not compile therefore in your 
# code this define is disabled
# Also do not forget to create the src folder under code
# add_compile_options(-DSTUDENT_SOLUTION)

# 2
# This define is used by the teaching team to compile and run the official solution
# Students: for your project this define should always be commented out
# If we commit it by mistake please disable it and let us know
#add_compile_options(-DCOURSE_SOLUTION)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS} -Wall -Wpedantic")


set(CMAKE_PREFIX_PATH
    /encs # For ENCS lab computers
    /opt/local # Macports
)

find_package(PkgConfig REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

file(GLOB SOURCES
    "source/*.cpp"
)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

aux_source_directory(external EXTERNAL_SOURCES)
aux_source_directory(src EXTERNAL_SOURCES)

add_executable(${PROJECT_NAME} 
	${SOURCES}
    ${EXTERNAL_SOURCES}
)
target_include_directories(${PROJECT_NAME}
    PRIVATE "${CMAKE_SOURCE_DIR}/external"
)