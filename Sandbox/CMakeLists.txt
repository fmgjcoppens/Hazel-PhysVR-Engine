project(Sandbox LANGUAGES CXX)

include(FileStructure.cmake)

add_executable(${PROJECT_NAME} ${SRC_ROOT})

target_link_libraries(${PROJECT_NAME} "HazelPVR")