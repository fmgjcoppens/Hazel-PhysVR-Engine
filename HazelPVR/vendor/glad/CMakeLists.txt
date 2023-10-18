cmake_minimum_required(VERSION 3.4...3.20 FATAL_ERROR)
project(glad LANGUAGES C)

set(INCLUDE include)
set(SOURCES src/glad.c )
set(HEADERS ${INCLUDE}/glad/glad.h ${INCLUDE}/KHR/khrplatform.h)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE})  # Use PUBLIC scope here, otherwise glad headers will
                                                               # not be available in higer level CMakeLists.txt.
