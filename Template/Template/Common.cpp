#include "Common.h"

int Rand(int _min, int _max)
{
    return _min + std::rand() % (_max - _min);
}
