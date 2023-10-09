#!/usr/bin/env bash
source build.vars
ACTION=$1

config () {
    cmake \
        -DCMAKE_CXX_COMPILER=${COMPILER} \
        -DCMAKE_CXX_FLAGS="${CXXFLAGS}" \
        -S . -B ${BUILD_DIR} -G "${SYSTEM}"
}

build () {
    cmake --build ${BUILD_DIR} -j ${NCORES}
    # [[ -f "${BUILD_DIR}/SandboxApp" ]] && ln -svf ${BUILD_DIR}/SandboxApp ${APP_NAME}
}

clean () {
    rm -rfv ${BUILD_DIR}
    # rm -fv ${APP_NAME}
}

case $ACTION in
    config)
        config
        ;;
    build)
        build
        ;;
    clean)
        clean
        ;;
    *)
        build
        ;;
esac
