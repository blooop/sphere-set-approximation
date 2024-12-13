#include "sphere_set_approximator.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, const char* argv[])
{
    //Ensure the program is called with the correct number of arguments
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file> <number_of_spheres>" << std::endl;
        return 1;
    }

    // Parse the number of spheres
    char* end;
    int n_sphere = std::strtol(argv[3], &end, 10);
    if (*end != '\0' || n_sphere <= 0) {
        std::cerr << "Error: <number_of_spheres> must be a positive integer." << std::endl;
        return 1;
    }
	sphere_set_approximator::sphere_set_approximator_params params;
	// parse command line arguments
	params.resolution = 20000;
	params.check_manifold = true;
	params.max_cost = 1e-2;
	params.max_faces = 10000;
	params.max_ratio = 0.2;
	
	params.n_finalsample = 100000;
	params.n_innersample = 8000;
	params.n_mutate = 10;
	params.n_sphere = n_sphere;
	params.n_surfacesample = 4000;
	params.seed = 19260817;

	sphere_set_approximator::approximate_spheres(argv[1], argv[2], params);
	return 0;
}
