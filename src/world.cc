/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "world.hpp"

#include "player.hpp"
#include "global.hpp"
#include "keys.hpp"

#include "clockObject.h"
#include "mouseWatcher.h"
#include "keyboardButton.h"
#include "pandaFramework.h"
#include "windowFramework.h"
#include "windowProperties.h"
#include <string>
#include <vector>
#include <cstdlib>

World::World(){
	deathFogIncrease = 0.0;
	deathMessageList = {
		////////////////max length
		"You have died"
		//"Oh, you are slain",
		//"Wasted",
		//":(",
		//"RIP"
	};
	
	menuStatus = 3;
	//ms = {ms_game=0, ms_pause=1, ms_option=2, ms_start=3, ms_optionfromstart=4, ms_deathfog=5, ms_dead=6};
}

void World::init(){
	player.init();
	for (auto &itm:itms)
		itm -> init();
}

void World::tick(){
	player.tick();
	
	//GameObject::gtrav.traverse(window -> get_render());
	//GameObject::ptrav.traverse(window -> get_render());
	
	
	Player::ptrav.traverse(window -> get_render());
	if(tickCount%2==0){
		Player::gtrav.traverse(window -> get_render());
	}
	if(tickCount%6==0){
		Enemy::ptrav.traverse(window -> get_render());
		Item::ptrav.traverse(window -> get_render());
		
		
		
	}
	if(tickCount%12==0){
		Item::gtrav.traverse(window -> get_render());
		Enemy::gtrav.traverse(window -> get_render());
	}
	for (unsigned int i=0;i<itms.size();i++){
		itms[i]->tick();
	}
	for (unsigned int i=0;i<enems.size();i++){
		enems[i]->tick(1);
	}
	
	
	
	player.calc_arms();
	if (player.mode==0){
		player.arms_shown=true;
		if (player.arms!=NULL){
			player.arms->show();
		}
	}
	else{
		player.arms_shown=false;
		if (player.arms!=NULL){
			player.arms->hide();
		}
	}
	
	
	if (player.pullout!=-1){
		if (player.pullout==0){
			player.pistol_collection.play("pistol_reload");
		}
		else if(player.pullout==2){
			player.bat_collection.play("bat_reload");
		}
		else if(player.pullout==10){
			player.ak_collection.play("ak_reload");
		}
		else if(player.pullout==11){
			player.negev_collection.play("negev_reload");
		}
		
		player.pullout=-1;
	}

	//RECOIL
	if (player.recoil_frames>0){
		float ranR=rand()/(float)RAND_MAX;
		ranR*=2;
		ranR-=1;
		player.recoil_frames--;
		
		//ranR*=1.4;
		
		if(player.mainHand!=NULL){
			if(player.mainHand->id==11){
				ranR*=2;
			}
		}
		
		player.camera.set_p(player.camera,player.recoil_mult*pow(pow(ranR,2),0.5));
		player.camera.set_h(player.camera,player.recoil_mult*ranR);
	}


	
	if (player.speed>1 && tickCount%15==1){
		//float rann=rand()/(float)RAND_MAX;
		
		/*if (rann<=(1.0/6.0)){
			world.gameSounds.walkSound1->play();
		}
		else if (rann<=(2.0/6.0)){
			world.gameSounds.walkSound2->play();
		}
		else if (rann<=(3.0/6.0)){
			world.gameSounds.walkSound3->play();
		}
		else if (rann<=(4.0/6.0)){
			world.gameSounds.walkSound4->play();
		}
		else if (rann<=(5.0/6.0)){
			world.gameSounds.walkSound5->play();
		}
		else{
			world.gameSounds.walkSound6->play();
		}*/
		
		/*if (rann<=0.5){
			world.gameSounds.walkSound2->play();
		}
		else{
			world.gameSounds.walkSound3->play();
		}*/
		
		world.gameSounds.walkSound3->play();

	}
	

	tickCount++;
	if (tickCount%120==0){
		float ran=rand()/(float)RAND_MAX;
		if (player.food<25 || player.water<35){
			if(ran<((100-pow(0.5,player.food))/1000.0)){
				player.health--;
			}
			if(ran<((100-pow(0.5,player.water))/1000.0)){
				player.health--;
			}
		}
		
		
		ran=ran/player.speed;
		if(ran<0.05){
			player.water-=1;
		}
		if(ran<0.025){
			player.food-=1;
		}
		
		if (player.food<1){
			player.food=1;
		}
		if (player.water<1){
			player.water=1;
		}
		if (tickCount>=120000){
			tickCount=0;
		}
	}
}

