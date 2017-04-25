#include "pandaFramework.h"
#include "pandaSystem.h"

#include "mouseButton.h"

//#include "PGButton.h"
#include "texturePool.h"

AsyncTaskManager* taskMgr = AsyncTaskManager::get_global_ptr(); 
ClockObject* globalClock = ClockObject::get_global_clock();

// Tasks to run every frame
AsyncTask::DoneStatus moveBut(GenericAsyncTask* task, void* data);

// Events
static void but_cb(const Event *ev, void *data);

int main(int argc, char* argv[]){
	PandaFramework framework;
	framework.open_framework(argc, argv);
	framework.set_window_title("Gui Test");
	WindowFramework *window = framework.open_window();

	taskMgr -> add(new GenericAsyncTask("Move Button", &moveBut, NULL));
	
	
	PGButton* button;
	button = new PGButton("ByMutton");
	button -> setup("Button", 0.1);
	//Texture* ButtonReady = TexturePool::load_texture("button.png");
	//Texture* ButtonRollover = TexturePool::load_texture("button_active.png");
	//Texture* ButtonPressed = TexturePool::load_texture("button_pressed.png");
	//Texture* ButtonInactive = TexturePool::load_texture("button_inactive.png");
	
	PGFrameStyle style = button->get_frame_style(0); // frame_style(0): ready state
	//style.set_texture(ButtonReady);    button->set_frame_style(0,style);
	//style.set_texture(ButtonRollover); button->set_frame_style(1,style);
	//style.set_texture(ButtonPressed);  button->set_frame_style(2,style);
	//style.set_texture(ButtonInactive); button->set_frame_style(3,style);
	
	NodePath defbutNP = window->get_aspect_2d().attach_new_node(button);
	defbutNP.set_scale(1);
	
	framework.define_key(button->get_click_event(MouseButton::one()), "push", &but_cb, button);

	framework.main_loop();
	framework.close_framework();
	return 0;
}

AsyncTask::DoneStatus moveBut(GenericAsyncTask* task, void* data){
	return AsyncTask::DS_cont;
}

static void but_cb(const Event *ev, void *data){
	cout << "AHHHHHHH" << endl;
}
