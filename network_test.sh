#!/bin/bash

./build/NULL/gem5.debug \
    --debug-flag=smart \
    --debug-file=debug.out \
    configs/example/garnet_synth_traffic.py \
    --num-cpus=64 \
    --num-dirs=64 \
    --network=garnet \
    --sim-cycles=50000 \
    --topology=Mesh_XY \
    --mesh-rows=8  \
    --synthetic=uniform_random \
    --injectionrate=0.05 \
    --single-sender-id=0 \
    --single-dest-id=7 \
    --enable-smart \
    --smart_hpcmax=7 \
    --smart_dest_bypass \
    #--debug-flags=smart,RubyNetwork \
    #--debug-file=debug.out \

