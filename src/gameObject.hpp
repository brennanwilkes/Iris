#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include "nodePath.h"
#include "collisionHandlerPusher.h"
#include "collisionHandlerQueue.h"
#include "collisionNode.h"
#include "collisionRay.h"
#include "collisionSphere.h"
#include "collisionTraverser.h"

class GameObject{
public:
	GameObject();
	
	virtual void init();
	
	void accel(float x, float y, float z);
	void setVel(float x, float y, float z);
	void setPos(float x,float y, float z);
	
	void tick(int m);
	void doGrav(int m);
	void checkGroundColl();
	
	float getX();
	float getY();
	float getZ();
	
	float getxV();
	float getyV();
	float getzV();
	
	bool ground;
	NodePath model;
	std::string filename;
	
	NodePath sphereModel;
	NodePath rayModel;
	
	PT(CollisionHandlerQueue) coll_queue;
	PT(CollisionHandlerPusher) coll_push;
	CollisionTraverser ptrav;
	CollisionTraverser qtrav;
	
	float weight;
	float volume;
	int health;
	
	
	float tint;
	
	
private:
	float x, y, z;
	float xV, yV, zV;
};

#endif
