#ifndef ITEM_H
#define ITEM_H
#include "gameObject.hpp"
#include "nodePath.h"
#include "windowFramework.h"
#include "pandaFramework.h"
#include "collisionHandlerPusher.h"
#include "collisionHandlerQueue.h"
#include "collisionNode.h"
#include "collisionRay.h"
#include "collisionSphere.h"
#include "collisionTraverser.h"
#include "cardMaker.h"
#include "texturePool.h"

class Item : public GameObject{
public:
	Item(char t,int xx,int yy,int zz,float wei,float vol, std::string fn,NodePath* parent,WindowFramework* w,PandaFramework* pf,float scale,int zzz,int xxx,int yyy,float rad,int zzzz,std::string fn2,float am,int idd);
	
	void init();
	void tick();
	
	bool pickupable;
	bool pickedup;
	char type;
	
	virtual void action1();
	
	//virtual float ammo;
	int id;
	float amount;
	int tot_ammo;
	float firerate;
	
	int gravFrame;
	
	int max_amount;
	NodePath handModel;
	
	string imgName;
	//int id;
	PT(Texture) imgTex;
	NodePath imgNode;
	//bool selected;
	//bool available;
	
	
private:
	
	
};

#endif
