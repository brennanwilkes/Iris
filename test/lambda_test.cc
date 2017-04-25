#include <iostream>

#include "pandaFramework.h"
#include "pandaSystem.h"
#include "genericAsyncTask.h"
#include "asyncTaskManager.h"
//~ #include "clockObject.h"
AsyncTaskManager* taskMgr = AsyncTaskManager::get_global_ptr(); 

//~ AsyncTask::DoneStatus function(GenericAsyncTask* task, void* data);

int main(int argc, char *argv[]) {
	PandaFramework framework;
	
	framework.open_framework(argc, argv);
	framework.set_window_title("GAME");
	
	WindowFramework *window = framework.open_window();	
	window -> enable_keyboard();
	
	// define_key("event_name", "description", function, data);
	framework.define_key("q", "nope", [] (const Event* e, void* v) {cout << "Hello!" << endl; return;}, NULL);
	// taskMgr -> add(new GenericAsyncTask("Description", &function, (void*) data));
	// Cannot take reference of temporary function (ie. lambda)
	// taskMgr -> add(new GenericAsyncTask("Description", &([] (GenericAsyncTask* task, void* data) {cout << "quack" << endl; return AsyncTask::DS_cont;}), NULL));
	
	framework.main_loop();
	framework.close_framework();
	return 0;
}
AsyncTask::DoneStatus func(GenericAsyncTask* task, void* data){
	//cout << ClockObject::get_global_clock() -> get_frame_time() << endl;
	cout << ClockObject::get_global_clock() -> get_dt() << endl;
	return AsyncTask::DS_cont;
}

