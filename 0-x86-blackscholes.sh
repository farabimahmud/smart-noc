#!/bin/bash


mkdir -p /home/grads/f/farabi/smart-noc/m5out/restore/x86/test_10000000/blackscholes-16-simmedium-x86-baseline
/home/grads/f/farabi/smart-noc/build/X86_MESI_Two_Level/gem5.opt --outdir=/home/grads/f/farabi/smart-noc/m5out/restore/test_10000000/blackscholes-16-simmedium-x86-baseline /home/grads/f/farabi/smart-noc/configs/example/fs.py --script=/home/grads/f/farabi/smart-noc/scripts_x86/blackscholes_16c_simmedium_ckpts.rcS --kernel=/home/grads/f/farabi/gem5-kernel/x86-parsec/binaries/x86_64-vmlinux-2.6.28.4-smp --disk-image=/home/grads/f/farabi/gem5-kernel/x86-parsec/disks/x86root.img --cpu-type=DerivO3CPU --checkpoint-dir=/home/grads/f/farabi/nuca/m5out/ckpts/blackscholes-16-simmedium-x86 --checkpoint-restore=1 --num-cpus=16 --mem-size=2GB --ruby --num-l2caches=16 --num-dirs=16 --l1d_assoc=8 --l2_assoc=16 --l1i_assoc=4 --l2_size=16kB --network=garnet --topology=Mesh_XY --mesh-rows=4 --maxinsts=10000000 
