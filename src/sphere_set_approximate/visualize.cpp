#ifndef VISUALIZE_HPP
#define VISUALIZE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include "math/vecmath.hpp"
#include "rtcore/mesh.hpp"
#include "sphere_set_approximate/sphere.hpp"

typedef std::vector<vec3f> PointSet;

std::string extractFilename(const std::string& str) {
  // 找到最后一个 '/' 的位置
  size_t lastSlash = str.find_last_of('/');

  // 找到最后一个 '.' 的位置
  size_t lastDot = str.find_last_of('.');

  // 提取文件名 (不包括扩展名)
  if (lastSlash != std::string::npos && lastDot != std::string::npos && lastDot > lastSlash) {
    return str.substr(lastSlash + 1, lastDot - lastSlash - 1);
  } else {
    // 处理找不到 '/' 或 '.' 的情况
    return ""; 
  }
}

void visualize(std::vector<Sphere> spheres, std::string visualizer_mesh_filename = "", std::string outfile = "scene.json", vec3f camerapos = vec3f(3,2,-5.76543))
{
	std::string name = extractFilename(outfile);
	name = name + ".png";
	console.info("For visualization, run: tungsten", outfile);
	std::ofstream fout(outfile);
	fout << "{\"primitives\":[\n";
	if (visualizer_mesh_filename != "")
	{
		fout << "{\"type\":\"mesh\",\"file\":\"" << visualizer_mesh_filename << "\",\"bsdf\":{\"type\":\"lambert\",\"albedo\":0.8}},\n";
	}
	for (auto sph : spheres)
	{
		fout << "{\"type\": \"sphere\",\"transform\":{\"position\":["
		<< sph.center.x << "," << sph.center.y << "," << sph.center.z << "],\"scale\":" << sph.radius << "},\"bsdf\":{\"type\":\"lambert\",\"ior\":1.3,\"albedo\":[1,0.6,0.6]}},\n";
	}
    fout << "{\"type\": \"skydome\",\"temperature\": 4777.0,\"gamma_scale\": 1.0,\"turbidity\": 3.0,\"intensity\": 6.0,\"sample\": true}";
	fout << "],\n";
	fout << "\"camera\":{\"resolution\":[2048,2048],\"transform\":{";
	// print camera pos
	fout << "\"position\": [" << camerapos.x << "," << camerapos.y << "," << camerapos.z << "], \"look_at\": [0,0,0], \"up\": [0,1,0]";

	fout << "},";
	fout << "\"type\":\"pinhole\",\"fov\":40},\n";
    fout << "\"integrator\": {\"min_bounces\": 0,\"max_bounces\": 16,\"type\": \"path_tracer\"},\n";
	fout << "\"renderer\": {\"scene_bvh\": true,\"spp\": 16,\"output_file\": \"" << name << "\"}\n";
    fout << "}\n";
}

void visualize(const PointSet& set, double visualradius = 0.01)
{
	std::string visualizer_mesh_filename = "";
	std::string tmp = visualizer_mesh_filename;
	visualizer_mesh_filename = "";
	std::vector<Sphere> s;
	for (auto p: set)
		s.push_back(Sphere(p, visualradius));
	visualize(s);
	visualizer_mesh_filename = tmp;
}

void visualize_with_mesh(const PointSet& set, std::string visualizer_mesh_filename, double visualradius = 0.01)
{
	std::vector<Sphere> s;
	for (auto p: set)
		s.push_back(Sphere(p, visualradius));
	visualize(s, visualizer_mesh_filename);
}
#endif