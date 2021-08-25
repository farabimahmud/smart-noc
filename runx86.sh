#!/bin/bash

./build/X86/gem5.opt \
    --debug-flags=smart,Ruby \
    --debug-file=debug.out \
    configs/example/se.py \
    --num-cpus=64 \
    --num-dirs=64 \
    --network=garnet \
    --topology=Mesh_XY \
    --mesh-row=8 \
    --ruby \
    --caches \
    --l2cache \
    --num-l2caches=64 \
    --cmd="a.out" \
    --enable-smart \

