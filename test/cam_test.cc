#include <map>

#include "pandaFramework.h"
#include "pandaSystem.h"
 
#include "genericAsyncTask.h"
#include "asyncTaskManager.h"
 
#include "cIntervalManager.h"
#include "cLerpNodePathInterval.h"
#include "cMetaInterval.h"
#include "mouseWatcher.h"

// Global stuff
AsyncTaskManager* taskMgr = AsyncTaskManager::get_global_ptr(); 
ClockObject* globalClock = ClockObject::get_global_clock();
NodePath camera;


//define main character class here
// ourClass dude = 



// Event Handlers
void sys_exit(const Event* eventPtr, void* dataPtr);

// Tasks
AsyncTask::DoneStatus CamLookTask(GenericAsyncTask* task, void* data);
AsyncTask::DoneStatus CamMoveTask(GenericAsyncTask* task, void* data);

 
int main(int argc, char *argv[]) {
	// Open a new window framework and set the title
	PandaFramework framework;
	framework.open_framework(argc, argv);
	framework.set_window_title("My Panda3D Window");
 
	// Open the window
	WindowFramework *window = framework.open_window();
	
	window -> enable_keyboard();
	
	PT(MouseWatcher) mouseWatcher = (MouseWatcher*)window -> get_mouse().node();
	
	camera = window->get_camera_group(); // Get the camera and store it
	camera.set_pos(0, 0, 3);
	
	// Set up relative mouse mode. This mode keeps the mouse in the centre (WHAT WE WANT),
	// and returns relative movements
	WindowProperties props = window->get_graphics_window()->get_properties();
	props.set_cursor_hidden (true);
	props.set_mouse_mode (WindowProperties::M_confined);
	window->get_graphics_window()->request_properties (props);
	
 
	// Load the environment model
	NodePath scene = window->load_model(framework.get_models(),
		"models/environment");
	scene.reparent_to(window->get_render());
	scene.set_scale(0.25 , 0.25, 0.25);
	scene.set_pos(-8, 42, 0);
 
	// Load our panda
	NodePath pandaActor = window->load_model(framework.get_models(),
		"models/panda-model");
	pandaActor.set_scale(0.005);
	pandaActor.reparent_to(window->get_render());
 
	// Load the walk animation
	window->load_model(pandaActor, "models/panda-walk4");
	window->loop_animations(0);
 
	// Create the lerp intervals needed to walk back and forth
	PT(CLerpNodePathInterval) pandaPosInterval1, pandaPosInterval2, pandaHprInterval1, pandaHprInterval2;
	pandaPosInterval1 = new CLerpNodePathInterval("pandaPosInterval1", 13.0, CLerpInterval::BT_no_blend, true, false, pandaActor, NodePath());
	pandaPosInterval1->set_start_pos(LPoint3f(0, 10, 0));
	pandaPosInterval1->set_end_pos(LPoint3f(0, -10, 0));
 
	pandaPosInterval2 = new CLerpNodePathInterval("pandaPosInterval2", 13.0, CLerpInterval::BT_no_blend, true, false, pandaActor, NodePath());
	pandaPosInterval2->set_start_pos(LPoint3f(0, -10, 0));
	pandaPosInterval2->set_end_pos(LPoint3f(0, 10, 0));
 
	pandaHprInterval1 = new CLerpNodePathInterval("pandaHprInterval1", 3.0, CLerpInterval::BT_no_blend, true, false, pandaActor, NodePath());
	pandaHprInterval1->set_start_hpr(LPoint3f(0, 0, 0));
	pandaHprInterval1->set_end_hpr(LPoint3f(180, 0, 0));
 
	pandaHprInterval2 = new CLerpNodePathInterval("pandaHprInterval2", 3.0, CLerpInterval::BT_no_blend, true, false, pandaActor, NodePath());
	pandaHprInterval2->set_start_hpr(LPoint3f(180, 0, 0));
	pandaHprInterval2->set_end_hpr(LPoint3f(0, 0, 0));
 
	// Create and play the sequence that coordinates the intervals
	PT(CMetaInterval) pandaPace;
	pandaPace = new CMetaInterval("pandaPace");
	pandaPace->add_c_interval(pandaPosInterval1, 0, CMetaInterval::RS_previous_end);
	pandaPace->add_c_interval(pandaHprInterval1, 0, CMetaInterval::RS_previous_end);
	pandaPace->add_c_interval(pandaPosInterval2, 0, CMetaInterval::RS_previous_end);
	pandaPace->add_c_interval(pandaHprInterval2, 0, CMetaInterval::RS_previous_end);
	pandaPace->loop();
 
	// Add our task.
	// taskMgr->add(new GenericAsyncTask("Spins the camera", &SpinCameraTask, (void*) NULL));
	taskMgr -> add(new GenericAsyncTask("Camera Look", &CamLookTask, (void*) window));
	taskMgr -> add(new GenericAsyncTask("Camera Move", &CamMoveTask, (void*) mouseWatcher));
	
	// Adding Event handlers
	window -> get_panda_framework() -> define_key("escape", "Quit the program", sys_exit, NULL);
	
	
	
	// This is a simpler way to do stuff every frame,
	// if you're too lazy to create a ypedef ‘pair_type’ locally defined but not used [-Wunused-local-typedefs]
	Thread *current_thread = Thread::get_current_thread();
	while(framework.do_frame(current_thread)) {
		// Step the interval manager
		CIntervalManager::get_global_ptr()->step();
	}
 
	framework.close_framework();
	return (0);
}

