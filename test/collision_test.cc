#include "pandaFramework.h"
#include "pandaSystem.h"
#include "collisionRay.h"
#include "collisionNode.h"

void grav(NodePath &cube);

int main(int argc, char* argv[]){
	PandaFramework fw;
	fw.open_framework(argc, argv);
	fw.set_window_title("Collision Test");
	
	PT(WindowFramework) win = fw.open_window();
	win -> enable_keyboard();
	
	Cube cube = window -> load_model(window -> get_render(), "./cube.egg");
	cube.set_pos(0, 0, 10);
	
	NodePath cube_C = (NodePath) cube;
	cube_C.node() -> set_into_collide_mask(BitMask32::all_off());
	
	PT(CollisionRay) collray = new CollisionRay;
	collray -> setOrigin(0, 0, 1);
	collray -> setDirection(0, 0, -1);
	
	NodePath terrain = window -> load_model(window -> get_render(), "./Terrain_C.egg");
	terrain.set_pos(-8, 42, 0);
	terrain.set_scale(2.5);
	
	NodePath terrain_C = terrain;
	terrain_C.node() -> set_into_collide_mask(BitMask32::bit(1));
	
	Thread *c_thr = Thread::get_current_thread();
	while (framework.do_frame(c_thr))
	{
		grav(cube);
	}
	framework.close_framework();
	return 0;
}

void grav(NodePath &cube) {
	if (!cube.is_ground)
		cube -> set_y(cube, -0.1);
}
