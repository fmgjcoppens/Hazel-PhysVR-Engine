#!/usr/bin/env bash

ACTION=$1

source build.vars

case $ACTION in
    configure)
        cmake \
            -DCMAKE_CXX_COMPILER=${COMPILER} \
            -DCMAKE_CXX_FLAGS="${CXXFLAGS}" \
            -S . -B ${BUILD_DIR}
        ;;
    build)
        (cd ${BUILD_DIR} && make -j)
        [[ -f "${BUILD_DIR}/SandboxApp" ]] && ln -svf ${BUILD_DIR}/SandboxApp ${APP_NAME}
        ;;
    clean)
        rm -rfv ${BUILD_DIR}
        rm -fv ${APP_NAME}
        ;;
    *)
        echo "Unknow or empty argument. Chosing 'build' as default!"
        (cd ${BUILD_DIR} && make -j)
        [[ -f "${BUILD_DIR}/SandboxApp" ]] && ln -svf ${BUILD_DIR}/SandboxApp ${APP_NAME}
        ;;
esac
