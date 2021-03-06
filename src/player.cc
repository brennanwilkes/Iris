/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "global.hpp"
#include "player.hpp"
#include "gameObject.hpp"
#include <animControlCollection.h>
#include <auto_bind.h>

Player::Player() : GameObject() {}


CollisionTraverser Player::gtrav;
CollisionTraverser Player::ptrav;


void Player::tick() {
	if (speed>1 || !ground){
		GameObject::tick(1,1); 
	}
	
	totaltickcount++;
	
	if (coll_grav->get_airborne_height()>0.5){
		main_collection.play("Jump");
		//cout<<"YAAAS"<<endl;
	}
	
	if (tint>0){
		model.clear_color_scale();
		model.set_color_scale(1.0,1-tint,1-tint,1.0);
		tint-=0.05;
		//cout<<tint<<endl;
		if (tint<0){
			tint=0;
		}
		hitFog->set_exp_density(tint/200.0);
		window->get_render().set_fog(hitFog);
	}
	
	if (coll_grav->get_velocity()<-50.0){
		if(coll_grav->is_on_ground()){
			health=health+((coll_grav->get_velocity()+50.0)/2.0);
			
			//cout<<model<<" height "<<coll_grav->get_airborne_height()<<endl;
			//cout<<model<<" speed "<<coll_grav->get_velocity()<<endl;
			//cout<<model<<" health "<<health<<endl;
			
			//coll_grav->set_velocity(0.0);
		}
		
	}
	
	//GameObject::tick(); 
	ptrav.traverse(window -> get_render());
	
	/*
	if(totaltickcount%60 == 0){
		for (unsigned int i=0;i<gameLevel->exits.size();i++){
			if (player.model.get_x() >= gameLevel->exits[i].x1 && player.model.get_x() <= gameLevel->exits[i].x2){
				if (player.model.get_y() >= gameLevel->exits[i].y1 && player.model.get_y() <= gameLevel->exits[i].y2){
					if (player.model.get_z() >= gameLevel->exits[i].z1 && player.model.get_z() <= gameLevel->exits[i].z2){
						cout<<"Level change!"<<endl;
						
						player.lvlid = gameLevel->exits[i].lvlid;
						
						gameLevel->clear();
						
						gameLevel->save("Saves/"+player.savefilename+"/"+to_string(player.lvlid)+".lvl");
						
						kaboom(gameModels);
						
						
						gameLevel->load("Saves/"+player.savefilename+"/"+to_string(player.lvlid)+".lvl");
						
						break;
						
					}
				}
			}
		}
	}
	
	*/
	
	
	
}

void Player::init() {
	
	
	
	
	GameObject::init();
	
	PT(CollisionNode) c_Node;
	//For collisions
	c_Node = new CollisionNode("Coll_Sphere");
	c_Node -> add_solid(new CollisionSphere(0, 0, 0, 2.0));
	c_Node -> set_from_collide_mask(BitMask32::bit(0));
	c_Node -> set_into_collide_mask(BitMask32::all_off());
	sphereModel = model.attach_new_node(c_Node);
	sphereModel.set_color(255,0,0,1.0);
	coll_push -> add_collider(sphereModel, model);
	
	ptrav.add_collider(sphereModel, coll_push);
	gtrav.add_collider(rayModel, coll_grav);
	
	coll_grav->set_gravity(70.0*2);
	
	sphereModel.set_pos(sphereModel.get_x(),sphereModel.get_y(),sphereModel.get_z()+5);
	sphereModelTwo.set_pos(sphereModel.get_x(),sphereModel.get_y(),sphereModel.get_z());
	
}

