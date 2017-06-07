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

int main(int argc, char* argv[]){
	if (true) 
	{ // This is panda setup.
	PandaFramework fw;
	fw.open_framework(argc, argv);
	fw.set_window_title("Half-Body Animations Test");
	
	PT(WindowFramework) window = fw.open_window();
	window -> enable_keyboard();
	
	WindowProperties props = window -> get_graphics_window() -> get_properties();
	props.set_cursor_hidden(true);
	props.set_mouse_mode(WindowProperties::M_confined);
	window -> get_graphics_window() -> request_properties(props);
	
	PT(MouseWatcher) mw = (MouseWatcher*)window -> get_mouse().node();
	
	NodePath SkyBox = window -> load_model(window -> get_render(), "../Assets/Stage/SkyBox.egg");
	SkyBox.set_pos(-8, 42, 0);
	
	NodePath cam = window -> get_camera_group();
	cam.set_pos(-1, 0, 0);
	}
	NodePath Model = window -> load_model(cam, "../Assets/Iris/Iris.egg");
	Model.set_pos(0, 25, 0);
	
	window -> load_model(Model, "../Assets/Iris/Iris-walk.egg");
	window -> load_model(Model, "../Assets/Iris/Iris-Death.egg");
	
	AnimControlCollection anim_collection;
	auto_bind(Model.node(), anim_collection, 0);
	anim_collection.play("Armature");
	
	float mdx, mdy, dx(0), dy(0), rot;
	GraphicsWindow *gw = window -> get_graphics_window();
	
	Thread *c_thr = Thread::get_current_thread();
	while (fw.do_frame(c_thr))
	{
		
		
		
		if (true)
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
		}
	}
	fw.close_framework();
	return 0;
}
