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
	game_running = 1;
	pause_menu = 0;
	option_menu = 0;
}

void World::init(){
	player.init();
	for (auto &itm:itms)
		itm -> init();
}

void World::tick(){
	//cout<<player.health<<endl;
	dt = globalClock -> get_real_time() - preTime;

	//float timetest=globalClock -> get_real_time();
	//float timetest2=globalClock -> get_real_time();
	
	player.tick();
	
	/*timetest=globalClock -> get_real_time()-timetest2;
	timetest2 = globalClock -> get_real_time();

	cout << "player tick \t\t"<<timetest << endl;
	*/
	
	
	for (unsigned int i=0;i<itms.size();i++){
		itms[i]->tick();
	}
	for (unsigned int i=0;i<enems.size();i++){
		enems[i]->tick(1);
	}
	

	//timetest=globalClock -> get_real_time()-timetest2;
	//timetest2 = globalClock -> get_real_time();
	//cout << "item tick \t\t"<<timetest << endl;
	
	
	//cout<<"before arms"<<endl;
	/*for (auto &itm:itms){
		itm -> tick();
	}*/
	
	
	player.calc_arms();
	
	
	//timetest=globalClock -> get_real_time()-timetest2;
	//timetest2 = globalClock -> get_real_time();
	//cout << timetest << endl;
	//cout<<"after arms"<<endl;
	
	
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
	
	
	//timetest=globalClock -> get_real_time()-timetest2;
	//timetest2 = globalClock -> get_real_time();
	//cout << timetest << endl;
	
	
	//RECOIL
	if (player.recoil_frames>0){
		
		float ranR=rand()/(float)RAND_MAX;
		
		ranR++;
		player.recoil_frames--;
		
		
		
		
		ranR-=1.5;
		ranR*=2;
		
		player.camera.set_p(player.camera,player.recoil_mult*ranR);
		player.camera.set_h(player.camera,player.recoil_mult*ranR);
		
		
	}
	
	
	//timetest=globalClock -> get_real_time()-timetest2;
	//timetest2 = globalClock -> get_real_time();
	//cout << timetest << endl;
	
	
	//cout<<tickCount&2<<endl;
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
	
	
	
	//timetest=globalClock -> get_real_time()-timetest2;
	//timetest2 = globalClock -> get_real_time();
	//cout << timetest << endl;
	
	
	
	
	
	
	
	
	tickCount++;
	if (tickCount>120){
		float ran=rand()/(float)RAND_MAX;
		
		//cout<<" "<<ran<<" "<<player.speed<<" "<<ran/player.speed<<endl;
		
		//cout << ran << " " << (100-player.water)/500.0 << endl;
		
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
		
		
		
		
		
		
		//cout<<player.water<<endl;
		tickCount=0;
	}
	
	
	//timetest=globalClock -> get_real_time()-timetest2;
	//timetest2 = globalClock -> get_real_time();
	//cout << timetest << endl<<endl;
	
	
	preTime = globalClock -> get_real_time();
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
		player.rayModel.show();
		for (unsigned int ij=0;ij<itms.size();ij++){
			itms[ij]->sphereModel.show();
			itms[ij]->rayModel.show();
		}
		for (unsigned int ij=0;ij<enems.size();ij++){
			enems[ij]->sphereModel.show();
			enems[ij]->rayModel.show();
			
		}
	}
	else{
		player.sphereModel.hide();
		player.rayModel.hide();
		for (unsigned int ij=0;ij<itms.size();ij++){
			itms[ij]->sphereModel.hide();
			itms[ij]->rayModel.hide();
		}
		for (unsigned int ij=0;ij<enems.size();ij++){
			enems[ij]->sphereModel.hide();
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

void World::look(WindowFramework *win){
	GraphicsWindow *gw = win -> get_graphics_window();
	if (gw)
	{
		int dx = (gw -> get_properties().get_x_size() / 2) - gw -> get_pointer(0).get_x();
		int dy = (gw -> get_properties().get_y_size() / 2) - gw -> get_pointer(0).get_y();
		
		player.camera.set_hpr(player.camera.get_hpr().get_x()+ dx * 0.03, player.camera.get_hpr().get_y() + dy * 0.03, 0);
		gw -> move_pointer(0, gw -> get_properties().get_x_size() / 2, gw -> get_properties().get_y_size() / 2);
	}
}

void World::move(map <std::string, pair<ButtonHandle, bool> > &keybinds){
	float rot = player.camera.get_hpr().get_x();
	float dx(0), dy(0);
	float walk(2);

	player.speed=1;
	if (keybinds["forward"].second) 
	{
		dx += -2.0 * sin(rot * (3.1416 / 180));
		dy += 2.0 * cos(rot * (3.1416 / 180));
		player.speed=4;
	}
	if (keybinds["backward"].second)
	{
		dx += 2.0 * sin(rot * (3.1416 / 180));
		dy += -2.0 * cos(rot * (3.1416 / 180));
		player.speed=4;
	}
	if (keybinds["left"].second)
	{
		dx += 2.0 * sin((rot - 90) * (3.1416 / 180));
		dy += -2.0 * cos((rot - 90) * (3.1416 / 180));
		player.speed=4;
	}
	if (keybinds["right"].second)
	{
		dx += 2.0 * sin((rot + 90) * (3.1416 / 180));
		dy += -2.0 * cos((rot + 90) * (3.1416 / 180));
		player.speed=4;
	}
	
	if (keybinds["walk"].second){
		walk=0.25;
		player.speed=2;
	}
	
	if (keybinds["sprint"].second){
		walk=5;
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
	
	/*if (keybinds["drop"].second)
		player.camera.set_hpr(player.camera.get_hpr().get_x() + 2.0, player.camera.get_hpr().get_y(), 0);
	if (keybinds["pickup].second)
		player.camera.set_hpr(player.camera.get_hpr().get_x() - 2.0, player.camera.get_hpr().get_y(), 0);
	*/
	
	// Move the player
	player.model.set_fluid_x(player.model.get_x() + dx * dt * 15 * walk);
	player.model.set_fluid_y(player.model.get_y() + dy * dt * 15 * walk);
	
	if (dx != 0  || dy != 0)
	{
		player.model.set_hpr(player.camera.get_hpr().get_x(), 0, 0);
	}
	
	
	
}



void World::apply_grav(){
	if (dt <= 0.1){
		
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
}

void World::menu(){
	game_running = 1 - game_running;
	pause_menu = 1 - pause_menu;
	
	if (game_running)
	{
		if (player.arms!=NULL){
			player.arms->show();
		}
		gameModels.show();
		menuItems.hide();
		optionMenuItems.hide();
		WindowProperties props = window -> get_graphics_window() -> get_properties();
		props.set_cursor_hidden(true);
		props.set_mouse_mode(WindowProperties::M_confined);
		window -> get_graphics_window() -> request_properties(props);
	}
	//cout<<"- "<<pause_menu<<endl;
	else if (pause_menu)
	{	
		/*for (unsigned int j=0;j<player.weapons.size();j++){
			if (j!=(unsigned int)player.weaponN){
				player.weapons[j].Node.hide();
			}
		}*/
		if (player.arms!=NULL){
			player.arms->hide();
		}
		gameModels.hide();
		menuItems.show();
		optionMenuItems.hide();
		WindowProperties props = window -> get_graphics_window() -> get_properties();
		props.set_cursor_hidden(false);
		props.set_mouse_mode(WindowProperties::M_absolute);
		window -> get_graphics_window() -> request_properties(props);
		
		
		
	}
	
	//if (option_menu)
	else
	{	
		/*for (unsigned int j=0;j<player.weapons.size();j++){
			if (j!=(unsigned int)player.weaponN){
				player.weapons[j].Node.hide();
			}
		}*/
		if (player.arms!=NULL){
			player.arms->hide();
		}
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
	option_menu= 1 - option_menu;
	pause_menu = 1 - pause_menu;
	
	//cout<<"- "<<pause_menu<<endl;
	//cout<<"-- "<<option_menu<<endl;
	if (option_menu)
	{	
		/*for (unsigned int j=0;j<player.weapons.size();j++){
			if (j!=(unsigned int)player.weaponN){
				player.weapons[j].Node.hide();
			}
		}*/
		if (player.arms!=NULL){
			player.arms->hide();
		}
		gameModels.hide();
		menuItems.hide();
		optionMenuItems.show();
		WindowProperties props = window -> get_graphics_window() -> get_properties();
		props.set_cursor_hidden(false);
		props.set_mouse_mode(WindowProperties::M_absolute);
		window -> get_graphics_window() -> request_properties(props);
		
		
		
	}
	
	if (pause_menu)
	{
		if (player.arms!=NULL){
			player.arms->hide();
		}
		gameModels.hide();
		menuItems.show();
		optionMenuItems.hide();
		WindowProperties props = window -> get_graphics_window() -> get_properties();
		props.set_cursor_hidden(false);
		props.set_mouse_mode(WindowProperties::M_absolute);
		window -> get_graphics_window() -> request_properties(props);
	}
	
}

