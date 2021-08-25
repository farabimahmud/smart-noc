#!/bin/bash

./build/NULL/gem5.debug \
    --debug-flags=smart \
    --debug-file=debug.out \
    configs/example/garnet_synth_traffic.py \
    --num-cpus=64 \
    --num-dirs=64 \
    --network=garnet \
    --sim-cycles=500000 \
    --topology=Mesh_XY \
    --mesh-rows=8  \
    --synthetic=uniform_random \
    --injectionrate=0.01 \
    --single-sender-id=0 \
    --single-dest-id=63 \
    
