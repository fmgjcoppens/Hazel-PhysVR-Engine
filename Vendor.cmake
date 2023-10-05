## Vendor (external dependencies) include dirs
set(VENDOR_INCL_DIR ${INCL_DIR}/vendor)

# spdlog logger (submodule) include dir
set(LOGGER_INCL_DIR ${VENDOR_INCL_DIR}/spdlog/include)

# GLFW (submodule) build target, suppress building docs, tests and examples
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
add_subdirectory(${VENDOR_INCL_DIR}/glfw)

# Glad static lib build target
add_subdirectory(${VENDOR_INCL_DIR}/glad)

# Imgui static lib build target
add_subdirectory(${VENDOR_INCL_DIR}/imgui)

# OpenGL Math (glm) (HEADER ONLY LIB!) include dir
set(GLM_INCL_DIR ${VENDOR_INCL_DIR}/glm)
