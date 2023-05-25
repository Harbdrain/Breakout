#!/bin/bash
[ ! -d build ] && mkdir build && cmake -B build
CC=clang cmake --build build
