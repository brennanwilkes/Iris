/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef ENEMY_H
#define ENEMY_H

#include <nodePath.h>
#include "gameObject.hpp"
#include "weapon.hpp"
#include "item.hpp"
#include "collisionTraverser.h"
#include "collisionHandlerQueue.h"
#include "collisionNode.h"
#include "collisionRay.h"
#include "collisionSegment.h"
#include <vector>
//#include "global.hpp"


class Enemy : public GameObject{
public:
	
	static CollisionTraverser gtrav;
	static CollisionTraverser ptrav;
	
	
	
	Enemy();
	void init();
	void tick(int m);
	
	//float max_health;
	//float health;			moved to gameobject

	
	int search_angle;
	
	bool sight;
	
	void bas_mov(float dis);
	void adv_mov();
	
	bool check_sight();
	
	
	Item* mainHand;
	NodePath handDisplay;
	
	
	
	NodePath shootRayModel;

	PT(CollisionHandlerQueue) qcoll_shoot;
	CollisionTraverser qtrav_shoot;
	
	AnimControlCollection name_collection;
	AnimControlCollection anim_collection;
	
	void set_up(NodePath* parent,WindowFramework* w,PandaFramework* pf,string fn,float HEALTH,int xx,int yy,int zz,float dmg,int ifc,int mfc,int afc,float xpe,float id);
	void coll_set_up(int dist);
	
	void attack();
	void death();
	
	int tickFrame;
	int tickFrame2;
	int animframe;
	int lastframe;
	int otherlastframe;
	
	int idleFC;
	int moveFC;
	int attackFC;
	
	float xp;
	
	int rot;
	float xdis;
	float ydis;
	
	float damage;
	
	bool running;
	
	float range;
	float target;
	int id;
	
	//bool pick_up(PandaNode* itm,vector<Item*> itms);
	//bool drop(int itr,vector<Item*> itms,NodePath* parent);
	
private:
	//vector<Item> inventory;
};
#endif
