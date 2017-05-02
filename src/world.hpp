#ifndef WORLD_H
#define WORLD_H

#include <map>
#include <vector>
#include "sounds.hpp"
#include "asyncTaskManager.h"
#include "genericAsyncTask.h"
#include "mouseWatcher.h"
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
	void look		(WindowFramework *win);
	void move 		(map <std::string, pair<ButtonHandle, bool> > &keybinds);
	void apply_grav	();
	
	Sounds gameSounds;
	
	//bool is_running() {return menuStatus;}
	void menu();
	void menuOption();
	void menuStart();
	//bool pause_menu;
	//bool option_menu;
	int menuStatus;
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
