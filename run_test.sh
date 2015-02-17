#!/bin/bash

if [ $# -eq 1 ]; then
    export JEMALLOC_PATH=/usr/lib/x86_64-linux-gnu/
    LD_PRELOAD=${JEMALLOC_PATH}/libjemalloc.so.1 $1 ./run_test
fi
