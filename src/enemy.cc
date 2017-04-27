#include "global.hpp"
#include "enemy.hpp"
#include "gameObject.hpp"

Enemy::Enemy() : GameObject() {}

void Enemy::tick(int m) {
	
	tickFrame++;
	tickFrame2++;
	if(tickFrame2>60){
		
		tickFrame2=0;
		
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
	
		if (td<30){
			attack();
		}
	}
	if (tickFrame>10){
		tickFrame=0;
		check_sight();
	}
	/*if(rot!=0){
		model.set_hpr((int)(model.get_hpr().get_x()+rot)%360,model.get_hpr().get_y(),model.get_hpr().get_z());
		
		running=true;
	}
	else{
		//model.look_at(player.model);
		//model.set_hpr(model.get_hpr().get_x()+180,model.get_hpr().get_y(),model.get_hpr().get_z());
		
		//Trig would probally be faster so maybe figure it out eventually
		
		model.set_hpr((atan2(player.model.get_y()-model.get_y(),player.model.get_x()-model.get_x())*180.0/3.14159265358979323846)+90,model.get_hpr().get_y(),model.get_hpr().get_z());
		
		
		bas_mov(3);
	}*/
	
	model.set_hpr((atan2(player.model.get_y()-model.get_y(),player.model.get_x()-model.get_x())*180.0/3.14159265358979323846)+90,model.get_hpr().get_y(),model.get_hpr().get_z());		
	bas_mov(3);
	if (running){
		if(anim_collection.get_frame()==anim_collection.get_num_frames()-1){// || lastframe==anim_collection.get_frame()){	
			anim_collection.loop("Armature.2",true);
		}
	}
	else{
		if(anim_collection.get_frame()==anim_collection.get_num_frames()-1){//|| lastframe==anim_collection.get_frame()){	
			anim_collection.loop("Armature.1",true);
		}
	}
	
	
	
	
	if (tint>0){
		model.clear_color_scale();
		model.set_color_scale(1.0,1-tint,1-tint,1.0);		
		tint-=0.05;
	}
	
	GameObject::tick(1,0);
	
	
	if (health<=0){
		death();
	}
	
}

void Enemy::init() {GameObject::init();}

bool Enemy::check_sight(){
	
	xdis=model.get_x()-player.model.get_x();
	ydis=model.get_y()-player.model.get_y();
	
	float trot=atan2(ydis,xdis)/3.14159265358979323846*180.0;
	trot=(int)trot%360;
	
	
	trot=trot-((int)model.get_hpr().get_x()%360)-90;
	
	rot=0;
	if ((10>trot && trot > 0)||(370>trot && trot>360)){
		rot=1;
	}
	if ((-10<trot && trot < 0)||(350<trot && trot<360)){
		rot=-1;
	}
	
	
	
	
	
	
	return false;
}

void Enemy::bas_mov(float dis){
	
	
	
	//shootRayModel.set_pos(0,0,0);
	shootRayModel.look_at(player.sphereModel);
	qtrav_shoot.traverse(window -> get_render());
	
	
	/*for (int i=0;i<qcoll_shoot->get_num_entries();i++){
		cout<<qcoll_shoot -> get_entry(i) -> get_into_node()->get_name()<<" ";
	}
	cout<<endl;
	*/
	running=false;
	
	if (qcoll_shoot -> get_num_entries() > 0)
	{
		
		qcoll_shoot -> sort_entries();
		
		if (qcoll_shoot -> get_entry(0) -> get_into_node()->get_name()!="Player_sphere"){
			return;
		}

	}
	else{
		//cout<<"naw! "<<qcoll_shoot->get_num_entries()<<endl;
		//running=false;
		return;
	}
	running=true;
	/*
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
	
	if (td>50){
		return;
	}
	*/
	
	float xtran=0;
	float ytran=0;
	
	if (player.model.get_x()-model.get_x()>dis+2){
		xtran=2.0;
	}
	else if (player.model.get_x()-model.get_x()<dis-2){
		xtran=-2.0;
	}
	
	float dis2=sqrt(pow(player.model.get_y()-model.get_y(),2)+pow(player.model.get_x()-model.get_x(),2));
	
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
	/*if (xtran==0 && ytran==0){
		running=false;
	}
	else{
		running=true;
	}*/
	
}

void Enemy::adv_mov(){
	
}

void Enemy::set_up(NodePath* parent,WindowFramework* w,PandaFramework* pf,string fn,float HEALTH,int xx,int yy,int zz,float dmg,int ifc,int mfc,int afc,float xpe){
	
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
	
}

void Enemy::coll_set_up(int dist){
	//qcoll_pickup = new CollisionHandlerQueue;

	PT(CollisionNode) c_Node;
	c_Node = new CollisionNode("Enemy_sphere");
	//c_Node -> add_solid(new CollisionSphere(0, 0, 4, 2.0));
	
	//c_Node = model.find("**/courseGeometry");
	//courseGeometry.setCollideMask(BitMask32.bit(0))
	
	c_Node -> add_solid(new CollisionSphere(0, 0, 4, 2.0));
	c_Node -> set_from_collide_mask(BitMask32::bit(0));
	c_Node -> set_into_collide_mask(BitMask32::bit(3));
	sphereModel = model.attach_new_node(c_Node);

	//sphereModel.show();
	coll_push -> add_collider(sphereModel, model);
	ptrav.add_collider(sphereModel, coll_push);


	qcoll_shoot = new CollisionHandlerQueue;
	c_Node = new CollisionNode("AI_Shoot");
	c_Node -> add_solid(new CollisionRay(0, 0, 5, 0, dist, 0));
	c_Node -> set_from_collide_mask(BitMask32::bit(0));
	c_Node -> set_into_collide_mask(BitMask32::all_off());
	shootRayModel = model.attach_new_node(c_Node);
	shootRayModel.set_pos(0,0,0);
	//shootRayModel.show();
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


