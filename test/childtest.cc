#include <iostream>
#include <cmath>

#include "pandaFramework.h"
#include "pandaSystem.h"
#include "collisionRay.h"
#include "collisionSphere.h"
#include "collisionSegment.h"
#include "collisionNode.h"
#include "collisionHandlerQueue.h"
#include "collisionTraverser.h"
#include "mouseWatcher.h"
#include "keyboardButton.h"

#include <auto_bind.h>
#include <animControlCollection.h>
#include "omniBoundingVolume.h"

CollisionTraverser qtrav_pick;
PT(CollisionHandlerQueue) qcoll_pick;
PT(CollisionRay) qray_pick;

PT(MouseWatcher) mW;
PT(WindowFramework) window;
NodePath camera;
NodePath Arms;

void select_model(const Event* eventPtr, void* dataPtr);
void test(const Event* eventPtr, void* dataPtr);

int main(int argc, char* argv[]){
	PandaFramework fw;
	fw.open_framework(argc, argv);
	fw.set_window_title("Item Looking");
	
	window = fw.open_window();
	window -> enable_keyboard();
	
	PT(MouseWatcher) mw = (MouseWatcher*)window -> get_mouse().node();
	mW = mw;
	
	NodePath cam = window -> get_camera_group();
	cam.set_pos(-1, 0, 0);
	camera = cam;

	Arms = window -> load_model(window -> get_render(), "../Assets/target.egg");
	Arms.set_tag("test", "value!");
	cout << Arms.get_tag("test") << endl;
	Arms.set_pos(0, 50, 0);
	Arms.ls();
	
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
	
	//Arms.show_bounds();
	/*
	window -> load_model(Arms, "../Assets/Iris/FirstPersonViewModel-Idle.egg");
	
	AnimControlCollection anim_collection;
	auto_bind(Arms.node(), anim_collection, 0);
	anim_collection.play("Armature");
	*/
	float mdx, mdy, dx(0), dy(0), rot;
	GraphicsWindow *gw = window -> get_graphics_window();
	
	window -> get_panda_framework() -> define_key("mouse1", "Select Model", select_model, NULL); // RMB shifts mouse mode
	window -> get_panda_framework() -> define_key("k", "test", test, (void*)(&Arms)); // RMB shifts mouse mode

	Thread *c_thr = Thread::get_current_thread();
	while (fw.do_frame(c_thr))
	{
		
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
		//NodePath new_sel = level.models[qcoll_pick -> get_entry(0) -> get_into_node_path().get_net_tag("id")];
		cout << "Clicked on:" << endl;
		qcoll_pick -> get_entry(0) -> get_into_node() -> ls(cout, 0);
		cout << qcoll_pick -> get_entry(0) -> get_into_node() << endl;
		if (qcoll_pick -> get_entry(0) -> get_into_node() -> get_parent(0) == Arms.node()) cout << "Dank" << endl;
		else cout << "Dry" << endl;
		
	}
	else
	{
		cout << "Clicked on nothing!" << endl;
	}
}

void test(const Event* eventPtr, void* dataPtr){
	static_cast<NodePath*>(dataPtr) -> node() -> ls(cout , 0);
	cout << static_cast<NodePath*>(dataPtr) -> node() << endl;
}
