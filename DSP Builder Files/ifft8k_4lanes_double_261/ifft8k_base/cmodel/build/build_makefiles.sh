#!/bin/sh
if [ -z "$DSPBA_ROOTDIR" ]; then
    DSPBA_ROOTDIR="/p/psg/swip/releases/acdskit/26.1/110/linux64/quartus/dspba/"
fi

CMAKE_PATH="../"
if [ -n "$1" ]; then
    CMAKE_PATH="$1"
fi
export DSPBA_ROOTDIR="$DSPBA_ROOTDIR"
cmake -DCMAKE_BUILD_TYPE="Release" -G "Unix Makefiles" $CMAKE_PATH
if [ $? -eq 0 ]; then
    cmake --build . --parallel 16 >&1 && echo Build status: $?
fi
