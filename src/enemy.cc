/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "global.hpp"
#include "enemy.hpp"
#include "gameObject.hpp"
#include <auto_bind.h>

Enemy::Enemy() : GameObject() {}

CollisionTraverser Enemy::gtrav;
CollisionTraverser Enemy::ptrav;

void Enemy::tick(int m) {
	
	tickFrame++;
	tickFrame2++;
	if(tickFrame2>60){
		
		tickFrame2=0;
		
		float xd,yd,zd,td;//,x2,y2,z2;
	
		xd=model.get_x()-player.model.get_x();
		yd=model.get_y()-player.model.get_y();
		zd=model.get_z()-player.model.get_z();
	
		xd= pow(xd*xd,0.5);
		yd= pow(yd*yd,0.5);
		zd= pow(zd*zd,0.5);
	
		td=pow(pow(pow((xd*xd)+(yd*yd),0.5),2)+(zd*zd),0.5);
	
		if (td<range && check_sight()){			//CHANGE TO VARIABLE
			attack();
		}
	}
	if (tickFrame>60 || (running&&tickFrame>6)){
		tickFrame=0;
		check_sight();
	}
	
	
	if (running){
		bas_mov(target);			//CHANGE TO VARIABLE
		if(anim_collection.get_frame()-anim_collection.get_num_frames()==-1 || anim_collection.which_anim_playing()=="idle"){
			anim_collection.loop("walk",true);
		}
	}
	else{
		if(anim_collection.get_frame()-anim_collection.get_num_frames()==-1 || anim_collection.which_anim_playing()=="walk"){	
			anim_collection.loop("idle",true);
		}
	}
	
	if (tint>0){
		model.clear_color_scale();
		model.set_color_scale(1.0,1-tint,1-tint,1.0);		
		tint-=0.05;
	}
	
	//GameObject::tick(1,0);
	
	if (health<=0){
		death();
	}
	
}

void Enemy::init() {
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
	
	coll_grav->set_gravity(70.0*12);
	
	sphereModel.set_pos(sphereModel.get_x(),sphereModel.get_y(),sphereModel.get_z()+5);
	sphereModelTwo.set_pos(sphereModel.get_x(),sphereModel.get_y(),sphereModel.get_z());
	sphereModelTwo.set_scale(1.5);
}

bool Enemy::check_sight(){
	
	float dis2=sqrt(pow(player.model.get_y()-model.get_y(),2)+pow(player.model.get_x()-model.get_x(),2));
	shootRayModel.look_at(player.sphereModel);
	//cout<<shootRayModel.get_hpr()<<endl;
	shootRayModel.set_hpr(shootRayModel.get_hpr().get_x(),shootRayModel.get_hpr().get_y()-atan2(2.0,dis2),shootRayModel.get_hpr().get_z());
	qtrav_shoot.traverse(window -> get_render());
	
	
	running=false;
	
	if (qcoll_shoot -> get_num_entries() > 1)
	{
		qcoll_shoot -> sort_entries();
		if (qcoll_shoot -> get_entry(1) -> get_into_node()->get_name()!="Interaction_Sphere"){
			return false;
		}
	}
	else{
		return false;
	}
	
	
	if(model.get_distance(player.model)>250){
		return false;
	}
	
	
	running=true;
	return true;
}

void Enemy::bas_mov(float dis){
	
	model.set_hpr((atan2(player.model.get_y()-model.get_y(),player.model.get_x()-model.get_x())*180.0/3.14159265358979323846)+90,model.get_hpr().get_y(),model.get_hpr().get_z());
	
	
	float dis2=sqrt(pow(player.model.get_y()-model.get_y(),2)+pow(player.model.get_x()-model.get_x(),2));
	
	
	float xtran=0;
	float ytran=0;
	
	if (player.model.get_x()-model.get_x()>dis+2){
		xtran=2.0;
	}
	else if (player.model.get_x()-model.get_x()<dis-2){
		xtran=-2.0;
	}
	
	
	
	float tmpx=(sqrt(pow(player.model.get_x()-model.get_x(),2))/dis2);
	float tmpy=(sqrt(pow(player.model.get_y()-model.get_y(),2))/dis2);
	
	if (isnan(tmpx)){
		tmpx=0;
	}
	if (isnan(tmpy)){
		tmpy=0;
	}
	
	
	if (player.model.get_y()-model.get_y()>dis+2){
		ytran=2.0;
	}
	else if (player.model.get_y()-model.get_y()<dis-2){
		ytran=-2.0;
	}
	
	if (xtran!=0){
		model.set_fluid_x(model.get_x() + xtran*tmpx*world.dt*15 );
	}
	if (ytran!=0){
		model.set_fluid_y(model.get_y() + ytran*tmpy*world.dt*15 );
	}
	
	
}

void Enemy::adv_mov(){
	
}

