#!/bin/python3

import os

benchmarks = [
"blackscholes",
"bodytrack",
"canneal",
"dedup",
"facesim",
"ferret",
"fluidanimate",
"freqmine",
"streamcluster",
"swaptions",
"x264",
]

run_size = "simlarge"
run_name = "parsec_"+run_size

base_dir = "/home/grads/f/farabi/gem5"
gem5_binary = os.path.join(base_dir, "build/X86_MESI_Two_Level/gem5.opt")
parsec_dir = "/home/grads/f/farabi/benchmarks/parsec-build"


input_sets = "/home/grads/f/farabi/gem5/inputsets.txt"
input_size = {
        "test":1,
        "simdev":2,
        "simsmall":3,
        "simmedium":4,
        "simlarge":5,
        }

def create_script(params=None):
    if params == None:
        params = {}
        params["num_cpu"] = 16
        params["network"] = "garnet"
        params["benchmark"] = "blackscholes"
        params["input_size"] = "simsmall"

    s = gem5_binary
    s += " --outdir={}".format(os.path.join(base_dir,
            "m5out",run_name,params["benchmark"]))
    s += " "+ os.path.join(base_dir, "configs/example/se.py")
    s += " --num-cpus={}".format(params["num_cpu"])
    s += " --num-dirs={}".format(params["num_cpu"])
    s += " --network={}".format(params["network"])
    s += " --topology={}".format("Mesh_XY")
    s += " --mesh-row={}".format(4)
    s += " --ruby"
    s += " --caches"
    s += " --l2cache"
    s += " --num-l2caches={}".format(params["num_cpu"])
    s += " --cpu-type={}".format("DerivO3CPU")
    s += " --cmd={}".format(os.path.join(parsec_dir,"bin",params["benchmark"]))
    input_str = ""
    with open(input_sets,"r") as f:
        for lines in f:
            data = lines.split(";")
            if data[0] == params["benchmark"]:
                input_str = data[input_size[params["input_size"]]]
                input_str = input_str.replace("<nthreads>",
                str(params["num_cpu"]))
                input_str = input_str.replace("<inputdir>",
                        os.path.join(parsec_dir,
                        "inputs",params["benchmark"])+"/")
                #print(input_str)

    s += " --options=\"{}\"".format(input_str)

    return s

if __name__=="__main__":
    params = {}
    params["num_cpu"] = 16
    params["network"] = "garnet"
    params["input_size"] = run_size

    for b in benchmarks:
        params["benchmark"] = b
        s = create_script(params)
        script_file = os.path.join(base_dir, "parsec_scripts", b+".sh")
        with open(script_file,"w") as f:
            print("#!/bin/bash", file=f)
            print("\n\n", file=f)
            print(s, file=f)






