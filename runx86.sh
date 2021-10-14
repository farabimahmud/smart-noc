#!/bin/bash

build/X86_MESI_Two_Level/gem5.opt \
    --debug-file=debug.out \
    --debug-flags=Ruby \
    configs/example/se.py \
    --num-cpus=16 \
    --num-dirs=16 \
    --network=garnet \
    --topology=Mesh_XY \
    --mesh-row=4 \
    --ruby \
    --caches \
    --l2cache \
    --num-l2caches=16 \
    --cpu-type=DerivO3CPU \
    --cmd="/home/grads/f/farabi/benchmarks/parsec-build/blackscholes/bin" \
    --maxinsts=1000000 \
    --options="16 /home/grads/f/farabi/benchmarks/parsec-build/blackscholes/in_4.txt /home/grads/f/farabi/benchmarks/parsec-build/blackscholes/output.out"  > log_file 2>&1 
   
