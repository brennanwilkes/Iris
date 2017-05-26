/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include "nodePath.h"
#include "collisionHandlerPusher.h"
#include "collisionHandlerGravity.h"
#include "collisionNode.h"
#include "collisionRay.h"
#include "collisionSphere.h"
#include "collisionTraverser.h"

class GameObject{
public:
	GameObject();
	virtual ~GameObject();
	//static CollisionTraverser gtrav;
	//static CollisionTraverser ptrav;
	
	virtual void init();
	
	void accel(float x, float y, float z);
	void setVel(float x, float y, float z);
	void setPos(float x,float y, float z);
	
	void tick(int m,int ind);
	void doGrav(int m);
	void checkGroundColl(int ind);
	
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
	NodePath sphereModelTwo;
	NodePath rayModel;
	
	PT(CollisionHandlerGravity) coll_grav;
	PT(CollisionHandlerPusher) coll_push;
	//CollisionTraverser ptrav;
	//CollisionTraverser qtrav;
	
	float weight;
	float volume;
	int health;
	
	float lastz;
	
	float tint;
	
	
private:
	float x, y, z;
	float xV, yV, zV;
};

#endif
