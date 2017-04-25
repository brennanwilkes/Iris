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
	
	NodePath cam = window -> get_camera_group();
	cam.set_pos(-1, 0, 0);
	cam.set_hpr(0, 0, 0);

	CollisionHandlerQueue* queue = new CollisionHandlerQueue();
	CollisionTraverser qtrav;
	CollisionNode* c_Node;

	NodePath Cube = window -> load_model(window -> get_render_2d(), "../Assets/Iris/Armsthatshootthings.egg");
	Cube.set_pos(0, 10, 0);
	Cube.set_hpr(0, 0, 0);

	c_Node = new CollisionNode("Cube_Sphere");
	c_Node -> add_solid(new CollisionSphere(0, 0, 0, 1));
	c_Node -> set_from_collide_mask(BitMask32::all_off());
	c_Node -> set_into_collide_mask(BitMask32::bit(0));
	NodePath Cube_Sphere = Cube.attach_new_node(c_Node);
	//Cube_Sphere.show();
	
	c_Node = new CollisionNode("Cam_ray");
	//~ c_Node -> add_solid(new CollisionRay(0, 0, 0, 0, 1, 0));
	c_Node -> add_solid(new CollisionSegment(0, 0, 0, 0, 4, 0));
	c_Node -> set_from_collide_mask(BitMask32::bit(0));
	c_Node -> set_into_collide_mask(BitMask32::all_off());
	NodePath Cam_Ray = cam.attach_new_node(c_Node);
	Cam_Ray.show();

	qtrav.add_collider(Cam_Ray, queue);

	cam.look_at(Cube);
	float mdx, mdy, dx(0), dy(0), rot;
	GraphicsWindow *gw = window -> get_graphics_window();
	
	Thread *c_thr = Thread::get_current_thread();
	while (fw.do_frame(c_thr))
	{
		mdx = gw -> get_properties().get_x_size() / 2 - gw -> get_pointer(0).get_x();
		mdy = gw -> get_properties().get_y_size() / 2 - gw -> get_pointer(0).get_y();
		cam.set_h(cam.get_h() + mdx * 0.03);
		cam.set_p(cam.get_p() + mdy * 0.03);
		gw -> move_pointer(0, gw -> get_properties().get_x_size() / 2, gw -> get_properties().get_y_size() / 2);
		
		rot = cam.get_h();
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
		cam.set_fluid_x(cam.get_x() + dx);
		cam.set_fluid_y(cam.get_y() + dy);
		dx = 0;
		dy = 0;
		qtrav.traverse(window -> get_render());
		if (queue -> get_num_entries() > 0)
		{
			queue -> sort_entries();
			for (int i(0); i < queue -> get_num_entries(); ++i)
				cout << queue -> get_entry(i) -> get_into_node() -> get_name() << ", " << cam.get_h();
			cout << endl;
		}
		//Cube.set_r((int)(Cube.get_r() + 1) % 360);
		//Cube.set_h((int)(Cube.get_h() + 1) % 360);
	}
	fw.close_framework();
	return 0;
}