void World::draw(){
	float tx(0),ty(0);
	float rot = player.camera.get_hpr().get_x();
	
	float tz2(0),ty2(0);
	float rot2 = player.camera.get_hpr().get_y();
	
	float trans(5);//,transA(0);
	
	if (player.mode == 1)
	{
		player.model.show();
		
		ty2 = 20.0*cos(rot2 * (3.1416 / 180));
		ty2 -= 20;
		tz2 = -20.0*sin(rot2 * (3.1416 / 180));
		
		tx = (20.0+ty2) * sin(rot * (3.1416 / 180));
		ty = (-20.0-ty2) * cos(rot * (3.1416 / 180));

		tx *= player.zoom;
		ty *= player.zoom;
		tz2 *= player.zoom;
	} 
	else
	{
		player.model.hide();
	}
	
	
	player.camera.set_pos(player.model.get_x()+tx, player.model.get_y()+ty,player.model.get_z()+trans+tz2);
	player.camera.set_hpr(player.camera.get_hpr().get_x(),player.camera.get_hpr().get_y(),0.0f);

	if (player.hitbox){
		player.sphereModel.show();
		player.sphereModelTwo.show();
		player.rayModel.show();
		for (unsigned ij=0;ij<itms.size();ij++){
			itms[ij]->sphereModel.show();
			itms[ij]->sphereModelTwo.show();
			itms[ij]->rayModel.show();
		}
		for (unsigned ij=0;ij<enems.size();ij++){
			enems[ij]->sphereModel.show();
			enems[ij]->sphereModelTwo.show();
			enems[ij]->rayModel.show();
			
		}
	}
	else{
		player.sphereModel.hide();
		player.sphereModelTwo.hide();
		player.rayModel.hide();
		for (unsigned ij=0;ij<itms.size();ij++){
			itms[ij]->sphereModel.hide();
			itms[ij]->sphereModelTwo.hide();
			itms[ij]->rayModel.hide();
		}
		for (unsigned ij=0;ij<enems.size();ij++){
			enems[ij]->sphereModel.hide();
			enems[ij]->sphereModelTwo.hide();
			enems[ij]->rayModel.hide();
			
		}
	}
	/*
	//////////////////		Weapon GUI 		///////////////////
	for (unsigned int j=0;j<player.weapons.size();j++){
		if (j!=(unsigned int)player.weaponN){
			player.weapons[j].Node.hide();
			player.weapons[j].selected=false;
		}
	}
	player.weapons[player.weaponN].selected=true;
	player.weapons[player.weaponN].Node.show();
	*/

}

void World::get_keys(MouseWatcher* mw, map <std::string, pair<ButtonHandle, bool> > &keybinds){
	for (auto& k:keybinds)
		if (mw -> is_button_down((k.second).first))
			(k.second).second = true;
		else
			(k.second).second = false;
}

void World::look(WindowFramework *win, float mouseSens){

	GraphicsWindow *gw = win -> get_graphics_window();
	if (gw)
	{
		int dx = (gw -> get_properties().get_x_size() / 2) - gw -> get_pointer(0).get_x();
		int dy = (gw -> get_properties().get_y_size() / 2) - gw -> get_pointer(0).get_y();

		player.camera.set_hpr(player.camera.get_hpr().get_x()+ dx * 0.03 * (mouseSens+1), player.camera.get_hpr().get_y() + dy * 0.03 * (mouseSens+1), 0);
		gw -> move_pointer(0, gw -> get_properties().get_x_size() / 2, gw -> get_properties().get_y_size() / 2);
	}
}

