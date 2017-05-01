// Bash function to compile:
// function compile() { g++ -Wall -std=c++11 -Wno-reorder $1 -o $2 -O2 -I/usr/include/panda3d -I/usr/include/python2.6 -L/usr/lib64/panda3d -lp3framework -lpanda -lpandafx -lpandaexpress -lp3dtoolconfig -lp3dtool -lp3pystub -lp3direct; }
// $ compile filename.cc executable
// Now, to compile on school machines, simply type 'make'
// Adding -j 2 to make will cause it to use 2 cores

/*
 * 	TO DO:
 * 		- Fix 3rd person camera
 * 		- Clean up code
 * 		- Add further features
 */

/*

http://soundbible.com/tags-gun.html

*/


/*

https://www.panda3d.org/manual/index.php/Common_State_Changes

*/


#include <iostream>
#include <map>
#include <string>
//#include <tostring>
#include <vector>
#include <cmath>

// Please keep includes in alphabetical order from now on
#include "ambientLight.h"
#include "asyncTaskManager.h"
#include "audioManager.h"
#include "boundingVolume.h"
#include "cardMaker.h"
#include "cIntervalManager.h"
#include "cLerpNodePathInterval.h"
#include "cMetaInterval.h"
#include "collisionHandlerPusher.h"
#include "collisionHandlerQueue.h"
#include "collisionNode.h"
#include "collisionRay.h"
#include "collisionSphere.h"
#include "collisionTraverser.h"
#include "directionalLight.h"
#include "executionEnvironment.h"
#include "filename.h"
#include "genericAsyncTask.h"
#include "mouseButton.h"
#include "mouseWatcher.h"
#include "omniBoundingVolume.h"
#include "pandaFramework.h"
#include "pandaSystem.h"
#include "pgButton.h"
#include "pgSliderBar.h"
#include "pgWaitBar.h"
#include "texturePool.h"
#include <auto_bind.h>
#include <animControlCollection.h>
#include "transparencyAttrib.h"
#include <cstdlib>

// Test includes
#include "mouseWatcherParameter.h"
// Our files
#include "player.hpp"
#include "world.hpp"
#include "weapon.hpp"
#include "item.hpp"
#include "staticObject.hpp"
#include "waterItem.hpp"
#include "foodItem.hpp"
#include "healthItem.hpp"
#include "enemy.hpp"
#include "keys.hpp"

#include "global.hpp"

#include "load_prc_file.h"
#include "configVariableFilename.h"



AsyncTaskManager* taskMgr = AsyncTaskManager::get_global_ptr(); 
ClockObject* globalClock = ClockObject::get_global_clock();
Filename mydir = ((Filename)ExecutionEnvironment::get_binary_name()).get_dirname()+"/";
vector<GameObject*> objs;
vector<Enemy*> enems;
vector<Item*> itms;
Player player;
Keys keys;
World world;
NodePath gameModels;
NodePath menuItems;
NodePath optionMenuItems;
PT(PGSliderBar) Slider=new PGSliderBar("MySliderBar");;

int scene;

WindowFramework* window;

// Forward declared functions
void sys_exit(const Event* eventPtr, void* dataPtr);
void toggle(const Event* eventPtr, void* dataPtr);
void toggleHitBox(const Event* eventPtr, void* dataPtr);
void toggleDoubleJump(const Event* eventPtr, void* dataPtr);
void toggleOptionMenu(const Event* eventPtr, void* dataPtr);
void invPress(const Event* eventPtr, void* dataPtr);
void jump(const Event* eventPtr, void* dataPtr);
void menu(const Event* eventPtr, void* dataPtr);
void hide_arms(const Event* eventPtr, void* dataPtr);
void onMouse1(const Event* eventPtr, void* dataPtr);
void onE(const Event* eventPtr, void* dataPtr);
void onR(const Event* eventPtr, void* dataPtr);
void drop(const Event* eventPtr, void* dataPtr);
int getMenuSliderInd();
void calc_inv(PGButton* fs,PGButton* ss,PGButton* ts,PT(Texture)* bt);

void rebindButton(const Event* eventPtr, void* dataPtr);

