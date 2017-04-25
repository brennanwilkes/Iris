#include "level.hpp"
#include <fstream>
#include <sys/stat.h>
#include <iostream>

using namespace std;
/*
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
		f << "\t\t\t" << sta.get_name() << endl;
		f << "\t\t\t{" << endl;
		
		f << "\t\t\tXpos:" << sta.get_x() << endl;
		f << "\t\t\tYpos:" << sta.get_y() << endl;
		f << "\t\t\tZpos:" << sta.get_z() << endl;
		
		f << "\t\t\t}" << endl;
		
	}
	f << "\t[Entity]" << endl;
	for (auto item:items)
	{
		f << "\t\t[Item]" << endl;
		f << "\t\t\t" << item.get_name() << endl;
		f << "\t\t\t{" << endl;
		f << "\t\t\tXpos:" << item.get_x() << endl;
		f << "\t\t\tYpos:" << item.get_y() << endl;
		f << "\t\t\tZpos:" << item.get_z() << endl;
		f << "\t\t\tHpos:" << item.get_h() << endl;
		f << "\t\t\tPpos:" << item.get_p() << endl;
		f << "\t\t\tRpos:" << item.get_r() << endl;
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
*/
