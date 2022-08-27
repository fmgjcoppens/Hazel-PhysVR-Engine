## Vendor (external dependencies) include dirs
set(VENDOR_INCL_DIR ${INCL_DIR}/vendor)

# spdlog logger (submodule) include dir
set(LOGGER_INCL_DIR ${VENDOR_INCL_DIR}/spdlog/include)

# GLFW (submodule) build target and suppress building docs, tests and examples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${VENDOR_INCL_DIR}/glfw)

# Glad build target
add_subdirectory(${VENDOR_INCL_DIR}/glad)
