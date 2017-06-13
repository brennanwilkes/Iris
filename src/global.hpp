/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
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
extern NodePath deathMenuItems;
extern NodePath loadMenuItems;
extern NodePath staticModels;
extern World world;
extern WindowFramework *window;
extern int scene;
extern PT(PGSliderBar) Slider;
extern vector<Level*> gameLevels;
#endif
