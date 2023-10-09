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
}

install () {
    mkdir -v ${INSTALL_DIR}
    cp -av ${BUILD_DIR}/Sandbox/Sandbox ${INSTALL_DIR}
    cp -av Sandbox/assets ${INSTALL_DIR}
}

run () {
    (cd ${INSTALL_DIR} && ./Sandbox)
}

clean () {
    rm -rfv ${BUILD_DIR}
}

distclean () {
    rm -rfv ${BUILD_DIR}
    rm -rfv ${INSTALL_DIR}
}

case $ACTION in
    config)
        config
        ;;
    build)
        build
        ;;
    install)
        install
        ;;
    run)
        run
        ;;
    clean)
        clean
        ;;
    distclean)
        distclean
        ;;
    *)
        build
        ;;
esac
