#ifndef GLOBAL_H
#define GLOBAL_H

#include "player.hpp"
#include "enemy.hpp"
#include "world.hpp"
#include "nodePath.h"
#include "windowFramework.h"
#include <vector>

extern AsyncTaskManager* taskMgr;
extern ClockObject* globalClock;
extern Player player;
extern vector<GameObject*> objs;
extern vector<Enemy*> enems;
extern vector<Item*> itms;
extern NodePath gameModels;
extern NodePath menuItems;
extern NodePath optionMenuItems;
extern World world;
extern WindowFramework *window;
extern int scene;
extern PT(PGSliderBar) Slider;
#endif
