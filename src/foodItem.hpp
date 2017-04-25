#ifndef FOOD_H
#define FOOD_H
#include "item.hpp"

class FoodItem : public Item{
public:
	
	
	FoodItem(char t,int xx,int yy,int zz,float wei,float vol, std::string fn,NodePath* parent,WindowFramework* w,PandaFramework* pf,float scale,int zzz,int xxx,int yyy,float rad,int zzzz,std::string fn2,float am,int idd);
	
	//float weight;
	//float volume;
	//float amount;
	std::string name;
	void action1();
private:
	
	
};

#endif
