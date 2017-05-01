#include "item.hpp"
#include "gameObject.hpp"
#include <cmath>

Item::Item(char t,int xx,int yy,int zz,float wei,float vol, std::string fn,NodePath* parent,WindowFramework* w,PandaFramework* pf,float scale,int zzz,int xxx,int yyy,float rad,int zzzz,std::string fn2,float am,int idd){
	type=t;
	amount=am;
	id=idd;
	//x=xx;
	//y=yy;
	//z=zz;
	model=w->load_model(pf->get_models(),fn);
	model.set_scale(scale);
	model.set_pos(xx,yy,zz);
	model.reparent_to(*parent);
	
	gravFrame=0;
	
	//PT(CollisionNode) c_Node;
	
	health=-1;
	
	/*
	c_Node = new CollisionNode("Item_sphere");
	c_Node -> add_solid(new CollisionSphere(xxx, yyy, zzz, rad));				//x y z radius
	c_Node -> set_from_collide_mask(BitMask32::all_off());
	c_Node -> set_into_collide_mask(BitMask32::bit(3));
	//c_Node -> set_into_collide_mask(BitMask32::bit(3));
	sphereModel = model.attach_new_node(c_Node);
	//sphereModel.show();
	coll_push -> add_collider(sphereModel, model);
	ptrav.add_collider(sphereModel, coll_push);
	
	//sphereModel.show();

	*/
	
	float xs = -(w -> get_graphics_window()->get_x_size() / (float)w ->get_graphics_window()->get_y_size());
		
	PT(Texture) wt;
	
	imgTex = wt;
	CardMaker cm("cardMaker");
	PT(PandaNode) readyCard = cm.generate();
	NodePath NN(readyCard);
	
	imgNode = NN;
	imgNode = w -> get_aspect_2d().attach_new_node(readyCard);
	imgNode.set_transparency(TransparencyAttrib::M_alpha, 1);
	imgNode.set_scale(0.5);
	imgNode.set_pos(xs+0.1,0, -1);
	
	
	
	setVel(0,0,0);
	
	

	weight=wei;
	volume=vol;
	
	
	imgTex=TexturePool::load_texture(fn2);
	imgNode.set_texture(imgTex);
	imgNode.hide();
}
void Item::action1(){
	cout<<"error, action for item not handled"<<endl;
}

void Item::init(){GameObject::init();}
	
void Item::tick(){
	
	gravFrame++;
	
	if (gravFrame>1){			//change this to change how often/fluid
		gravFrame=0;
		GameObject::tick(1,0);
	}
	
	if (getxV()!=0){
		if(coll_grav->get_airborne_height()<0.2){
			if (getxV()<=1 && getxV()>=-1){
				setVel(0.0,getyV(),getzV());
			}
			else{
				if (getxV()>0){
					setVel(pow(getxV(),0.5),getyV(),getzV());
				}
				else{
					setVel(-1*pow(-1*getxV(),0.5),getyV(),getzV());
				}
			}
		}
	}
	if (getyV()!=0){
		if(coll_grav->get_airborne_height()<0.2){
			if (getyV()<=1 && getyV()>=-1){
				setVel(getxV(),0.0,getzV());
			}
			else{
				if (getyV()>0){
					setVel(getxV(),pow(getyV(),0.5),getzV());
				}
				else{
					setVel(getxV(),-1*pow(-1*getyV(),0.5),getzV());
				}
			}
		}
	}
	
	
	if(getxV()!=0){
		model.set_fluid_x(model.get_x()+getxV());
	}
	if(getyV()!=0){
		model.set_fluid_y(model.get_y()+getyV());
	}
	
	
	
	
}
