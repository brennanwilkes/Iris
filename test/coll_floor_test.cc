#include <iostream>
#include <cmath>

#include "pandaFramework.h"
#include "pandaSystem.h"
#include "collisionRay.h"
#include "collisionSphere.h"
#include "collisionSegment.h"
#include "collisionNode.h"
#include "collisionHandlerFloor.h"
#include "collisionTraverser.h"
#include "mouseWatcher.h"
#include "keyboardButton.h"

#include <auto_bind.h>
#include <animControlCollection.h>
#include "omniBoundingVolume.h"

int main(int argc, char* argv[]){
	PandaFramework fw;
	fw.open_framework(argc, argv);
	fw.set_window_title("Item Looking");
	
	PT(WindowFramework) window = fw.open_window();
	window -> enable_keyboard();
	
	WindowProperties props = window -> get_graphics_window() -> get_properties();
	props.set_cursor_hidden(true);
	props.set_mouse_mode(WindowProperties::M_confined);
	window -> get_graphics_window() -> request_properties(props);
	
	PT(MouseWatcher) mw = (MouseWatcher*)window -> get_mouse().node();
	
	// Init camera
	NodePath camN = window -> get_camera_group();
	NodePath cam = window -> get_render().attach_new_node("camera");
	camN.reparent_to(cam);
	camN.set_pos(0, 0, 2);
	cam.set_pos(-1, 0, 100);
	
	// Terrain
	NodePath ter = window -> load_model(window -> get_render(), "../Assets/Stage/Terrain_C.egg");
	ter.set_pos(-8, 42, 0);
	ter.find("**/+CollisionNode").node() -> set_into_collide_mask(BitMask32::bit(0));
	
	// Object
	NodePath obj = window -> load_model(window -> get_render(), "../Assets/INSECT/insect.bam");
	obj.set_pos(0, 50, 5);
	CollisionTraverser trav;
	PT(CollisionHandlerFloor) coll = new CollisionHandlerFloor;
	coll -> set_max_velocity(9.8);
	
	PT(CollisionNode) c_Node;
	c_Node = new CollisionNode("Ground_coll_ray");
	c_Node -> add_solid(new CollisionRay(0, 0, 4, 0, 0, -1));
	c_Node -> set_from_collide_mask(BitMask32::bit(0));
	c_Node -> set_into_collide_mask(BitMask32::all_off());
	NodePath rayModel = cam.attach_new_node(c_Node);
	rayModel.show();
	coll -> add_collider(rayModel, cam);
	trav.add_collider(rayModel, coll);
	

	float mdx, mdy, dx(0), dy(0), rot;
	GraphicsWindow *gw = window -> get_graphics_window();
	
	Thread *c_thr = Thread::get_current_thread();
	while (fw.do_frame(c_thr))
	{
		trav.traverse(window -> get_render());
		mdx = gw -> get_properties().get_x_size() / 2 - gw -> get_pointer(0).get_x();
		mdy = gw -> get_properties().get_y_size() / 2 - gw -> get_pointer(0).get_y();
		camN.set_h(camN.get_h() + mdx * 0.03);
		camN.set_p(camN.get_p() + mdy * 0.03);
		gw -> move_pointer(0, gw -> get_properties().get_x_size() / 2, gw -> get_properties().get_y_size() / 2);
		
		rot = camN.get_h();
			
		if (mw -> is_button_down(KeyboardButton::ascii_key('w'))) 
		{
			dx += -0.2 * sin(rot * (3.1416 / 180));
			dy += 0.2 * cos(rot * (3.1416 / 180));
		}
		if (mw -> is_button_down(KeyboardButton::ascii_key('s')))
		{
			dx += 0.2 * sin(rot * (3.1416 / 180));
			dy += -0.2 * cos(rot * (3.1416 / 180));
		}
		if (mw -> is_button_down(KeyboardButton::ascii_key('a')))
		{
			dx += 0.2 * sin((rot - 90) * (3.1416 / 180));
			dy += -0.2 * cos((rot - 90) * (3.1416 / 180));
		}
		if (mw -> is_button_down(KeyboardButton::ascii_key('d')))
		{
			dx += 0.2 * sin((rot + 90) * (3.1416 / 180));
			dy += -0.2 * cos((rot + 90) * (3.1416 / 180));
		}
		if (mw -> is_button_down(KeyboardButton::ascii_key('u')))
		{
			cam.set_fluid_z(cam, .1);
		}
		if (mw -> is_button_down(KeyboardButton::ascii_key('j')))
		{
			cam.set_fluid_z(cam, -.1);
		}
		if (mw -> is_button_down(KeyboardButton::ascii_key('l')))
		{
			cam.set_z(100);
		}
		cam.set_fluid_x(cam.get_x() + dx);
		cam.set_fluid_y(cam.get_y() + dy);
		dx = 0;
		dy = 0;
		
		
		
		
		
		if (mw -> is_button_down(KeyboardButton::ascii_key('q')))
			break;

	}
	fw.close_framework();
	return 0;
}
