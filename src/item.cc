/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "item.hpp"
#include "gameObject.hpp"
#include <cmath>



CollisionTraverser Item::gtrav;
CollisionTraverser Item::ptrav;



Item::Item(char t,int xx,int yy,int zz,float wei,float vol, std::string fn,NodePath* parent,WindowFramework* w,PandaFramework* pf,float scale,int zzz,int xxx,int yyy,float rad,int zzzz,std::string fn2,float am,int idd){
	
	
	float ran1=rand()/(float)RAND_MAX;
	
	
	type=t;
	amount=am;
	id=idd;
	//x=xx;
	//y=yy;
	//z=zz;
	model=w->load_model(pf->get_models(),fn);
	model.set_scale(scale);
	
	float ran2=rand()/(float)RAND_MAX;
	
	model.set_pos(xx,yy,zz);
	model.reparent_to(*parent);
	
	float ran3=rand()/(float)RAND_MAX;
	
	ran1=ran1/2.0;
	ran2=ran2/2.0;
	ran3=ran3/2.0;
	
	model.clear_color_scale();
	model.set_color_scale(1-ran1,1-ran2,1-ran3,1.0);
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
	
	filename=fn;
	imgName=fn2;
	
}
void Item::action1(){
	cout<<"error, action for item not handled"<<endl;
}

void Item::init(){
	
	GameObject::init();
	
	
	PT(CollisionNode) c_Node;
	//For collisions
	c_Node = new CollisionNode("Coll_Sphere");
	c_Node -> add_solid(new CollisionSphere(0, 0, 0, 2.0));
	c_Node -> set_from_collide_mask(BitMask32::all_off());
	c_Node -> set_into_collide_mask(BitMask32::all_off());
	sphereModel = model.attach_new_node(c_Node);
	sphereModel.set_color(255,0,0,1.0);
	coll_push -> add_collider(sphereModel, model);
	ptrav.add_collider(sphereModel, coll_push);
	gtrav.add_collider(rayModel, coll_grav);
	
	coll_grav->set_gravity(70.0*12);

}
	
void Item::tick(){
	
	gravFrame++;
	
	if (gravFrame>1){			//change this to change how often/fluid
		gravFrame=0;
		GameObject::tick(1,0);
	}
	//cout<<model<<" "<<coll_grav->get_airborne_height()<<" "<<coll_grav->is_on_ground()<<endl;
	if (getxV()!=0){
		//if(coll_grav->is_on_ground()){
		if (getxV()<=1.2 && getxV()>=-1.2){
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
		//}
	}
	if (getyV()!=0){
		//if(coll_grav->is_on_ground()){
		if (getyV()<=1.2 && getyV()>=-1.2){
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
		//}
	}
	
	
	if(getxV()!=0){
		model.set_fluid_x(model.get_x()+getxV());
	}
	if(getyV()!=0){
		model.set_fluid_y(model.get_y()+getyV());
	}
	
	
	
	
}
