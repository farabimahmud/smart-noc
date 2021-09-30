#!/bin/bash



/home/grads/f/farabi/gem5/build/X86_MESI_Two_Level/gem5.opt --outdir=/home/grads/f/farabi/gem5/m5out/parsec_simlarge/canneal /home/grads/f/farabi/gem5/configs/example/se.py --num-cpus=16 --num-dirs=16 --network=garnet --topology=Mesh_XY --mesh-row=4 --ruby --caches --l2cache --num-l2caches=16 --cpu-type=DerivO3CPU --cmd=/home/grads/f/farabi/benchmarks/parsec-build/bin/canneal --options="16 15000 2000 /home/grads/f/farabi/benchmarks/parsec-build/inputs/canneal/400000.nets 128
"
