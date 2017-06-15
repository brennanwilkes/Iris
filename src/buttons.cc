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

Buttons::Buttons(){
	Keys keys;
	xs = -(window -> get_graphics_window()->get_x_size() / (float)window ->get_graphics_window()->get_y_size());


	//Menu items
	menuItems.hide();

	OptionTogButton = new PGButton("OptionTogButton");
	OptionTogButton -> setup("Toggle Option Menu");
	defbutNP5 = window -> get_pixel_2d().attach_new_node(OptionTogButton);
	defbutNP5.set_scale(0.1);
	defbutNP5.set_pos(xs + 0.1, 0, 0.85);
	defbutNP5.reparent_to(menuItems);
	keys.buttonIndex["click-mouse1-"+OptionTogButton->get_id()] = OptionTogButton;


	HitTogButton = new PGButton("HitTogButton");
	HitTogButton -> setup("Toggle Hit Boxes");
	defbutNP3 = window -> get_pixel_2d().attach_new_node(HitTogButton);
	defbutNP3.set_scale(0.1);
	defbutNP3.set_pos(xs + 0.1, 0, 0.65);
	defbutNP3.reparent_to(menuItems);
	keys.buttonIndex["click-mouse1-"+HitTogButton->get_id()] = HitTogButton;

	DoubleTogButton = new PGButton("DoubleTogButton");
	DoubleTogButton -> setup("Toggle Double Jump");
	defbutNP4 = window -> get_pixel_2d().attach_new_node(DoubleTogButton);
	defbutNP4.set_scale(0.1);
	defbutNP4.set_pos(xs + 0.1, 0, 0.45);
	defbutNP4.reparent_to(menuItems);
	keys.buttonIndex["click-mouse1-"+DoubleTogButton->get_id()] = DoubleTogButton;

	SaveButton = new PGButton("SaveButton");
	SaveButton -> setup("Save Game");
	defbutNP9000 = window -> get_pixel_2d().attach_new_node(SaveButton);
	defbutNP9000.set_scale(0.1);
	defbutNP9000.set_pos(xs+0.1,0, 0.25);
	defbutNP9000.reparent_to(menuItems);
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
	bnp = window -> get_pixel_2d().attach_new_node(StartGameButton);
	bnp.set_scale(0.1);
	bnp.set_pos(xs + 0.1, 0, 0.85);
	bnp.reparent_to(startMenuItems);
	keys.buttonIndex["click-mouse1-"+StartGameButton->get_id()] = StartGameButton;

	loadGameButton = new PGButton("loadGameButton");
	loadGameButton -> setup("Load Game");
	bnp2 = window -> get_pixel_2d().attach_new_node(loadGameButton);
	bnp2.set_scale(0.1);
	bnp2.set_pos(xs + 0.1, 0, 0.65);
	bnp2.reparent_to(startMenuItems);
	keys.buttonIndex["click-mouse1-"+loadGameButton->get_id()] = loadGameButton;

	//doStep(&framework,Thread::get_current_thread());
	
	realQuitButton = new PGButton("QuitButton");
	realQuitButton -> setup("Quit");
	defbutNPk = window -> get_pixel_2d().attach_new_node(realQuitButton);
	defbutNPk.set_scale(0.1);
	defbutNPk.set_pos(xs+0.1,0, 0.25);
	defbutNPk.reparent_to(startMenuItems);
	keys.buttonIndex["click-mouse1-"+realQuitButton->get_id()] = realQuitButton;

	OptionTogButton3 = new PGButton("OptionTogButton");
	OptionTogButton3 -> setup("Toggle Option Menu");
	defbutNP7 = window -> get_pixel_2d().attach_new_node(OptionTogButton3);
	defbutNP7.set_scale(0.1);
	defbutNP7.set_pos(xs + 0.1, 0, 0.45);
	defbutNP7.reparent_to(startMenuItems);
	keys.buttonIndex["click-mouse1-"+OptionTogButton3->get_id()] = OptionTogButton3;


	//Load Menu Items
	loadMenuItems.hide();

	MainMenuReturnButton = new PGButton("MainMenuReturnButton");
	MainMenuReturnButton -> setup("Main Menu");
	defbutNP69 = window -> get_pixel_2d().attach_new_node(MainMenuReturnButton);
	defbutNP69.set_scale(0.1);
	defbutNP69.set_pos(xs + 0.1, 0, 0.85);
	defbutNP69.reparent_to(loadMenuItems);

	//Death Menu Items
	deathMenuItems.hide();

	respawnButton = new PGButton("respawnButton");
	respawnButton -> setup("Respawn");
	bresp = window -> get_pixel_2d().attach_new_node(respawnButton);
	bresp.set_scale(0.1);
	bresp.set_pos(xs + 0.1, 0, 0.85);
	bresp.reparent_to(deathMenuItems);
	keys.buttonIndex["click-mouse1-"+respawnButton->get_id()] = respawnButton;

	restartButton = new PGButton("restartButton");
	restartButton -> setup("Main Menu");
	brest = window -> get_pixel_2d().attach_new_node(restartButton);
	brest.set_scale(0.1);
	brest.set_pos(xs + 0.1, 0, 0.65);
	brest.reparent_to(deathMenuItems);
	keys.buttonIndex["click-mouse1-"+restartButton->get_id()] = restartButton;



	
}
