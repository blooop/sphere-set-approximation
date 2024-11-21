// calculate Sphere Outside Volume (SOV)

#ifndef SOV_HPP
#define SOV_HPP

#include "math/vecmath.hpp"
#include "rtcore/mesh.hpp"
#include "rtcore/triangle.hpp"
#include "point_in_mesh.hpp"
#include "sotv.hpp"
#include "sphere.hpp"

// parameters: mesh, sphere center & radius
double sov(const RTcore::Mesh& mesh, vec3f o, double r);
double sov(const RTcore::Mesh& mesh, const Sphere& sphere);

#endif