void Player::set_up(NodePath* parent,WindowFramework* w,PandaFramework* pf,string dir,bool respawn){
	if(respawn){
		model = w -> load_model(pf->get_models(),dir+"Assets/Iris/Iris.egg");
		model.set_scale(0.5);
		model.set_pos(0, 0, 2);
		model.set_hpr(0, 0, 0);
		model.set_shader_auto();
		model.reparent_to(*parent);
		
		
		name_collection.clear_anims();
		NodePath animNp9 = w->load_model(model, dir + "Assets/Iris/Iris-walk.egg");
		auto_bind(model.node(), name_collection);
		PT(AnimControl) animPtr = name_collection.get_anim(0);
		main_collection.store_anim(animPtr, "walk");
		string animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp9.detach_node();
		main_collection.play("walk");
		NodePath animNp10 = w->load_model(model, dir + "Assets/Iris/Iris-Idle.egg");
		auto_bind(model.node(), name_collection);
		animPtr = name_collection.get_anim(0);
		main_collection.store_anim(animPtr, "idle");
		animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp10.detach_node();
		main_collection.play("idle");
		
		
	
		NodePath animNp11 = w->load_model(model, dir + "Assets/Iris/Iris-Jump.egg");
		auto_bind(model.node(), name_collection);
		animPtr = name_collection.get_anim(0);
		main_collection.store_anim(animPtr, "Jump");
		animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp11.detach_node();
		main_collection.play("Jump");
	
	}
	else{
		camera = w -> get_camera_group(); 
		camera.set_pos(0, 0, 6);
		mode=1;
		type="player";
		zoom=1.0;
		doublejump=false;
		hitbox=false;
	
		max_weight=40.0;
		weight=0.0;
	
		max_volume=10.0;
		volume=0.0;
	
		recoil_frames=0;
		recoil_mult=0.0;
	
		tint=0;
	
		kills=0;
		deaths=0;
		xp=0.0;
	
		pullout=-1;
	
		totaltickcount=0;
	
		model = w -> load_model(pf->get_models(),dir+"Assets/Iris/Iris.egg");
		model.set_scale(0.5);
		model.set_pos(0, 0, 2);
		model.set_hpr(0, 0, 0);
		model.set_shader_auto();
		model.reparent_to(*parent);

		pistol_arms = w -> load_model(pf->get_models(),dir+"Assets/Iris/FirstPersonViewModel.egg");
		pistol_arms.set_scale(0.5);
		pistol_arms.set_pos(0.1, 0.3, -0.57);
		pistol_arms.set_hpr(0, 0, 0);
		pistol_arms.set_shader_auto();
		pistol_arms.reparent_to(camera);
		arms_shown = false;
		pistol_arms.hide();
	
		bat_arms = w -> load_model(pf->get_models(),dir+"Assets/Iris/fpvBat.egg");
		bat_arms.set_scale(0.5);
		bat_arms.set_pos(0.1, 0.3, -0.57);
		bat_arms.set_hpr(0, 0, 0);
		bat_arms.set_shader_auto();
		bat_arms.reparent_to(camera);
		//arms_shown = false;
		bat_arms.hide();
	
		empty_arms = w -> load_model(pf->get_models(),dir+"Assets/Iris/EmptyHands.egg");
		empty_arms.set_scale(0.5);
		empty_arms.set_pos(0.1, 0.3, -0.57);
		empty_arms.set_hpr(0, 0, 0);
		empty_arms.set_shader_auto();
		empty_arms.reparent_to(camera);
		//arms_shown = false;
		empty_arms.hide();
	
		ak_arms = w -> load_model(pf->get_models(),dir+"Assets/Iris/fpvak47.egg");
		ak_arms.set_scale(0.5);
		ak_arms.set_pos(0.2, 0.7, -0.57);
		ak_arms.set_hpr(0, 0, 0);
		ak_arms.set_shader_auto();
		ak_arms.reparent_to(camera);
		//arms_shown = false;
		ak_arms.hide();
	
		negev_arms = w -> load_model(pf->get_models(),dir+"Assets/Iris/negev.egg");
		negev_arms.set_scale(0.5);
		negev_arms.set_pos(0.2, 0.7, -0.57);
		negev_arms.set_hpr(0, 0, 0);
		negev_arms.set_shader_auto();
		negev_arms.reparent_to(camera);
		//arms_shown = false;
		negev_arms.hide();
		//NodePath cheese_arms;
		//NodePath pill_arms;
		//NodePath water_arms;
		
		cheese_arms = w -> load_model(pf->get_models(),dir+"Assets/Iris/cheesehands.egg");
		cheese_arms.set_scale(0.5);
		cheese_arms.set_pos(0.1, 0.3, -0.57);
		cheese_arms.set_hpr(0, 0, 0);
		cheese_arms.set_shader_auto();
		cheese_arms.reparent_to(camera);
		cheese_arms.hide();
		
		water_arms = w -> load_model(pf->get_models(),dir+"Assets/Iris/waterbottlehands.egg");
		water_arms.set_scale(0.5);
		water_arms.set_pos(0.1, 0.3, -0.57);
		water_arms.set_hpr(0, 0, 0);
		water_arms.set_shader_auto();
		water_arms.reparent_to(camera);
		water_arms.hide();
		
		pill_arms = w -> load_model(pf->get_models(),dir+"Assets/Iris/pillhands.egg");
		pill_arms.set_scale(0.5);
		pill_arms.set_pos(0.1, 0.3, -0.57);
		pill_arms.set_hpr(0, 0, 0);
		pill_arms.set_shader_auto();
		pill_arms.reparent_to(camera);
		pill_arms.hide();
		
		gauze_arms = w -> load_model(pf->get_models(),dir+"Assets/Iris/gauzehands.egg");
		gauze_arms.set_scale(0.5);
		gauze_arms.set_pos(0.1, 0.3, -0.57);
		gauze_arms.set_hpr(0, 0, 0);
		gauze_arms.set_shader_auto();
		gauze_arms.reparent_to(camera);
		gauze_arms.hide();
		
		
		
		///////////////////////////////////////////////////////////////////////////
		//PT(AnimControl) animPtr;
		name_collection.clear_anims();
	
		//AnimControlCollection tempCollection;
		NodePath animNp1 = w->load_model(pistol_arms, dir + "Assets/Iris/FirstPersonViewModel-Fire.egg");
		auto_bind(pistol_arms.node(), name_collection);
		PT(AnimControl) animPtr = name_collection.get_anim(0);
		pistol_collection.store_anim(animPtr, "pistol_shoot");
		string animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp1.detach_node();
		pistol_collection.play("pistol_shoot");
		NodePath animNp2 = w->load_model(pistol_arms, dir + "Assets/Iris/FirstPersonViewModel-pull_out_pistol.egg");
		auto_bind(pistol_arms.node(), name_collection);
		animPtr = name_collection.get_anim(0);
		pistol_collection.store_anim(animPtr, "pistol_reload");
		animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp2.detach_node();
		pistol_collection.play("pistol_reload");
	
		NodePath animNp3 = w->load_model(bat_arms, dir + "Assets/Iris/fpvBat-atttack.egg");
		auto_bind(bat_arms.node(), name_collection);
		animPtr = name_collection.get_anim(0);
		bat_collection.store_anim(animPtr, "bat_shoot");
		animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp3.detach_node();
		bat_collection.play("bat_shoot");
		NodePath animNp4 = w->load_model(bat_arms, dir + "Assets/Iris/fpvBat-pull_out_bat.egg");
		auto_bind(bat_arms.node(), name_collection);
		animPtr = name_collection.get_anim(0);
		bat_collection.store_anim(animPtr, "bat_reload");
		animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp4.detach_node();
		bat_collection.play("bat_reload");
	
		NodePath animNp5 = w->load_model(ak_arms, dir + "Assets/Iris/fpvak47-fire.egg");
		auto_bind(ak_arms.node(), name_collection);
		animPtr = name_collection.get_anim(0);
		ak_collection.store_anim(animPtr, "ak_shoot");
		animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp5.detach_node();
		ak_collection.play("ak_shoot");
		NodePath animNp6 = w->load_model(ak_arms, dir + "Assets/Iris/fpvak47-pull_out_gun.egg");
		auto_bind(ak_arms.node(), name_collection);
		animPtr = name_collection.get_anim(0);
		ak_collection.store_anim(animPtr, "ak_reload");
		animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp6.detach_node();
		ak_collection.play("ak_reload");
	
		NodePath animNp7 = w->load_model(negev_arms, dir + "Assets/Iris/negev-fire.egg");
		auto_bind(negev_arms.node(), name_collection);
		animPtr = name_collection.get_anim(0);
		negev_collection.store_anim(animPtr, "negev_shoot");
		animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp7.detach_node();
		negev_collection.play("negev_shoot");
		NodePath animNp8 = w->load_model(negev_arms, dir + "Assets/Iris/negev-pull_out_gun.egg");
		auto_bind(negev_arms.node(), name_collection);
		animPtr = name_collection.get_anim(0);
		negev_collection.store_anim(animPtr, "negev_reload");
		animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp8.detach_node();
		negev_collection.play("negev_reload");
	
		NodePath animNp9 = w->load_model(model, dir + "Assets/Iris/Iris-walk.egg");
		auto_bind(model.node(), name_collection);
		animPtr = name_collection.get_anim(0);
		main_collection.store_anim(animPtr, "walk");
		animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp9.detach_node();
		main_collection.play("walk");
		NodePath animNp10 = w->load_model(model, dir + "Assets/Iris/Iris-Idle.egg");
		auto_bind(model.node(), name_collection);
		animPtr = name_collection.get_anim(0);
		main_collection.store_anim(animPtr, "idle");
		animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp10.detach_node();
		main_collection.play("idle");
	
		NodePath animNp11 = w->load_model(model, dir + "Assets/Iris/Iris-Jump.egg");
		auto_bind(model.node(), name_collection);
		animPtr = name_collection.get_anim(0);
		main_collection.store_anim(animPtr, "Jump");
		animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp11.detach_node();
		main_collection.play("Jump");
	
	
	
	
	
		w->load_model(empty_arms, dir + "Assets/Iris/EmptyHands-Idle.egg");
		auto_bind(empty_arms.node(), empty_collection);
		empty_collection.loop_all(true);//"Armature");
		
		w->load_model(cheese_arms, dir + "Assets/Iris/cheesehands-Idle.egg");
		auto_bind(cheese_arms.node(), cheese_collection);
		cheese_collection.loop_all(true);//"Armature");
		
		w->load_model(water_arms, dir + "Assets/Iris/waterbottlehands-Idle.egg");
		auto_bind(water_arms.node(), water_collection);
		water_collection.loop_all(true);//"Armature");
		
		w->load_model(pill_arms, dir + "Assets/Iris/pillhands-Idle.egg");
		auto_bind(pill_arms.node(), pill_collection);
		pill_collection.loop_all(true);//"Armature");
		
		NodePath animNp88 = w->load_model(gauze_arms, dir + "Assets/Iris/gauzehands-pull_out_pistol.egg");
		auto_bind(gauze_arms.node(), name_collection);
		animPtr = name_collection.get_anim(0);
		gauze_collection.store_anim(animPtr, "gauze_reload");
		animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp88.detach_node();
		gauze_collection.play("gauze_reload");
		
		/*w->load_model(gauze_arms, dir + "Assets/Iris/waterbottlehands-Idle.egg");
		auto_bind(gauze_arms.node(), gauze_collection);
		gauze_collection.loop_all(true);//"Armature");*/
	
		////////////////////////////////////////////////////////////////////////////////
	
		max_food=100;
		food=100;
	
		max_water=100;
		water=100;
	
		max_health=100;
		health=100;
	
	
		setVel(0,0,0);
	
	
	
		//Fog hitFog;
		hitFog = new Fog("Hit Fog");
		hitFog->set_color(1.0,0.0,0.0);
		hitFog->set_exp_density(0.0);
		w->get_render().set_fog(hitFog);

		deathFog = new Fog("deathFog");
		deathFog->set_color(0.0,0.0,0.0);
		deathFog->set_exp_density(0.0);
		w->get_render().set_fog(deathFog);

		ground = false;
	
		lvlid=0;
	}
	
}

