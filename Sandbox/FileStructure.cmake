# Set SOURCE dirs
set(SRC_ROOT_DIR src)

# Glob SOURCE files
file(GLOB SRC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_ROOT_DIR}/*.cpp)

# Set INCLUDE dirs
set(INCLUDES
    ../HazelPVR/vendor/spdlog/include
    ../HazelPVR/vendor/glm
    ../HazelPVR/include
)