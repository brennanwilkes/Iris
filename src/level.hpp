#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <map>

#include "nodePath.h"

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
	static map< const string, vector<string> > used_dat;
	static map< const string, vector<string> > gen_used_dat();
	
	Level();
	
	void save(std::string file, bool ov = true); // Saves this instance of Level to a file
	void load(std::string file); // Loads the save file into this instance of Level
	void clear(); // Empties all loaded models
	void tagify(); // Empties all loaded models
	bool file_exists(std::string file); // Checks if a file exists
	std::vector<std::string> split(std::string &inp, std::string delim = " "); // Splits a string by delimiter

	string add_model(NodePath model);
	
	map<string, NodePath> models;
	unsigned int uuid = 0;
	
	int id;
	
	float spawn_x;
	float spawn_y;
	float spawn_z;
	
	Level(int idd,float sx,float sy,float sz);
	
	vector<ChangeRegion> exits;
};

#endif