void Player::coll_set_up(){
	qcoll_pickup = new CollisionHandlerQueue;

	PT(CollisionNode) c_Node;
	/*
	c_Node = new CollisionNode("Player_sphere");
	c_Node -> add_solid(new CollisionSphere(0, 0, 4, 2.0));
	c_Node -> set_from_collide_mask(BitMask32::bit(0));
	c_Node -> set_into_collide_mask(BitMask32::bit(0));
	sphereModel = model.attach_new_node(c_Node);

	sphereModel.show();
	coll_push -> add_collider(sphereModel, model);
	ptrav.add_collider(sphereModel, coll_push);
	*/
	
	
	
	/*c_Node = new CollisionNode("Player_sphere_Tracker");
	c_Node -> add_solid(new CollisionSphere(0, 0, 4, 2.0));
	c_Node -> set_from_collide_mask(BitMask32::bit(0));
	c_Node -> set_into_collide_mask(BitMask32::bit(4));
	sphereModelTracker = model.attach_new_node(c_Node);

	sphereModelTracker.show();
	//coll_push -> add_collider(sphereModelTracker, model);
	//ptrav.add_collider(sphereModelTracker, coll_push);
	*/
	
	
	
	
	/*c_Node = new CollisionNode("Player_pickup_ray");
	c_Node -> add_solid(new CollisionSegment(0, 0, 0, 0, 20, 0));
	c_Node -> set_from_collide_mask(BitMask32::bit(2));
	c_Node -> set_into_collide_mask(BitMask32::all_off());
	pickupRayModel = camera.attach_new_node(c_Node);

	//pickupRayModel.show();
	qtrav_pickup.add_collider(pickupRayModel, qcoll_pickup);
	*/
	
	// Player Shoot ray setup.
	// BRENNAN when you set up the player constructor, put this in there as well. It should be the same as everything else.
	// I have a function called shoot that does the raytrace and randomized inaccuracy called "shoot"
	qcoll_shoot = new CollisionHandlerQueue;
	c_Node = new CollisionNode("Player_Shoot");
	c_Node -> add_solid(new CollisionRay(0, 0, 0, 0, 1, 0));
	c_Node -> set_from_collide_mask(BitMask32::bit(1));
	c_Node -> set_into_collide_mask(BitMask32::all_off());
	shootRayModel = camera.attach_new_node(c_Node);
	shootRayModel.show();
	qtrav_shoot.add_collider(shootRayModel, qcoll_shoot);
	
	
	
	
	
	
	
}


