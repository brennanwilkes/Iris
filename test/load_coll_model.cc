#include "pandaFramework.h"
#include "pandaSystem.h"
#include "collisionRay.h"
#include "collisionPolygon.h"
#include "collisionBox.h"
#include "collisionNode.h"
#include "collisionSphere.h"
#include "collisionHandlerQueue.h"
#include "collisionHandlerPusher.h"
#include "collisionTraverser.h"
#include "mouseWatcher.h"
#include "keyboardButton.h"

int main(int argc, char* argv[]){
	PandaFramework fw;
	fw.open_framework(argc, argv);
	fw.set_window_title("Collision Test");
	
	PT(WindowFramework) window = fw.open_window();
	window -> enable_keyboard();
	
	PT(MouseWatcher) mw = (MouseWatcher*)window -> get_mouse().node();
	
	CollisionHandlerQueue* queue = new CollisionHandlerQueue();
	CollisionTraverser qtrav;
	CollisionNode* c_Node;
	
	CollisionHandlerPusher* push = new CollisionHandlerPusher();
	CollisionTraverser ptrav;
	
	NodePath Terrain = window -> load_model(window -> get_render(), "../Assets/Stage/Terrain_C.egg");
	Terrain.set_pos(-8, 42, 0);
	Terrain.set_scale(2.5);
	//Terrain.ls();
	//Terrain.hide();
	Terrain.find("**/+CollisionNode").node() -> set_into_collide_mask(BitMask32::bit(1));
	
	NodePath Building = window -> load_model(window -> get_render(), "../Assets/Stage/Building_C.egg");
	Building.set_pos(-8, 42, 0);
	Building.set_scale(2.5);
	Building.find("**/+CollisionNode").node() -> set_into_collide_mask(BitMask32::bit(2));
	
	NodePath Cube_dummy = window -> get_render().attach_new_node("Cube Base Node");
	Cube_dummy.ls();
	NodePath Cube = window -> load_model(Cube_dummy, "../Assets/cube/cube.egg");
	Cube_dummy.set_pos(0, 0, 10);
	Cube_dummy.set_hpr(0, 0, 0);
	//Cube.hide();
	
	//c_Node = new CollisionNode("Cube");
	//c_Node -> add_solid(new CollisionBox(LPoint3(0, 0, 0), 1, 1, 1));
	//NodePath Cube_C = Cube.attach_new_node(c_Node);
	c_Node = new CollisionNode("Cube_sphere");
	c_Node -> add_solid(new CollisionSphere(0, 0, 0, 1.0));
	c_Node -> set_from_collide_mask(BitMask32::bit(2));
	c_Node -> set_into_collide_mask(BitMask32::all_off());
	NodePath Cube_Sphere = Cube_dummy.attach_new_node(c_Node);
	
	push -> add_collider(Cube_Sphere, Cube_dummy);
	ptrav.add_collider(Cube_Sphere, push);
	
	c_Node = new CollisionNode("Cube_ray");
	c_Node -> add_solid(new CollisionRay(0, 0, 0, 0, 0, -1));
	c_Node -> set_from_collide_mask(BitMask32::bit(1));
	c_Node -> set_into_collide_mask(BitMask32::all_off());
	NodePath Cube_Ray = Cube_dummy.attach_new_node(c_Node);
	
	//Cube_C.show();
	Cube_Ray.show();
	//queue -> add_collider(Cube_Ray, Cube_dummy);
	qtrav.add_collider(Cube_Ray, queue);
	
	NodePath cam = window -> get_camera_group();
	cam.set_pos(20, 20, 20);
	cam.look_at(Cube_dummy);
	//Cube.ls();
	Thread *c_thr = Thread::get_current_thread();
	while (fw.do_frame(c_thr))
	{
		Cube.set_h((int)(Cube.get_h() + 1) % 360);
		Cube.set_p((int)(Cube.get_p() + 1) % 360);
		Cube.set_r((int)(Cube.get_r() + 1) % 360);
		//Cube_dummy.set_z(Cube_dummy.get_z() - 0.1);
		if (mw -> is_button_down(KeyboardButton::ascii_key('w')))
			Cube_dummy.set_x(Cube_dummy.get_x() - 0.5);
		if (mw -> is_button_down(KeyboardButton::ascii_key('a')))
			Cube_dummy.set_y(Cube_dummy.get_y() - 0.5);
		if (mw -> is_button_down(KeyboardButton::ascii_key('d')))
			Cube_dummy.set_y(Cube_dummy.get_y() + 0.5);
		if (mw -> is_button_down(KeyboardButton::ascii_key('s')))
			Cube_dummy.set_x(Cube_dummy.get_x() + 0.5);
		cam.look_at(Cube_dummy);
		qtrav.traverse(window -> get_render());
		ptrav.traverse(window -> get_render());
		queue -> sort_entries();
		//for (int i(0); i < queue -> get_num_entries(); ++i)
			//cout << queue -> get_entry(i) -> get_into_node() -> get_name() << ", ";
		//cout << endl;
		
		if (queue -> get_num_entries() > 0 )
		{
			//cout << queue -> get_entry(0) -> get_into_node() -> get_name() << ", ";
			//cout << queue -> get_entry(1) -> get_into_node() -> get_name() << ", ";
			Cube_dummy.set_z(queue -> get_entry(0) -> get_surface_point(window -> get_render()).get_z() + 5);
		}
		
	}
	fw.close_framework();
	return 0;
}
