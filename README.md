# Sphere Set Approximation

Approximate a mesh by bounding it with a set of spheres, which can be used for collision detection, shadowing, etc.

![demo](attachments/demo.jpg)

Integrate [hjwdzh/Manifold](https://github.com/hjwdzh/Manifold) and [111116/sphere-set-approximation](https://github.com/111116/sphere-set-approximation)

You may try with different seeds to get better result.

The algorithm runs quite slow (proportional to number of triangular faces of the manifold).

The manifold must be closed and orientable.

## Usage

```bash
sh ./demo.sh

// tungsten render
cd ~/workspace/3rd_party
git clone git@github.com:tunabrain/tungsten.git
cd tungsten
./setup_builds.sh
cd builds/release
make
echo "alias tungsten="~/workspace/3rd_party/tungsten/build/release/tungsten"" >> ~/.zshrc

tungsten example/armadillo.json
```

#### paper abstract

We approximate a solid object represented as a triangle mesh by a bounding set of spheres having minimal summed volume outside the object. We show how outside volume for a single sphere can be computed using a simple integration over the object’s triangles. We then minimize the total outside volume over all spheresin the set using a variant of iterative Lloyd clustering which splits the mesh points into sets and bounds each with an outside volume-minimizing sphere. The resulting sphere sets are tighter than those of previous methods. In experiments comparing against a state-of-the-art alternative (adaptive medial axis), our method often requires half or fewer as many spheres to obtain the same error, under a variety of error metrics including total outside volume, shadowing fidelity, and proximity measurement.
