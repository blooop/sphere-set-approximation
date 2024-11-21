#ifndef POINTSET_HPP
#define POINTSET_HPP

#include <unordered_set>
#include <algorithm>
#include <tuple>
#include "rtcore/mesh.hpp"
#include "rtcore/mt19937sampler.hpp"
#include "point_in_mesh.hpp"
#include "math/vecmath.hpp"
#include "visualize.hpp"
#include "util.hpp"


typedef std::vector<vec3f> PointSet;


std::tuple<vec3f, vec3f> farthest_points_apart(const PointSet& p);
PointSet allvertices(const RTcore::Mesh& mesh);

double diameter(const RTcore::Mesh& mesh);


PointSet voxelized(const RTcore::Mesh& mesh, double vxsize);

PointSet get_inner_points(const RTcore::Mesh& mesh, int n_approx);


double volume(const RTcore::Mesh& mesh, int n_approx);


PointSet sample_surface(const RTcore::Mesh& mesh, int n_approx);

PointSet sample_surface_bestcandidate(const RTcore::Mesh& mesh, int n_approx);

PointSet get_surface_points(const RTcore::Mesh& mesh, int n_approx);
#endif