int main(int argc, char *argv[]) {
	// Panda Objects
	PandaFramework framework;
	WindowProperties props;
	MouseWatcher* mouseWatcher;
	AmbientLight* al;
	DirectionalLight* dl;
	
	// NodePaths
	NodePath alnp;
	NodePath dlnp;
	
	// Other variables
	
	//ConfigVariableFilename a;
	//cout<<a.get_fullpath()<<endl;
	//load_prc_file("Config.prc");


	// Set up framework
	framework.open_framework(argc, argv);
	framework.set_window_title("GAME");
	
	
	world.gameSounds.AM = AudioManager::create_AudioManager();
	world.gameSounds.akFireSound = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/akFire.wav");
	world.gameSounds.akFireSound->set_volume(0.25);
	world.gameSounds.akEmptySound = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/akEmpty.wav");
	world.gameSounds.akEmptySound->set_volume(0.75);
	world.gameSounds.akReloadSound = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/akReload.wav");
	world.gameSounds.akReloadSound->set_volume(0.75);
	
	
	
	world.gameSounds.pistolFireSound = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/pistolFire.wav");
	world.gameSounds.pistolFireSound->set_volume(0.25);
	world.gameSounds.pistolEmptySound = world.gameSounds.akEmptySound;
	world.gameSounds.pistolEmptySound->set_volume(0.75);
	world.gameSounds.pistolReloadSound = world.gameSounds.akReloadSound;
	world.gameSounds.pistolReloadSound->set_volume(0.75);
	
	world.gameSounds.batFireSound = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/batFire.wav");
	world.gameSounds.batFireSound->set_volume(0.5);
	
	
	world.gameSounds.ricochetSound1 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/ricochet-1.wav");
	world.gameSounds.ricochetSound1->set_volume(0.25);
	world.gameSounds.ricochetSound2 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/ricochet-2.wav");
	world.gameSounds.ricochetSound2->set_volume(0.25);
	world.gameSounds.ricochetSound3 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/ricochet-3.wav");
	world.gameSounds.ricochetSound3->set_volume(0.25);
	world.gameSounds.ricochetSound4 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/ricochet-4.wav");
	world.gameSounds.ricochetSound4->set_volume(0.25);
	world.gameSounds.ricochetSound5 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/ricochet-5.wav");
	world.gameSounds.ricochetSound5->set_volume(0.25);
	world.gameSounds.ricochetSound6 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/ricochet-6.wav");
	world.gameSounds.ricochetSound6->set_volume(0.25);
	
	world.gameSounds.walkSound1 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/walk1.wav");
	world.gameSounds.walkSound1->set_volume(1.0);
	world.gameSounds.walkSound2 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/walk2.wav");
	world.gameSounds.walkSound2->set_volume(1.0);
	world.gameSounds.walkSound3 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/walk3.wav");
	world.gameSounds.walkSound3->set_volume(1.0);
	world.gameSounds.walkSound4 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/walk4.wav");
	world.gameSounds.walkSound4->set_volume(1.0);
	world.gameSounds.walkSound5 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/walk5.wav");
	world.gameSounds.walkSound5->set_volume(1.0);
	world.gameSounds.walkSound6 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/walk6.wav");
	world.gameSounds.walkSound6->set_volume(1.0);
	
	world.gameSounds.bulletHitSound1 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/bulletHit.wav");
	world.gameSounds.bulletHitSound1->set_volume(1.0);
	world.gameSounds.bulletHitSound2 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/bulletHit2.wav");
	world.gameSounds.bulletHitSound2->set_volume(1.0);
	
	world.gameSounds.bulletCasingFallSound = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/BulletCasingFall.wav");
	world.gameSounds.bulletCasingFallSound->set_volume(1.0);
	
	world.gameSounds.femaleGrunt1 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/female-grunt1.wav");
	world.gameSounds.femaleGrunt1->set_volume(1.0);
	world.gameSounds.femaleGrunt2 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/female-grunt2.wav");
	world.gameSounds.femaleGrunt2->set_volume(1.0);
	world.gameSounds.femaleGrunt3 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/female-grunt3.wav");
	world.gameSounds.femaleGrunt3->set_volume(1.0);
	world.gameSounds.femaleGrunt4 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/female-grunt4.wav");
	world.gameSounds.femaleGrunt4->set_volume(1.0);
	world.gameSounds.femaleGrunt5 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/female-grunt5.wav");
	world.gameSounds.femaleGrunt5->set_volume(1.0);
	world.gameSounds.femaleGrunt6 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/female-grunt6.wav");
	world.gameSounds.femaleGrunt6->set_volume(1.0);
	world.gameSounds.femaleGrunt7 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/female-grunt7.wav");
	world.gameSounds.femaleGrunt7->set_volume(1.0);
	
	
	world.gameSounds.scream1 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/scream1.wav");
	world.gameSounds.scream1->set_volume(1.0);
	world.gameSounds.scream2 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/scream2.wav");
	world.gameSounds.scream2->set_volume(1.0);
	world.gameSounds.scream3 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/scream3.wav");
	world.gameSounds.scream3->set_volume(1.0);
	world.gameSounds.scream4 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/scream4.wav");
	world.gameSounds.scream4->set_volume(1.0);
	
	
	world.gameSounds.glass = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/glass.wav");
	world.gameSounds.glass->set_volume(1.0);
	
	world.gameSounds.heyShout = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/heyShout.wav");
	world.gameSounds.heyShout->set_volume(1.0);
	
	world.gameSounds.hiss = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/hiss.wav");
	world.gameSounds.hiss->set_volume(1.0);
	
	world.gameSounds.impact = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/impact.wav");
	world.gameSounds.impact->set_volume(1.0);
	
	world.gameSounds.Snarl = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/Snarl.wav");
	world.gameSounds.Snarl->set_volume(1.0);
	world.gameSounds.Snarl2 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/Snarl2.wav");
	world.gameSounds.Snarl2->set_volume(1.0);
	
	world.gameSounds.walkSand = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/walk-sand.wav");
	world.gameSounds.walkSand->set_volume(1.0);
	
	world.gameSounds.wood1 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/wood1.wav");
	world.gameSounds.wood1->set_volume(1.0);
	world.gameSounds.wood2 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/wood2.wav");
	world.gameSounds.wood2->set_volume(1.0);
	
	world.gameSounds.background1 = world.gameSounds.AM->get_sound(mydir+"Assets/Sounds/background1.wav");
	world.gameSounds.background1->set_volume(0.25);
	
	
	
	// Set up window
	window = framework.open_window();
	window -> enable_keyboard();
	
	props = window -> get_graphics_window() -> get_properties();
	props.set_cursor_hidden(true);
	props.set_mouse_mode(WindowProperties::M_confined);
	window -> get_graphics_window() -> request_properties(props);

	
	
	

	window -> get_display_region_3d() -> set_clear_color( LColor(0.53,0.81,0.92, 1) );
	
	// Create a mousewatcher (needed to check for key held)
	mouseWatcher = (MouseWatcher*)window -> get_mouse().node();
	
	//loadscreen
	float xss = -(window -> get_graphics_window()->get_x_size() / (float)window ->get_graphics_window()->get_y_size());
	
	PT(Texture) wts;
	CardMaker cms("cardMaker");
	PT(PandaNode) readycards = cms.generate();
	NodePath NNS(readycards);
	NNS = window -> get_aspect_2d().attach_new_node(readycards);
	NNS.set_transparency(TransparencyAttrib::M_alpha, 1);
	NNS.set_scale(1);
	NNS.set_pos(xss,0, 0);
	
	
	wts=TexturePool::load_texture(mydir+"Assets/loadscreen-temp.png");
	NNS.set_texture(wts);
	
	NNS.show();
	
	Thread *current_thread = Thread::get_current_thread();
	if(framework.do_frame(current_thread))
	{
		framework.get_graphics_engine()->render_frame();
		CIntervalManager::get_global_ptr() -> step();
	}

	// Lighting
	al = new AmbientLight("my a_light");
	al -> set_color(LVecBase4f(0.0, 0.1, 0.1, 0.1));
	alnp = window -> get_render().attach_new_node(al);
	window -> get_render().set_light(alnp);

	dl = new DirectionalLight("my d_light");
	dlnp = window -> get_render().attach_new_node(dl);
	dlnp.set_hpr(-30, -60, 0);
	window -> get_render().set_light(dlnp);
	dl -> set_shadow_caster(true, 512, 512);
	
	
	// Create a dummy node to attach things to. Does not affect anything,
	// but makes it easier to hide all the game nodes at once.
	gameModels = window -> get_render().attach_new_node("All game models");
		NodePath staticModels = gameModels.attach_new_node("All Static (Terrain)");
		NodePath entityModels = gameModels.attach_new_node("All Entities");
			NodePath shootableModels = entityModels.attach_new_node("All Shootables");
			NodePath itemModels = entityModels.attach_new_node("All items");
			NodePath pushableModels = entityModels.attach_new_node("All pushables");
			NodePath interactModels = entityModels.attach_new_node("All interactables");
	menuItems = window -> get_aspect_2d().attach_new_node("Buttons and such");
	menuItems.set_transparency(TransparencyAttrib::M_alpha, 1);
	optionMenuItems = window -> get_aspect_2d().attach_new_node("Option Menu Buttons");
	optionMenuItems.set_transparency(TransparencyAttrib::M_alpha, 1);
	
	
	
	
	/*
	PT(Texture) tbak;
	CardMaker cms2("cardMaker");
	PT(PandaNode) readycards2 = cms2.generate();
	NodePath NNS2(readycards2);
	NNS2 = window -> get_aspect_2d().attach_new_node(readycards2);
	NNS2.set_transparency(TransparencyAttrib::M_alpha, 1);
	NNS2.set_scale(3);
	NNS2.set_pos(xss,0, -1.0);
	
	
	tbak=TexturePool::load_texture(mydir+"Assets/temp-bak.png");
	NNS2.set_texture(tbak);
	
	NNS2.show();
	NNS2.reparent_to(menuItems);
	
	*/
	
	
	
	
	
	NodePath Bars = window -> get_pixel_2d().attach_new_node("Status Bars");
	Bars.set_transparency(TransparencyAttrib::M_alpha, 1);
	Bars.reparent_to(window->get_aspect_2d());
	
	

	menuItems.hide();
	optionMenuItems.hide();

	
	// Set up player camera and model
	player.set_up(&gameModels,window,&framework,mydir);
	
	
	
	window->load_model(player.pistol_arms, mydir + "Assets/Iris/FirstPersonViewModel-Fire.egg");
	// don't use PT or CPT with AnimControlCollection 
	//bind the animations to the model
	auto_bind(player.pistol_arms.node(), player.pistol_collection);
	player.pistol_collection.play("Armature");
	
	
	window->load_model(player.bat_arms, mydir + "Assets/Iris/fpvBat-atttack.egg");
	auto_bind(player.bat_arms.node(), player.bat_collection);
	player.bat_collection.play("Armature");
	
	
	window->load_model(player.empty_arms, mydir + "Assets/Iris/EmptyHands-Idle.egg");
	auto_bind(player.empty_arms.node(), player.empty_collection);
	player.empty_collection.play("Armature");
	
	window->load_model(player.ak_arms, mydir + "Assets/Iris/fpvak47-fire.egg");
	auto_bind(player.ak_arms.node(), player.ak_collection);
	player.ak_collection.play("Armaturblender how to seperate a meshe");
	
	
	// the name of an animation is preceded in the .egg file with <BunBdle>:
	// loop a specific animation
	//anim_collection.loop("Armature", true);
	 
	// loop all animations
	//anim_collection.loop_all(true);
	 
	// play an animation once:
	//[] (int a, string b, etc.) { CODE; GOES; HERE; }
	

	
	objs.push_back(&player);
	
	// Load models of the scene (eventually should be one model)

	//vector<string> Dir = {"Assets/starea/Terrain.egg","Assets/starea/Terrain1.egg","Assets/starea/Terrain2.egg","Assets/starea/Terrain3.egg","Assets/starea/Terrain4.egg","Assets/starea/Terrain5.egg","Assets/starea/Terrain6.egg","Assets/starea/Terrain7.egg","Assets/starea/Terrain8.egg","Assets/starea/Terrain9.egg"};
	//vector<string> Dir ={"Assets/starea/lag_.egg"};
	//vector<NodePath> ND;

	vector<string> Dir = {"Assets/Stage/Terrain_C.egg","Assets/Stage/SkyBox.egg","Assets/Stage/Grave.egg","Assets/Stage/Building_C.egg","Assets/Stage/Stone_C.egg","Assets/Stage/Ramp_C.egg","Assets/Stage/Stairs_C.egg","Assets/sphere/sphere.egg"};
	
	//vector<string> Dir = {"Assets/starea/lag_.egg"};

	vector<StaticObject> ND;
	for(auto x:Dir)
	{
		//StaticObject(int xx,int yy,int zz, std::string fn,NodePath* parent,WindowFramework* w,PandaFramework* pf,float scale=1){
		ND.push_back(StaticObject(-8,42,0,mydir+x,&gameModels,window,&framework,2.6));
		
	}
	PT(CollisionNode) c_Node;
	//ptrav.set_respect_prev_transform(true);

	
	player.coll_set_up();

	// Menu items
	float xs = -(window -> get_graphics_window()->get_x_size() / (float)window ->get_graphics_window()->get_y_size());

	PGButton* QuitButton;
	QuitButton = new PGButton("QuitButton");
	QuitButton -> setup("Quit Program");
	NodePath defbutNP = window -> get_pixel_2d().attach_new_node(QuitButton);
	defbutNP.set_scale(0.1);
	defbutNP.set_pos(xs+0.1,0, 0.25);
	defbutNP.reparent_to(menuItems);
	keys.buttonIndex["click-mouse1-"+QuitButton->get_id()] = QuitButton;
	
	/*PGButton* CamTogButton;
	CamTogButton = new PGButton("CamTogButton");
	CamTogButton -> setup("Toggle Camera");
	NodePath defbutNP2 = window -> get_pixel_2d().attach_new_node(CamTogButton);
	defbutNP2.set_scale(0.1);
	defbutNP2.set_pos(xs + 0.1, 0, 0.65);
	defbutNP2.reparent_to(menuItems);
	*/
	
	PGButton* HitTogButton;
	HitTogButton = new PGButton("HitTogButton");
	HitTogButton -> setup("Toggle Hit Boxes");
	NodePath defbutNP3 = window -> get_pixel_2d().attach_new_node(HitTogButton);
	defbutNP3.set_scale(0.1);
	defbutNP3.set_pos(xs + 0.1, 0, 0.65);
	defbutNP3.reparent_to(menuItems);
	keys.buttonIndex["click-mouse1-"+HitTogButton->get_id()] = HitTogButton;
	
	PGButton* DoubleTogButton;
	DoubleTogButton = new PGButton("DoubleTogButton");
	DoubleTogButton -> setup("Toggle Double Jump");
	NodePath defbutNP4 = window -> get_pixel_2d().attach_new_node(DoubleTogButton);
	defbutNP4.set_scale(0.1);
	defbutNP4.set_pos(xs + 0.1, 0, 0.45);
	defbutNP4.reparent_to(menuItems);
	keys.buttonIndex["click-mouse1-"+DoubleTogButton->get_id()] = DoubleTogButton;

	
	PGButton* OptionTogButton;
	OptionTogButton = new PGButton("OptionTogButton");
	OptionTogButton -> setup("Toggle Option Menu");
	NodePath defbutNP5 = window -> get_pixel_2d().attach_new_node(OptionTogButton);
	defbutNP5.set_scale(0.1);
	defbutNP5.set_pos(xs + 0.1, 0, 0.85);
	defbutNP5.reparent_to(menuItems);
	NodePath defbutNP6 = window -> get_pixel_2d().attach_new_node(OptionTogButton);
	defbutNP6.set_scale(0.1);
	defbutNP6.set_pos(xs + 0.1, 0, 0.85);
	defbutNP6.reparent_to(optionMenuItems);
	keys.buttonIndex["click-mouse1-"+OptionTogButton->get_id()] = OptionTogButton;


	for (unsigned int i=0; i<keys.keybindItems.size(); i++){
		PGButton* butt;
		butt = new PGButton("Bind"+keys.keybindItems.at(i));
		butt -> setup(keys.keybindItems.at(i)+":"+ keys.keybinds[keys.keybindItems.at(i)].first.get_name());
		NodePath BindNode1 = window -> get_pixel_2d().attach_new_node(butt);
		BindNode1.set_scale(0.1);
		BindNode1.set_pos(xs+0.1*(i/8*8+1),0,0.85-(.2*(i%8+1)));
		BindNode1.reparent_to(optionMenuItems);
		window -> get_panda_framework() -> define_key(butt->get_click_event(MouseButton::one() ), "Bind "+keys.keybindItems.at(i)+"Press",&rebindButton, butt);
		keys.keybindMenu.push_back(butt);
		keys.buttonIndex["click-mouse1-"+butt->get_id()] = butt;
	}





	PT(Texture) redTex=TexturePool::load_texture(mydir+"Assets/Red.png");
	PT(Texture) greenTex=TexturePool::load_texture(mydir+"Assets/Blue.png");
	PT(Texture) blueTex=TexturePool::load_texture(mydir+"Assets/Green.png");
	
	PGWaitBar* HealthBar;
	HealthBar = new PGWaitBar("HealthBar");
	HealthBar->setup(10.0,0.5,100.0);
	NodePath HealthNode = window -> get_pixel_2d().attach_new_node(HealthBar);
	HealthNode.set_scale(0.1);
	HealthNode.set_pos(xs + 2.1, 0, -0.80);
	HealthNode.show();
	HealthNode.reparent_to(Bars);
	HealthNode.set_texture(redTex);
	
	
	PGWaitBar* FoodBar;
	FoodBar = new PGWaitBar("FoodBar");
	FoodBar->setup(10.0,0.5,100.0);
	NodePath FoodNode = window -> get_pixel_2d().attach_new_node(FoodBar);
	FoodNode.set_scale(0.1);
	FoodNode.set_pos(xs + 2.1, 0, -0.87);
	FoodNode.show();
	FoodNode.reparent_to(Bars);
	FoodNode.set_texture(blueTex);
	
	PGWaitBar* WaterBar;
	WaterBar = new PGWaitBar("WaterBar");
	WaterBar->setup(10.0,0.5,100.0);
	NodePath WaterNode = window -> get_pixel_2d().attach_new_node(WaterBar);
	WaterNode.set_scale(0.1);
	WaterNode.set_pos(xs + 2.1, 0, -0.94);
	WaterNode.show();
	WaterNode.reparent_to(Bars);
	WaterNode.set_texture(greenTex);
	
	

	
	player.ammoNode = new TextNode("ammoNode");
	player.ammoNode->set_text("0");
	player.ammoNodePath = window->get_aspect_2d().attach_new_node(player.ammoNode);
	player.ammoNodePath.set_scale(0.07);
	player.ammoNodePath.set_pos(xs+0.5,0, -0.9);
	
	player.ammoNode2 = new TextNode("ammoNode2");
	player.ammoNode2->set_text("0");
	player.ammoNodePath2 = window->get_aspect_2d().attach_new_node(player.ammoNode2);
	player.ammoNodePath2.set_scale(0.04);
	player.ammoNodePath2.set_pos(xs+0.6,0, -0.9);

	
	player.weightNode = new TextNode("weightNode");
	player.weightNode->set_text("0");
	player.weightNodePath = window->get_aspect_2d().attach_new_node(player.weightNode);
	player.weightNodePath.set_scale(0.07);
	player.weightNodePath.set_pos(xs+0.5,0, -0.98);
	
	player.volumeNode = new TextNode("volumeNode");
	player.volumeNode->set_text("0");
	player.volumeNodePath = window->get_aspect_2d().attach_new_node(player.volumeNode);
	player.volumeNodePath.set_scale(0.07);
	player.volumeNodePath.set_pos(xs+0.8,0, -0.98);
	
	
				//This is example code for fancy buttons. Dont delete
	/*
	PT(PGButton) MyButton;
	MyButton = new PGButton("MyButton");
	MyButton->setup("Button",0.1);
	PT(Texture) ButtonReady=TexturePool::load_texture("Assets/Red.png");
	PT(Texture) ButtonRollover=TexturePool::load_texture("Assets/Blue.png");
	PT(Texture) ButtonPressed=TexturePool::load_texture("Assets/Green.png");
	PT(Texture) ButtonInactive=TexturePool::load_texture("Assets/Yellow.png");
	
	PGFrameStyle MyStyle=MyButton->get_frame_style(0); // frame_style(0): ready state
	MyStyle.set_type(PGFrameStyle::T_flat);
	
	MyStyle.set_texture(ButtonReady);    MyButton->set_frame_style(0,MyStyle);
	MyStyle.set_texture(ButtonRollover); MyButton->set_frame_style(1,MyStyle);
	MyStyle.set_texture(ButtonPressed);  MyButton->set_frame_style(2,MyStyle);
	MyStyle.set_texture(ButtonInactive); MyButton->set_frame_style(3,MyStyle);
	
	
	NodePath defbutNP3 = window->get_aspect_2d().attach_new_node(MyButton);
	defbutNP3.set_scale(0.1);
	defbutNP3.set_pos(xs+0.1,0, 0.45);
	defbutNP3.reparent_to(menuItems);
	*/
	
	

	
	
	
	

	 
	// Setup, feeding the constructor with (bool vertical,float lenght,float width,float bevel)
	Slider->setup_scroll_bar(true,1.5,0.5,0); // 'rail' properties
	Slider->set_range(0,1);
	Slider->set_value(0);
	 
	// Setup scroll bar (the 'moving thumb button' including left and right button)
	Slider->setup_slider(true,1,0.05,false);
	NodePath SliderNP=window->get_aspect_2d().attach_new_node(Slider);
	SliderNP.set_pos(0.15,0,0);
	
	SliderNP.reparent_to(menuItems);
	
	
	
	
	
	
	
	
	
	NodePath blank_plane = window->load_model(framework.get_models(),mydir+"Assets/plane.egg");
	blank_plane.set_transparency(TransparencyAttrib::M_alpha, 1);
	PT(Texture) blankTex=TexturePool::load_texture(mydir+"Assets/blank_slot2.png");
	
	



	PGButton* InvButton1;
	InvButton1 = new PGButton("InvButton1");
	InvButton1 -> setup(blank_plane);
	
	
	
	NodePath invBut = window -> get_pixel_2d().attach_new_node(InvButton1);
	invBut.set_transparency(TransparencyAttrib::M_alpha, 1);
	invBut.set_tag("invBut","1");
	invBut.set_scale(0.25);
	invBut.set_pos(xs + 2, 0, 0.6);
	invBut.reparent_to(menuItems);
	invBut.show();
	keys.buttonIndex["click-mouse1-"+InvButton1->get_id()] = InvButton1;

	//////////////////////////////////////////////
	
	PGButton* InvButton2;
	InvButton2 = new PGButton("InvButton2");
	InvButton2 -> setup(blank_plane);
	

	
	NodePath invBut2 = window -> get_pixel_2d().attach_new_node(InvButton2);
	invBut2.set_transparency(TransparencyAttrib::M_alpha, 1);
	invBut2.set_tag("invBut","2");
	invBut2.set_scale(0.25);
	invBut2.set_pos(xs + 2, 0, 0.0);
	invBut2.reparent_to(menuItems);
	invBut2.show();
	keys.buttonIndex["click-mouse1-"+InvButton2->get_id()] = InvButton2;

	//////////////////////////////////////////////
	
	PGButton* InvButton3;
	InvButton3 = new PGButton("InvButton3");
	InvButton3 -> setup(blank_plane);
	
	NodePath invBut3 = window -> get_pixel_2d().attach_new_node(InvButton3);
	invBut3.set_transparency(TransparencyAttrib::M_alpha, 1);
	invBut3.set_tag("invBut","3");
	invBut3.set_scale(0.25);
	invBut3.set_pos(xs + 2, 0, -0.6);
	invBut3.reparent_to(menuItems);
	invBut3.show();
	keys.buttonIndex["click-mouse1-"+InvButton3->get_id()] = InvButton3;

	//////////////////////////////////////////////
	
	
	
	
	
	
	///////////////////////////////////////////////////////////////////////////////////
	///Pill bottle
	
	//Item(char t,int xx,int yy,int zz,float wei,float vol, std::string fn,NodePath* parent,WindowFramework* w,PandaFramework* pf,float scale,int zzz,int xxx,int yyy,float rad,int zzzz)
	
	
	
	
	
	
	WeaponObject ak47('g',35,0,20,1.0f,1.0f, mydir+"blenderFiles/AK47.egg",&gameModels,window,&framework,1.0f,1,0,0,1.5f,0,mydir+"blenderFiles/ak47icon.png",24.0,10);
	ak47.weapon_init(24,25.0,1.0,0,64,1);
	itms.push_back(&ak47);
	
	
	WeaponObject ak48('g',37,0,20,1.0f,1.0f, mydir+"blenderFiles/AK47.egg",&gameModels,window,&framework,1.0f,1,0,0,1.5f,0,mydir+"blenderFiles/ak47icon.png",24.0,10);
	ak48.weapon_init(24,25.0,1.0,0,64,1);
	itms.push_back(&ak48);
	
	
	
	WeaponObject ak49('g',39,0,20,1.0f,1.0f, mydir+"blenderFiles/AK47.egg",&gameModels,window,&framework,1.0f,1,0,0,1.5f,0,mydir+"blenderFiles/ak47icon.png",24.0,10);
	ak49.weapon_init(24,25.0,1.0,0,64,1);
	itms.push_back(&ak49);
	
	
	WeaponObject Bat('g',15,0,20,1.0f,1.0f, mydir+"Model/Baseballbat.egg",&gameModels,window,&framework,1.0f,1,0,0,1.5f,0,mydir+"blenderFiles/baticon.png",15.0,2);
	Bat.weapon_init(15,1.0,1.0,0,0,1);
	itms.push_back(&Bat);
	
	
	
	WeaponObject Pis('g',25,0,25,1.0f,1.0f, mydir+"Model/PIstol/Pistol.egg",&gameModels,window,&framework,0.25f,1,0,0,1.5f,0,mydir+"Model/PIstol/ITSAGUN.png",8.0,0);
	Pis.weapon_init(8,1.0,1.0,0,64,1);	
	itms.push_back(&Pis);
	
		
	
	HealthItem Pill('c',0,0,20,1.0f,1.0f, mydir+"Assets/pillBottle.egg",&gameModels,window,&framework,0.5f,1,0,0,1.5f,0,mydir+"blenderFiles/pbottleicon.png",100.0,1);
	itms.push_back(&Pill);
	
	Item Ammo('a',5,0,20,1.0f,1.0f, mydir+"Assets/pillBottle.egg",&gameModels,window,&framework,0.5f,1,0,0,1.5f,0,mydir+"blenderFiles/pbottleicon.png",35.0,10);
	itms.push_back(&Ammo);
	
	FoodItem cheese('c',55,0,20,1.0f,1.0f, mydir+"blenderFiles/cheese.egg",&gameModels,window,&framework,0.5f,1,0,0,1.5f,0,mydir+"blenderFiles/cheeseicon.png",25.0,5);
	itms.push_back(&cheese);
	
	WaterItem booootle('c',45,5,20,1.0f,1.0f, mydir+"blenderFiles/Bootle.egg",&gameModels,window,&framework,0.5f,1,0,0,1.5f,0,mydir+"blenderFiles/BottleIcon.png",80.0,6);
	itms.push_back(&booootle);
	
	//healthItem dora('c',25,15,500,1.0f,1.0f, mydir+"blenderFiles/Bootle.egg",&gameModels,window,&framework,0.5f,1,0,0,1.5f,0,mydir+"blenderFiles/BottleIcon.png",80.0,4);
	//itms.push_back(&dora);
	

	Enemy romar;
	romar.set_up(&shootableModels,window,&framework,mydir+"Assets/INSECT/insect.egg",50.0,-10,-10,0,15.0,40,24,0,10.0);
	romar.init();
	romar.coll_set_up(1000);
	enems.push_back(&romar);
	

	window->load_model(romar.model, mydir + "Assets/INSECT/insect-Idle.egg");
	auto_bind(romar.model.node(), romar.anim_collection);
	window->load_model(romar.model, mydir + "Assets/INSECT/insect-Move.egg");
	auto_bind(romar.model.node(), romar.anim_collection);
	romar.anim_collection.loop("Armature.1", true);
	
	

	/*
	Enemy sebastian;
	sebastian.set_up(&shootableModels,window,&framework,mydir+"Assets/INSECT/insect.egg",500.0,10,10,10,15.0);
	sebastian.init();
	sebastian.coll_set_up(10);
	enems.push_back(&sebastian);
	*/
	
	
	
	
	//Deprecated but useful notes so dont delete
	/*
	vector<string> Dirs = {"ak-colour","ak-black","ak-red"};
	
	for(auto xx:Dirs)
	{
		WeaponObject w;
		
		PT(Texture) wt;
		
		w.tex = wt;
		CardMaker cm("cardMaker");
		PT(PandaNode) readyCard = cm.generate();
		NodePath NN(readyCard);
		
		w.Node = NN;
		w.Node = window -> get_aspect_2d().attach_new_node(readyCard);
		w.Node.set_transparency(TransparencyAttrib::M_alpha, 1);
		w.Node.set_scale(0.5);
		w.Node.set_pos(xs+0.1,0, -1);

		w.name=xx;
		w.id=player.weapons.size();
		w.available=true;
		w.selected=false;
		
		
		
		w.tex=TexturePool::load_texture(mydir+"Assets/"+xx+".png");
		w.Node.set_texture(w.tex);
		w.Node.hide();
		player.weapons.push_back(w);
		player.weapons.back().Node.hide();
	}
	*/
	
	CardMaker cm("cardMaker");
	PT(PandaNode) readyCard = cm.generate();
	NodePath NN(readyCard);
	player.handDisplay=NN;
	
	player.handDisplay = window -> get_aspect_2d().attach_new_node(readyCard);
	player.handDisplay.set_transparency(TransparencyAttrib::M_alpha, 1);
	player.handDisplay.set_scale(0.4);
	player.handDisplay.set_pos(xs+0.1,0, -0.9);
	player.handDisplay.show();
	player.handDisplay.set_texture(blankTex);
	
	
	
	
	PT(Texture) tex_crosshair;
	CardMaker cm_crosshair("cardMaker");
	PT(PandaNode) rc_crosshair = cm_crosshair.generate();
	NodePath nd_crosshair(rc_crosshair);
	nd_crosshair = window -> get_aspect_2d().attach_new_node(rc_crosshair);
	nd_crosshair.set_transparency(TransparencyAttrib::M_alpha, 1);
	nd_crosshair.set_scale(0.5);
	nd_crosshair.set_pos(-0.25, 0 ,-0.25);
	
	
	tex_crosshair=TexturePool::load_texture(mydir+"Assets/CrossHair.png");
	nd_crosshair.set_texture(tex_crosshair);
	
	nd_crosshair.show();
	
	
	
	// lambda functions are as thus:
	// [] (int a, string b, etc.) { CODE; GOES; HERE; }
	
	// define_key("event_name", "description", function, data);
	// data is a void pointer, so it can take anything.

	window -> get_panda_framework() -> define_key(keys.keybinds["menu"].first.get_name(), "menu", &menu, window);
	window -> get_panda_framework() -> define_key(keys.keybinds["jump"].first.get_name(), "jump", &jump, NULL);
	window -> get_panda_framework() -> define_key(keys.keybinds["cameraToggle"].first.get_name(), "cameraToggle", &toggle, NULL);
	window -> get_panda_framework() -> define_key(keys.keybinds["use"].first.get_name(), "use", &onMouse1, &blankTex);
	window -> get_panda_framework() -> define_key(keys.keybinds["pickup"].first.get_name(), "pickup", &onE, NULL);
	window -> get_panda_framework() -> define_key(keys.keybinds["reload"].first.get_name(), "reload", &onR, NULL);
	window -> get_panda_framework() -> define_key(keys.keybinds["drop"].first.get_name(), "drop", &drop, &blankTex);

	window -> get_panda_framework() -> define_key("h", "hide_arms", hide_arms, NULL);

	keys.wildKeys["menu"] = &menu;
	keys.wildKeys["jump"] = &jump;
	keys.wildKeys["cameraToggle"] = &toggle;
	keys.wildKeys["use"] = &onMouse1;
	keys.wildKeys["pickup"] = &onE;
	keys.wildKeys["reload"] = &onR;
	keys.wildKeys["drop"] = &drop;


	window -> get_panda_framework() -> define_key(QuitButton->get_click_event(MouseButton::one() ), "quit button press", &sys_exit, QuitButton);
	window -> get_panda_framework() -> define_key(HitTogButton->get_click_event(MouseButton::one() ), "Hit button press", &toggleHitBox, HitTogButton);
	window -> get_panda_framework() -> define_key(DoubleTogButton->get_click_event(MouseButton::one() ), "Double button press", &toggleDoubleJump, DoubleTogButton);
	window -> get_panda_framework() -> define_key(OptionTogButton->get_click_event(MouseButton::one() ), "Option button press", &toggleOptionMenu, OptionTogButton);
	

	
	window -> get_panda_framework() -> define_key(InvButton1->get_click_event(MouseButton::one() ), "Inventory slot press", &invPress, &blankTex);
	window -> get_panda_framework() -> define_key(InvButton2->get_click_event(MouseButton::one() ), "Inventory slot press", &invPress, &blankTex);
	window -> get_panda_framework() -> define_key(InvButton3->get_click_event(MouseButton::one() ), "Inventory slot press", &invPress, &blankTex);
	
	
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	NNS.hide();
	// Start the loop / gameoptionMe
	//Thread *current_thread = Thread::get_current_thread();
	world.init();
	world.tickCount=0;
	
	player.health=50;
	int temptickcount=0;

	world.gameSounds.background1->set_loop(true);
	world.gameSounds.background1->play();
	while(framework.do_frame(current_thread))
	{
		if(temptickcount<=2){
			temptickcount++;
		}
		// Things to do every frame
		// Keybinds should not go here.
		if (world.menuStatus==0)
		{
			player.volumeNodePath.show();
			player.weightNodePath.show();
			//Main Game
			player.handDisplay.show();
			
			world.get_keys(mouseWatcher, keys.keybinds); // updates keybinds held status . THIS SHOULD BE DONE FIRST
			world.look(window);
			world.move(keys.keybinds);
			

			if(temptickcount>=2){
				world.tick();
			}

			if (player.health<=0){
				player.handDisplay.set_texture(*(static_cast<PT(Texture)*>(&blankTex)));
				player.death(itms,&entityModels);
			}
			
			
			if (player.mainHand!=NULL){
				if (player.mainHand->type=='g'){
					if (player.mainHand->firerate>1 && (world.tickCount%(int)(30-player.mainHand->firerate))==0){
						if (mouseWatcher -> is_button_down((keys.keybinds["use"]).first)){
							onMouse1(NULL,&blankTex);
						}
					}
				}
			}
			
			HealthBar->set_value(player.health);
			WaterBar->set_value(player.water);
			FoodBar->set_value(player.food);
			Bars.show();
			
			
			
			world.draw();
			
			
		}
		else if(world.menuStatus==1){
			player.volumeNodePath.hide();
			player.weightNodePath.hide();
			player.ammoNodePath.hide();
			player.ammoNodePath2.hide();
			Bars.hide();
		}
		else{
			player.handDisplay.hide();
			player.volumeNodePath.hide();
			player.weightNodePath.hide();
			player.ammoNodePath.hide();
			player.ammoNodePath2.hide();
			Bars.hide();
		}
		/*else if (world.menuStatus!=0){
			//pause menu
			Bars.hide();
			
		}*/
		
		world.dt = globalClock -> get_real_time() - world.preTime;
		world.preTime = globalClock -> get_real_time();
		
		calc_inv(InvButton1,InvButton2,InvButton3,&blankTex);
		
		// Step the interval manager
		CIntervalManager::get_global_ptr() -> step();
	}
	// Once the game is finished, close everything
	framework.close_framework();
	return (0);
}


