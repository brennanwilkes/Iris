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
	
	void set_up(NodePath* parent,WindowFramework* w,PandaFramework* pf,string fn,float HEALTH,int xx,int yy,int zz,float dmg,int ifc,int mfc,int afc,float xpe);
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
	
	
	//bool pick_up(PandaNode* itm,vector<Item*> itms);
	//bool drop(int itr,vector<Item*> itms,NodePath* parent);
	
private:
	//vector<Item> inventory;
};
#endif
