#include <iostream>
#include <cmath>
#include <unistd.h>

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

#include "animControlCollection.h"
#include "omniBoundingVolume.h"

#include "nodePathCollection.h"

// For Half-Body Animations
#include "partBundle.h"
#include "partSubset.h"

int main(int argc, char* argv[]){
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
	
	NodePath Model = window -> load_model(window -> get_render(), "../Assets/Iris/Iris.egg");
	Model.set_pos(0, 25, -5);
	
	window -> load_model(Model, "../Assets/Iris/Iris-walk.egg");
	window -> load_model(Model, "../Assets/Iris/Iris-Death.egg");
	
	AnimControlCollection anim_collection;
	
	PartBundle Model_Upper("Model_Upper");
	PartBundle Model_Lower("Model_Lower");
	
	PartSubset MDU;
	const vector<string> UJoints = {
		"Head",
		"Neck",
		"Chest",
		"Shoulder_R",
		"Shoulder_L",
		"Upperarm_R",
		"Upperarm_L",
		"Lowerarm_R",
		"Lowerarm_L",
		"Arm_IK_R",
		"Arm_IK_L",
		"Waist"
	};
	for (auto &joint:UJoints)
	{
		MDU.add_include_joint(joint);
	}
	
	PartSubset MDL;
	const vector<string> LJoints = {
		"Pelvis",
		"Thigh_R",
		"Thigh_L",
		"Calf_R",
		"Calf_L",
		"Leg_IK_R",
		"Leg_IK_L",
		"Foot_R",
		"Foot_L",
		"Toe_R",
		"Toe_L"
	};
	for (auto &joint:LJoints)
	{
		MDL.add_include_joint(joint);
	}
	
	NodePathCollection Model_Anims = Model.find_all_matches("**/+AnimBundleNode");
	for (int i(0); i < Model_Anims.get_num_paths(); ++i)
	{
		Model_Anims.get_path(i).ls();
		cout << "Name: " << ((AnimBundle*) Model_Anims.get_path(i).node()) -> get_name() << endl;
	}
	
	//AnimControl *U_Anim;
	//AnimControl *L_Anim;
	
	//Model_Upper.do_bind_anim(U_Anim, AnimBundle, 0, MDU)
	//Model_Lower.do_bind_anim(L_Anim, AnimBundle, 0, MDL)

	
	Thread *c_thr = Thread::get_current_thread();
	while (fw.do_frame(c_thr))
	{
		
		sleep(1);
	}
	fw.close_framework();
	return 0;
}
