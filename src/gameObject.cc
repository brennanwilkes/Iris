/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "gameObject.hpp"
#include "global.hpp"

GameObject::GameObject(){
	coll_grav = new CollisionHandlerGravity;
	coll_push = new CollisionHandlerPusher;
	ground = false;
	lastz=0.0;
}

GameObject::~GameObject(){
	// cout << "Deleted GameObject"
}

void GameObject::init(){
	PT(CollisionNode) c_Node;
	
	c_Node = new CollisionNode("Ground_coll_ray");
	c_Node -> add_solid(new CollisionRay(0, 0, 3, 0, 0, -1));
	c_Node -> set_from_collide_mask(BitMask32::bit(0));
	c_Node -> set_into_collide_mask(BitMask32::all_off());
	rayModel = model.attach_new_node(c_Node);
	//rayModel.set_pos(0,0,0);
	coll_grav -> add_collider(rayModel, model);
	coll_grav->set_gravity(70.0);
	
	
	/*
	//For collisions
	c_Node = new CollisionNode("Coll_Sphere");
	c_Node -> add_solid(new CollisionSphere(0, 0, 0, 2.0));
	c_Node -> set_from_collide_mask(BitMask32::all_off());
	c_Node -> set_into_collide_mask(BitMask32::all_off());
	sphereModel = model.attach_new_node(c_Node);
	sphereModel.set_color(255,0,0,1.0);
	coll_push -> add_collider(sphereModel, model);
	GameObject::ptrav.add_collider(sphereModel, coll_push);
	*/
	
	
	//For obj interaction
	c_Node = new CollisionNode("Interaction_Sphere");
	c_Node -> add_solid(new CollisionSphere(0, 0, 0, 2.0));
	c_Node -> set_from_collide_mask(BitMask32::all_off());
	c_Node -> set_into_collide_mask(BitMask32::bit(1));
	//c_Node -> set_pos(model.get_pos());
	sphereModelTwo = model.attach_new_node(c_Node);
	sphereModelTwo.set_color(0,0,255,1.0);
	
	
	zV=0;
	xV=0;
	yV=0;
	
	coll_grav->set_velocity(0.0);
	
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