// Event Handlers
void sys_exit(const Event* eventPtr, void* dataPtr){
	exit(0);
}
// Tasks
AsyncTask::DoneStatus CamLookTask(GenericAsyncTask* task, void* data){
	// This function should be passed window, which is type casted
	static GraphicsWindow* gw = static_cast<WindowFramework*>(data) -> get_graphics_window();
	if (gw)
	{
		int dx = (gw -> get_properties().get_x_size() / 2) - gw -> get_pointer(0).get_x();
		int dy = (gw -> get_properties().get_y_size() / 2) - gw -> get_pointer(0).get_y();
		//cout << "dx: " << dx << endl;
		//cout << "dy: " << dy << endl;
		camera.set_hpr(camera.get_hpr().get_x() + dx * 0.03, camera.get_hpr().get_y() + dy * 0.03, 0);
	}
	gw -> move_pointer(0, gw -> get_properties().get_x_size() / 2, gw -> get_properties().get_y_size() / 2);
	return AsyncTask::DS_cont;
}

AsyncTask::DoneStatus CamMoveTask(GenericAsyncTask* task, void* data){
	static MouseWatcher* mW = static_cast<MouseWatcher*>(data);
	float rot = camera.get_hpr().get_x();
	float dx(0), dy(0);
	if (mW -> is_button_down(KeyboardButton::ascii_key('w'))) 
	{
		dx += -0.25 * sin(rot * (3.1416 / 180));
		dy += 0.25 * cos(rot * (3.1416 / 180));
	}
	if (mW -> is_button_down(KeyboardButton::ascii_key('s')))
	{
		dx += 0.25 * sin(rot * (3.1416 / 180));
		dy += -0.25 * cos(rot * (3.1416 / 180));
	}
	if (mW -> is_button_down(KeyboardButton::ascii_key('a')))
	{
		dx += 0.25 * sin((rot - 90) * (3.1416 / 180));
		dy += -0.25 * cos((rot - 90) * (3.1416 / 180));
	}
	if (mW -> is_button_down(KeyboardButton::ascii_key('d')))
	{
		dx += 0.25 * sin((rot + 90) * (3.1416 / 180));
		dy += -0.25 * cos((rot + 90) * (3.1416 / 180));
	}
	camera.set_pos(camera.get_pos().get_x() + dx, camera.get_pos().get_y() + dy, 3);
	
	return AsyncTask::DS_cont;
}
	
