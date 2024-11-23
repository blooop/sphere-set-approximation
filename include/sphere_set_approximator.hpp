#ifndef SPHERE_SET_APPROXIMATOR_HPP
#define SPHERE_SET_APPROXIMATOR_HPP

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Eigen/Core>

#include "manifold/Model_OBJ.h"
#include "igl/circulation.h"
#include "igl/collapse_edge.h"
#include "igl/edge_flaps.h"
#include "igl/shortest_edge_and_midpoint.h"
#include "igl/read_triangle_mesh.h"
#include "igl/write_triangle_mesh.h"
#include "igl/decimate.h"
#include "igl/qslim.h"

#include "rtcore/objmesh.hpp"
#include "sphere_set_approximate/visualize.hpp"
#include "sphere_set_approximate/mesh_test.hpp"
#include "sphere_set_approximate/util.hpp"
#include "sphere_set_approximate/pointset.hpp"
#include "sphere_set_approximate/sphere_set_approximate.hpp"
#include "argparse.h"

extern int g_sharp;

namespace sphere_set_approximator{

    struct sphere_set_approximator_params {
        int resolution;
        int max_faces;
        double max_ratio;
        double max_cost;
        bool check_manifold;

        int n_sphere;
        int n_innersample;
        int n_surfacesample;
        int n_finalsample;
        int n_mutate;
        int seed;

        sphere_set_approximator_params() {
            resolution = 20000;
            max_faces = 0x7fffffff;
            max_ratio = 0.5;
            max_cost = 0.1;
            check_manifold = true;

            n_sphere = 64;
            n_innersample = 8000;
            n_surfacesample = 4000;
            n_finalsample = 100000;
            n_mutate = 10;
            seed = 19260817;
        }
    };

    void simplify(std::string input_file, std::string output_obj, int max_faces, double max_ratio, double max_cost, bool check_manifold);
    void manifold(std::string input_file, std::string output_file, int resolution);
    void manifold_simple(const std::string &input_file, const std::string &output_file, const sphere_set_approximator_params &params);
    bool approximate_spheres(const std::string &input_file, const std::string &pt_output_file, const sphere_set_approximator_params &params);
}

#endif