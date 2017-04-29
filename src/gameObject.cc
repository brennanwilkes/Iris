#include "gameObject.hpp"
#include "global.hpp"

GameObject::GameObject(){
	coll_grav = new CollisionHandlerGravity;
	coll_push = new CollisionHandlerPusher;
	ground = false;
	lastz=0.0;
}

CollisionTraverser GameObject::gtrav;
CollisionTraverser GameObject::ptrav;

void GameObject::init(){
	PT(CollisionNode) c_Node;
	
	c_Node = new CollisionNode("Ground_coll_ray");
	c_Node -> add_solid(new CollisionRay(0, 0, 4, 0, 0, -1));
	c_Node -> set_from_collide_mask(BitMask32::bit(0));
	c_Node -> set_into_collide_mask(BitMask32::all_off());
	rayModel = model.attach_new_node(c_Node);
	
	coll_grav -> add_collider(rayModel, model);

	GameObject::gtrav.add_collider(rayModel, coll_grav);

	c_Node = new CollisionNode("Coll_Sphere");
	c_Node -> add_solid(new CollisionSphere(0, 0, 4, 2.0));
	c_Node -> set_from_collide_mask(BitMask32::bit(0));
	c_Node -> set_into_collide_mask(BitMask32::bit(3));
	sphereModel = model.attach_new_node(c_Node);
	coll_push -> add_collider(sphereModel, model);
	GameObject::ptrav.add_collider(sphereModel, coll_push);
	
	zV=0;
	xV=0;
	yV=0;
	
	tint=0.0;
	
}

void GameObject::accel(float x, float y, float z){
	xV += x;
	yV += y;
	
	zV += z;
	return;
}

void GameObject::setVel(float x, float y, float z){
	xV = x;
	yV = y;
	zV = z;
}

void GameObject::setPos(float xx, float yy, float zz){
	x = xx;
	y = yy;
	z = zz;
}
void GameObject::tick(int m,int ind){
	//cout<<coll_grav->get_impact_velocity()<<endl;
	if (coll_grav->get_impact_velocity()<-50.0){
		health=health+((coll_grav->get_impact_velocity()+50.0)/2.0);
		cout<<health<<endl;
	}
	if(getxV()!=0){
		model.set_fluid_x(model.get_x()+getxV());
	}
	if(getyV()!=0){
		model.set_fluid_y(model.get_y()+getyV());
	}
	
}

void GameObject::doGrav(int m){
	
}

void GameObject::checkGroundColl(int ind){
	
}


float GameObject::getxV(){
	return xV;
}

float GameObject::getyV(){
	return yV;
}

float GameObject::getzV(){
	return zV;
}

float GameObject::getX(){
	return x;
}

float GameObject::getY(){
	return y;
}

float GameObject::getZ(){
	return z;
}
