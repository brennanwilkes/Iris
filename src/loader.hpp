#ifndef LOADER_H
#define LOADER_H

// Our files
#include "player.hpp"
#include "world.hpp"
#include "weapon.hpp"
#include "item.hpp"
#include "staticObject.hpp"
#include "waterItem.hpp"
#include "foodItem.hpp"
#include "healthItem.hpp"
#include "enemy.hpp"
#include "keys.hpp"
#include "level.hpp"
#include "global.hpp"

#include <map>

#include "nodePath.h"

class Loader{
public:
	void load_level(Level L);
	
private:

};

#endif
