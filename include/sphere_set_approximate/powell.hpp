#ifndef POWELL_HPP
#define POWELL_HPP

#include <functional>
#include <algorithm>
#include <vector>
#include <numeric>
#include "math/vecmath.hpp"
#include "consolelog.hpp"
#include "util.hpp"

double optimize(double initial, std::function<double(double)> loss);

vec3f optimize(vec3f initial, std::function<double(vec3f)> loss);
#endif