void sys_exit(const Event* eventPtr, void* dataPtr){
	exit(0);
}

void jump(const Event* eventPtr, void* dataPtr){
	if (world.menuStatus==0){
		cout<<player.coll_grav->get_airborne_height()<<endl;
		if(player.doublejump || player.coll_grav->get_airborne_height()<2.0)
		{
			world.gameSounds.femaleGrunt7->play();
			if (player.doublejump){
				player.coll_grav->add_velocity(25.0);
			}
			else{
				player.coll_grav->set_velocity(25.0);
			}
		}
		world.tickCount=121;
		
		
	}
}

void toggle(const Event* eventPtr, void* dataPtr){
	if(world.menuStatus==0){
		player.mode = 1 - player.mode;
	
		if (player.arms!=NULL){
			if (player.arms_shown) {
				player.arms->show();
			}
			else{
				player.arms->hide();
				player.pistol_arms.hide();
				player.bat_arms.hide();
				player.ak_arms.hide();
			}
		}
	}
}

void toggleHitBox(const Event* eventPtr, void* dataPtr){
	if (player.hitbox){
		player.hitbox=false;
	}
	else{
		player.hitbox=true;
	}
}

void toggleDoubleJump(const Event* eventPtr, void* dataPtr){
	if (player.doublejump){
		player.doublejump=false;
	}
	else{
		player.doublejump=true;
	}
}

