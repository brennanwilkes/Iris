#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>

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

#include "../src/level.hpp"

void select_model(const Event* eventPtr, void* dataPtr);
void toggle_mouse_mode(const Event* eventPtr = NULL, void* dataPtr = NULL);

void load_new_model(const Event* eventPtr, void* dataPtr);
void unload_model(const Event* eventPtr, void* dataPtr);
void move_model(const Event* eventPtr, void* dataPtr);
void rot_model(const Event* eventPtr, void* dataPtr);
void edit_model(const Event* eventPtr, void* dataPtr);
void mwheel_up(const Event* eventPtr, void* dataPtr);
void mwheel_down(const Event* eventPtr, void* dataPtr);
void save_level(const Event* eventPtr, void* dataPtr);
void load_level(const Event* eventPtr, void* dataPtr);
void append_level(const Event* eventPtr, void* dataPtr);

void test_func(const Event* eventPtr, void* dataPtr);

void setup(WindowFramework* win);

void move_cam();
void rot_cam_locked(GraphicsWindow* gw);
void rot_cam_unlocked(GraphicsWindow* gw);

void move_sel_locked();
void move_sel_unlocked();

// Current directory
Filename mydir;

// Global variables
NodePath camera;
PandaFramework fw;
PT(WindowFramework) window;

// Selected model 
NodePath selected;
NodePath empty;

map<string, NodePath> nodes;

// Picker ray to select NodePath
CollisionTraverser qtrav_pick;
PT(CollisionHandlerQueue) qcoll_pick;
PT(CollisionRay) qray_pick;

// Rotating Camera in unlocked mouse mode
float prevMx(0), prevMy(0);
bool mouse2_down(0);

// Global Clock object
PT(ClockObject) globalClock = ClockObject::get_global_clock();

// MouseWatcher object for keyboard/mouse input
PT(MouseWatcher) mW;

// Timers
float preTime(0);
float dt(0);

// Mouse mode: 0 - Unlocked, 1 - Locked
bool mouse_mode(0);

float mv_dist(5);

// Current level
Level level;

// States
enum state {base, sel, mov_sel, edit_sel};
state cur_state = base;

// Thread (our one and only)
Thread *c_thr = Thread::get_current_thread();

