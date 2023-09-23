#!/usr/bin/env bash

source build.vars
ACTION=$1

configure () {
    cmake \
        -DCMAKE_CXX_COMPILER=${COMPILER} \
        -DCMAKE_CXX_FLAGS="${CXXFLAGS}" \
        -S . -B ${BUILD_DIR}
}

build () {
    (cd ${BUILD_DIR} && make -j)
    [[ -f "${BUILD_DIR}/SandboxApp" ]] && ln -svf ${BUILD_DIR}/SandboxApp ${APP_NAME}
}

clean () {
    rm -rfv ${BUILD_DIR}
    rm -fv ${APP_NAME}
}

case $ACTION in
    configure)
        configure
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
