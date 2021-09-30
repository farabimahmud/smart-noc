#!/bin/bash



/home/grads/f/farabi/gem5/build/X86_MESI_Two_Level/gem5.opt --outdir=/home/grads/f/farabi/gem5/m5out/parsec_simlarge/fluidanimate /home/grads/f/farabi/gem5/configs/example/se.py --num-cpus=16 --num-dirs=16 --network=garnet --topology=Mesh_XY --mesh-row=4 --ruby --caches --l2cache --num-l2caches=16 --cpu-type=DerivO3CPU --cmd=/home/grads/f/farabi/benchmarks/parsec-build/bin/fluidanimate --options="16 5 /home/grads/f/farabi/benchmarks/parsec-build/inputs/fluidanimate/in_300K.fluid /home/grads/f/farabi/benchmarks/parsec-build/inputs/fluidanimate/out.fluid
"
