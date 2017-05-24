#ifndef OURLOADER_H
#define OURLOADER_H

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

class OurLoader{
public:
	void load_level(Level L,WindowFramework* w,PandaFramework* pf);
private:

};

#endif
