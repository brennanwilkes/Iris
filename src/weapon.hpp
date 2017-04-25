#ifndef WEAPON_H
#define WEAPON_H

#include "nodePath.h"
#include "item.hpp"

class WeaponObject : public Item{
public:
	WeaponObject(char t,int xx,int yy,int zz,float wei,float vol, std::string fn,NodePath* parent,WindowFramework* w,PandaFramework* pf,float scale,int zzz,int xxx,int yyy,float rad,int zzzz,std::string fn2,float am,int idd);
	
	
	void weapon_init(int max,float f,float a,int bt,int mc,int c);
	
	//string name;
	int id;
	//int max_ammo;
	//int max_amount;
	//int ammo;			we're going to use "amount" which is inherited from item instead instead
	//float firerate;
	float accuracy;
	int bullet_type;
	//int tot_ammo;
	int clip;
	
	void action1();
	
	
	//PT(Texture) tex;
	//NodePath Node;
	//bool selected;
	//bool available;
	
private:
};

#endif
