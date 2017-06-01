/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "staticObject.hpp"
#include "global.hpp"

StaticObject::StaticObject(int xx,int yy,int zz, std::string fn,NodePath* parent,WindowFramework* w,PandaFramework* pf,float h,float p,float r,float scale=1){
	//setPos(xx,yy,zz);
	//model=w->load_model(pf->get_models(),fn);
	//model.set_scale(scale);
	//model.reparent_to(*parent);
	
	
	model=w->load_model(pf->get_models(),fn);
	model.reparent_to(*parent);
	model.set_scale(scale);
	//setPos(xx,yy,zz);
	model.set_pos(xx,yy,zz);
	model.set_hpr(h,p,r);
	
	NodePath coll_node = model.find("**/+CollisionNode");
	if (!coll_node.is_empty()){
		coll_node.node() -> set_into_collide_mask(BitMask32::all_on());
	}
	
}
StaticObject::StaticObject(NodePath* parent,WindowFramework* w,PandaFramework* pf,string dir){
	model=w->load_model(pf->get_models(),dir+"/Assets/Iris/Iris.egg");
	model.reparent_to(*parent);
	model.set_scale(0.5);
	//setPos(xx,yy,zz);
	model.set_pos(player.model.get_pos());
	model.set_hpr(player.model.get_hpr());
	
	//NodePath coll_node = model.find("**/+CollisionNode");
	//if (!coll_node.is_empty()){
	//	coll_node.node() -> set_into_collide_mask(BitMask32::all_on());
	//}
	
	AnimControlCollection name_collection;
	name_collection.clear_anims();
	
	NodePath animNp0 = w->load_model(model, dir + "/Assets/Iris/Iris-Death.egg");
	auto_bind(model.node(), name_collection);
	PT(AnimControl) animPtr = name_collection.get_anim(0);
	main_collection.store_anim(animPtr, "Death.1");
	string animName = name_collection.get_anim_name(0);
	name_collection.unbind_anim(animName);
	animNp0.detach_node();
	
	
	NodePath animNp1 = w->load_model(model, dir + "/Assets/Iris/Iris-Death2.egg");
	auto_bind(model.node(), name_collection);
	animPtr = name_collection.get_anim(0);
	main_collection.store_anim(animPtr, "Death.2");
	animName = name_collection.get_anim_name(0);
	name_collection.unbind_anim(animName);
	animNp1.detach_node();
	
	NodePath animNp2 = w->load_model(model, dir + "/Assets/Iris/Iris-DeathE.egg");
	auto_bind(model.node(), name_collection);
	animPtr = name_collection.get_anim(0);
	main_collection.store_anim(animPtr, "Death.3");
	animName = name_collection.get_anim_name(0);
	name_collection.unbind_anim(animName);
	animNp2.detach_node();
	
	
	
	
	
	
	
	
	
	
}