void World::move(map <std::string, pair<ButtonHandle, bool> > &keybinds){
	float rot = player.camera.get_hpr().get_x();
	float dx(0), dy(0);
	float walk(2);
	float spin=-1;
	player.speed=1;
	if (keybinds["forward"].second) 
	{
		dx += -2.0 * sin(rot * (3.1416 / 180));
		dy += 2.0 * cos(rot * (3.1416 / 180));
		player.speed=4;
		spin=0.0;
	}
	if (keybinds["backward"].second)
	{
		dx += 2.0 * sin(rot * (3.1416 / 180));
		dy += -2.0 * cos(rot * (3.1416 / 180));
		player.speed=4;
		spin=180.0;
	}
	if (keybinds["left"].second)
	{
		dx += 2.0 * sin((rot - 90) * (3.1416 / 180));
		dy += -2.0 * cos((rot - 90) * (3.1416 / 180));
		player.speed=4;
		if(spin==0){
			spin=45.0;
		}
		else if (spin==180){
			spin=135.0;
		}
		else{
			spin=90.0;
		}
	}
	if (keybinds["right"].second)
	{
		dx += 2.0 * sin((rot + 90) * (3.1416 / 180));
		dy += -2.0 * cos((rot + 90) * (3.1416 / 180));
		player.speed=4;
		if(spin==0){
			spin=315.0;
		}
		else if (spin==180){
			spin=225.0;
		}
		else{
			spin=270.0;
		}
	}
	
	if (keybinds["walk"].second){
		walk=0.25;
		player.speed=2;
	}
	
	if (keybinds["sprint"].second){
		walk=4;
		player.speed=12;
	}
	
	if (keybinds["zoomOut"].second){
		player.zoom+=0.02;
	}
	
	if (keybinds["zoomIn"].second){
		player.zoom-=0.02;
	}
	
	if (player.zoom<0){
		player.zoom=0;
	}
	
	
	
	// Move the player
	player.model.set_fluid_x(player.model.get_x() + (dx * dt * 5 * walk));
	player.model.set_fluid_y(player.model.get_y() + (dy * dt * 5 * walk));
	
	/*
	for (int i=0;i<player.main_collection.get_num_anims();i++){
		cout<<player.main_collection.get_anim_name(i)<<endl;
	}
	*/
	
	
	if (dx != 0  || dy != 0)
	{
		//cout<<player.main_collection.get_frame()<<" - "<<player.main_collection.get_num_frames()<<endl;
		if(player.main_collection.get_frame()-player.main_collection.get_num_frames()==-1 || player.main_collection.which_anim_playing()=="idle"){
			if(player.coll_grav->get_airborne_height()<0.2){
				player.main_collection.play("walk");
			}
		}
		//cout<<"walk"<<endl;
		player.model.set_hpr(rot+spin, 0, 0);
	}
	else{
		//cout<<"idle"<<endl;
		//cout<<player.main_collection.get_frame()<<" - "<<player.main_collection.get_num_frames()<<endl;
		if(player.main_collection.get_frame()-player.main_collection.get_num_frames()==-1 || player.main_collection.which_anim_playing()=="walk"){
			if(player.coll_grav->get_airborne_height()<0.2){
				player.main_collection.play("idle");
			}
		}
	}
	
}

void World::apply_grav(){
	/*if (dt <= 0.1){
		
		for (unsigned int i=0;i<itms.size();i++){
			itms[i]->accel(0,0,-9.8*dt);
			if (!itms[i]->ground){
				itms[i]->model.set_fluid_z(itms[i]->model.get_z() + itms[i]->getzV());
			}
		}
		player.accel(0, 0, -9.8 * dt);
	}
	if (!player.ground)
		player.model.set_fluid_z(player.model.get_z() + player.getzV());
	*/
}

