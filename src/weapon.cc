#include "weapon.hpp"

WeaponObject::WeaponObject(char t,int xx,int yy,int zz,float wei,float vol, std::string fn,NodePath* parent,WindowFramework* w,PandaFramework* pf,float scale,int zzz,int xxx,int yyy,float rad,int zzzz,std::string fn2,float am,int idd):Item(t,xx,yy,zz,wei,vol, fn,parent,w,pf,scale,zzz,xxx,yyy,rad,zzzz,fn2,am,idd){}

void WeaponObject::action1(){
	cout<<"shooty shooty"<<endl;
}

void WeaponObject::weapon_init(int max,float f,float a,int bt,int mc,int c){
	//id=idd;
	//int max_ammo;
	max_amount=max;
	
	
	//DO random colours like this
	//model.set_color_scale(222/255.0,184/225.0,135/225.0,1.0);
	
	
	
	if(id==10){	//ak
		
	}
	else if(id==0){	//pistol
		
	}
	else if(id==2){	//bat
		
	}
	if(id==11){	//nedgev
		
	}
	
	
	
	
	firerate=f;
	accuracy=a;
	bullet_type=bt;
	tot_ammo=mc;
	clip=c;
	
}
