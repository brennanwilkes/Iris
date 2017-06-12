/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef WORLD_H
#define WORLD_H

#include <map>
#include <vector>
#include "sounds.hpp"
#include "asyncTaskManager.h"
#include "genericAsyncTask.h"
#include "mouseWatcher.h"
#include "textNode.h"
#include "nodePath.h"
class WindowFramework;


class World{
public:
	World();
	float preTime;
	float dt;
	int tickCount;
	
	void init		();
	
	void tick		();
	void draw		();
	void get_keys	(MouseWatcher* mw, map <std::string, pair<ButtonHandle, bool> >&keybinds);
	void look		(WindowFramework *win, float mouseSens);
	void move 		(map <std::string, pair<ButtonHandle, bool> > &keybinds);
	void apply_grav	();
	
	Sounds gameSounds;
	
	void menu();
	void menuOption();
	void menuStart();
	void menuDeath();
	void menuLoad();
	float deathFogIncrease;

	std::vector<std::string> deathMessageList;
	
	int menuStatus;
	enum ms  {ms_game, ms_pause, ms_option, ms_start, ms_optionfromstart, ms_deathfog, ms_dead, ms_load};

//	static AsyncTask::DoneStatus	addToTime		(GenericAsyncTask* task, void* data);
//	static AsyncTask::DoneStatus	CamLookTask		(GenericAsyncTask* task, void* data);
//	static AsyncTask::DoneStatus	SpinCameraTask	(GenericAsyncTask* task, void* data);
//	static AsyncTask::DoneStatus	Hello			(GenericAsyncTask* task, void* data);
//	static AsyncTask::DoneStatus	CamMoveTask		(GenericAsyncTask* task, void* data);
//	static AsyncTask::DoneStatus	phys			(GenericAsyncTask* task, void* data);
private:
	bool game_running;
	
};

#endif
