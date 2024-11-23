#include "sphere_set_approximator.hpp"

int main(int argc, const char* argv[])
{
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
	params.n_sphere = 64;
	params.n_surfacesample = 4000;
	params.seed = 19260817;

	sphere_set_approximator::approximate_spheres(argv[1], argv[2], params);
	return 0;
}
