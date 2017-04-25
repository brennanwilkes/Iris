#include "pandaFramework.h"
#include "collisionHandlerPusher.h"
#include "collisionHandlerFloor.h"
#include "collisionNode.h"
#include "collisionSphere.h"
#include "mouseWatcher.h"

int main(int argc, char *argv[])
{
	PandaFramework framework;
	framework.open_framework(argc, argv);
	framework.set_window_title("Pusher");
	WindowFramework* window = framework.open_window();
	window->enable_keyboard();
	NodePath mouseNode = window->get_mouse();
	NodePath camera = window->get_camera_group();
	camera.set_pos(0., 0., 35.);
	camera.set_p(-90.);
	
	CollisionTraverser collTrav;
	CollisionNode* cNode;
	
	NodePath player = window -> load_model(window -> get_render(), "../Assets/Kanon/Kanon.egg");
	NodePath playerC = player.attach_new_node(CollisionNode("playerColNode"));
	playerC.node().add_solid(CollisionRay(0, 0, 0, 0, 0, -1));
	
	NodePath terrain = window -> load_model(window -> get_render(), "../Assets/Stage/Terrain.egg");
	NodePath terrainC = terrain.attach_new_node(CollisionNode("terrain"));
	
	CollisionHandlerFloor floor;
	
	floor.add_collider(, terrain);

	// set up collisions handler and pusher
	CollisionHandlerPusher pusher;

	Thread *current_thread = Thread::get_current_thread();
	while (framework.do_frame(current_thread))
	{
		if(!mouseNode.is_empty())
		{
			MouseWatcher* mouseWatcher = dynamic_cast<MouseWatcher*>(mouseNode.node());
			if(mouseWatcher != NULL && mouseWatcher->has_mouse())
			{

			}
		}
		// check collisions, will call pusher collision handler
		// if a collision is detected
		collTrav.traverse(window->get_render());
	}

	framework.close_framework();
	return (0);
}

