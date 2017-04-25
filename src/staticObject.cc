#include "staticObject.hpp"

StaticObject::StaticObject(int xx,int yy,int zz, std::string fn,NodePath* parent,WindowFramework* w,PandaFramework* pf,float scale=1){
	//setPos(xx,yy,zz);
	//model=w->load_model(pf->get_models(),fn);
	//model.set_scale(scale);
	//model.reparent_to(*parent);
	
	
	model=w->load_model(pf->get_models(),fn);
	model.reparent_to(*parent);
	model.set_scale(scale);
	//setPos(xx,yy,zz);
	model.set_pos(xx,yy,zz);
	
	NodePath coll_node = model.find("**/+CollisionNode");
	if (!coll_node.is_empty()){
		coll_node.node() -> set_into_collide_mask(BitMask32::bit(0));
	}
	
}


