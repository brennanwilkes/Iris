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
	m["enemy"] = {"file", "x", "y", "z", "h", "p", "r", "s", "heal", "dmg", "xp", "id"};
	m["item"] = {"type", "x", "y", "z", "h", "p", "r", "s", "wei", "vol", "file", "icon", "amo", "id"};
	m["food_item"] = m["item"];
	m["health_item"] = m["item"];
	m["water_item"] = m["item"];
	m["ammo_item"] = m["item"];
	
	return m;
}

map< const string, vector<string> > Level::default_tags = Level::gen_default_tags();

map< const string, vector<string> > Level::gen_default_tags(){
	map< const string, vector<string> > m;
	m["ak"] = {"g", "0", "0", "0", "0", "0", "0", "1", "3.1", "2", "blenderFiles/AK47.egg", "blenderFiles/ak47icon.png", "24", "10", "24", "25", "64"};
	m["negev"] = {"g", "0", "0", "0", "0", "0", "0", "1", "7.6", "3", "blenderFiles/negevitem.egg", "blenderFiles/negevicon.png", "140", "11", "140", "27", "560"};
	m["pistol"] = {"g", "0", "0", "0", "0", "0", "0", "1", "1", "1", "Model/PIstol/Pistol.egg", "Model/PIstol/ITSAGUN.png", "8", "0", "8", "1", "64"};
	m["bat"] = {"g", "0", "0", "0", "0", "0", "0", "0", "1", "1", "Model/Baseballbat.egg", "blenderFiles/baticon.png", "15", "2", "15", "1", "0"};
	m["spider"] = {"Assets/INSECT/insect.egg", "0", "0", "0", "0", "0", "0", "0", "50", "15", "10", "50"};
	m["bandit"] = {"Assets/bandit/Bandit.egg", "0", "0", "0", "0", "0", "0", "0", "50", "15", "10", "51"};
	//~ m["item"] = {"type", "x", "y", "z", "h", "p", "r", "s", "wei", "vol", "file", "icon", "amo", "id"};
	m["cheese"] = {"c", "0", "0", "0", "0", "0", "0", "1", "1", "1", "blenderFiles/cheese.egg", "blenderFiles/cheeseicon.png", "25", "5"};
	m["pills"] = {"c", "0", "0", "0", "0", "0", "0", "1", "1", "1", "Assets/pillBottle.egg", "blenderFiles/pbottleicon.png", "100", "1"};
	m["gauze"] = {"c", "0", "0", "0", "0", "0", "0", "1", "1", "1", "", "", "25", ""};
	m["water"] = {"c", "0", "0", "0", "0", "0", "0", "1", "1", "1", "blenderFiles/Bootle.egg", "blenderFiles/BottleIcon.png", "80", "6"};

	
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
	
	//tagify();		//seriously fuck this line it has made my life so hard
	
	
	//string reg_file = filename;
	//string dat_file= filename.substr(0,filename.length()-5)+"data";
	
	
	for (const auto &np:models)
	{
		t_np = np.second;
		
		if(t_np.get_tag("save_kind")=="inventory"){
			continue;
		}
		
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
		
		//cout<<t_np.get_tag("class")<<" x "<<t_np.get_tag("x")<<endl;
		
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
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	std::ofstream f2(filename.substr(0,filename.length()-5)+"data",std::ios::app);
	
	
	to_save = {};
	equiv_data = {"item", "food_item", "health_item", "water_item"};
	
	//tagify();		//seriously fuck this line it has made my life so hard
	
	
	
	for (const auto &np:models)
	{
		t_np = np.second;
		
		if(t_np.get_tag("save_kind")=="world"){
			continue;
		}
		
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
			f2 << t_np.get_tag("class") << " " << t_np.get_name() << " ";
		}
		
		// Get data that needs to be saved
		to_save = used_dat[t_np.get_tag("class")];	
		
		//cout<<t_np.get_tag("class")<<" x "<<t_np.get_tag("x")<<endl;
		
		// Check data and save to file
		for (const auto &dat:to_save)
		{
			if (!t_np.has_tag(dat) || t_np.get_tag(dat) == "")
			{
				cout << "WARNING: NodePath " << t_np.get_name() << " has no data for " << dat << "!" << endl;
				cout << "\tUsing value of 0" << endl;
				f2 << "0" << " ";
			}
			else
			{
				f2 << t_np.get_tag(dat) << " ";
			}
		}
		f2 << "\n";
	}
	
	f2.close();
	
	
	
	
	
}

void Level::load(string filename){
	if (!file_exists(filename))
	{
		std::cout << "Level, " << filename << " does not exist!"<<endl;
		return;
	}
	
	if(filename.substr(filename.length()-4)!="data"){
		int num = stoi(filename.substr(filename.size()-5,filename.size()-4));
		
		id=num;
		fn=filename.substr(0,filename.size()-5);
	}
	
	
	ifstream f(filename);
	
	vector<string> data;
	vector<string> to_load;
	
	for (string line; getline(f, line);)
	{
		data = split(line);
		if(data.size()==1){
			continue;
		}
		if (Level::used_dat.find(data[0]) == Level::used_dat.end())
		{
			cout << "ERROR: Invalid Save file:" << endl;
			cout << "\tClass type " << data[0] << " not valid" << endl;
			continue;
		}
		NodePath temp_model(data[1]);
		
		temp_model.set_tag("class", data[0]);
		
		for (unsigned int i(0); i < min( (Level::used_dat[data[0]]).size(), data.size() ); ++i)
		{
			temp_model.set_tag(Level::used_dat[data[0]][i], data[i + 2]);
		}
		if(filename.substr(filename.length()-4)=="data"){
			temp_model.set_tag("load_type","inv");
		}
		else{
			temp_model.set_tag("load_type","world");
		}
		add_model(temp_model);
	}
	
	f.close();
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
	models[id_s].set_tag("uuid", id_s);
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


