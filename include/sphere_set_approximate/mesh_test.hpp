#ifndef MESH_TEST_HPP
#define MESH_TEST_HPP

#include "consolelog.hpp"
#include "rtcore/mesh.hpp"
#include "rtcore/triangle.hpp"
#include "point_in_mesh.hpp"

void test_all_normal_outward(const RTcore::Mesh& mesh);

void fix_normal(const RTcore::Mesh& mesh);

#endif