void Enemy::set_up(NodePath* parent,WindowFramework* w,PandaFramework* pf,string fn,float HEALTH,int xx,int yy,int zz,float dmg,int ifc,int mfc,int afc,float xpe,float idd){
	
	model = w -> load_model(pf->get_models(),fn);
	model.set_scale(0.5);
	model.set_pos(xx, yy, zz);
	model.set_hpr(0, 0, 0);
	model.set_shader_auto();
	model.reparent_to(*parent);
	
	damage = dmg;
	
	lastframe=0;
	otherlastframe=0;
	
	rot=0;
	//max_health=100;
	health=HEALTH;
	
	search_angle=0;
	sight=false;
	
	running=false;
	tickFrame=0;
	tickFrame2=0;
	animframe=0;
	
	idleFC=ifc;
	moveFC=mfc;
	attackFC=afc;
	
	xp=xpe;
	
	ground = false;
	
	
	setVel(0,0,0);
	
	id=idd;
	
	if(id==50){
		range=30;
		target=0.25;
	}
	else if(id==51){
		range=130;
		target=25;
	}
	
	filename=fn;
	
	
	AnimControlCollection name_collection;

	
	if(id==50){
		NodePath animNp1 = w->load_model(model, mydir + "Assets/INSECT/insect-Idle.egg");
		auto_bind(model.node(), name_collection);
		PT(AnimControl) animPtr = name_collection.get_anim(0);
		anim_collection.store_anim(animPtr, "idle");
		string animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp1.detach_node();
		anim_collection.play("idle");
		
		
		NodePath animNp2 = w->load_model(model, mydir + "Assets/INSECT/insect-Move.egg");
		auto_bind(model.node(), name_collection);
		animPtr = name_collection.get_anim(0);
		anim_collection.store_anim(animPtr, "walk");
		animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp2.detach_node();
		anim_collection.play("walk");
		
		
		NodePath animNp3 = w->load_model(model, mydir + "Assets/INSECT/insect-Attack.egg");
		auto_bind(model.node(), name_collection);
		animPtr = name_collection.get_anim(0);
		anim_collection.store_anim(animPtr, "attack");
		animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp3.detach_node();
		anim_collection.play("attack");
	}
	else if(id==51){
		NodePath animNp1 = w->load_model(model, mydir + "Assets/bandit/Bandit-idle.egg");
		auto_bind(model.node(), name_collection);
		PT(AnimControl) animPtr = name_collection.get_anim(0);
		anim_collection.store_anim(animPtr, "idle");
		string animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp1.detach_node();
		anim_collection.play("idle");
		NodePath animNp2 = w->load_model(model, mydir + "Assets/bandit/Bandit-Walk.egg");
		auto_bind(model.node(), name_collection);
		animPtr = name_collection.get_anim(0);
		anim_collection.store_anim(animPtr, "walk");
		animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp2.detach_node();
		anim_collection.play("walk");
		NodePath animNp3 = w->load_model(model, mydir + "Assets/bandit/Bandit-shoot.egg");
		auto_bind(model.node(), name_collection);
		animPtr = name_collection.get_anim(0);
		anim_collection.store_anim(animPtr, "attack");
		animName = name_collection.get_anim_name(0);
		name_collection.unbind_anim(animName);
		animNp3.detach_node();
		anim_collection.play("attack");
	}
}

void Enemy::coll_set_up(int dist){
	//qcoll_pickup = new CollisionHandlerQueue;
	
	PT(CollisionNode) c_Node;
	
	
	//c_Node = new CollisionNode("Enemy_sphere");
	//c_Node -> add_solid(new CollisionSphere(0, 0, 4, 2.0));
	
	//c_Node = model.find("**/courseGeometry");
	//courseGeometry.setCollideMask(BitMask32.bit(0))
	
	//c_Node -> add_solid(new CollisionSphere(0, 0, 4, 2.0));
	//c_Node -> set_from_collide_mask(BitMask32::bit(0));
	//c_Node -> set_into_collide_mask(BitMask32::bit(0));
	//sphereModel = model.attach_new_node(c_Node);

	//sphereModel.show();
	//coll_push -> add_collider(sphereModel, model);
	//ptrav.add_collider(sphereModel, coll_push);
	

	qcoll_shoot = new CollisionHandlerQueue;
	c_Node = new CollisionNode("AI_Shoot");
	c_Node -> add_solid(new CollisionRay(0, 0, 2, 0, dist, 0));
	c_Node -> set_from_collide_mask(BitMask32::bit(1));
	c_Node -> set_into_collide_mask(BitMask32::all_off());
	shootRayModel = model.attach_new_node(c_Node);
	shootRayModel.set_pos(0,0,0);
	shootRayModel.hide();
	qtrav_shoot.add_collider(shootRayModel, qcoll_shoot);

	
}


void Enemy::death() {
	for(unsigned int i=0;i<enems.size();i++){
		if (enems[i]==this){
			enems.erase(enems.begin()+i);
		}
	}
	player.xp+=xp;
	player.kills++;
	
	sphereModel.remove_node();
	shootRayModel.remove_node();
	model.remove_node();
	
}


void Enemy::attack() {
	
	float xd,yd,zd,td;//,x2,y2,z2;
	
	xd=model.get_x();
	yd=model.get_y();
	zd=model.get_z();
	
	xd=xd-player.model.get_x();
	yd=yd-player.model.get_y();
	zd=zd-player.model.get_z();
	
	xd= pow(xd*xd,0.5);
	yd= pow(yd*yd,0.5);
	zd= pow(zd*zd,0.5);
	
	td=pow(pow(pow((xd*xd)+(yd*yd),0.5),2)+(zd*zd),0.5);
	
	player.health-=damage/td;
	anim_collection.play("attack");
	
	player.tint=1;
	float ran=rand()/(float)RAND_MAX;
	if(ran>(6.0/7.0)){
		world.gameSounds.scream1->play();
	}
	else if(ran>(5.0/7.0)){
		world.gameSounds.scream2->play();
	}
	else if(ran>(4.0/7.0)){
		world.gameSounds.scream3->play();
	}
	else if(ran>(3.0/7.0)){
		world.gameSounds.femaleGrunt1->play();
	}
	else if(ran>(2.0/7.0)){
		world.gameSounds.femaleGrunt5->play();
	}
	else if(ran>(1.0/7.0)){
		world.gameSounds.femaleGrunt6->play();
	}
	else{
		world.gameSounds.femaleGrunt7->play();
	}
	
	
}


