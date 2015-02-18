#!/bin/bash

if [ $# -eq 1 ]; then
    scan-build-3.5 -analyze-headers make re
    make test re
    export JEMALLOC_PATH=/usr/lib/x86_64-linux-gnu/
    LD_PRELOAD=${JEMALLOC_PATH}/libjemalloc.so.1 $1 ./run_test
fi
