/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef PLAYER_H
#define PLAYER_H

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
#include "fog.h"
#include "fogAttrib.h"
//#include "global.hpp"


class Player : public GameObject{
public:
	
	static CollisionTraverser gtrav;
	static CollisionTraverser ptrav;
	
	
	Player();
	NodePath look();
	
	void init();
	void tick();
	
	bool doublejump;
	bool hitbox;
	bool arms_shown;
	
	float zoom;
	std::string type;
	int mode;
	int weaponN;
	
	float max_weight;
	float max_volume;
	
	void refill(int,float);
	
	float max_food;
	float food;
	
	float max_water;
	float water;
	
	float max_health;
	//float health;
	
	int speed;
	
	int recoil_frames;
	float recoil_mult;
	
	float tint;
	PT(Fog) hitFog;
	PT(Fog) deathFog;
	
	PT(TextNode) ammoNode;
	NodePath ammoNodePath;
	PT(TextNode) ammoNode2;
	NodePath ammoNodePath2;
	
	PT(TextNode) weightNode;
	NodePath weightNodePath;
	PT(TextNode) volumeNode;
	NodePath volumeNodePath;
	
	
	//std::vector<WeaponObject> weapons;
	std::vector<Item*> inventory;
	Item* mainHand;
	NodePath handDisplay;
	int handInd;
	
	void removeItem(int itr);
	
	NodePath camera;
	NodePath* arms;
	NodePath shootRayModel;
	NodePath pickupRayModel;

	PT(CollisionHandlerQueue) qcoll_shoot;
	PT(CollisionHandlerQueue) qcoll_pickup;

	//CollisionTraverser ptrav;
	//CollisionTraverser qtrav;
	CollisionTraverser qtrav_shoot;
	CollisionTraverser qtrav_pickup;
	
	NodePath sphereModelTracker;
	
	AnimControlCollection name_collection;
	
	AnimControlCollection main_collection;
	AnimControlCollection pistol_collection;
	AnimControlCollection bat_collection;
	AnimControlCollection empty_collection;
	AnimControlCollection ak_collection;
	AnimControlCollection negev_collection;
	
	AnimControlCollection cheese_collection;
	AnimControlCollection pill_collection;
	AnimControlCollection water_collection;
	AnimControlCollection gauze_collection;
	
	NodePath pistol_arms;
	NodePath bat_arms;
	NodePath empty_arms;
	NodePath ak_arms;
	NodePath negev_arms;
	
	NodePath cheese_arms;
	NodePath pill_arms;
	NodePath water_arms;
	NodePath gauze_arms;
	
	float xp;
	int deaths;
	int kills;
	
	void death(vector<Item*> &v,NodePath* parent);
	
	
	void set_up(NodePath* parent,WindowFramework* w,PandaFramework* pf,string dir,bool respawn);
	void coll_set_up();
	bool pick_up(PandaNode* itm,vector<Item*> &itms);
	bool drop(int itr,vector<Item*> &itms,NodePath* parent);
	//void recoil(int fc, float mult);
	
	
	void calc_arms();
	void play_anim();
	
	
	int lvlid;
	string savefilename;
	
	
	int totaltickcount;
	
	int pullout;
	
	void kaboom(NodePath root);
	
private:
	//vector<Item> inventory;
};
#endif
