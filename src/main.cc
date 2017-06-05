/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
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
#include "level.hpp"
#include "global.hpp"
#include "ourloader.hpp"

#include "load_prc_file.h"
#include "configVariableFilename.h"



AsyncTaskManager* taskMgr = AsyncTaskManager::get_global_ptr(); 
ClockObject* globalClock = ClockObject::get_global_clock();
Filename mydir = ((Filename)ExecutionEnvironment::get_binary_name()).get_dirname()+"/";
vector<GameObject*> objs;
vector<Enemy*> enems;
vector<Item*> itms;
vector<StaticObject*> stats;
Player player;
Keys keys;
World world;
NodePath gameModels;
NodePath startMenuItems;
NodePath menuItems;
NodePath optionMenuItems;
NodePath deathMenuItems;
NodePath staticModels;
PT(PGSliderBar) Slider=new PGSliderBar("MySliderBar");;
PT(PGSliderBar) mouseSlider=new PGSliderBar("mouseSliderBar");;

vector<Level*> gameLevels;

OurLoader gameloader;

int scene;

WindowFramework* window;

// Forward declared functions
void startGame(const Event* eventPtr, void* dataPtr);
void loadGame(const Event* eventPtr, void* dataPtr);
void sys_exit(const Event* eventPtr, void* dataPtr);
void toggle(const Event* eventPtr, void* dataPtr);
void toggleHitBox(const Event* eventPtr, void* dataPtr);
void toggleDoubleJump(const Event* eventPtr, void* dataPtr);
void toggleOptionMenu(const Event* eventPtr, void* dataPtr);
void toggleFPS(const Event* eventPtr, void* dataPtr);
void invHotkey(const Event* eventPtr, void* dataPtr);
void invPress(const Event* eventPtr, void* dataPtr);
void jump(const Event* eventPtr, void* dataPtr);
void rebindButton(const Event* eventPtr, void* dataPtr);
void rebindMouseSens(const Event* eventPtr, void* dataPtr);
void menu(const Event* eventPtr, void* dataPtr);
void spiderClick(const Event* eventPtr, void* dataPtr);
void hide_arms(const Event* eventPtr, void* dataPtr);
void onMouse1(const Event* eventPtr, void* dataPtr);
void onE(const Event* eventPtr, void* dataPtr);
void onR(const Event* eventPtr, void* dataPtr);
void drop(const Event* eventPtr, void* dataPtr);
int getMenuSliderInd();
void calc_inv(PGButton* fs,PGButton* ss,PGButton* ts,PT(Texture)* bt);

void makeAmmobox(int x, int y, int z,NodePath* parentNode);
void makeBat(int x, int y, int z,NodePath* parentNode);
void makeCheese(int x, int y, int z,NodePath* parentNode);
void makePill(int x, int y, int z,NodePath* parentNode);
void makePistol(int x, int y, int z,NodePath* parentNode);
void makeKalashnikov(int x, int y, int z,NodePath* parentNode);
void makeNegev(int x, int y, int z,NodePath* parentNode);
void makeSpider(int x, int y, int z,NodePath* parentNode);
void makeBandit(int x, int y, int z,NodePath* parentNode);
void makeWaterbottle(int x, int y, int z,NodePath* parentNode);