bool Player::pick_up(PandaNode* itm,vector<Item*> &itms){
	//cout<<"HARDER DADDY"<<endl;
	for (unsigned int i = 0; i < itms.size(); i++){
		if(itm == itms[i] -> sphereModelTwo.node()){
			int trans=0;
			if (player.mode){
				trans=20;
			}
			if (player.model.get_distance(itms[i]->model)-trans > 30){
				return false;
			}
			if (itms[i]->type=='g'){
				/*for (unsigned int x=0;x<inventory.size();x++){
					if (itms[i]->id==inventory[x]->id){
						inventory[x]->tot_ammo+=itms[i]->tot_ammo;
						itms[i]->tot_ammo=0;
						itms[i]->model.set_color_scale(0.1,0.1,0.1,1.0);
						return true;
					}
				
				}*/			//this is taking ammo from guns dont delete
			}
			else if (itms[i]->type=='a'){
				for (unsigned int x=0;x<inventory.size();x++){
					if (itms[i]->id==inventory[x]->id){
						inventory[x]->tot_ammo+=itms[i]->amount;
						itms[i]->model.detach_node();
						itms[i]->model.remove_node();
						itms.erase(itms.begin()+i);
						return true;
					}
			
				}
				return false;
			}
			if((itms[i] -> weight + weight <= max_weight) && (itms[i] -> volume + volume <= max_volume)){
				inventory.push_back(itms[i]);
				itms.erase(itms.begin()+i);
				weight+=inventory.back()->weight;
				volume+=inventory.back()->volume;
				inventory.back()->model.detach_node();
				
				return true;
			}
			else{
				return false;
			}
			
		}
	}
	return false;
	
	
}
bool Player::drop(int itr,vector<Item*> &itms,NodePath* parent){
	if ((unsigned int)itr >= 0 && (unsigned int)itr < inventory.size()){
		itms.push_back(inventory[itr]);
		player.removeItem(itr);
		//cout<<model.get_pos()<<endl;
		itms.back() -> model.reparent_to(*parent);
		itms.back() -> model.set_pos(model.get_pos().get_x(),model.get_pos().get_y(),model.get_pos().get_z()+5);
		itms.back() -> model.show();
		itms.back() -> sphereModelTwo.show();
		
		float rot = player.camera.get_hpr().get_x();
		float tx = -20.0 * sin(rot * (3.1416 / 180));
		float ty = 20.0 * cos(rot * (3.1416 / 180));
		//cout<<tx<<" "<<ty<<endl;
		itms.back() -> setVel(tx,ty,0);
		return true;
	}
	
	return false;
}

