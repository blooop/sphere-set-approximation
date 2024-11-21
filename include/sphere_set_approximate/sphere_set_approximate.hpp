#ifndef SPHERE_SET_APPROXIMATE_HPP
#define SPHERE_SET_APPROXIMATE_HPP

#include <vector>
#include <algorithm>
#include <map>
#include <cassert>

#include "sov.hpp"
#include "rtcore/mesh.hpp"
#include "visualize.hpp"
#include "util.hpp"
#include "pointset.hpp"
#include "powell.hpp"


std::tuple<std::vector<Sphere>, std::vector<PointSet>>
	points_assign_MO(const std::vector<vec3f>& center, const PointSet& points, std::function<double(Sphere)> loss);

std::tuple<std::vector<Sphere>, std::vector<PointSet>>
	points_assign(const std::vector<vec3f>& center, const PointSet& points, std::function<double(Sphere)> loss);
Sphere sphere_fit(const Sphere& initial, const PointSet& points, std::function<double(Sphere)> loss);

void checkContain(const Sphere& s, const PointSet& points);

// Note: radii are invalidated after teleportation
void teleport(std::vector<Sphere>& sphere, std::vector<PointSet>& points, std::function<double(Sphere)> loss);

// Note: radii are invalidated after teleportation
void teleport_n(std::vector<Sphere>& sphere, std::vector<PointSet>& points, std::function<double(Sphere)> loss);

std::vector<Sphere> sphere_set_approximate(const std::string &pt_output_file, const RTcore::Mesh& originalmesh, std::string visualizer_mesh_filename, const RTcore::Mesh& manifold, int ns, int ninner, int nsurface, int n_finalsample, int n_mutate);
#endif