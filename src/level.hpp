/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
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
	void remove_nd(std::string uuid); // Checks if a file exists
	std::vector<std::string> split(std::string &inp, std::string delim = " "); // Splits a string by delimiter

	string add_model(NodePath model);
	
	map<string, NodePath> models;
	map<string, map<string, string> > nd_dat;	// First string is uuid, same as parent model
												// Map in map is data_name:value
	unsigned int uuid = 0;
	
	int id;
	
	float spawn_x;
	float spawn_y;
	float spawn_z;
	
	Level(int idd,float sx,float sy,float sz);
	
	vector<ChangeRegion> exits;
};

#endif
