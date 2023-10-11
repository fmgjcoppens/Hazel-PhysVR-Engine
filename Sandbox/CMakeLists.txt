project(Sandbox LANGUAGES CXX)

# Sandbox file structure
include(FileStructure.cmake)

add_executable(${PROJECT_NAME} ${SRC_ROOT})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES})

target_link_libraries(${PROJECT_NAME} HazelPVR)
