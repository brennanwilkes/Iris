#ifndef LEVEL_H
#define LEVEL_H

#include "staticObject.hpp"
#include "player.hpp"
#include "item.hpp"

#include <string>


class ChangeRegion{
public:
	
	ChangeRegion(float xx1,float xx2,float yy1,float yy2,float zz1,float zz2,int lvlidd);
	
	float x1;
	float x2;
	float y1;
	float y2;
	float z1;
	float z2;
	
	int lvlid;
	
};

class Level{
public:
	// Add another vector or object here to be tracked by savefile
	vector<StaticObject> statics;
	vector<Item> items;
	
	void save(std::string file); // Saves this instance of Level to a file
	void load(std::string file); // Loads the save file into this instance of Level
	bool file_exists(std::string file); // Checks if a file exists
	int id;
	
	Level(int idd);
	
	vector<ChangeRegion> exits;
	
};

#endif
