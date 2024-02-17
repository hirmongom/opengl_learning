#!/bin/bash

CC=gcc
MACROS="-DUNUSED=__attribute__((__unused__))"
CFLAGS="-Wall -Wextra -Iinclude"
LDFLAGS="-lm -lGL -lglfw"
OUT_FILE="build/main"
SRC_FILES="src/main.c src/glad/glad.c $(find src/custom/ -name '*.c' -printf '%p ')"

# Check for AVX2 support
if grep -q avx2 /proc/cpuinfo; then
	CFLAGS+=" -mavx2"
fi

# Check for Intel SSE support
if grep -q 'GenuineIntel' /proc/cpuinfo && grep -q sse /proc/cpuinfo; then
	CFLAGS+=" -msse"
fi

# Check for AMD SSE4a support
if grep -q 'AuthenticAMD' /proc/cpuinfo && grep -q sse4a /proc/cpuinfo; then
	CFLAGS+=" -msse4a"
fi

CFLAGS+=" -march=native -funroll-loops -mtune=native -O2 -ftree-vectorize"

echo "$CC $CFLAGS $MACROS -o $OUT_FILE $SRC_FILES $LDFLAGS"

$CC $CFLAGS $MACROS -o $OUT_FILE $SRC_FILES $LDFLAGS