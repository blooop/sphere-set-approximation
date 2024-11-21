#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "math/vecmath.hpp"
#include <vector>

struct Sphere
{
	vec3f center;
	double radius;
	Sphere(vec3f center, double radius): center(center), radius(radius) {}
	Sphere& operator= (const Sphere& s)
	{
		center = s.center;
		radius = s.radius;
		return *this;
	}
	double volume() const
	{
		return 4.0/3*PI*radius*radius*radius;
	}
};

double sphere_overlap_volume(vec3f o1, double r1, vec3f o2, double r2);

double sphere_overlap_volume(Sphere a, Sphere b);

// of each sphere, ratio of volume shared with at least one other spherein the set to its total volume
// complexity: O(|sphere|^2 * n_approx) but in fact fast enough
std::vector<double> overlap_ratio(const std::vector<Sphere>& sphere, int n_approx);

// of each sphere, volume ushared with all other spheres in the set
// complexity: O(|sphere|^2 * n_approx) but in fact fast enough
std::vector<double> unique_volume(const std::vector<Sphere>& sphere, int n_approx);

// volume of union geometry
// complexity: O(|sphere|^2 * n_approx) but in fact fast enough
double volume(const std::vector<Sphere>& sphere, int n_approx);
#endif