#!/usr/bin/env bash

# BUILD_DIR=_build_linux

source vars.sh

(cd ${BUILD_DIR} && make -j)

[[ -f "${BUILD_DIR}/SandboxApp" ]] && ln -svf ${BUILD_DIR}/SandboxApp ${APP_NAME}
