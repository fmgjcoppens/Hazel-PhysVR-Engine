#!/usr/bin/env bash

rm -rfv _build/ bin/ &&  cmake -S . -B _build/ && (cd _build/ && make)

mkdir bin
mv -v _build/SandboxApp bin/

