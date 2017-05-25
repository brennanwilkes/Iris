#ifndef GLOBAL_H
#define GLOBAL_H

#include "player.hpp"
#include "enemy.hpp"
#include "world.hpp"
#include "level.hpp"
#include "staticObject.hpp"
#include "nodePath.h"
#include "windowFramework.h"
#include <vector>

#include "filename.h"
#include "executionEnvironment.h"

extern AsyncTaskManager* taskMgr;
extern ClockObject* globalClock;
extern Filename mydir; 
extern Player player;
extern vector<GameObject*> objs;
extern vector<Enemy*> enems;
extern vector<Item*> itms;
extern vector<StaticObject*> stats;
extern NodePath startMenuItems;
extern NodePath gameModels;
extern NodePath menuItems;
extern NodePath optionMenuItems;
extern NodePath staticModels;
extern World world;
extern WindowFramework *window;
extern int scene;
extern PT(PGSliderBar) Slider;
extern vector<Level*> gameLevels;
#endif
