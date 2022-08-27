#!/usr/bin/env bash

rm -rf _build/ &&  cmake -S . -B _build/ && (cd _build/ && make)

mkdir bin
mv -v _build/SandboxApp bin/

