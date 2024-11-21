#ifndef VISUALIZE_HPP
#define VISUALIZE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include "math/vecmath.hpp"
#include "rtcore/mesh.hpp"
#include "sphere.hpp"

typedef std::vector<vec3f> PointSet;

std::string extractFilename(const std::string& str);

void visualize(std::vector<Sphere> spheres, std::string visualizer_mesh_filename = "", std::string outfile = "scene.json", vec3f camerapos = vec3f(3,2,-5.76543));

void visualize(const PointSet& set, double visualradius = 0.01);

void visualize_with_mesh(const PointSet& set, std::string visualizer_mesh_filename, double visualradius = 0.01);
#endif