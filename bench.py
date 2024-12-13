
#!/usr/bin/env -S uv run
# /// script
# dependencies = ["holobench[rerun]==1.32.0"]
# ///

import bencher as bch
import numpy as np
import math
import sys
import os
from pathlib import Path

class SphereGenerator(bch.ParametrizedSweep):
    num_spheres = bch.IntSweep(default=1, bounds=(1, 64))
    image = bch.ResultImage()

    def __call__(self, **kwargs):
        self.update_params_from_kwargs(**kwargs)
        self.image =self.call_sphere_gen("./example/input.obj",   self.num_spheres) 
        return super().__call__()
    
    def call_sphere_gen(self,input_obj:str,num_spheres:int): 
        input_path = Path(input_obj)
        output_file = Path(bch.gen_image_path())
        print(output_file)
        output_file = output_file.with_stem(f"{input_path.stem}-sph-{num_spheres}")
        print(output_file)
        output_file = output_file.with_suffix(".json")  
        print(output_file)

        cmd= f"/workspaces/sphere-set-approximation/build/main {input_path} {output_file} {num_spheres}"
        print(cmd) 
        if not output_file.exists():
            os.system(cmd)
        os.system(f"/workspaces/sphere-set-approximation/3rd_party/tungsten/build/release/tungsten {output_file}")
        return output_file.with_suffix(".png")


def sphere_gen(run_cfg=None,report=None):
    bench = SphereGenerator().to_bench(run_cfg,report)
    bench.plot_sweep()
    return bench

if __name__ == "__main__":
    bench_run = bch.BenchRunner("bench_runner_test")
    bench_run.add_run(sphere_gen)
    bench_run.run(show=True)
    # bench_run.run(level =2,show=True,use_cache=False)

    # run_cfg = bch.BenchRunCfg()   
    # run_cfg.use_sample_cache = True
    # run_cfg.only_hash_tag = True
    # run_cfg.level =4
    # # run_cfg.executor = bch.Executors.MULTIPROCESSING
    # bench = SphereGenerator().to_bench(run_cfg)
    
    # bench.plot_sweep()

    # bench.report.show()