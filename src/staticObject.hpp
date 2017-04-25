#ifndef STATIC_OBJ_H
#define STATIC_OBJ_H

#include "gameObject.hpp"
#include "nodePath.h"
#include "windowFramework.h"
#include "pandaFramework.h"

class StaticObject{
public:
	void setPos(float x,float y, float z);
	StaticObject(int xx,int yy,int zz, std::string fn,NodePath* parent,WindowFramework* w,PandaFramework* pf,float scale);
	float getX();
	float getY();
	float getZ();
	
	NodePath model;
	std::string filename;
private:
	float x, y, z;
};

#endif