void toggleOptionMenu(const Event* eventPtr, void* dataPtr){
	world.menuOption();
}

void invPress(const Event* eventPtr, void* dataPtr){
	int si=getMenuSliderInd();
	int t=0;
	string tag = keys.buttonIndex[eventPtr->get_name()]->get_name();
	if(tag == "InvButton2"){
		t=1;
	}
	else if(tag == "InvButton3"){
		t=2;
	}
	
	player.handInd=(si+t);
	if ((int)player.inventory.size()>t){
		player.mainHand=player.inventory[si+t];
		player.handDisplay.set_texture(player.inventory[si+t]->imgTex);
	}
	else{
		player.mainHand=NULL;
		player.handDisplay.set_texture(*(static_cast<PT(Texture)*>(dataPtr)));
	}
}

void hide_arms(const Event* eventPtr, void* dataPtr){
	player.arms_shown = !player.arms_shown;
	if (player.arms!=NULL){
		if (player.arms_shown) {
			player.arms->show();
		}
		else {
			player.arms->hide();
		}
	}
	
}

void rebindButton(const Event* eventPtr, void* dataPtr){
	MouseWatcher* mouseWatcher = (MouseWatcher*)window -> get_mouse().node();
	string tag = keys.buttonIndex[eventPtr->get_name()]->get_name();
	for (auto i: keys.keybindItems){
		if (tag == ("Bind"+i)){
			string oldKey = keys.keybinds[i].first.get_name();
			for (auto k: keys.allKeys){
				if (mouseWatcher-> is_button_down(k)){
					keys.keybinds[i].first = k;
					keys.buttonIndex[eventPtr->get_name()] -> setup(i+":"+ k.get_name());
					for (auto j: keys.wildKeys){
						if (i==(j.first)){
							window -> get_panda_framework() -> define_key(oldKey, "NULL", &jump, NULL);
							window -> get_panda_framework() -> define_key(k.get_name(), i, keys.wildKeys[i], NULL);
							return;
						}
					}
					return;
				}
			}
		}
	}
}

