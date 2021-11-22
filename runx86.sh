#!/bin/bash

build/X86_MESI_Two_Level/gem5.opt \
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
    --cpu-type=DerivO3CPU \
    --cmd="blackscholes" \
    --maxinsts=10000000 \
    --enable-smart \
    --smart_hpcmax=7 \
    --smart_dest_bypass \
    --options="64 in_16K.txt output.out"  > log_file 2>&1 
   
