#!/bin/sh
if [ -z "$DSPBA_ROOTDIR" ]; then
    DSPBA_ROOTDIR="/p/psg/swip/releases/acdskit/26.1/110/linux64/quartus/dspba/"
fi

CMAKE_PATH="../"
if [ -n "$1" ]; then
    CMAKE_PATH="$1"
fi
export DSPBA_ROOTDIR="$DSPBA_ROOTDIR"
cmake -G "Ninja Multi-Config" $CMAKE_PATH
if [ $? -eq 0 ]; then
    cmake --build . --parallel 16 --config Release 2>&1 && echo Build status: $?
fi