void menu(const Event* eventPtr, void* dataPtr){
	world.menu();
}

void drop(const Event* eventPtr, void* dataPtr){
	if (world.menuStatus==0){
		if(player.mainHand==NULL){
			cout<<"empty"<<endl;
		}
		else{
			player.drop(player.handInd,itms,&gameModels);
			player.arms=&player.empty_arms;
			player.mainHand=NULL;
			player.handDisplay.set_texture(*(static_cast<PT(Texture)*>(dataPtr)));
		}
	}
}

void onE(const Event* eventPtr, void* dataPtr){
	if(world.menuStatus==0){
		player.qtrav_shoot.traverse(window -> get_render());
		if (player.qcoll_shoot -> get_num_entries() > 0){
			if (player.qcoll_shoot -> get_entry(0) ->get_into_node()->get_name()=="Coll_Sphere"){
				player.qcoll_shoot -> sort_entries();
				player.pick_up(player.qcoll_shoot -> get_entry(0) -> get_into_node(), itms);
			}
		}
		else{
			float x,y,d = 0.0;
			for (unsigned int i=0;i<itms.size();i++){
				x=itms[i]->model.get_x()-player.model.get_x();
				y=itms[i]->model.get_y()-player.model.get_y();
				d=sqrt(pow(x,2)+pow(y,2));
				if(d<20){
					player.pick_up(itms[i]-> sphereModel.node(), itms);
					break;
				}
			}
		}
	}
}

