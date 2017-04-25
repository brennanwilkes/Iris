#include <iostream>
#include <cmath>
#include <vector>
#include <map>

#include "pandaFramework.h"
#include "pandaSystem.h"
#include "mouseWatcher.h"
#include "keyboardButton.h"
#include "mouseButton.h"
#include "nodePath.h"
#include "clockObject.h"

#include "collisionHandlerQueue.h"
#include "collisionTraverser.h"
#include "collisionRay.h"

#include "filename.h"
#include "executionEnvironment.h"

void select_model(const Event* eventPtr, void* dataPtr);
void toggle_mouse_mode(const Event* eventPtr = NULL, void* dataPtr = NULL);

void load_new_model(const Event* eventPtr, void* dataPtr);
void move_model(const Event* eventPtr, void* dataPtr);
void rot_model(const Event* eventPtr, void* dataPtr);
void mwheel_up(const Event* eventPtr, void* dataPtr);
void mwheel_down(const Event* eventPtr, void* dataPtr);

void test_func(const Event* eventPtr, void* dataPtr);

void setup(WindowFramework* win);

void move_cam();
void rot_cam_locked(GraphicsWindow* gw);
void rot_cam_unlocked(GraphicsWindow* gw);

void move_sel();

// Current directory
Filename mydir;

// Global variables
NodePath camera;
PT(WindowFramework) window;

NodePath selected;
bool moving_selected;

vector<NodePath> models;
map<string, NodePath> nodes;

// Picker ray to select NodePath
CollisionTraverser qtrav_pick;
PT(CollisionHandlerQueue) qcoll_pick;
PT(CollisionRay) qray_pick;

// Rotating Camera in unlocked mouse mode
float prevMx(0), prevMy(0);
bool mouse1_down(0);

// Global Clock object
PT(ClockObject) globalClock = ClockObject::get_global_clock();

// MouseWatcher object for keyboard/mouse input
PT(MouseWatcher) mW;

// Previous time; Delta time between frames
float preTime(0);
float dt(0);

// Mouse mode: 0 - Unlocked, 1 - Locked
bool mouse_mode(0);

float mv_dist(5);

int main(int argc, char* argv[])
{
	PandaFramework fw;
	fw.open_framework(argc, argv);
	fw.set_window_title("Level Editor");
	
	window = fw.open_window();
	window -> enable_keyboard();
	mW = (MouseWatcher*)window -> get_mouse().node();
	
	camera = window -> get_camera_group();
	
	mydir = ((Filename)ExecutionEnvironment::get_binary_name()).get_dirname() + "/../";
	
	setup(window);

	PT(MouseWatcher) mw = (MouseWatcher*)window -> get_mouse().node();

	// Set up picker ray
	NodePath pick_ND;
	PT(CollisionNode) c_Node;
	
	c_Node = new CollisionNode("Mouse ray");
	c_Node -> set_from_collide_mask(GeomNode::get_default_collide_mask());
	qray_pick = new CollisionRay();
	c_Node->add_solid(qray_pick);
	pick_ND = camera.attach_new_node(c_Node);
	qcoll_pick = new CollisionHandlerQueue;
	qtrav_pick.add_collider(pick_ND, qcoll_pick);

	window -> get_panda_framework() -> define_key("mouse1", "Select Model", select_model, NULL); // RMB shifts mouse mode
	window -> get_panda_framework() -> define_key("mouse3", "Change Mouse Mode", toggle_mouse_mode, window); // RMB shifts mouse mode
	window -> get_panda_framework() -> define_key("l", "Load Model", load_new_model, window);
	window -> get_panda_framework() -> define_key("m", "Move Model", move_model, NULL);
	window -> get_panda_framework() -> define_key("wheel_up", "Move Model", mwheel_up, NULL);
	window -> get_panda_framework() -> define_key("wheel_down", "Move Model", mwheel_down, NULL);
	window -> get_panda_framework() -> define_key("t", "Test Function", test_func, NULL);
	
	Thread *c_thr = Thread::get_current_thread();
	while (fw.do_frame(c_thr))
	{
		dt = globalClock -> get_real_time() - preTime;
		preTime = globalClock -> get_real_time();
		
		if (mouse_mode) // Locked mouse mode
		{
			rot_cam_locked(window -> get_graphics_window());
			if (moving_selected) move_sel();
		}
		else
		{
			rot_cam_unlocked(window -> get_graphics_window());
		}
		
		move_cam();
	} 
	fw.close_framework();
	return 0;
}

