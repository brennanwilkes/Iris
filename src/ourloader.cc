/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "ourloader.hpp"

void OurLoader::load_level(Level L,WindowFramework* w,PandaFramework* pf){
	//map<string,NodePath> model_vector = L.models;
	
	/*
	
	
	m["weapon"] = {"type", "x", "y", "z", "h", "p", "r", "s", "wei", "vol", "file", "icon", "amo", "id", "max", "rate", "ammo"};
	m["static"] = {"type", "x", "y", "z", "h", "p", "r", "s", "file"};
	m["enemy"] = {"file", "x", "y", "z", "h", "p", "r", "s", "heal", "dmg", "xp", "dist"};
	m["item"] = {"type", "x", "y", "z", "h", "p", "r", "s", "wei", "vol", "file", "icon", "amo", "id"};
	m["food_item"] = m["item"];
	m["health_item"] = m["item"];
	m["water_item"] = m["item"];
	
	michael please add an Ammo thing
	it needs x,y,z,file,icon,amo,id
	
	*/
	
	for (auto i:L.models){
		
		if (i.second.get_tag("class") == "weapon"){
			WeaponObject* weapon = new WeaponObject('g',stoi(i.second.get_tag("x")),stoi(i.second.get_tag("y")),stoi(i.second.get_tag("z")),stof(i.second.get_tag("wei")),stof(i.second.get_tag("vol")), mydir+i.second.get_tag("file"),&gameModels,w,pf,1.0f,1,0,0,1.5f,0,mydir+i.second.get_tag("icon"),stoi(i.second.get_tag("amo")),stoi(i.second.get_tag("id")));
			weapon->weapon_init(stoi(i.second.get_tag("amo")),stof(i.second.get_tag("rate")),1.0,0,stoi(i.second.get_tag("ammo")),1);
			itms.push_back(weapon);
		}
		else if (i.second.get_tag("class") == "food_item"){
			FoodItem* FOOD = new FoodItem('c',stoi(i.second.get_tag("x")),stoi(i.second.get_tag("y")),stoi(i.second.get_tag("z")),stof(i.second.get_tag("wei")),stof(i.second.get_tag("vol")), mydir+i.second.get_tag("file"),&gameModels,w,pf,0.5f,1,0,0,1.5f,0,mydir+i.second.get_tag("icon"),stoi(i.second.get_tag("amo")),stoi(i.second.get_tag("id")));
			FOOD->init();
			itms.push_back(FOOD);
		}
		else if (i.second.get_tag("class") == "health_item"){
			HealthItem* DRUGS = new HealthItem('c',stoi(i.second.get_tag("x")),stoi(i.second.get_tag("y")),stoi(i.second.get_tag("z")),stof(i.second.get_tag("wei")),stof(i.second.get_tag("vol")), mydir+i.second.get_tag("file"),&gameModels,w,pf,0.5f,1,0,0,1.5f,0,mydir+i.second.get_tag("icon"),stoi(i.second.get_tag("amo")),stoi(i.second.get_tag("id")));
			DRUGS->init();
			itms.push_back(DRUGS);
		}
		else if (i.second.get_tag("class") == "water_item"){
			WaterItem* BOOZE = new WaterItem('c',stoi(i.second.get_tag("x")),stoi(i.second.get_tag("y")),stoi(i.second.get_tag("z")),stof(i.second.get_tag("wei")),stof(i.second.get_tag("vol")), mydir+i.second.get_tag("file"),&gameModels,w,pf,0.5f,1,0,0,1.5f,0,mydir+i.second.get_tag("icon"),stoi(i.second.get_tag("amo")),stoi(i.second.get_tag("id")));
			BOOZE->init();
			itms.push_back(BOOZE);
		}
		else if (i.second.get_tag("class") == "static"){
			StaticObject* wall = new StaticObject(stoi(i.second.get_tag("x")),stoi(i.second.get_tag("y")),stoi(i.second.get_tag("z")),mydir+i.second.get_tag("file"),&gameModels,window,pf,stoi(i.second.get_tag("h")),stoi(i.second.get_tag("p")),stoi(i.second.get_tag("r")),1.0);
			stats.push_back(wall);
		}
		else if (i.second.get_tag("class") == "ammo_item"){
				Item* Ammo= new Item('a',stoi(i.second.get_tag("x")),stoi(i.second.get_tag("y")),stoi(i.second.get_tag("z")),1.0f,1.0f, mydir+i.second.get_tag("file"),&gameModels,w,pf,0.5f,1,0,0,1.5f,0,mydir+i.second.get_tag("icon"),stoi(i.second.get_tag("amo")),stoi(i.second.get_tag("id")));
				Ammo->init();
				itms.push_back(Ammo);
		}
		else if (i.second.get_tag("class") == "enemy"){
			Enemy* romar = new Enemy;
			romar->set_up(&gameModels, w, pf, mydir+i.second.get_tag("file"),stof(i.second.get_tag("heal")),stoi(i.second.get_tag("x")),stoi(i.second.get_tag("y")),stoi(i.second.get_tag("z")),stof(i.second.get_tag("dmg")),40,24,0,stof(i.second.get_tag("xp")),stof(i.second.get_tag("id")));
			romar->init();
			romar->coll_set_up(1000);
			enems.push_back(romar);
		}
	}
	
}



