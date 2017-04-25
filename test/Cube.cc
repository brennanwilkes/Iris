#include "Cube.hpp"
#include "nodePath.h"

Cube::Cube() : public NodePath{
	is_ground = false;
	vel = 0;
}