void onR(const Event* eventPtr, void* dataPtr){
	if (player.mainHand!=NULL && world.menuStatus==0){
		if (player.mainHand->type=='g'){
			if (player.mainHand->tot_ammo-(player.mainHand->max_amount-player.mainHand->amount)>0){
				player.mainHand->tot_ammo-=(player.mainHand->max_amount-player.mainHand->amount);
				player.mainHand->amount=player.mainHand->max_amount;
				if (player.mainHand->id==10){
					world.gameSounds.akReloadSound->play();
				}
				else if (player.mainHand->id==0){
					world.gameSounds.pistolReloadSound->play();
				}
				
			}
			else if(player.mainHand->tot_ammo > 0){
				player.mainHand->amount+=player.mainHand->tot_ammo;
				player.mainHand->tot_ammo=0;
				if (player.mainHand->id==10){
					world.gameSounds.akReloadSound->play();
				}
				else if (player.mainHand->id==0){
					world.gameSounds.pistolReloadSound->play();
				}
			}
		}
	}
}

int getMenuSliderInd(){
	return (round(Slider->get_value()*player.inventory.size()));
}

void calc_inv(PGButton* fs,PGButton* ss,PGButton* ts,PT(Texture)* bt){
	if (world.menuStatus==1){
	
		PGFrameStyle sb=fs->get_frame_style(0); // frame_style(0): ready state
		sb.set_type(PGFrameStyle::T_flat);
		sb.set_texture(*bt);    
		fs->set_frame_style(0,sb);
		fs->set_frame_style(1,sb);
		fs->set_frame_style(2,sb);
		fs->set_frame_style(3,sb);
		ss->set_frame_style(0,sb);
		ss->set_frame_style(1,sb);
		ss->set_frame_style(2,sb);
		ss->set_frame_style(3,sb);
		ts->set_frame_style(0,sb);
		ts->set_frame_style(1,sb);
		ts->set_frame_style(2,sb);
		ts->set_frame_style(3,sb);
		
		
		int si=getMenuSliderInd();
		
		
		
		
		if ((int)player.inventory.size()>si){
			
			PGFrameStyle sf=fs->get_frame_style(0); // frame_style(0): ready state
			sf.set_type(PGFrameStyle::T_flat);
			sf.set_texture(player.inventory[si]->imgTex);    
			fs->set_frame_style(0,sf);
			fs->set_frame_style(1,sf);
			fs->set_frame_style(2,sf);
			fs->set_frame_style(3,sf);
			
			if ((int)player.inventory.size()>si+1){
				//player.inventory[si+1]->imgNode.show();
				PGFrameStyle tf=ss->get_frame_style(0); // frame_style(0): ready state
				tf.set_type(PGFrameStyle::T_flat);
				tf.set_texture(player.inventory[si+1]->imgTex);    
				ss->set_frame_style(0,tf);
				ss->set_frame_style(1,tf);
				ss->set_frame_style(2,tf);
				ss->set_frame_style(3,tf);
			
				if ((int)player.inventory.size()>si+2){
					//player.inventory[si+2]->imgNode.show();
					PGFrameStyle tf=ts->get_frame_style(0); // frame_style(0): ready state
					tf.set_type(PGFrameStyle::T_flat);
					tf.set_texture(player.inventory[si+2]->imgTex);    
					ts->set_frame_style(0,tf);
					ts->set_frame_style(1,tf);
					ts->set_frame_style(2,tf);
					ts->set_frame_style(3,tf);
				}
			}
		}
		
		
		
		
	}
}

