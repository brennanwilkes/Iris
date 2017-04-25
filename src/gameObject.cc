#include "gameObject.hpp"
#include "global.hpp"

GameObject::GameObject(){
	coll_queue = new CollisionHandlerQueue;
	coll_push = new CollisionHandlerPusher;
	ground = false;
}

void GameObject::init(){
	PT(CollisionNode) c_Node;
	
	c_Node = new CollisionNode("Ground_coll_ray");
	c_Node -> add_solid(new CollisionRay(0, 0, 4, 0, 0, -1));
	c_Node -> set_from_collide_mask(BitMask32::bit(0));
	c_Node -> set_into_collide_mask(BitMask32::all_off());
	rayModel = model.attach_new_node(c_Node);
	
	rayModel.show();
	qtrav.add_collider(rayModel, coll_queue);
	
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
	checkGroundColl(ind);
	doGrav(m);
	
	
	
}

void GameObject::doGrav(int m){
	//cout<<"dt: "<<world.dt<<endl;
	
	
	
	if (world.dt <= 0.1)		
		accel(0, 0, world.dt * -9.8*m);
	if (!ground){
		model.set_fluid_z(model.get_z() + getzV());
	}
}

void GameObject::checkGroundColl(int ind){
	// Set up traversers
	ptrav.traverse(window -> get_render());
	qtrav.traverse(window -> get_render());
	// Do ground collision
	if (coll_queue -> get_num_entries() > ind)
	{
		coll_queue -> sort_entries();
		// Stepping down
		
		
		
		const auto dankmemes = coll_queue -> get_entry(ind) -> get_surface_point(window -> get_render()).get_z();
		if (ground)
		{
			
			
			if (model.get_z() - 0.01 < dankmemes)
				model.set_fluid_z(dankmemes);
			else if (model.get_z() > dankmemes)
				ground = false;
		}
		// Stop falling if next pos is underground
		if (model.get_z() + getzV() <= dankmemes)
		{
			model.set_fluid_z(dankmemes);
			setVel(0, 0, 0);
			ground = true;
		}
		//~ for (int i(0); i < coll_queue -> get_num_entries(); ++i)
			//~ cout << coll_queue -> get_entry(i) -> get_into_node() -> get_name() << ", ";
		//~ cout << endl;
	}
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
