#include "level.hpp"
#include <fstream>
#include <sys/stat.h>
#include <iostream>

using namespace std;

void Level::save(string filename){
	char overwrite('y');
	if (file_exists(filename))
	{
		std::cout << "Are you sure you want to overwrite " << filename << " [Y/n]? ";
		std::cin >> overwrite;
		if (overwrite == 'n') return;
	}
	std::ofstream f(filename);
	f << "[Game]" << endl;
	f << "\t[Static]" << endl;
	for (auto sta:statics)
	{
		f << "\t\t[StatObj]" << endl;
		f << "\t\t\t" << sta.model.get_name() << endl;
		f << "\t\t\t{" << endl;
		
		f << "\t\t\tXpos:" << sta.model.get_x() << endl;
		f << "\t\t\tYpos:" << sta.model.get_y() << endl;
		f << "\t\t\tZpos:" << sta.model.get_z() << endl;
		
		f << "\t\t\t}" << endl;
		
	}
	f << "\t[Entity]" << endl;
	for (auto item:items)
	{
		f << "\t\t[Item]" << endl;
		f << "\t\t\t" << item.model.get_name() << endl;
		f << "\t\t\t{" << endl;
		f << "\t\t\tXpos:" << item.model.get_x() << endl;
		f << "\t\t\tYpos:" << item.model.get_y() << endl;
		f << "\t\t\tZpos:" << item.model.get_z() << endl;
		f << "\t\t\tHpos:" << item.model.get_h() << endl;
		f << "\t\t\tPpos:" << item.model.get_p() << endl;
		f << "\t\t\tRpos:" << item.model.get_r() << endl;
		f << "\t\t\tid:" << item.id << endl;
		f << "\t\t\ttype:" << item.type << endl;
		f << "\t\t\t}" << endl;
	}
	f.close();
}

void Level::load(string filename){
	
}

bool Level::file_exists(string filename){
	struct stat buffer;
	return (stat(filename.c_str(), &buffer) == 0);
}
Level::Level(int idd){
	id=idd;
}

ChangeRegion::ChangeRegion(float xx1,float xx2,float yy1,float yy2,float zz1,float zz2,int lvlidd){
	x1=xx1;
	x2=xx2;
	
	y1=yy1;
	y2=yy2;
	
	z1=zz1;
	z2=zz2;
	lvlid=lvlidd;
	
	
}