void World::menu(){
	if ((menuStatus==ms_start) || (menuStatus==ms_optionfromstart) || (menuStatus==ms_deathfog)){
		return;
	}
	if (menuStatus == ms_deathfog || menuStatus==ms_dead){
		deathFogIncrease=0.0;
		player.deathFog->set_exp_density(0.0);
		window->get_render().set_fog(player.deathFog);
	}
	
	if (menuStatus==ms_game){
		menuStatus=ms_pause;
	}	else{
		menuStatus=ms_game;
	}

	if (menuStatus==ms_game)
	{
		if (player.arms!=NULL){
			player.arms->show();
		}
		startMenuItems.hide();
		gameModels.show();
		menuItems.hide();
		optionMenuItems.hide();
		deathMenuItems.hide();
		WindowProperties props = window -> get_graphics_window() -> get_properties();
		props.set_cursor_hidden(true);
		props.set_mouse_mode(WindowProperties::M_confined);
		window -> get_graphics_window() -> request_properties(props);
	}
	else if (menuStatus==ms_pause)
	{	
		if (player.arms!=NULL){
			player.arms->hide();
		}
		
		startMenuItems.hide();

		gameModels.hide();
		menuItems.show();
		optionMenuItems.hide();
		deathMenuItems.hide();
		WindowProperties props = window -> get_graphics_window() -> get_properties();
		props.set_cursor_hidden(false);
		props.set_mouse_mode(WindowProperties::M_absolute);
		window -> get_graphics_window() -> request_properties(props);
		
		
		
	}
	
	else if (menuStatus==ms_option)
	{	
		
		if (player.arms!=NULL){
			player.arms->hide();
		}
		startMenuItems.hide();

		gameModels.hide();
		menuItems.hide();
		optionMenuItems.show();
		WindowProperties props = window -> get_graphics_window() -> get_properties();
		props.set_cursor_hidden(false);
		props.set_mouse_mode(WindowProperties::M_absolute);
		window -> get_graphics_window() -> request_properties(props);
		
		
		
	}
	else
	{
		if (player.arms!=NULL){
			player.arms->hide();
		}
		startMenuItems.show();
		gameModels.hide();
		menuItems.hide();
		optionMenuItems.show();
		WindowProperties props = window -> get_graphics_window() -> get_properties();
		props.set_cursor_hidden(false);
		props.set_mouse_mode(WindowProperties::M_absolute);
		window -> get_graphics_window() -> request_properties(props);
	}

	
}

void World::menuOption(){
	if (menuStatus==ms_option){
		menuStatus=ms_pause;
	}
	else if (menuStatus ==ms_pause){
		menuStatus=ms_option;
	}
	
	if (menuStatus == ms_start){
		menuStatus = ms_optionfromstart;
	}
	else if (menuStatus == ms_optionfromstart){
		menuStatus = ms_start;
	}

	if (menuStatus==ms_optionfromstart)
	{	
		if (player.arms!=NULL){
			player.arms->hide();
		}
		startMenuItems.hide();
		gameModels.hide();
		menuItems.hide();
		optionMenuItems.show();
		deathMenuItems.hide();
		WindowProperties props = window -> get_graphics_window() -> get_properties();
		props.set_cursor_hidden(false);
		props.set_mouse_mode(WindowProperties::M_absolute);
		window -> get_graphics_window() -> request_properties(props);
	}
	if (menuStatus==ms_start)
	{	
		if (player.arms!=NULL){
			player.arms->hide();
		}
		startMenuItems.show();
		gameModels.hide();
		menuItems.hide();
		optionMenuItems.hide();
		deathMenuItems.hide();
		WindowProperties props = window -> get_graphics_window() -> get_properties();
		props.set_cursor_hidden(false);
		props.set_mouse_mode(WindowProperties::M_absolute);
		window -> get_graphics_window() -> request_properties(props);
	}
	if (menuStatus==ms_option)
	{	
		if (player.arms!=NULL){
			player.arms->hide();
		}
		startMenuItems.hide();
		gameModels.hide();
		menuItems.hide();
		optionMenuItems.show();
		//deathMenuItems.hide();
		WindowProperties props = window -> get_graphics_window() -> get_properties();
		props.set_cursor_hidden(false);
		props.set_mouse_mode(WindowProperties::M_absolute);
		window -> get_graphics_window() -> request_properties(props);
	}
	
	if (menuStatus==ms_pause)
	{
		if (player.arms!=NULL){
			player.arms->hide();
		}
		startMenuItems.hide();
		gameModels.hide();
		menuItems.show();
		optionMenuItems.hide();
		//deathMenuItems.hide();
		WindowProperties props = window -> get_graphics_window() -> get_properties();
		props.set_cursor_hidden(false);
		props.set_mouse_mode(WindowProperties::M_absolute);
		window -> get_graphics_window() -> request_properties(props);
	}
	
}