void Player::refill(int md,float am){
	if (md==0){
		health+=am;
		if (health>max_health){
			health=max_health;
		}
	}
	else if (md==1){
		food+=am;
		if (food>max_food){
			food=max_food;
		}
	}
	else if (md==2){
		water+=am;
		if (water>max_water){
			water=max_water;
		}
	}
	
}

void Player::removeItem(int itr){
	weight -= inventory[itr] -> weight;
	volume -= inventory[itr] -> volume;
	inventory.erase(inventory.begin() + itr);
	
}

void Player::play_anim(){
	if (player.mainHand->id==0){
		pistol_collection.play("pistol_shoot");
	}
	if (player.mainHand->id==2){
		bat_collection.play("bat_shoot");
	}
	if (player.mainHand->id==10){
		ak_collection.play("ak_shoot");
	}
	if (player.mainHand->id==11 && player.negev_collection.get_frame()>1 ){
		//cout<<negev_collection.get_anim_name(0)<<endl;
		//cout<<negev_collection.get_anim_name(1)<<endl;
		negev_collection.play("negev_shoot");
	}
	
	
}

void Player::death(vector<Item*> &v,NodePath* parent){
	
	float r,r2,r3;
	unsigned int send_nudes=inventory.size();
	for (unsigned int i=0;i<send_nudes;i++){
		r=rand()/(float)RAND_MAX;
		r2=rand()/(float)RAND_MAX;
		r3=rand()/(float)RAND_MAX;
		
		
		drop(0,v,parent);
		v.back() -> accel((r-0.5),(r2-0.5),r3);
	}
	deaths++;
	xp+=1;
	health=100;
	food=100;
	water=100;
	player.arms=&player.empty_arms;
	player.mainHand=NULL;
	calc_arms();
	
	player.model.set_x(gameLevel->spawn_x);
	player.model.set_y(gameLevel->spawn_y);
	player.model.set_z(gameLevel->spawn_z);

	//this was segfaulting 
	
	//cout<<player.lvlid<<endl;
	//cout<<gameLevels.size()<<endl;
	
	model.set_x(gameLevel->spawn_x);
	model.set_y(gameLevel->spawn_y);
	model.set_z(gameLevel->spawn_z);
	model.show();
	
}
void Player::calc_arms(){
	
	
	weightNode->set_text(to_string((int)weight)+" kg");
	volumeNode->set_text(to_string((int)volume)+" L");
	weightNodePath.show();
	volumeNodePath.show();
	
	
	bool on=false;
	
	pistol_arms.hide();
	bat_arms.hide();
	empty_arms.hide();
	ak_arms.hide();
	negev_arms.hide();
	cheese_arms.hide();
	water_arms.hide();
	pill_arms.hide();
	gauze_arms.hide();
	if (arms!=NULL){
		arms->hide();
	}
	
	
	
	ammoNodePath.hide();
	ammoNodePath2.hide();
	
	if (mainHand!=NULL){
		
		
		ammoNode->set_text(to_string((int)mainHand->amount));
		ammoNode2->set_text(to_string((int)mainHand->tot_ammo));
		
		
		if (arms_shown){
			if (mainHand->type=='g'){
				
				ammoNodePath.show();
				ammoNodePath2.show();
				
				//arms->hide();
				if (mainHand->id==0){
					on=true;
					arms=&pistol_arms;

				}
				if (mainHand->id==2){
					on=true;
					arms=&bat_arms;

				}
				if (mainHand->id==10){
					on=true;
					arms=&ak_arms;

				}
				if (mainHand->id==11){
					on=true;
					arms=&negev_arms;

				}
		
			}
			else if (mainHand->type=='c'){
				ammoNodePath.show();
				
				if (mainHand->id==20){
					on=true;
					arms=&cheese_arms;

				}
				if (mainHand->id==21){
					on=true;
					arms=&water_arms;

				}
				if (mainHand->id==22){
					on=true;
					arms=&pill_arms;

				}
				if (mainHand->id==23){
					on=true;
					arms=&gauze_arms;

				}
				
			}
		}
		
	}
	else{
		arms=&empty_arms;
		//arms->show();
		on=true;
	}
	
	if (!on){
		arms=NULL;
		arms_shown=false;
		//arms=&empty_arms;
		
	}
	else{
		//arms->show();
	}
}

//void recoil(int fc, float mult){
//
//}


void Player::kaboom(NodePath root){
	
	
	
	int t;
	StaticObject* t_stat;
	Item* t_itm;
	Enemy* t_enem;
		
	t=stats.size();
	for (int i=0;i<t;i++){
		stats[0]->model.remove_node();
		t_stat=stats[0];
		stats.erase(stats.begin());
		delete t_stat;
	}
	
	t=itms.size();
	for (int i=0;i<t;i++){
		itms[0]->model.remove_node();
		t_itm=itms[0];
		itms.erase(itms.begin());
		delete t_itm;
	}
	
	t=enems.size();
	for (int i=0;i<t;i++){
		enems[0]->model.remove_node();
		t_enem=enems[0];
		enems.erase(enems.begin());
		delete t_enem;
	}	
}

