/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "buttons.hpp"
#include "keys.hpp"
#include "global.hpp"

#include "nodePath.h"
#include "pgButton.h"
#include "pgSliderBar.h"

Buttons::Buttons(){
	Keys keys;
	xs = -(window -> get_graphics_window()->get_x_size() / (float)window ->get_graphics_window()->get_y_size());


	//Menu items
	menuItems.hide();

	OptionTogButton = new PGButton("OptionTogButton");
	OptionTogButton -> setup("Toggle Option Menu");
	defbutNP = window -> get_pixel_2d().attach_new_node(OptionTogButton);
	defbutNP.set_scale(0.1);
	defbutNP.set_pos(xs + 0.1, 0, 0.85);
	defbutNP.reparent_to(menuItems);
	keys.buttonIndex["click-mouse1-"+OptionTogButton->get_id()] = OptionTogButton;


	HitTogButton = new PGButton("HitTogButton");
	HitTogButton -> setup("Toggle Hit Boxes");
	defbutNP = window -> get_pixel_2d().attach_new_node(HitTogButton);
	defbutNP.set_scale(0.1);
	defbutNP.set_pos(xs + 0.1, 0, 0.65);
	defbutNP.reparent_to(menuItems);
	keys.buttonIndex["click-mouse1-"+HitTogButton->get_id()] = HitTogButton;

	DoubleTogButton = new PGButton("DoubleTogButton");
	DoubleTogButton -> setup("Toggle Double Jump");
	defbutNP = window -> get_pixel_2d().attach_new_node(DoubleTogButton);
	defbutNP.set_scale(0.1);
	defbutNP.set_pos(xs + 0.1, 0, 0.45);
	defbutNP.reparent_to(menuItems);
	keys.buttonIndex["click-mouse1-"+DoubleTogButton->get_id()] = DoubleTogButton;

	SaveButton = new PGButton("SaveButton");
	SaveButton -> setup("Save Game");
	defbutNP = window -> get_pixel_2d().attach_new_node(SaveButton);
	defbutNP.set_scale(0.1);
	defbutNP.set_pos(xs+0.1,0, 0.25);
	defbutNP.reparent_to(menuItems);
	keys.buttonIndex["click-mouse1-"+SaveButton->get_id()] = SaveButton;

	QuitButton = new PGButton("MenuButton");
	QuitButton -> setup("Main Menu");
	defbutNP = window -> get_pixel_2d().attach_new_node(QuitButton);
	defbutNP.set_scale(0.1);
	defbutNP.set_pos(xs+0.1,0, 0.05);
	defbutNP.reparent_to(menuItems);
	keys.buttonIndex["click-mouse1-"+QuitButton->get_id()] = QuitButton;

	// Start Menu items
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
	nd_hellothere=window->load_model(window->get_panda_framework()->get_models(),mydir+"Assets/Iris/Iris.egg");
	nd_hellothere.reparent_to(window->get_render());
	nd_hellothere.set_pos(0,20,-1.0);
	nd_hellothere.set_hpr(180,0,0);
	
	nd_hellothere.hide();
	
	loadnode2 = window->load_model(nd_hellothere, mydir + "Assets/Iris/Iris-Idle.egg");
	auto_bind(nd_hellothere.node(), start_anim_collection);
	animPtrLoad2 = start_anim_collection.get_anim(0);
	start_anim_collection.store_anim(animPtrLoad2, "load");
	loadnode2.detach_node();
	start_anim_collection.loop("load",1);
	
	//doStep(&framework,Thread::get_current_thread());

	StartGameButton = new PGButton("StartGameButton");
	StartGameButton -> setup("New Game");
	defbutNP = window -> get_pixel_2d().attach_new_node(StartGameButton);
	defbutNP.set_scale(0.1);
	defbutNP.set_pos(xs + 0.1, 0, 0.85);
	defbutNP.reparent_to(startMenuItems);
	keys.buttonIndex["click-mouse1-"+StartGameButton->get_id()] = StartGameButton;

	loadGameButton = new PGButton("loadGameButton");
	loadGameButton -> setup("Load Game");
	defbutNP = window -> get_pixel_2d().attach_new_node(loadGameButton);
	defbutNP.set_scale(0.1);
	defbutNP.set_pos(xs + 0.1, 0, 0.65);
	defbutNP.reparent_to(startMenuItems);
	keys.buttonIndex["click-mouse1-"+loadGameButton->get_id()] = loadGameButton;

	//doStep(&framework,Thread::get_current_thread());
	
	realQuitButton = new PGButton("QuitButton");
	realQuitButton -> setup("Quit");
	defbutNP = window -> get_pixel_2d().attach_new_node(realQuitButton);
	defbutNP.set_scale(0.1);
	defbutNP.set_pos(xs+0.1,0, 0.25);
	defbutNP.reparent_to(startMenuItems);
	keys.buttonIndex["click-mouse1-"+realQuitButton->get_id()] = realQuitButton;

	OptionTogButton3 = new PGButton("OptionTogButton");
	OptionTogButton3 -> setup("Toggle Option Menu");
	defbutNP = window -> get_pixel_2d().attach_new_node(OptionTogButton3);
	defbutNP.set_scale(0.1);
	defbutNP.set_pos(xs + 0.1, 0, 0.45);
	defbutNP.reparent_to(startMenuItems);
	keys.buttonIndex["click-mouse1-"+OptionTogButton3->get_id()] = OptionTogButton3;



	//Option Menu Items
	optionMenuItems.hide();

	OptionTogButton2 = new PGButton("OptionTogButton");
	OptionTogButton2 -> setup("Toggle Option Menu");
	defbutNP = window -> get_pixel_2d().attach_new_node(OptionTogButton2);
	defbutNP.set_scale(0.1);
	defbutNP.set_pos(xs + 0.1, 0, 0.85);
	defbutNP.reparent_to(optionMenuItems);
	keys.buttonIndex["click-mouse1-"+OptionTogButton2->get_id()] = OptionTogButton2;

	//Option menu buttons are in main

	//doStep(&framework,Thread::get_current_thread());
	mouseSlider=new PGSliderBar("mouseSliderBar");

	mouseSlider->setup_scroll_bar(true,1.5,0.5,0); // 'rail' properties
	mouseSlider->set_range(0,1);
	mouseSlider->set_value(0);


	mouseSlider->setup_slider(true,1,0.05,false);
	defbutNP = window->get_aspect_2d().attach_new_node(mouseSlider);
	defbutNP.set_pos(xs+2.5,0,.25);
	defbutNP.reparent_to(optionMenuItems);

	mouseSensBut = new PGButton("mouseSensBut");
	mouseSensBut -> setup("Change mouse sens");
	defbutNP = window -> get_pixel_2d().attach_new_node(mouseSensBut);
	defbutNP.set_scale(0.1);
	defbutNP.set_pos(xs+0.1*(17/8*8+1),0, 0.85);
	defbutNP.reparent_to(optionMenuItems);


	//Death Menu Items
	deathMenuItems.hide();

	respawnButton = new PGButton("respawnButton");
	respawnButton -> setup("Respawn");
	defbutNP = window -> get_pixel_2d().attach_new_node(respawnButton);
	defbutNP.set_scale(0.1);
	defbutNP.set_pos(xs + 0.1, 0, 0.85);
	defbutNP.reparent_to(deathMenuItems);
	keys.buttonIndex["click-mouse1-"+respawnButton->get_id()] = respawnButton;

	restartButton = new PGButton("restartButton");
	restartButton -> setup("Main Menu");
	defbutNP = window -> get_pixel_2d().attach_new_node(restartButton);
	defbutNP.set_scale(0.1);
	defbutNP.set_pos(xs + 0.1, 0, 0.65);
	defbutNP.reparent_to(deathMenuItems);
	keys.buttonIndex["click-mouse1-"+restartButton->get_id()] = restartButton;

	//Death message
	deathNode = new TextNode("deathNode");
	deathMessage= window->get_aspect_2d().attach_new_node(deathNode);
	deathMessage.set_scale(0.2);
	deathMessage.set_pos(xs+0.1,0, 0.5);
	deathMessage.hide();


	//Load Menu Items
	loadMenuItems.hide();

	MainMenuReturnButton = new PGButton("MainMenuReturnButton");
	MainMenuReturnButton -> setup("Main Menu");
	defbutNP = window -> get_pixel_2d().attach_new_node(MainMenuReturnButton);
	defbutNP.set_scale(0.1);
	defbutNP.set_pos(xs + 0.1, 0, 0.85);
	defbutNP.reparent_to(loadMenuItems);


}

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
