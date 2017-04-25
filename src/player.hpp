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

	CollisionTraverser ptrav;
	CollisionTraverser qtrav;
	CollisionTraverser qtrav_shoot;
	CollisionTraverser qtrav_pickup;
	
	NodePath sphereModelTracker;
	
	AnimControlCollection pistol_collection;
	AnimControlCollection bat_collection;
	AnimControlCollection empty_collection;
	AnimControlCollection ak_collection;
	
	NodePath pistol_arms;
	NodePath bat_arms;
	NodePath empty_arms;
	NodePath ak_arms;
	
	float xp;
	int deaths;
	int kills;
	
	void death(vector<Item*> v,NodePath* parent);
	
	
	void set_up(NodePath* parent,WindowFramework* w,PandaFramework* pf,string dir);
	void coll_set_up();
	bool pick_up(PandaNode* itm,vector<Item*> itms);
	bool drop(int itr,vector<Item*> itms,NodePath* parent);
	//void recoil(int fc, float mult);
	
	
	void calc_arms();
	void play_anim();
	
private:
	//vector<Item> inventory;
};
#endif