void doStep(PandaFramework* pf,Thread* current_thread);



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
	framework.set_window_title("Iris alpha");
	
	
	world.gameSounds.setup(mydir);
	
	
	
	// Set up window
	window = framework.open_window();
	window -> enable_keyboard();
	
	props = window -> get_graphics_window() -> get_properties();
	props.set_cursor_hidden(false);
	props.set_mouse_mode(WindowProperties::M_absolute);

	window -> get_graphics_window() -> request_properties(props);
	window -> get_display_region_3d() -> set_clear_color( LColor(0.53,0.81,0.92, 1) );


	// Create a mousewatcher (needed to check for key held)
	mouseWatcher = (MouseWatcher*)window -> get_mouse().node();


	//loadscreen
	float xs = -(window -> get_graphics_window()->get_x_size() / (float)window ->get_graphics_window()->get_y_size());
	
	NodePath blank_plane = window->load_model(framework.get_models(),mydir+"Assets/plane.egg");
	blank_plane.set_transparency(TransparencyAttrib::M_alpha, 1);
	

	//////////////////////////////////////////////
	
	//Loading screen

	PT(Texture) wts;
	wts=TexturePool::load_texture(mydir+"Assets/loadscreen.png");
	
	CardMaker cm2("cardMaker");
	PT(PandaNode) readyCard2 = cm2.generate();
	NodePath NNS(readyCard2);
	
	NNS = window -> get_aspect_2d().attach_new_node(readyCard2);
	NNS.set_transparency(TransparencyAttrib::M_alpha, 1);
	NNS.set_scale(2.0);
	NNS.set_pos(xs,0,-1);
	//NNS.show();
	NNS.set_texture(wts);
	NNS.hide();
	
	NodePath loadanim=window->load_model(framework.get_models(),mydir+"Assets/INSECT/insect.egg");
	loadanim.reparent_to(window->get_render());
	loadanim.set_pos(0,30,-1.5);
	loadanim.show();
	
	
	AnimControlCollection load_anim_collection;
	NodePath loadnode = window->load_model(loadanim, mydir + "Assets/INSECT/insect-Move.egg");
	auto_bind(loadanim.node(), load_anim_collection);
	PT(AnimControl) animPtrLoad = load_anim_collection.get_anim(0);
	load_anim_collection.store_anim(animPtrLoad, "load");
	loadnode.detach_node();
	load_anim_collection.loop("load",1);
	
	
	Thread *current_thread = Thread::get_current_thread();
	
	
	/*
	
	Thread *current_thread = Thread::get_current_thread();
	if(framework.do_frame(current_thread))
	{
		framework.get_graphics_engine()->render_frame();
		CIntervalManager::get_global_ptr() -> step();
	}
	
	*/
	doStep(&framework,Thread::get_current_thread());

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
	
	doStep(&framework,Thread::get_current_thread());

	// Create a dummy node to attach things to. Does not affect anything,
	// but makes it easier to hide all the game nodes at once.
	gameModels = window -> get_render().attach_new_node("All game models");
		staticModels = gameModels.attach_new_node("All Static (Terrain)");
		NodePath entityModels = gameModels.attach_new_node("All Entities");
			NodePath shootableModels = entityModels.attach_new_node("All Shootables");
			NodePath itemModels = entityModels.attach_new_node("All items");
			NodePath pushableModels = entityModels.attach_new_node("All pushables");
			NodePath interactModels = entityModels.attach_new_node("All interactables");
	startMenuItems = window -> get_aspect_2d().attach_new_node("Start Menu Buttons");
	startMenuItems.set_transparency(TransparencyAttrib::M_alpha, 1);
	menuItems = window -> get_aspect_2d().attach_new_node("Buttons and such");
	menuItems.set_transparency(TransparencyAttrib::M_alpha, 1);
	optionMenuItems = window -> get_aspect_2d().attach_new_node("Option Menu Buttons");
	optionMenuItems.set_transparency(TransparencyAttrib::M_alpha, 1);
	deathMenuItems = window -> get_aspect_2d().attach_new_node("Death Menu Buttons");
	deathMenuItems.set_transparency(TransparencyAttrib::M_alpha, 1);
	
	doStep(&framework,Thread::get_current_thread());
	
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
	
	doStep(&framework,Thread::get_current_thread());


	NodePath Bars = window -> get_pixel_2d().attach_new_node("Status Bars");
	Bars.set_transparency(TransparencyAttrib::M_alpha, 1);
	Bars.reparent_to(window->get_aspect_2d());
	Bars.hide();
	



	// Set up player camera and model
	player.set_up(&gameModels,window,&framework,mydir,false);
	
	
	doStep(&framework,Thread::get_current_thread());
	
	
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
		doStep(&framework,Thread::get_current_thread());
		//StaticObject(int xx,int yy,int zz, std::string fn,NodePath* parent,WindowFramework* w,PandaFramework* pf,float scale=1){
		stats.push_back(new StaticObject(-8,42,0,mydir+x,&gameModels,window,&framework,0,0,0,2.6));
		stats.back()->model.hide();
	}
	PT(CollisionNode) c_Node;
	//ptrav.set_respect_prev_transform(true);

	
	player.coll_set_up();
	player.model.set_pos(player.model.get_x(),player.model.get_y(),player.model.get_z()+25);

	doStep(&framework,Thread::get_current_thread());

	// Start Menu items
	PGButton* StartGameButton;
	PGButton* loadGameButton;
	PGButton* realQuitButton;
	PGButton* OptionTogButton3;
	startMenuItems.hide();


	/*
	PT(Texture) tex_hellothere;
	CardMaker cm_hellothere("cardMaker");
	PT(PandaNode) rc_hellothere = cm_hellothere.generate();
	NodePath nd_hellothere(rc_hellothere);
	nd_hellothere = window -> get_aspect_2d().attach_new_node(rc_hellothere);
	nd_hellothere.set_transparency(TransparencyAttrib::M_alpha, 1);
	nd_hellothere.set_pos(-0.5, 0,-0.5);
	nd_hellothere.reparent_to(startMenuItems);
	nd_hellothere.set_scale(window->get_render(),1);
	tex_hellothere=TexturePool::load_texture(mydir+"Assets/Hellothere.jpg");
	nd_hellothere.set_texture(tex_hellothere);
	*/
	NodePath nd_hellothere=window->load_model(framework.get_models(),mydir+"Assets/Iris/Iris.egg");
	nd_hellothere.reparent_to(window->get_render());
	nd_hellothere.set_pos(0,20,-1.0);
	nd_hellothere.set_hpr(180,0,0);
	
	nd_hellothere.hide();
	
	
	AnimControlCollection start_anim_collection;
	NodePath loadnode2 = window->load_model(nd_hellothere, mydir + "Assets/Iris/Iris-Idle.egg");
	auto_bind(nd_hellothere.node(), start_anim_collection);
	PT(AnimControl) animPtrLoad2 = start_anim_collection.get_anim(0);
	start_anim_collection.store_anim(animPtrLoad2, "load");
	loadnode2.detach_node();
	start_anim_collection.loop("load",1);
	
	doStep(&framework,Thread::get_current_thread());


	StartGameButton = new PGButton("StartGameButton");
	StartGameButton -> setup("Start Game");
	NodePath bnp = window -> get_pixel_2d().attach_new_node(StartGameButton);
	bnp.set_scale(0.1);
	bnp.set_pos(xs + 0.1, 0, 0.85);
	bnp.reparent_to(startMenuItems);
	keys.buttonIndex["click-mouse1-"+StartGameButton->get_id()] = StartGameButton;

	loadGameButton = new PGButton("loadGameButton");
	loadGameButton -> setup("Load Game");
	NodePath bnp2 = window -> get_pixel_2d().attach_new_node(loadGameButton);
	bnp2.set_scale(0.1);
	bnp2.set_pos(xs + 0.1, 0, 0.65);
	bnp2.reparent_to(startMenuItems);
	keys.buttonIndex["click-mouse1-"+loadGameButton->get_id()] = loadGameButton;

	doStep(&framework,Thread::get_current_thread());
	
	realQuitButton = new PGButton("QuitButton");
	realQuitButton -> setup("Quit");
	NodePath defbutNPk = window -> get_pixel_2d().attach_new_node(realQuitButton);
	defbutNPk.set_scale(0.1);
	defbutNPk.set_pos(xs+0.1,0, 0.25);
	defbutNPk.reparent_to(startMenuItems);
	keys.buttonIndex["click-mouse1-"+realQuitButton->get_id()] = realQuitButton;

	OptionTogButton3 = new PGButton("OptionTogButton");
	OptionTogButton3 -> setup("Toggle Option Menu");
	NodePath defbutNP7 = window -> get_pixel_2d().attach_new_node(OptionTogButton3);
	defbutNP7.set_scale(0.1);
	defbutNP7.set_pos(xs + 0.1, 0, 0.45);
	defbutNP7.reparent_to(startMenuItems);
	keys.buttonIndex["click-mouse1-"+OptionTogButton3->get_id()] = OptionTogButton3;

	doStep(&framework,Thread::get_current_thread());
	


	// Menu items
	PT(PGButton) QuitButton;
	PGButton* HitTogButton;
	PGButton* DoubleTogButton;
	PGButton* OptionTogButton;
	menuItems.hide();


	QuitButton = new PGButton("MenuButton");
	QuitButton -> setup("Main Menu");
	NodePath defbutNP = window -> get_pixel_2d().attach_new_node(QuitButton);
	defbutNP.set_scale(0.1);
	defbutNP.set_pos(xs+0.1,0, 0.25);
	defbutNP.reparent_to(menuItems);
	keys.buttonIndex["click-mouse1-"+QuitButton->get_id()] = QuitButton;

	HitTogButton = new PGButton("HitTogButton");
	HitTogButton -> setup("Toggle Hit Boxes");
	NodePath defbutNP3 = window -> get_pixel_2d().attach_new_node(HitTogButton);
	defbutNP3.set_scale(0.1);
	defbutNP3.set_pos(xs + 0.1, 0, 0.65);
	defbutNP3.reparent_to(menuItems);
	keys.buttonIndex["click-mouse1-"+HitTogButton->get_id()] = HitTogButton;

	DoubleTogButton = new PGButton("DoubleTogButton");
	DoubleTogButton -> setup("Toggle Double Jump");
	NodePath defbutNP4 = window -> get_pixel_2d().attach_new_node(DoubleTogButton);
	defbutNP4.set_scale(0.1);
	defbutNP4.set_pos(xs + 0.1, 0, 0.45);
	defbutNP4.reparent_to(menuItems);
	keys.buttonIndex["click-mouse1-"+DoubleTogButton->get_id()] = DoubleTogButton;

	OptionTogButton = new PGButton("OptionTogButton");
	OptionTogButton -> setup("Toggle Option Menu");
	NodePath defbutNP5 = window -> get_pixel_2d().attach_new_node(OptionTogButton);
	defbutNP5.set_scale(0.1);
	defbutNP5.set_pos(xs + 0.1, 0, 0.85);
	defbutNP5.reparent_to(menuItems);
	doStep(&framework,Thread::get_current_thread());



	//Option Menu Items
	PGButton* OptionTogButton2;
	PGButton* mouseSensBut;
	optionMenuItems.hide();


	OptionTogButton2 = new PGButton("OptionTogButton");
	OptionTogButton2 -> setup("Toggle Option Menu");
	NodePath defbutNP6 = window -> get_pixel_2d().attach_new_node(OptionTogButton2);
	defbutNP6.set_scale(0.1);
	defbutNP6.set_pos(xs + 0.1, 0, 0.85);
	defbutNP6.reparent_to(optionMenuItems);

	for (unsigned int i=0; i<keys.keybindItems.size(); i++){
		doStep(&framework,Thread::get_current_thread());
		PGButton* butt;
		butt = new PGButton("Bind"+keys.keybindItems.at(i));
		butt -> setup(keys.keybindItems.at(i)+":"+ keys.keybinds[keys.keybindItems.at(i)].first.get_name());
		NodePath BindNode1 = window -> get_pixel_2d().attach_new_node(butt);
		BindNode1.set_scale(0.1);
		BindNode1.set_pos(xs+0.1*(i/11*8+1),0,0.85-(.15*(i%11+1)));
		BindNode1.reparent_to(optionMenuItems);
		window -> get_panda_framework() -> define_key(butt->get_click_event(keys.keybinds["use"].first ), "Bind "+keys.keybindItems.at(i)+"Press",&rebindButton, butt);
		keys.keybindMenu.push_back(butt);
		keys.buttonIndex["click-mouse1-"+butt->get_id()] = butt;
	}

	doStep(&framework,Thread::get_current_thread());
	mouseSlider->setup_scroll_bar(true,1.5,0.5,0); // 'rail' properties
	mouseSlider->set_range(0,1);
	mouseSlider->set_value(0);
	 
	mouseSlider->setup_slider(true,1,0.05,false);
	NodePath mouseSliderNP = window->get_aspect_2d().attach_new_node(mouseSlider);
	mouseSliderNP.set_pos(xs+2.5,0,.25);
	mouseSliderNP.reparent_to(optionMenuItems);

	mouseSensBut = new PGButton("mouseSensBut");
	mouseSensBut -> setup("Change mouse sens");
	NodePath defbutNPmous = window -> get_pixel_2d().attach_new_node(mouseSensBut);
	defbutNPmous.set_scale(0.1);
	defbutNPmous.set_pos(xs+0.1*(17/8*8+1),0, 0.85);
	defbutNPmous.reparent_to(optionMenuItems);


	//Death Menu Items
	PGButton* respawnButton;
	PGButton* restartButton;
	deathMenuItems.hide();


	respawnButton = new PGButton("respawnButton");
	respawnButton -> setup("Respawn");
	NodePath bresp = window -> get_pixel_2d().attach_new_node(respawnButton);
	bresp.set_scale(0.1);
	bresp.set_pos(xs + 0.1, 0, 0.85);
	bresp.reparent_to(deathMenuItems);
	keys.buttonIndex["click-mouse1-"+respawnButton->get_id()] = respawnButton;

	restartButton = new PGButton("restartButton");
	restartButton -> setup("Main Menu");
	NodePath brest = window -> get_pixel_2d().attach_new_node(restartButton);
	brest.set_scale(0.1);
	brest.set_pos(xs + 0.1, 0, 0.65);
	brest.reparent_to(deathMenuItems);
	keys.buttonIndex["click-mouse1-"+restartButton->get_id()] = restartButton;

	//Death message
	PT(TextNode) deathNode = new TextNode("deathNode");
	NodePath deathMessage= window->get_aspect_2d().attach_new_node(deathNode);
	deathMessage.set_scale(0.2);
	deathMessage.set_pos(xs+0.1,0, 0.5);
	deathMessage.hide();



	//Status bar items
	PT(Texture) redTex=TexturePool::load_texture(mydir+"Assets/Red.png");
	PT(Texture) greenTex=TexturePool::load_texture(mydir+"Assets/Blue.png");
	PT(Texture) blueTex=TexturePool::load_texture(mydir+"Assets/Green.png");

	doStep(&framework,Thread::get_current_thread());
	
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
	
	doStep(&framework,Thread::get_current_thread());
	
	PGWaitBar* WaterBar;
	WaterBar = new PGWaitBar("WaterBar");
	WaterBar->setup(10.0,0.5,100.0);
	NodePath WaterNode = window -> get_pixel_2d().attach_new_node(WaterBar);
	WaterNode.set_scale(0.1);
	WaterNode.set_pos(xs + 2.1, 0, -0.94);
	WaterNode.show();
	WaterNode.reparent_to(Bars);
	WaterNode.set_texture(greenTex);
	
	doStep(&framework,Thread::get_current_thread());

	//HUD info items
	player.ammoNode = new TextNode("ammoNode");
	player.ammoNode->set_text("0");
	player.ammoNodePath = window->get_aspect_2d().attach_new_node(player.ammoNode);
	player.ammoNodePath.set_scale(0.07);
	player.ammoNodePath.set_pos(xs+0.5,0, -0.9);
	player.ammoNodePath.hide();

	doStep(&framework,Thread::get_current_thread());

	player.ammoNode2 = new TextNode("ammoNode2");
	player.ammoNode2->set_text("0");
	player.ammoNodePath2 = window->get_aspect_2d().attach_new_node(player.ammoNode2);
	player.ammoNodePath2.set_scale(0.04);
	player.ammoNodePath2.set_pos(xs+0.6,0, -0.9);
	player.ammoNodePath2.hide();

	doStep(&framework,Thread::get_current_thread());

	player.weightNode = new TextNode("weightNode");
	player.weightNode->set_text("0");
	player.weightNodePath = window->get_aspect_2d().attach_new_node(player.weightNode);
	player.weightNodePath.set_scale(0.07);
	player.weightNodePath.set_pos(xs+0.5,0, -0.98);
	player.weightNodePath.hide();
	
	doStep(&framework,Thread::get_current_thread());
	
	player.volumeNode = new TextNode("volumeNode");
	player.volumeNode->set_text("0");
	player.volumeNodePath = window->get_aspect_2d().attach_new_node(player.volumeNode);
	player.volumeNodePath.set_scale(0.07);
	player.volumeNodePath.set_pos(xs+0.8,0, -0.98);
	player.volumeNodePath.hide();

	PT(TextNode)fpsNode = new TextNode("fpsNode");
	fpsNode->set_text("0");
	NodePath fpsNodePath= window->get_aspect_2d().attach_new_node(fpsNode);
	fpsNodePath.set_scale(0.07);
	fpsNodePath.set_pos(xs,0, -0.98);
	fpsNodePath.hide();
	doStep(&framework,Thread::get_current_thread());



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
	
	
	NodePath defbutNPa = window->get_aspect_2d().attach_new_node(MyButton);
	defbutNPa.set_scale(0.1);
	defbutNPa.set_pos(xs+0.1,0, 0.45);
	defbutNPa.reparent_to(menuItems);
	*/
	
	//Inventory buttons

	// Setup, feeding the constructor with (bool vertical,float lenght,float width,float bevel)
	Slider->setup_scroll_bar(true,1.5,0.5,0); // 'rail' properties
	Slider->set_range(0,1);
	Slider->set_value(0);
	 
	// Setup scroll bar (the 'moving thumb button' including left and right button)
	Slider->setup_slider(true,1,0.05,false);
	NodePath SliderNP=window->get_aspect_2d().attach_new_node(Slider);
	SliderNP.set_pos(0.15,0,0);
	SliderNP.reparent_to(menuItems);
	
	doStep(&framework,Thread::get_current_thread());

	PT(Texture) blankTex=TexturePool::load_texture(mydir+"Assets/blank_slot2.png");

	//////////////////////////////////////////////

	PGButton* InvButton1;
	InvButton1 = new PGButton("InvButton1");
	InvButton1 -> setup(blank_plane);
	doStep(&framework,Thread::get_current_thread());
	NodePath invBut = window -> get_pixel_2d().attach_new_node(InvButton1);
	invBut.set_transparency(TransparencyAttrib::M_alpha, 1);
	invBut.set_tag("invBut","1");
	invBut.set_scale(0.25);
	invBut.set_pos(xs + 2, 0, 0.6);
	invBut.reparent_to(menuItems);
	//invBut.show();
	keys.buttonIndex["click-mouse1-"+InvButton1->get_id()] = InvButton1;

	//////////////////////////////////////////////
	doStep(&framework,Thread::get_current_thread());
	PGButton* InvButton2;
	InvButton2 = new PGButton("InvButton2");
	InvButton2 -> setup(blank_plane);
	
	NodePath invBut2 = window -> get_pixel_2d().attach_new_node(InvButton2);
	invBut2.set_transparency(TransparencyAttrib::M_alpha, 1);
	invBut2.set_tag("invBut","2");
	invBut2.set_scale(0.25);
	invBut2.set_pos(xs + 2, 0, 0.0);
	invBut2.reparent_to(menuItems);
	//invBut2.show();
	keys.buttonIndex["click-mouse1-"+InvButton2->get_id()] = InvButton2;

	//////////////////////////////////////////////

	PGButton* InvButton3;
	InvButton3 = new PGButton("InvButton3");
	InvButton3 -> setup(blank_plane);
	doStep(&framework,Thread::get_current_thread());
	NodePath invBut3 = window -> get_pixel_2d().attach_new_node(InvButton3);
	invBut3.set_transparency(TransparencyAttrib::M_alpha, 1);
	invBut3.set_tag("invBut","3");
	invBut3.set_scale(0.25);
	invBut3.set_pos(xs + 2, 0, -0.6);
	invBut3.reparent_to(menuItems);
	//invBut3.show();
	keys.buttonIndex["click-mouse1-"+InvButton3->get_id()] = InvButton3;

	//////////////////////////////////////////////
	doStep(&framework,Thread::get_current_thread());
	
	Level testlevel(0,0,0,5);
	
	ChangeRegion testregion(-10,10,-10,10,2,10,0);
	
	testlevel.exits.push_back(testregion);
	
	gameLevels.push_back(&testlevel);
	
	
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
	doStep(&framework,Thread::get_current_thread());
	//Hand display
	CardMaker cm("cardMaker");
	PT(PandaNode) readyCard = cm.generate();
	NodePath NN(readyCard);
	player.handDisplay=NN;
	player.handDisplay = window -> get_aspect_2d().attach_new_node(readyCard);
	player.handDisplay.set_transparency(TransparencyAttrib::M_alpha, 1);
	player.handDisplay.set_scale(0.4);
	player.handDisplay.set_pos(xs+0.1,0, -0.9);
	player.handDisplay.hide();
	player.handDisplay.set_texture(blankTex);

	doStep(&framework,Thread::get_current_thread());

	//Crosshair
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
	nd_crosshair.hide();
	
	
	
	// lambda functions are as thus:
	// [] (int a, string b, etc.) { CODE; GOES; HERE; }
	
	// define_key("event_name", "description", function, data);
	// data is a void pointer, so it can take anything.
	
	if ("hide keybinds"){
	window -> get_panda_framework() -> define_key(keys.keybinds["menu"].first.get_name(), "menu", &menu, NULL);
	keys.wildKeys["menu"] = &menu;
	keys.dataPtrs["menu"] = window;
	doStep(&framework,Thread::get_current_thread());
	window -> get_panda_framework() -> define_key(keys.keybinds["jump"].first.get_name(), "jump", &jump, NULL);
	keys.wildKeys["jump"] = &jump;
	keys.dataPtrs["jump"] = NULL;
	doStep(&framework,Thread::get_current_thread());
	window -> get_panda_framework() -> define_key(keys.keybinds["cameraToggle"].first.get_name(), "cameraToggle", &toggle, NULL);
	keys.wildKeys["cameraToggle"] = &toggle;
	keys.dataPtrs["cameraToggle"] = NULL;
	doStep(&framework,Thread::get_current_thread());
	window -> get_panda_framework() -> define_key(keys.keybinds["use"].first.get_name(), "use", &onMouse1, &blankTex);
	keys.wildKeys["use"] = &onMouse1;
	keys.dataPtrs["use"] = &blankTex;
	doStep(&framework,Thread::get_current_thread());
	window -> get_panda_framework() -> define_key(keys.keybinds["pickup"].first.get_name(), "pickup", &onE, NULL);
	keys.wildKeys["pickup"] = &onE;
	keys.dataPtrs["pickup"] = NULL;
	doStep(&framework,Thread::get_current_thread());
	window -> get_panda_framework() -> define_key(keys.keybinds["reload"].first.get_name(), "reload", &onR, NULL);
	keys.wildKeys["reload"] = &onR;
	keys.dataPtrs["reload"] = NULL;
	doStep(&framework,Thread::get_current_thread());
	window -> get_panda_framework() -> define_key(keys.keybinds["drop"].first.get_name(), "drop", &drop, &blankTex);
	keys.wildKeys["drop"] = &drop;
	keys.dataPtrs["drop"] = &blankTex;
	doStep(&framework,Thread::get_current_thread());
	window -> get_panda_framework() -> define_key(keys.keybinds["spider"].first.get_name(), "spider", &spiderClick, &shootableModels);
	keys.wildKeys["spider"] = &spiderClick;
	keys.dataPtrs["spider"] = &shootableModels;
	doStep(&framework,Thread::get_current_thread());
	window -> get_panda_framework() -> define_key(keys.keybinds["toggleFPS"].first.get_name(), "toggleFPS", &toggleFPS, NULL);
	keys.wildKeys["toggleFPS"] = &toggleFPS;
	keys.dataPtrs["toggleFPS"] = NULL;
	doStep(&framework,Thread::get_current_thread());
	
	for (int i=1; i<10; i++){
		window -> get_panda_framework() -> define_key(keys.keybinds["inv"+to_string(i)].first.get_name(), "inv"+to_string(i), &invHotkey, &blankTex);
		keys.wildKeys["inv"+to_string(i)] = &invHotkey;
		keys.dataPtrs["inv"+to_string(i)] = &blankTex;
	}

	window -> get_panda_framework() -> define_key("h", "hide_arms", hide_arms, NULL);

	window -> get_panda_framework() -> define_key(StartGameButton->get_click_event(keys.keybinds["use"].first ), "Start game button press", &startGame, NULL);
	window -> get_panda_framework() -> define_key(loadGameButton->get_click_event(keys.keybinds["use"].first ), "Load game button press", &loadGame, NULL);
	window -> get_panda_framework() -> define_key(realQuitButton->get_click_event(keys.keybinds["use"].first ), "Quit button press", &sys_exit, realQuitButton);
	//MouseButton::one()
	window -> get_panda_framework() -> define_key(QuitButton->get_click_event(keys.keybinds["use"].first ), "Menu button press", &startGame, QuitButton);
	window -> get_panda_framework() -> define_key(HitTogButton->get_click_event(keys.keybinds["use"].first ), "Hitbox button press", &toggleHitBox, HitTogButton);
	window -> get_panda_framework() -> define_key(DoubleTogButton->get_click_event(keys.keybinds["use"].first ), "Double jump button press", &toggleDoubleJump, DoubleTogButton);

	window -> get_panda_framework() -> define_key(OptionTogButton->get_click_event(keys.keybinds["use"].first ), "Option menu button press", &toggleOptionMenu, OptionTogButton);
	window -> get_panda_framework() -> define_key(OptionTogButton2->get_click_event(keys.keybinds["use"].first ), "Option menu button press", &toggleOptionMenu, OptionTogButton2);
	window -> get_panda_framework() -> define_key(OptionTogButton3->get_click_event(keys.keybinds["use"].first ), "Option menu button press", &toggleOptionMenu, OptionTogButton3);
	window -> get_panda_framework() -> define_key(mouseSensBut->get_click_event(keys.keybinds["use"].first ), "Mousebind button press", &rebindMouseSens, mouseSensBut);

	window -> get_panda_framework() -> define_key(respawnButton->get_click_event(keys.keybinds["use"].first ), "Respawn button press", &menu, NULL);
	window -> get_panda_framework() -> define_key(restartButton->get_click_event(keys.keybinds["use"].first ), "Restart button press", &startGame, restartButton);
	
	window -> get_panda_framework() -> define_key(InvButton1->get_click_event(keys.keybinds["use"].first ), "Inventory 1 slot press", &invPress, &blankTex);
	window -> get_panda_framework() -> define_key(InvButton2->get_click_event(keys.keybinds["use"].first ), "Inventory 2 slot press", &invPress, &blankTex);
	window -> get_panda_framework() -> define_key(InvButton3->get_click_event(keys.keybinds["use"].first ), "Inventory 3 slot press", &invPress, &blankTex);
	}
	
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	doStep(&framework,Thread::get_current_thread());
	//Item(char t,int xx,int yy,int zz,float wei,float vol, std::string fn,NodePath* parent,WindowFramework* w,PandaFramework* pf,float scale,int zzz,int xxx,int yyy,float rad,int zzzz)
	makeKalashnikov(35, 0, 20,&gameModels);
	makeNegev(30,0,20, &gameModels);
	makeBat(15,0,20, &gameModels);
	makePistol(25,0,20, &gameModels);
	makePistol(22,3,20, &gameModels);

	makePill(10,0,20, &gameModels);
	makeWaterbottle(45,5,20, &gameModels);
	makeCheese(55,0,20, &gameModels);
	makeAmmobox(0,5,20, &gameModels);
	
	
	
	
	// Start the loop / gameoptionMe
	//Thread *current_thread = Thread::get_current_thread();
	world.init();
	world.tickCount=0;
	
	player.health=1;
	int temptickcount=0;
	int frameDelay=0;
	int savedt=0;
	int frameDelayCount=0;
	gameModels.hide();
	loadanim.hide();
	NNS.hide();
	startMenuItems.show();//	player.handDisplay.show();
	nd_hellothere.show();
	world.gameSounds.background1->set_loop(true);
	world.gameSounds.background1->play();
	while(framework.do_frame(current_thread)){

		// Things to do every frame dependant on menu status
		// Keybinds should not go here.
		if(world.menuStatus==world.ms_start){
			nd_hellothere.show();
			//cout<<player.camera.get_pos()<<endl;
			//cout<<player.camera.get_hpr()<<endl;
			
			player.camera.set_pos(0,0,6);
			player.camera.set_hpr(0,0,0);
			
			nd_hellothere.set_hpr(nd_hellothere.get_hpr().get_x()+1,0,0);
		}
		else if (world.menuStatus==world.ms_game){
			nd_hellothere.hide();
			if(temptickcount<=10){
				temptickcount++;
				//nd_hellothere.hide();
			}
			player.volumeNodePath.show();
			player.weightNodePath.show();
			//Main Game
			player.handDisplay.show();
			
			world.get_keys(mouseWatcher, keys.keybinds); // updates keybinds held status . THIS SHOULD BE DONE FIRST
			world.look(window, keys.mouseSens);
			world.move(keys.keybinds);
			

			if(temptickcount>=10){		//buffer zone for loading
				world.tick();
			}

			//if u ded
			if (player.health<=0){
				
				StaticObject* tempStat = new StaticObject(&gameModels,window,&framework,mydir.get_dirname());
				stats.push_back(tempStat);
				float ranStat=rand()/(float)RAND_MAX;
				if(ranStat>(2.0/3)){
					stats.back()->main_collection.play("Death.1");
				}
				else if(ranStat>(1.0/3)){
					stats.back()->main_collection.play("Death.2");
				}
				else if(ranStat>0.0){
					stats.back()->main_collection.play("Death.3");
				}
				//else 
				//window->get_render().analyze();
				player.handDisplay.set_texture(*(static_cast<PT(Texture)*>(&blankTex)));
				float ranD=rand()/(float)RAND_MAX;
				ranD*=360;
				world.menuDeath(); //changes menu status to start death fog and then player.death
				deathNode->set_text(world.deathMessageList.at(rand()%world.deathMessageList.size())); //set death message
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
			nd_crosshair.show();

		}
		else if (world.menuStatus==world.ms_deathfog){
			player.volumeNodePath.hide();
			player.weightNodePath.hide();
			player.ammoNodePath.hide();
			player.ammoNodePath2.hide();
			Bars.hide();
			nd_crosshair.hide();
			deathMessage.show();
			world.deathFogIncrease+=world.dt;
			player.model.hide();
			
			
			if (world.deathFogIncrease < 5){
				player.deathFog->set_exp_density(world.deathFogIncrease/50.0);
				window->get_render().set_fog(player.deathFog);
				//player.model.hide();
			} else{
				player.death(itms,&entityModels);
				deathMenuItems.show();
				deathMessage.hide();
				world.menuStatus=world.ms_dead;
			}
		}
		else if(world.menuStatus==world.ms_pause){
			player.volumeNodePath.hide();
			player.weightNodePath.hide();
			player.ammoNodePath.hide();
			player.ammoNodePath2.hide();
			Bars.hide();
			nd_crosshair.hide();
		}
		else{
			player.handDisplay.hide();
			player.volumeNodePath.hide();
			player.weightNodePath.hide();
			player.ammoNodePath.hide();
			player.ammoNodePath2.hide();
			Bars.hide();
			nd_crosshair.hide();
		}

		//Things to do every frame regardless of menu status
		if (keys.showFPS){
			if (frameDelay>30){
				//cout<<world.dt<<" "<<1/world.dt<<endl;
				savedt+=(int)(1/world.dt);
				frameDelay =0;
				frameDelayCount++;
			}
			if(frameDelayCount==4){
				fpsNode->set_text(to_string(savedt/4)+" fps");
				frameDelayCount=0;
				savedt=0.0;
			}
			fpsNodePath.show();
		} else{
			fpsNodePath.hide();
		}

		frameDelay++;

		world.dt = globalClock -> get_real_time() - world.preTime;
		world.preTime = globalClock -> get_real_time();
		calc_inv(InvButton1,InvButton2,InvButton3,&blankTex);
		
		// Step the interval manager
		//CIntervalManager::get_global_ptr() -> step();
	}
	// Once the game is finished, close everything
	framework.close_framework();
	return (0);
}

