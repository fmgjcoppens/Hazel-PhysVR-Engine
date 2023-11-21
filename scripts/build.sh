#!/usr/bin/env bash
ACTION=$1
EXEC_DIR=$PWD

source ${EXEC_DIR}/scripts/build.vars

config () {
    cmake \
        -DCMAKE_CXX_COMPILER=${COMPILER} \
        -DCMAKE_CXX_FLAGS="${CXXFLAGS}" \
        -S ${EXEC_DIR} -B ${EXEC_DIR}/${BUILD_DIR} -G "${SYSTEM}"
}

build () {
    cmake --build ${EXEC_DIR}/${BUILD_DIR} -j ${NCORES}
}

install () {
    mkdir -v ${EXEC_DIR}/${INSTALL_DIR}
    cp -av ${EXEC_DIR}/${BUILD_DIR}/Sandbox/Sandbox ${EXEC_DIR}/${INSTALL_DIR}
    cp -av Sandbox/assets ${EXEC_DIR}/${INSTALL_DIR}
}

run () {
    (cd ${EXEC_DIR}/${INSTALL_DIR} && ./Sandbox)
}

clean () {
    rm -rfv ${EXEC_DIR}/${BUILD_DIR}
}

distclean () {
    rm -rfv ${EXEC_DIR}/${BUILD_DIR}
    rm -rfv ${EXEC_DIR}/${INSTALL_DIR}
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
