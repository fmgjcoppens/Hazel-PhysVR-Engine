# The TARGET_COMPILE_DEFINITIONS, TARGET_PRECOMPILE_HEADERS and 
# TARGET_INCLUDE_DIRECTORIES all have visibility PRIVATE, which means that they
# are not automatically available to other CMake targets (like Sandbox). They
# must be explicitly added to each target that needs them. It is advised to use
# PRIVATE as often as possible and to be as explicit as possible when
# indicating the dependencies for each target.
project(HazelPVR LANGUAGES CXX)

# HazelPVR file structure
include(FileStructure.cmake)

# HazelPVR-specific platform settings
include(SetPlatformAttributes.cmake)

# Build and import GLFW (docs, tests & examples force-disabled)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${GLFW})

# Build and import Dear ImGui
add_subdirectory(${IMGUI})

# Build and import Glad
add_subdirectory(${GLAD})

# HazelPVR target itself
add_library(${PROJECT_NAME} STATIC
    ${SRC_HZPVR_CORE}
    ${SRC_HZPVR_IMGUI}
    ${SRC_HZPVR_RENDERER}
    ${SRC_PLATFORM_OS}
    ${SRC_PLATFORM_OPENGL}
    ${SRC_STB_IMAGE}
)

# HazelPVR-specific definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE
    GLFW_INCLUDE_NONE # Prevent GLFW from including OpenGL/Vulkan headers
)

target_precompile_headers(${PROJECT_NAME} PRIVATE ${PCH})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${HDR_ROOT_DIR}
    ${SPDLOG_HDR}
    ${GLAD_HDR}
    ${GLM}
    ${IMGUI}
    ${GLFW_HDR}
    ${STB_IMAGE}
)

target_link_libraries(${PROJECT_NAME}
    glfw
    glad
    imgui
)