void startGame(const Event* eventPtr, void* dataPtr){
	for (unsigned int i=0;i<stats.size();i++){
		stats[i]->model.show();
	}
	world.menuStart();
}

void loadGame(const Event* eventPtr, void* dataPtr){
	cout << "load game" << endl;
}

void sys_exit(const Event* eventPtr, void* dataPtr){
	exit(0);
}

void jump(const Event* eventPtr, void* dataPtr){
	if (world.menuStatus==world.ms_game){
		//cout<<player.coll_grav->get_airborne_height()<<" "<<player.coll_grav->is_on_ground()<<" "<<player.coll_grav->get_velocity()<<endl;
		if(player.doublejump || player.coll_grav->is_on_ground())
		{
			world.gameSounds.femaleGrunt7->play();
			if (player.doublejump){
				player.coll_grav->add_velocity(25.0);
			}
			else{
				player.coll_grav->set_velocity(25.0);
			}
		}
		//player.coll_grav->set_velocity(25.0);
		world.tickCount=121;
		
		
	}
}

void toggle(const Event* eventPtr, void* dataPtr){
	if(world.menuStatus==world.ms_game){
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
				player.negev_arms.hide();
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

void toggleFPS(const Event* eventPtr, void* dataPtr){
	keys.showFPS = 1-keys.showFPS;
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
		if(player.mainHand->type=='g'){
			player.pullout=player.mainHand->id;
		}
		
	}
	else{
		player.mainHand=NULL;
		player.handDisplay.set_texture(*(static_cast<PT(Texture)*>(dataPtr)));
	}
}

void invHotkey(const Event* eventPtr, void* dataPtr){
	int t=0;
	for (int i=1; i<10; i++){
		if (keys.keybinds["inv" + to_string(i)].first.get_name() == eventPtr->get_name()){
			t = i;
			break;
		}
	}
	if (!t){
		return;
	}
	player.handInd=t-1;
	if ((int)player.inventory.size()>=t){
		player.mainHand=player.inventory[t-1];
		player.handDisplay.set_texture(player.inventory[t-1]->imgTex);
		if(player.mainHand->type=='g'){
			player.pullout=player.mainHand->id;
		}
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
							window -> get_panda_framework() -> define_key(k.get_name(), i, keys.wildKeys[i], keys.dataPtrs[i]);
							window -> get_panda_framework() -> get_event_handler().remove_hook(oldKey, keys.wildKeys[i], keys.dataPtrs[i]);
							return;
						}
					}
					return;
				}
			}
		}
	}
}

