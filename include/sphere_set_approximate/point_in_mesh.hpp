#ifndef POINT_IN_MESH_HPP
#define POINT_IN_MESH_HPP

#include "math/vecmath.hpp"
#include "rtcore/ray.hpp"
#include "rtcore/mesh.hpp"
#include "rtcore/triangle.hpp"
#include "rtcore/sharedsampler.hpp"

bool point_in_mesh(vec3f p, const RTcore::Mesh& mesh);

#endif