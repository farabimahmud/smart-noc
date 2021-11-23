#!/bin/bash

build/X86_MESI_Two_Level/gem5.opt \
    --debug-flags=ReadingPCFile \
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
    --fast-forward=9223372036854775807 \
    --cpu-type=DerivO3CPU \
    --cmd="pathfinder" \
    --read_pc_list_from_file \
    --pc_list_filename="pcs/pathfinder.txt" \
    --options="100 1 64"  > log_file 2>&1 


#     --enable-smart \
#    --smart_hpcmax=6 \
#    --smart_dest_bypass \

   