void select_model(const Event* eventPtr, void* dataPtr){
	qray_pick -> set_from_lens(window -> get_camera(0), mW -> get_mouse().get_x(), mW -> get_mouse().get_y());
	
	qtrav_pick.traverse(window -> get_render());
	if (qcoll_pick -> get_num_entries() > 0)
	{
		NodePath new_sel = window -> get_render().find_path_to(qcoll_pick -> get_entry(0) -> get_into_node());
		if (selected == new_sel)
		{
			if (!moving_selected)
			{
				moving_selected = true;
				cout << "Now moving selected object, " << selected.get_name() << endl;
			}
			else
			{
				moving_selected = false;
				cout << "Done moving object, " << selected.get_name() << endl;
			}
		}
		else
		{
			selected = new_sel;
			moving_selected = false;
			cout << "Selected new object: " << selected.get_name() << endl;
		}
		//~ 
		//selected = &(qcoll_pick -> get_entry(0) -> get_into_node() -> get_parent(2) -> find_net_tag("sel"));
		//cout << "Selected model: " << qcoll_pick -> get_entry(0) -> get_into_node() -> get_tag("sel") << endl;
	}
	else
	{
		if (moving_selected) 
		{
			moving_selected = false;
			cout << "Stopped moving selected object" << endl;
		}
	}
}

void toggle_mouse_mode(const Event* eventPtr, void* dataPtr){
	mouse_mode = !mouse_mode;
	WindowProperties props = window -> get_graphics_window() -> get_properties();
	props.set_cursor_hidden(mouse_mode);
	props.set_mouse_mode(mouse_mode?WindowProperties::M_confined:WindowProperties::M_absolute);
	window -> get_graphics_window() -> request_properties(props);
}

void load_new_model(const Event* eventPtr, void* dataPtr){
	// Prompts user for model to load into the scene graph
	PT(WindowFramework) window = (WindowFramework*)dataPtr;
	string parent;
	string filepath;
	cout << "Attach to (Root / Static / Entity / Item / ...) :";
	cin >> parent;
	cout << "Model path: ";
	cin >> filepath;
	models.push_back(window -> load_model(nodes[parent], mydir + filepath));
	models.back().set_pos(camera, 0, 10, 0);
	selected = models.back();
}

void move_model(const Event* eventPtr, void* dataPtr){ if (selected) {
	// Prompts user for new positional values for selected object
	float x(0), y(0), z(0);
	cout << "Moving selected object: " << selected.get_name() << " to: " << endl;
	cout << "New x: " << endl;
	cin >> x;
	cout << "New y: " << endl;
	cin >> y;
	cout << "New z: " << endl;
	cin >> z;
	
	selected.set_x(x);
	selected.set_y(y);
	selected.set_z(z);
	
	cout << "Moved " << selected.get_name() << " to " << x << ", " << y << ", " << z << endl;
} else {cout << "Nothing selected!" << endl;}}

void rot_model(const Event* eventPtr, void* dataPtr){ if (selected) {
	// Prompts user for new rotational values for selected object
	float h(0), p(0), r(0);
	cout << "New h: " << endl;
	cin >> h;
	cout << "New p: " << endl;
	cin >> p;
	cout << "New r: " << endl;
	cin >> r;
	
	cout << "Rotated Object!" << endl;
	
} else {cout << "Nothing selected!" << endl;}}