void World::menuStart(){
	if (menuStatus == ms_deathfog || menuStatus==ms_dead){
		deathFogIncrease=0.0;
		player.deathFog->set_exp_density(0.0);
		window->get_render().set_fog(player.deathFog);
	}

	if (menuStatus==ms_start){
		menuStatus=ms_game;
	}
	else{
		menuStatus=ms_start;
	}
	
	if (menuStatus==ms_game)
	{	
		if (player.arms!=NULL){
			player.arms->hide();
		}
		startMenuItems.hide();
		gameModels.show();
		menuItems.hide();
		optionMenuItems.hide();
		deathMenuItems.hide();
		WindowProperties props = window -> get_graphics_window() -> get_properties();
		props.set_cursor_hidden(true);
		props.set_mouse_mode(WindowProperties::M_confined);
		window -> get_graphics_window() -> request_properties(props);
	}
	
	if (menuStatus==ms_start)
	{
		if (player.arms!=NULL){
			player.arms->hide();
		}
		startMenuItems.show();
		gameModels.hide();
		menuItems.hide();
		optionMenuItems.hide();
		deathMenuItems.hide();
		WindowProperties props = window -> get_graphics_window() -> get_properties();
		props.set_cursor_hidden(false);
		props.set_mouse_mode(WindowProperties::M_absolute);
		window -> get_graphics_window() -> request_properties(props);
	}
	
}

void World::menuDeath(){
	if (menuStatus == ms_deathfog || menuStatus==ms_dead){
		menuStatus=ms_start;
	}
	else{
		menuStatus=ms_deathfog;
	}
	

	if (menuStatus == ms_deathfog || menuStatus==ms_dead)
	{
		if (player.arms!=NULL){
			player.arms->hide();
		}

		startMenuItems.hide();
		gameModels.show();
		menuItems.hide();
		optionMenuItems.hide();
		//deathMenuItems.show(); //this shows later after the fog happens
		WindowProperties props = window -> get_graphics_window() -> get_properties();
		props.set_cursor_hidden(false);
		props.set_mouse_mode(WindowProperties::M_absolute);
		window -> get_graphics_window() -> request_properties(props);
	}else
	{	// (menuStatus==ms_start)
		if (player.arms!=NULL){
			player.arms->hide();
		}
		startMenuItems.show();
		gameModels.hide();
		menuItems.hide();
		optionMenuItems.hide();
		deathMenuItems.hide();
		player.deathFog->set_exp_density(0.0);
		window->get_render().set_fog(player.deathFog);

		WindowProperties props = window -> get_graphics_window() -> get_properties();
		props.set_cursor_hidden(true);
		props.set_mouse_mode(WindowProperties::M_confined);
		window -> get_graphics_window() -> request_properties(props);
	}
}

