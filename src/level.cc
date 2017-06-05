/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "level.hpp"
#include <fstream>
#include <sys/stat.h>
#include <iostream>

using namespace std;

//const map< string, vector<string> > Level::used_dat = Level::gen_used_dat();
map< const string, vector<string> > Level::used_dat = Level::gen_used_dat();

map< const string, vector<string> > Level::gen_used_dat(){
	map< const string, vector<string> > m;
	m["weapon"] = {"type", "x", "y", "z", "h", "p", "r", "s", "wei", "vol", "file", "icon", "amo", "id", "max", "rate", "ammo"};
	m["static"] = {"type", "x", "y", "z", "h", "p", "r", "s", "file"};
	m["enemy"] = {"file", "x", "y", "z", "h", "p", "r", "s", "heal", "dmg", "xp", "dist"};
	m["item"] = {"type", "x", "y", "z", "h", "p", "r", "s", "wei", "vol", "file", "icon", "amo", "id"};
	m["food_item"] = m["item"];
	m["health_item"] = m["item"];
	m["water_item"] = m["item"];
	m["ammo_item"] = m["item"];
	
	return m;
}

Level::Level(){
	
}

Level::Level(int idd,float sx,float sy,float sz){
    id=idd;
    spawn_x=sx;
    spawn_y=sy;
    spawn_z=sz;
}

void Level::save(string filename, bool ov){
	string overwrite("y");
	if (!ov && file_exists(filename))
	{
		std::cout << "Are you sure you want to overwrite " << filename << " [Y]/n? ";
		getline(cin, overwrite);
		if (overwrite != "y" || overwrite != "Y" || overwrite != "\n") return;
	}
	std::ofstream f(filename);
	
	NodePath t_np;
	vector<string> to_save = {};
	vector<string> equiv_data = {"item", "food_item", "health_item", "water_item"};
	
	for (const auto &np:models)
	{
		t_np = np.second;
		to_save = {};
		
		// Check class tag and save to file
		if (!t_np.has_tag("class") || t_np.get_tag("class") == "" || Level::used_dat.find(t_np.get_tag("class")) == Level::used_dat.end())
		{
			cout << "ERROR: Nodepath " << t_np.get_name() << " has invalid class attribute!" << endl;
			cout << "\tThis object will not be saved!" << endl;
			cout << "\tPlease report this incident as a bug" << endl;
			continue;
		}
		else
		{
			f << t_np.get_tag("class") << " " << t_np.get_name() << " ";
		}
		
		
		// Get data that needs to be saved
		to_save = used_dat[t_np.get_tag("class")];	

		// Check data and save to file
		for (const auto &dat:to_save)
		{
			if (!t_np.has_tag(dat) || t_np.get_tag(dat) == "")
			{
				cout << "WARNING: NodePath " << t_np.get_name() << " has no data for " << dat << "!" << endl;
				cout << "\tUsing value of 0" << endl;
				f << "0" << " ";
			}
			else
			{
				f << t_np.get_tag(dat) << " ";
			}
		}
		f << "\n";
	}
	
	f.close();
}

void Level::load(string filename){
	if (!file_exists(filename))
	{
		std::cout << "Level, " << filename << " does not exist!";
		return;
	}
	
	
	
	ifstream f(filename);
	
	vector<string> data;
	vector<string> to_load;
	
	for (string line; getline(f, line);)
	{
		data = split(line);
		if (Level::used_dat.find(data[0]) == Level::used_dat.end())
		{
			cout << "ERROR: Invalid Save file:" << endl;
			cout << "\tClass type " << data[0] << " not valid" << endl;
			continue;
		}
		NodePath temp_model;
		for (unsigned int i(0); i < min( (Level::used_dat[data[0]]).size() + 2, data.size() ); ++i)
		{
			temp_model.set_tag(Level::used_dat[data[0]][i], data[i + 2]);
		}
		add_model(temp_model);
	}
}

void Level::clear(){
	for (auto &np:models)
	{
		np.second.remove_node();
	}
	models.clear();
	id = 0;
}

void Level::tagify(){
	for (auto &p:models)
	{
		p.second.set_tag("x", to_string(p.second.get_x()));
		p.second.set_tag("y", to_string(p.second.get_y()));
		p.second.set_tag("z", to_string(p.second.get_z()));
		p.second.set_tag("h", to_string(p.second.get_h()));
		p.second.set_tag("p", to_string(p.second.get_p()));
		p.second.set_tag("r", to_string(p.second.get_r()));
		p.second.set_tag("s", to_string(p.second.get_scale().get_x()));
	}
}

std::vector<string> Level::split(string &inp, string delim){
	vector<string> out;
	string datum = "";
	string c = "";
	for (unsigned int i(0); i < inp.size(); ++i)
	{
		c = string(1, inp[i]);
		if ((c == delim && datum != ""))
		{
			out.push_back(datum);
			datum = "";
		}
		else datum += c;
	}
	if (datum != "") out.push_back(datum);
	return out;
}

bool Level::file_exists(string filename){
	struct stat buffer;
	return (stat(filename.c_str(), &buffer) == 0);
}

string Level::add_model(NodePath model){
	string id_s = to_string(uuid);
	models[id_s] = model;
	models[id_s].set_tag("id", id_s);
	++uuid;
	return to_string(uuid - 1);
}

/*
 * ChangeRegion class
 * 
 * 
 * 
 * 
 */

ChangeRegion::ChangeRegion(float xx1,float xx2,float yy1,float yy2,float zz1,float zz2,int lvlidd){
	x1=xx1;
	x2=xx2;
	
	y1=yy1;
	y2=yy2;
	
	z1=zz1;
	z2=zz2;
	lvlid=lvlidd;
	
	
}