void setup(WindowFramework* win){
	// Creates the scene graph root nodes.
	nodes["Root"] = win -> get_render().attach_new_node("All game models");
	nodes["Static"] = nodes["Root"].attach_new_node("All Static (Terrain)");
	nodes["Entity"] = nodes["Root"].attach_new_node("All Entities");
	nodes["Item"] = nodes["Entity"].attach_new_node("All Items");
}

void move_cam(){
	float rot = camera.get_h();
	float dx(0), dy(0), dz(0);
	if (mW -> is_button_down(KeyboardButton::ascii_key('w'))) { dx += -4.0 * sin(rot * (3.1416 / 180));		dy += 4.0 * cos(rot * (3.1416 / 180)); }
	if (mW -> is_button_down(KeyboardButton::ascii_key('s'))) { dx += 4.0 * sin(rot * (3.1416 / 180));		dy += -4.0 * cos(rot * (3.1416 / 180)); }
	if (mW -> is_button_down(KeyboardButton::ascii_key('a'))) { dx += 4.0 * sin((rot - 90) * (3.1416 / 180));	dy += -4.0 * cos((rot - 90) * (3.1416 / 180)); }
	if (mW -> is_button_down(KeyboardButton::ascii_key('d'))) { dx += 4.0 * sin((rot + 90) * (3.1416 / 180));	dy += -4.0 * cos((rot + 90) * (3.1416 / 180)); }
	if (mW -> is_button_down(KeyboardButton::space())) { dz += 2; }
	if (mW -> is_button_down(KeyboardButton::lshift())) { dz -= 2; }
	if (dx) camera.set_x(camera.get_x() + dx * dt);
	if (dy) camera.set_y(camera.get_y() + dy * dt);
	if (dz) camera.set_z(camera.get_z() + dz * dt);
}

void rot_cam_locked(GraphicsWindow* gw){ if (gw) {
	int dx = (gw -> get_properties().get_x_size() / 2) - gw -> get_pointer(0).get_x();
	int dy = (gw -> get_properties().get_y_size() / 2) - gw -> get_pointer(0).get_y();
	camera.set_h(camera.get_h() + dx * dt);
	camera.set_p(camera.get_p() + dy * dt);
	gw -> move_pointer(0, gw -> get_properties().get_x_size() / 2, gw -> get_properties().get_y_size() / 2);
} else { cout << "ERROR! EMPTY GRAPHICS WINDOW!" << endl; } }

void rot_cam_unlocked(GraphicsWindow* gw){ if (gw) { if (mW -> is_button_down(MouseButton::one())) {
	if (!mouse1_down) {	prevMx = gw -> get_pointer(0).get_x(); prevMy = gw -> get_pointer(0).get_y(); }
	mouse1_down = 1;
	int dx = prevMx - gw -> get_pointer(0).get_x();
	int dy = prevMy - gw -> get_pointer(0).get_y();
	camera.set_h(camera.get_h() - dx * dt * 5);
	camera.set_p(camera.get_p() - dy * dt * 5);
	prevMx = gw -> get_pointer(0).get_x();
	prevMy = gw -> get_pointer(0).get_y();
} else {mouse1_down = 0;}} else { cout << "ERROR! EMPTY GRAPHICS WINDOW!" << endl; } }


void test_func(const Event* eventPtr, void* dataPtr){
	selected.ls();
}

void move_sel(){
	selected.set_pos(camera, 0, mv_dist, 0);
	selected.set_hpr(camera, 0, 0, 0);
}

void mwheel_up(const Event* eventPtr, void* dataPtr){
	if (moving_selected) mv_dist += 0.5;
	else
	{
		selected.set_h(selected, 5);
	}
}

void mwheel_down(const Event* eventPtr, void* dataPtr){
	if (moving_selected) mv_dist -= 0.5;
	else
	{
		selected.set_h(selected, -5);
	}
}

