#!/usr/bin/env sh

set -xe

CFLAGS="-Wall -Werror"
CFILES="main.c allocator.c"

clang ${CFLAGS} -o main ${CFILES}