void rebindMouseSens(const Event* eventPtr, void* dataPtr){
	keys.mouseSens = mouseSlider->get_value()*2.0;
}

void menu(const Event* eventPtr, void* dataPtr){
	world.menu();
}

void spiderClick(const Event* eventPtr, void* dataPtr){
	NodePath* shootableModels = static_cast<NodePath*>(dataPtr);
	makeSpider(player.model.get_x()+50, player.model.get_y(), player.model.get_z()+6, shootableModels);
	makeBandit(player.model.get_x()+25, player.model.get_y(), player.model.get_z()+6, shootableModels);
	//player.main_collection.play("Death.1");
}

void drop(const Event* eventPtr, void* dataPtr){
	if (world.menuStatus==world.ms_game){
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
	if(world.menuStatus==world.ms_game){
		player.qtrav_shoot.traverse(window -> get_render());
		if (player.qcoll_shoot -> get_num_entries() > 0){
			player.qcoll_shoot->sort_entries();
			cout<<player.qcoll_shoot -> get_entry(0) -> get_into_node() -> get_name()<<endl;
			if (player.qcoll_shoot -> get_entry(0) ->get_into_node()->get_name()=="Interaction_Sphere"){
				//player.qcoll_shoot -> sort_entries();
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
	
	//player.main_collection.play("Armature");
	//return;
	
	
	if (player.mainHand!=NULL && world.menuStatus==world.ms_game){
		if (player.mainHand->type=='g'){
			if (player.mainHand->tot_ammo-(player.mainHand->max_amount-player.mainHand->amount)>0){
				player.mainHand->tot_ammo-=(player.mainHand->max_amount-player.mainHand->amount);
				player.mainHand->amount=player.mainHand->max_amount;
				if (player.mainHand->id==10){
					world.gameSounds.akReloadSound->play();
					player.ak_collection.play("ak_reload");
				}
				else if (player.mainHand->id==11){
					world.gameSounds.akReloadSound->play();
					player.negev_collection.play("negev_reload");
				}
				else if (player.mainHand->id==0){
					world.gameSounds.pistolReloadSound->play();
					player.pistol_collection.play("pistol_reload");
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
	if (world.menuStatus==world.ms_pause){
	
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
	if (world.menuStatus==world.ms_game && player.mode==0){
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
						//cout<<player.pistol_collection.get_frame()<<" "<<player.pistol_collection.get_num_frames()<<endl;	
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
					else if(player.mainHand->id==11){
						frameGunCount = player.negev_collection.get_frame()-player.negev_collection.get_num_frames();
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
							
							
							if (player.qcoll_shoot -> get_entry(0) ->get_into_node()->get_name()=="Interaction_Sphere"){
								bool enem=false;
								
								
								// WE NEED MAPS LOL WITH TAGS
								for (unsigned int i = 0; i < enems.size(); i++){
									
									//Don't delete these comments
									
									//cout << "i: " << i << endl;
									//cout << "enems[i]: " << enems[i] << endl;
									//cout << "enems[i] -> model: " << enems[i] -> sphereModel << endl;
									//cout << "enems[i] -> model child: " << enems[i] -> sphereModel.get_child(0) << endl;
									//if (enems[i]->sphereModel.get_child(0).is_empty()) cout << "Ohes noes!" << endl;
									
									//cout<<i<<" "<<enems[i]->sphereModelTwo.node()<<" - "<<player.qcoll_shoot -> get_entry(0) ->get_into_node()<<endl;
									
									if (enems[i]->sphereModelTwo.node()==player.qcoll_shoot -> get_entry(0) ->get_into_node()){
										
										enem=true;
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
								if (!enem){
									//hit item
									// WE NEED MAPS LOL WITH TAGS
									
									for (unsigned int h = 0; h < itms.size(); h++){
										if (itms[h]->sphereModelTwo.node()==player.qcoll_shoot -> get_entry(0) ->get_into_node()){
											float xd,yd,zd,td;
										
											xd=itms[h]->model.get_x();
											yd=itms[h]->model.get_y();
											zd=itms[h]->model.get_z();
										
											xd=xd-player.model.get_x();
											yd=yd-player.model.get_y();
											zd=zd-player.model.get_z();
				
											td=pow(pow(pow((xd*xd)+(yd*yd),0.5),2)+(zd*zd),0.5);
											dmg=(dmg/(pow(td,rngM)/100.0));
											itms[h]->accel(dmg*xd/100.0,dmg*yd/100.0,0.0);
										
										}
									}
								}
								
							}
							//else if (player.qcoll_shoot -> get_entry(0) ->get_into_node()->get_name()=="Interaction_Sphere"){
							//	
							//	
							//}
							//cout<<player.qcoll_shoot -> get_entry(0) ->get_into_node()->get_name()<<endl;
							
		
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
						else if (player.mainHand->id==11){
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


void makeAmmobox(int x, int y, int z,NodePath* parentNode){
	Item* Ammo= new Item('a',x,y,z,1.0f,1.0f, mydir+"Assets/pillBottle.egg",parentNode,window,window->get_panda_framework(),0.5f,1,0,0,1.5f,0,mydir+"blenderFiles/pbottleicon.png",35.0,10);
	itms.push_back(Ammo);
}

void makeBat(int x, int y, int z,NodePath* parentNode){
	WeaponObject* Bat = new WeaponObject('g',15,0,20,1.0f,1.0f, mydir+"Model/Baseballbat.egg",parentNode,window,window->get_panda_framework(),1.0f,1,0,0,1.5f,0,mydir+"blenderFiles/baticon.png",15.0,2);
	Bat->weapon_init(15,1.0,1.0,0,0,1);
	itms.push_back(Bat);
}

void makeCheese(int x, int y, int z,NodePath* parentNode){
	FoodItem* cheese = new FoodItem('c',x,y,z,1.0f,1.0f, mydir+"blenderFiles/cheese.egg",parentNode,window,window->get_panda_framework(),0.5f,1,0,0,1.5f,0,mydir+"blenderFiles/cheeseicon.png",25.0,5);
	itms.push_back(cheese);
}

void makePill(int x, int y, int z,NodePath* parentNode){
	HealthItem* Pill = new HealthItem('c',x,y,z,1.0f,1.0f, mydir+"Assets/pillBottle.egg",parentNode,window,window->get_panda_framework(),0.5f,1,0,0,1.5f,0,mydir+"blenderFiles/pbottleicon.png",100.0,1);
	itms.push_back(Pill);
}

void makePistol(int x, int y, int z,NodePath* parentNode){
	WeaponObject* Pis = new WeaponObject('g',x,y,z,1.0f,1.0f, mydir+"Model/PIstol/Pistol.egg",parentNode,window,window->get_panda_framework(),1.0f,1,0,0,1.5f,0,mydir+"Model/PIstol/ITSAGUN.png",8.0,0);
	Pis->weapon_init(8,1.0,1.0,0,64,1);
	itms.push_back(Pis);
}

void makeKalashnikov(int x, int y, int z,NodePath* parentNode){
	WeaponObject* ak47 = new WeaponObject('g',x,y,z,8.0f,1.0f, mydir+"blenderFiles/AK47.egg",parentNode,window,window->get_panda_framework(),1.0f,1,0,0,1.5f,0,mydir+"blenderFiles/ak47icon.png",24.0,10);
	ak47->weapon_init(24,25.0,1.0,0,64,1);
	itms.push_back(ak47);
}

void makeNegev(int x, int y, int z,NodePath* parentNode){
	WeaponObject* nedgev = new WeaponObject('g',x,y,z,17.0f,2.0f, mydir+"blenderFiles/negevitem.egg",parentNode,window,window->get_panda_framework(),1.0f,1,0,0,1.5f,0,mydir+"blenderFiles/negevicon.png",140.0,11);
	nedgev->weapon_init(140,27.0,1.0,0,560,1);
	itms.push_back(nedgev);
}

void makeSpider(int x, int y, int z, NodePath* parentNode){
	
	Enemy* romar = new Enemy;
	romar->set_up(parentNode, window, window->get_panda_framework(), mydir+"Assets/INSECT/insect.egg",50.0,x,y,z,15.0,40,24,0,10.0,50);
	romar->init();
	romar->coll_set_up(1000);
	enems.push_back(romar);
	cout<<"Spider!"<<endl;
}

void makeBandit(int x, int y, int z, NodePath* parentNode){
	Enemy* bryan = new Enemy;
	bryan->set_up(parentNode, window, window->get_panda_framework(), mydir+"Assets/bandit/Bandit.egg",50.0,x,y,z,15.0,40,24,0,10.0,51);
	bryan->init();
	bryan->coll_set_up(1000);
	enems.push_back(bryan);
	
}

void makeWaterbottle(int x, int y, int z,NodePath* parentNode){
	WaterItem* booootle = new WaterItem('c',x,y,z,1.0f,1.0f, mydir+"blenderFiles/Bootle.egg",parentNode,window,window->get_panda_framework(),0.5f,1,0,0,1.5f,0,mydir+"blenderFiles/BottleIcon.png",80.0,6);
	itms.push_back(booootle);
}

void doStep(PandaFramework* pf,Thread *current_thread){
	if(pf->do_frame(current_thread))
	{
		pf->get_graphics_engine()->render_frame();
		//CIntervalManager::get_global_ptr() -> step();
	}
}