int main(int argc, char* argv[])
{
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
	// End pickup ray setup
	
	window -> get_panda_framework() -> define_key("mouse1", "Select Model", select_model, NULL); // RMB shifts mouse mode
	window -> get_panda_framework() -> define_key("mouse3", "Change Mouse Mode", toggle_mouse_mode, window); // RMB shifts mouse mode
	window -> get_panda_framework() -> define_key("l", "Load Model", load_new_model, window);
	window -> get_panda_framework() -> define_key("u", "Unload Selected Model", unload_model, NULL);
	window -> get_panda_framework() -> define_key("m", "Move Model", move_model, NULL);
	window -> get_panda_framework() -> define_key("wheel_up", "Rotate Model", mwheel_up, NULL);
	window -> get_panda_framework() -> define_key("wheel_down", "Rotate Model", mwheel_down, NULL);
	window -> get_panda_framework() -> define_key("control-s", "Save Level to file", save_level, NULL);
	window -> get_panda_framework() -> define_key("control-l", "Load Level from file", load_level, NULL);
	window -> get_panda_framework() -> define_key("control-a", "Append Level from file", append_level, NULL);
	window -> get_panda_framework() -> define_key("e", "Edit model attributes", edit_model, NULL);
	window -> get_panda_framework() -> define_key("t", "Test Function", test_func, NULL);
	
	while (fw.do_frame(c_thr))
	{
		dt = globalClock -> get_real_time() - preTime;
		preTime = globalClock -> get_real_time();
		
		if (mouse_mode) // Locked mouse mode
		{
			rot_cam_locked(window -> get_graphics_window());
			if (cur_state == mov_sel) move_sel_locked();
		}
		else
		{
			rot_cam_unlocked(window -> get_graphics_window());
			if (cur_state == mov_sel) move_sel_unlocked();
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
		qcoll_pick -> sort_entries();
		NodePath new_sel = level.models[qcoll_pick -> get_entry(0) -> get_into_node_path().get_net_tag("id")];
		if (cur_state == mov_sel)
		{
			cur_state = sel;
			selected.set_collide_mask(BitMask32::all_on());
			cout << "Done moving " << selected.get_name() << endl;
		}
		else if (selected == new_sel)
		{
			if (cur_state != mov_sel)
			{
				cur_state = mov_sel;
				selected.set_collide_mask(BitMask32::all_off());
				cout << "Now moving selected object, " << selected.get_name() << endl;
			}
		}
		else
		{
			if (!selected.is_empty()) selected.set_collide_mask(BitMask32::all_on());
			selected = new_sel;
			cur_state = sel;
			cout << "Selected new object: " << selected.get_name() << endl;
		}
		//~ 
		//selected = &(qcoll_pick -> get_entry(0) -> get_into_node() -> get_parent(2) -> find_net_tag("sel"));
		//cout << "Selected model: " << qcoll_pick -> get_entry(0) -> get_into_node() -> get_tag("sel") << endl;
	}
	else
	{
		if (!selected.is_empty()) selected.set_collide_mask(BitMask32::all_on());
		cout << "Deselected all objects." << endl;
		cur_state = base;
		selected = empty;
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
	string parent;
	string filepath;
	
	// Get parent
	cout << "Attach to (Root / Static / Entity / Item / ...) :";
	cin >> parent;
	transform(parent.begin(), parent.end(), parent.begin(), ::tolower);
	
	// Check if parent exists
	if (nodes.find(parent) == nodes.end())
	{
		cout << "ERROR: Invalid parent: " << parent << endl;
		return;
	}
	
	// Get path to model
	cout << "Model path: ";
	cin >> filepath;
	filepath = mydir + filepath;
	
	// Check if file exists
	if (!level.file_exists(filepath))
	{
		cout << "ERROR: File does not exist: " << filepath << endl;
		return;
	}
	
	// Load the model
	PT(WindowFramework) window = (WindowFramework*)dataPtr;
	string id;
	id = level.add_model(window -> load_model(nodes[parent], filepath));
	selected = level.models[id];
	cur_state = sel;
	cout << "Loaded model: [" << id << "] " << selected.get_name() << endl;
}

void unload_model(const Event* eventPtr, void* dataPtr){
	if (cur_state == sel)
	{
		string id = selected.get_tag("id");
		cout << "Removed selected node, " << selected.get_name() << endl;
		level.models[id].remove_node();
		level.models.erase(id);
		selected.remove_node();
		cur_state = base;
	}
}

void move_model(const Event* eventPtr, void* dataPtr){
	// Prompts user for new positional values for selected object
	if (selected.is_empty())
	{
		cout << "Nothing selected!" << endl;
		return;
	}
	
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
}

void rot_model(const Event* eventPtr, void* dataPtr){
	// Prompts user for new rotational values for selected object
	if (selected.is_empty())
	{
		cout << "Nothing selected!" << endl;
		return;
	}
	
	float h(0), p(0), r(0);
	cout << "New h: " << endl;
	cin >> h;
	cout << "New p: " << endl;
	cin >> p;
	cout << "New r: " << endl;
	cin >> r;
	
	cout << "Rotated Object!" << endl;
}

void edit_model(const Event* eventPtr, void* dataPtr){
	if (selected.is_empty()) 
	{
		cout << "Nothing selected!" << endl;
		return;
	}
	
	cur_state = edit_sel;
	
	string datum;
	
	while (true)
	{
		cout << "Class type: ";
		cin >> datum;
		if (Level::used_dat.find(datum) != Level::used_dat.end())
		{
			selected.set_tag("class", datum);
			break;
		}
		cout << "Invalid class type. Valid class types are: ";
		for (auto &x:Level::used_dat)
		{
			cout << x.first << ", ";
		}
		cout << endl;
	}
	
	vector<string> data = Level::used_dat[datum];
	for (const auto &dat:data)
	{
		cout << dat << ": ";
		cin >> datum;
		selected.set_tag(dat, datum);
	}
	cout << "Done editing!" << endl;
	cur_state = sel;
}

void setup(WindowFramework* win){
	// Creates the scene graph root nodes.
	nodes["root"] = win -> get_render().attach_new_node("All game models");
	nodes["static"] = nodes["root"].attach_new_node("All Static (Terrain)");
	nodes["entity"] = nodes["root"].attach_new_node("All Entities");
	nodes["item"] = nodes["entity"].attach_new_node("All Items");
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
	camera.set_h(camera.get_h() + dx * dt * 3);
	camera.set_p(camera.get_p() + dy * dt * 3);
	gw -> move_pointer(0, gw -> get_properties().get_x_size() / 2, gw -> get_properties().get_y_size() / 2);
} else { cout << "ERROR! EMPTY GRAPHICS WINDOW!" << endl; } }

void rot_cam_unlocked(GraphicsWindow* gw){ if (gw) { if (mW -> is_button_down(MouseButton::two())) {
	if (!mouse2_down) {	prevMx = gw -> get_pointer(0).get_x(); prevMy = gw -> get_pointer(0).get_y(); }
	mouse2_down = 1;
	int dx = prevMx - gw -> get_pointer(0).get_x();
	int dy = prevMy - gw -> get_pointer(0).get_y();
	camera.set_h(camera.get_h() - dx * dt * 5);
	camera.set_p(camera.get_p() - dy * dt * 5);
	prevMx = gw -> get_pointer(0).get_x();
	prevMy = gw -> get_pointer(0).get_y();
} else {mouse2_down = 0;}} else { cout << "ERROR! EMPTY GRAPHICS WINDOW!" << endl; } }

void test_func(const Event* eventPtr, void* dataPtr){
	selected.ls();
}

void move_sel_locked(){
	selected.set_pos(camera, 0, mv_dist, 0);
	selected.set_hpr(camera, 0, 0, 0);
	selected.set_p(0);
}

void move_sel_unlocked(){
	if (mW -> has_mouse())
	{
	qray_pick -> set_from_lens(window -> get_camera(0), mW -> get_mouse().get_x(), mW -> get_mouse().get_y());
	qtrav_pick.traverse(window -> get_render());
	if (qcoll_pick -> get_num_entries() > 0)
	{
		qcoll_pick -> sort_entries();
		selected.set_pos(qcoll_pick -> get_entry(0) -> get_surface_point(window -> get_render()));
		
		//~ for (int i(0); i < qcoll_pick -> get_num_entries(); ++i)
			//~ cout << i << " : " << level.models[qcoll_pick -> get_entry(i) -> get_into_node_path().get_net_tag("id")].get_name() << endl;
	}
	}
}

void mwheel_up(const Event* eventPtr, void* dataPtr){
	if (cur_state == mov_sel) mv_dist += 0.5;
	else
	{
		selected.set_h(selected, 5);
	}
}

void mwheel_down(const Event* eventPtr, void* dataPtr){
	if (cur_state == mov_sel) mv_dist -= 0.5;
	else
	{
		selected.set_h(selected, -5);
	}
}

void save_level(const Event* eventPtr, void* dataPtr){
	string filename;
	cout << "Save to: ";
	cin >> filename;
	level.save(filename);
	cout << "Saved level to " << filename << endl;
}

void load_level(const Event* eventPtr, void* dataPtr){
	string filename;
	level.clear();
	cout << "Load level from file: ";
	cin >> filename;
	level.load(filename);
	cout << "Loaded level from " << filename << endl;
}

void append_level(const Event* eventPtr, void* dataPtr){
	string filename;
	cout << "Append level from file: ";
	cin >> filename;
	level.load(filename);
	cout << "Appended level from " << filename << endl;
}
