#!/bin/bash

/home/grads/f/farabi/gem5/build/X86_MESI_Two_Level/gem5.opt \
    /home/grads/f/farabi/gem5/configs/example/se.py \
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
    --options="16 /home/grads/f/farabi/benchmarks/parsec-build/blackscholes/in_64K.txt /home/grads/f/farabi/benchmarks/parsec-build/blackscholes/output.out"
   
