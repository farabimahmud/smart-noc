#!/bin/bash


mkdir -p /home/grads/f/farabi/smart-noc/m5out/ckpts/freqmine-64-test-x86
/home/grads/f/farabi/smart-noc/build/X86_MESI_Two_Level/gem5.opt --outdir=/home/grads/f/farabi/smart-noc/m5out/ckpts/freqmine-64-test-x86 /home/grads/f/farabi/smart-noc/configs/example/fs.py --script=/home/grads/f/farabi/smart-noc/scripts_x86/freqmine_64c_test_ckpts.rcS --kernel=/home/grads/f/farabi/gem5-kernel/x86-parsec/binaries/x86_64-vmlinux-2.6.28.4-smp --disk-image=/home/grads/f/farabi/gem5-kernel/x86-parsec/disks/x86root.img --cpu-type=AtomicSimpleCPU --take-checkpoints=100000000 --at-instruction --checkpoint-dir=/home/grads/f/farabi/smart-noc/m5out/ckpts/freqmine-64-test-x86 --num-cpus=64 --mem-size=4GB 
