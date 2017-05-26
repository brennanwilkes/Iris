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
		
		//	i.second	=	NodePath
		
		if (i.second.get_tag("class") == "weapon"){
			WeaponObject* weapon = new WeaponObject('g',stoi(i.second.get_tag("x")),stoi(i.second.get_tag("y")),stoi(i.second.get_tag("z")),stof(i.second.get_tag("wei")),stof(i.second.get_tag("vol")), mydir+i.second.get_tag("file"),&gameModels,w,pf,1.0f,1,0,0,1.5f,0,mydir+i.second.get_tag("icon"),stoi(i.second.get_tag("amo")),stoi(i.second.get_tag("id")));
			weapon->weapon_init(stoi(i.second.get_tag("amo")),stof(i.second.get_tag("rate")),1.0,0,stoi(i.second.get_tag("ammo")),1);
			itms.push_back(weapon);
		}
		else if (i.second.get_tag("class") == "food_item"){
			FoodItem* FOOD = new FoodItem('c',stoi(i.second.get_tag("x")),stoi(i.second.get_tag("y")),stoi(i.second.get_tag("z")),stof(i.second.get_tag("wei")),stof(i.second.get_tag("vol")), mydir+i.second.get_tag("file"),&gameModels,w,pf,0.5f,1,0,0,1.5f,0,mydir+i.second.get_tag("icon"),stoi(i.second.get_tag("amo")),stoi(i.second.get_tag("id")));
			itms.push_back(FOOD);
		}
		else if (i.second.get_tag("class") == "health_item"){
			HealthItem* DRUGS = new HealthItem('c',stoi(i.second.get_tag("x")),stoi(i.second.get_tag("y")),stoi(i.second.get_tag("z")),stof(i.second.get_tag("wei")),stof(i.second.get_tag("vol")), mydir+i.second.get_tag("file"),&gameModels,w,pf,0.5f,1,0,0,1.5f,0,mydir+i.second.get_tag("icon"),stoi(i.second.get_tag("amo")),stoi(i.second.get_tag("id")));
			itms.push_back(DRUGS);
		}
		else if (i.second.get_tag("class") == "water_item"){
			WaterItem* BOOZE = new WaterItem('c',stoi(i.second.get_tag("x")),stoi(i.second.get_tag("y")),stoi(i.second.get_tag("z")),stof(i.second.get_tag("wei")),stof(i.second.get_tag("vol")), mydir+i.second.get_tag("file"),&gameModels,w,pf,0.5f,1,0,0,1.5f,0,mydir+i.second.get_tag("icon"),stoi(i.second.get_tag("amo")),stoi(i.second.get_tag("id")));
			itms.push_back(BOOZE);
		}
		else if (i.second.get_tag("class") == "static"){
			StaticObject* wall = new StaticObject(stoi(i.second.get_tag("x")),stoi(i.second.get_tag("y")),stoi(i.second.get_tag("z")),mydir+i.second.get_tag("file"),&gameModels,window,pf,stoi(i.second.get_tag("h")),stoi(i.second.get_tag("p")),stoi(i.second.get_tag("r")),1.0);
			//this may need to be push_backed to a vector idk tbh
		}
		else if (i.second.get_tag("class") == "Ammo"){
				Item* Ammo= new Item('a',stoi(i.second.get_tag("x")),stoi(i.second.get_tag("y")),stoi(i.second.get_tag("z")),1.0f,1.0f, mydir+i.second.get_tag("file"),&gameModels,w,pf,0.5f,1,0,0,1.5f,0,mydir+i.second.get_tag("icon"),stoi(i.second.get_tag("amo")),stoi(i.second.get_tag("id")));
				itms.push_back(Ammo);
		}
		else if (i.second.get_tag("class") == "Enemy"){
			Enemy* romar = new Enemy;
			
			//romar->set_up(parentNode, window, window->get_panda_framework(), mydir+"Assets/INSECT/insect.egg",50.0,x,y,z,15.0,40,24,0,10.0);
			
			//void Enemy::set_up(NodePath* parent,WindowFramework* w,PandaFramework* pf,string fn,float HEALTH,int xx,int yy,int zz,float dmg,int ifc,int mfc,int afc,float xpe){
			
			romar->set_up(&gameModels, w, pf, mydir+i.second.get_tag("file"),stof(i.second.get_tag("heal")),stoi(i.second.get_tag("x")),stoi(i.second.get_tag("y")),stoi(i.second.get_tag("z")),stof(i.second.get_tag("dmg")),40,24,0,stof(i.second.get_tag("xp")),stof(i.second.get_tag("id")));
			romar->init();
			romar->coll_set_up(1000);
			enems.push_back(romar);
		}
	}
	
}



