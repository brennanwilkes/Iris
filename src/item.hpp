/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
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
	
	
	static CollisionTraverser gtrav;
	static CollisionTraverser ptrav;
	
	
	Item(char t,int xx,int yy,int zz,float wei,float vol, std::string fn,NodePath* parent,WindowFramework* w,PandaFramework* pf,float scale,int zzz,int xxx,int yyy,float rad,int zzzz,std::string fn2,float am,int idd);
	
	void init();
	void tick();
	
	bool pickupable;
	bool pickedup;
	char type;
	
	char consumable_type;
	//This shouldn't be a thing its just a work around for now for a saving problem. This is only to tell the saver which "class" to use.
	
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
