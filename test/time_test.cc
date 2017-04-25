#include <iostream>
#include <cmath>

#include "pandaFramework.h"
#include "windowFramework.h"
#include "nodePath.h"
#include "pandaSystem.h"
#include "genericAsyncTask.h"
#include "asyncTaskManager.h"
#include "clockObject.h"

AsyncTaskManager* taskMgr = AsyncTaskManager::get_global_ptr(); 
//ClockObject* globalClock = ClockObject::get_global_clock();

//~ AsyncTask::DoneStatus function(GenericAsyncTask* task, void* data);
AsyncTask::DoneStatus func(GenericAsyncTask* task, void* data);

int main(int argc, char *argv[]) {
	//globalClock -> reset();
	//globalClock -> set_mode(ClockObject::M_non_real_time);
	globalClock -> set_frame_rate(60);
	PandaFramework framework;
	
	framework.open_framework(argc, argv);
	framework.set_window_title("GAME");
	
	WindowFramework *window = framework.open_window();	
	
	// define_key("event_name", "description", function, data);
	
	// taskMgr -> add(new GenericAsyncTask("Description", &function, (void*) data));
	taskMgr -> add(new GenericAsyncTask("Description", &func, (void*) Thread::get_current_thread()));
	
	framework.main_loop();
	framework.close_framework();
	return 0;
}
AsyncTask::DoneStatus func(GenericAsyncTask* task, void* data){
	//cout << ClockObject::get_global_clock() -> get_frame_time() << endl;
	cout << ClockObject::get_global_clock() -> get_dt() << endl;
	return AsyncTask::DS_cont;
}