void onMouse1(const Event* eventPtr, void* dataPtr){
	if (world.menuStatus==0 && player.mode==0){
		if (player.mainHand!=NULL){
			if (player.mainHand->type=='c'){		//Consumable item
				player.mainHand->action1();
		
				player.mainHand=NULL;
				player.handDisplay.set_texture(*(static_cast<PT(Texture)*>(dataPtr)));
			}
			
			else if (player.mainHand->type=='g'){		//Gun
				if (player.mainHand->amount>0){
					int frameGunCount=-1;
					int dmg=0;
					float rngM=1.0;
					
					if (player.mainHand->id==0){
						frameGunCount = player.pistol_collection.get_frame()-player.pistol_collection.get_num_frames();			
						dmg=10;
						rngM=1.05;
					}
					else if(player.mainHand->id==2){
						frameGunCount = player.bat_collection.get_frame()-player.bat_collection.get_num_frames();
						dmg=10;
						rngM=1.5;
					}
					else if(player.mainHand->id==10){
						frameGunCount = player.ak_collection.get_frame()-player.ak_collection.get_num_frames();
						dmg=15;
						rngM=1.005;
					}
					if (eventPtr==NULL || frameGunCount==-1){
						player.mainHand->amount--;		//this is ammo
						
						/*		//scream while firing ak
						if(player.mainHand->id==10&&eventPtr!=NULL){
							world.gameSounds.scream4->play();
						}
						*/
						
						player.qtrav_shoot.traverse(window -> get_render());
						if (player.qcoll_shoot -> get_num_entries() > 0) 
						{
							//HIT
							player.qcoll_shoot -> sort_entries();
							world.gameSounds.bulletHitSound1->play();
							
							//cout << player.qcoll_shoot -> get_entry(0) -> get_into_node() -> get_name() << " hit!" << endl;
							
							if (player.qcoll_shoot -> get_entry(0) ->get_into_node()->get_name()=="Enemy_sphere"){
								
								// WE NEED MAPS LOL WITH TAGS
								for (unsigned int i = 0; i < enems.size(); i++){
									
									//Don't delete these comments
									
									//cout << "i: " << i << endl;
									//cout << "enems[i]: " << enems[i] << endl;
									//cout << "enems[i] -> model: " << enems[i] -> sphereModel << endl;
									//cout << "enems[i] -> model child: " << enems[i] -> sphereModel.get_child(0) << endl;
									//if (enems[i]->sphereModel.get_child(0).is_empty()) cout << "Ohes noes!" << endl;
									
									
									if (enems[i]->sphereModel.node()==player.qcoll_shoot -> get_entry(0) ->get_into_node()){
										
										float xd,yd,zd,td;
										
										xd=enems[i]->model.get_x();
										yd=enems[i]->model.get_y();
										zd=enems[i]->model.get_z();
										
										xd=xd-player.model.get_x();
										yd=yd-player.model.get_y();
										zd=zd-player.model.get_z();
										
										xd= pow(xd*xd,0.5);
										yd= pow(yd*yd,0.5);
										zd= pow(zd*zd,0.5);
										
										td=pow(pow(pow((xd*xd)+(yd*yd),0.5),2)+(zd*zd),0.5);
										dmg=((dmg/(pow(td,rngM)/10.0))-1);
										
										dmg=dmg*2;
										
										dmg=dmg*(1+(player.kills/50)+(player.xp/1000));
										
										enems[i]->health-=dmg;
										//cout<<enems[i]->health<<endl;
										
										if (dmg>0){
											enems[i]->tint=1.0;
										}
										
										float ran=rand()/(float)RAND_MAX;
										if(ran>(2.0/3.0)){
											world.gameSounds.Snarl->play();
										}
										else if(ran>(1.0/3.0)){
											world.gameSounds.Snarl2->play();
										}
										else{
											world.gameSounds.hiss->play();
										}
										
									}
								}
							}
							else if (player.qcoll_shoot -> get_entry(0) ->get_into_node()->get_name()=="Coll_Sphere"){
								//hit item
								// WE NEED MAPS LOL WITH TAGS
								cout<<"hit"<<endl;
								for (unsigned int h = 0; h < itms.size(); h++){
									if (itms[h]->sphereModel.node()==player.qcoll_shoot -> get_entry(0) ->get_into_node()){
										float xd,yd,zd,td;
										
										xd=itms[h]->model.get_x();
										yd=itms[h]->model.get_y();
										zd=itms[h]->model.get_z();
										
										xd=xd-player.model.get_x();
										yd=yd-player.model.get_y();
										zd=zd-player.model.get_z();
				
										td=pow(pow(pow((xd*xd)+(yd*yd),0.5),2)+(zd*zd),0.5);
										dmg=(dmg/(pow(td,rngM)/100.0));
										itms[h]->accel(dmg*xd/100.0,dmg*yd/100.0,dmg*zd/100.0);
										
									}
								}
								
							}
							cout<<player.qcoll_shoot -> get_entry(0) ->get_into_node()->get_name()<<endl;
							
		
						}
						else{
							//MISS
							if (player.mainHand->id==10 || player.mainHand->id==0){
								float ran=rand()/(float)RAND_MAX;
								ran-=0.5;
								ran*=2;
								
								if (ran<=-0.66){
									world.gameSounds.ricochetSound1->set_balance(ran);
									world.gameSounds.ricochetSound1->play();
								}
								else if (ran<=-0.33){
									world.gameSounds.ricochetSound2->set_balance(ran);
									world.gameSounds.ricochetSound2->play();
								}
								else if (ran<=0.0){
									world.gameSounds.ricochetSound3->set_balance(ran);
									world.gameSounds.ricochetSound3->play();
								}
								else if (ran>=0.66){
									world.gameSounds.ricochetSound4->set_balance(ran);
									world.gameSounds.ricochetSound4->play();
								}
								else if (ran>=0.33){
									world.gameSounds.ricochetSound5->set_balance(ran);
									world.gameSounds.ricochetSound5->play();
								}
								else {
									world.gameSounds.ricochetSound6->set_balance(ran);
									world.gameSounds.ricochetSound6->play();
								}
								
								
								
							}
							
						}
						
						if (player.mainHand->id==10){
							world.gameSounds.akFireSound->play();
						}
						else if (player.mainHand->id==0){
							world.gameSounds.pistolFireSound->play();
						}
						else if (player.mainHand->id==2){
							world.gameSounds.batFireSound->play();
						}
						
						
						
						player.play_anim();
						
					
					
						player.recoil_frames+=(int)((player.mainHand->firerate+1) / 8.0);
					
						if (player.mainHand->firerate==1.0){
							player.recoil_mult=0.4;
							player.recoil_frames+=5;
						}
						else{
							player.recoil_mult=player.mainHand->firerate / 29.0;
						}
					}
				}
				else{
					if (player.mainHand->id==10){
						world.gameSounds.akEmptySound->play();
					}
					else if (player.mainHand->id==0){
						world.gameSounds.pistolEmptySound->play();
					}
				}
			}
		}
	}
}
