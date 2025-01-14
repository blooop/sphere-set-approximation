#include "sphere_set_approximate/mesh_test.hpp"

void test_all_normal_outward(const RTcore::Mesh& mesh)
{
	for (auto t: mesh.list)
	{
		vec3f p = (t->v1 + t->v2 + t->v3)/3 + 0.01 * norm(t->v1-t->v2) * t->planeNormal;
		bool out = 1;
		for (int i=0; i<5; ++i)
			out &= !point_in_mesh(p, mesh);
		if (!out) {
			console.warn("It looks like vn is not pointing outward!");
			console.info("N:",t->planeNormal);
			console.info("V:",t->v1);
			console.info("V:",t->v2);
			console.info("V:",t->v3);
			console.info("p:",p);
			console.info("center:",(t->v1 + t->v2 + t->v3)/3);
		}
	}
}

void fix_normal(const RTcore::Mesh& mesh)
{
	for (auto t: mesh.list)
	{
		vec3f p = (t->v1 + t->v2 + t->v3)/3 + 0.01 * norm(t->v1-t->v2) * t->planeNormal;
		bool out = 1;
		for (int i=0; i<5; ++i)
			out &= !point_in_mesh(p, mesh);
		if (!out) {
			t->planeNormal = -t->planeNormal;
		}
	}
}