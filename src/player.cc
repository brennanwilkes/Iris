#include "global.hpp"
#include "player.hpp"
#include "gameObject.hpp"

Player::Player() : GameObject() {}

void Player::tick() {
	if (speed>1 || !ground){
		GameObject::tick(1,1); 
	}
	
	totaltickcount++;
	
	
	if (tint>0){
		model.clear_color_scale();
		model.set_color_scale(1.0,1-tint,1-tint,1.0);		
		tint-=0.05;
		//cout<<tint<<endl;
		if (tint<0){
			tint=0;
		}
		hitFog->set_exp_density(tint/200.0);
	}
	
	if (coll_grav->get_velocity()<-50.0){
		if(coll_grav->is_on_ground()){
			health=health+((coll_grav->get_velocity()+50.0)/2.0);
			
			cout<<model<<" height "<<coll_grav->get_airborne_height()<<endl;
			cout<<model<<" speed "<<coll_grav->get_velocity()<<endl;
			cout<<model<<" health "<<health<<endl;
			
			//coll_grav->set_velocity(0.0);
		}
		/*cout<<model<<" height "<<coll_grav->get_airborne_height()<<endl;
		cout<<model<<" speed "<<coll_grav->get_impact_velocity()<<endl;
		cout<<model<<" health "<<health<<endl;*/
	}
	
	//GameObject::tick(); 
	ptrav.traverse(window -> get_render());
	if(totaltickcount%60 == 0){
		if(gameLevels.size()>(unsigned int)player.lvlid){
			for (unsigned int i=0;i<gameLevels[player.lvlid]->exits.size();i++){
				if (player.model.get_x() >= gameLevels[player.lvlid]->exits[i].x1 && player.model.get_x() <= gameLevels[player.lvlid]->exits[i].x2){
					if (player.model.get_y() >= gameLevels[player.lvlid]->exits[i].y1 && player.model.get_y() <= gameLevels[player.lvlid]->exits[i].y2){
						if (player.model.get_z() >= gameLevels[player.lvlid]->exits[i].z1 && player.model.get_z() <= gameLevels[player.lvlid]->exits[i].z2){
							cout<<"Level change!"<<endl;
							
							//gameLevels[player.lvlid]->save("Saves/"+player.savefilename+"/"+to_string(player.lvlid)+".isf");
							
							player.lvlid = gameLevels[player.lvlid]->exits[i].lvlid;
							
							//gameLevels[player.lvlid]->load("Story/"+to_string(player.lvlid)+".isf");
							
							
							
							break;
							
						}
					}
				}
			}
		}
	}
	
	
	
	
	
	
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
	GameObject::ptrav.add_collider(sphereModel, coll_push);
	
	
	sphereModel.set_pos(sphereModel.get_x(),sphereModel.get_y(),sphereModel.get_z()+5);
	sphereModelTwo.set_pos(sphereModel.get_x(),sphereModel.get_y(),sphereModel.get_z());
	
}

void Player::set_up(NodePath* parent,WindowFramework* w,PandaFramework* pf,string dir){
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
	
	
	//cout<<dir<<endl;
	
	
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
	
	ground = false;
	
	lvlid=0;
	
	
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
bool Player::drop(int itr,vector<Item*> itms,NodePath* parent){
	if ((unsigned int)itr >= 0 && (unsigned int)itr < inventory.size()){
		itms.push_back(inventory[itr]);
		player.removeItem(itr);
		cout<<model.get_pos()<<endl;
		itms.back() -> model.reparent_to(*parent);
		itms.back() -> model.set_pos(model.get_pos().get_x(),model.get_pos().get_y(),model.get_pos().get_z()+5);
		itms.back() -> model.show();
		itms.back() -> setVel(0,0,0);
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
		pistol_collection.play("Armature");
	}
	if (player.mainHand->id==2){
		bat_collection.play("Armature");
	}
	if (player.mainHand->id==10){
		ak_collection.play("Armature");
	}
	
	
}
void Player::death(vector<Item*> v,NodePath* parent){
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
}
void Player::calc_arms(){
	
	
	weightNode->set_text(to_string((int)weight)+" lbs");
	volumeNode->set_text(to_string((int)volume)+" m^3");
	weightNodePath.show();
	volumeNodePath.show();
	
	
	bool on=false;
	
	pistol_arms.hide();
	bat_arms.hide();
	empty_arms.hide();
	ak_arms.hide();
	if (arms!=NULL){
		arms->hide();
	}
	
	//cout<<"hji"<<endl;
	
	ammoNodePath.hide();
	ammoNodePath2.hide();
	
	//cout<<"yp"<<endl;
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
		
			}
			else if (mainHand->type=='c'){
				ammoNodePath.show();
			}
		}
		
	}
	else{
		arms=&empty_arms;
		//arms->show();
		on=true;
	}
	
	//cout<<on<<endl;
	if (!on){
		arms=NULL;
		arms_shown=false;
		//arms=&empty_arms;
		
	}
	else{
		//arms->show();
	}
	//cout<<"Blah"<<endl;
}

//void recoil(int fc, float mult){
//
//}




