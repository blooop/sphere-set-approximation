#pragma once

#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>

#include "consolelog.hpp"
#include "triangle.hpp"
#include "mesh.hpp"

namespace RTcore
{

// load mesh from an ascii Wavefront .obj file
Mesh objmesh(const char* filename);

}
