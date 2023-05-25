#!/bin/bash
export CC=/usr/bin/clang
[ ! -d build ] && mkdir build && cmake -B build
cmake --build build
