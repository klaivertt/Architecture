#ifndef COMMON__H
#define COMMON__H

#include <vector>
#include <memory>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <format>
#include <time.h>
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <utility>

constexpr const float M_PI = 3.141592654f;


class Visitor;
class SystemeBase;
class Files;
class Directory;

int Rand(int _min = 0, int _max = 100);

#endif