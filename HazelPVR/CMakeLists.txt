project(HazelPVR LANGUAGES CXX)

include(FileStructure.cmake)

add_subdirectory(${GLFW})
add_subdirectory(${IMGUI})
add_subdirectory(${GLAD})

add_library(${PROJECT_NAME} STATIC
    ${SRC_HZPVR}
    ${SRC_HZPVR_IMGUI}
    ${SRC_HZPVR_RENDERER}
    ${SRC_PLATFORM_WINDOWS}
    ${SRC_PLATFORM_OPENGL}
)

target_precompile_headers(${PROJECT_NAME} PUBLIC
    ${HDR_ROOT_DIR}/hzpvrpch.hpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${HDR_ROOT_DIR}
    ${SPDLOG}/include
    ${GLAD}/include
    ${GLM}
    ${IMGUI}
    ${GLFW}/include
)

target_link_libraries(${PROJECT_NAME}
    glfw
    glad
    imgui
)
