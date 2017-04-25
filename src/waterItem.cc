#include "waterItem.hpp"
#include "global.hpp"


WaterItem::WaterItem(char t,int xx,int yy,int zz,float wei,float vol, std::string fn,NodePath* parent,WindowFramework* w,PandaFramework* pf,float scale,int zzz,int xxx,int yyy,float rad,int zzzz,std::string fn2,float am,int idd):Item(t,xx,yy,zz,wei,vol, fn,parent,w,pf,scale,zzz,xxx,yyy,rad,zzzz,fn2,am,idd){}


void WaterItem::action1(){
	player.refill(2,amount);
	
	player.removeItem(player.handInd);
	
}
