#ifndef KEYS_H
#define KEYS_H

#include "nodePath.h"
#include "keyboardButton.h"
#include "mouseButton.h"
#include "pgButton.h"

#include <string>
#include <vector>

class Keys{
public: //will do enum later
	Keys();
	map <std::string, pair<ButtonHandle, bool> > keybinds; //world.move
	map <std::string, void(*)(const Event* , void*)> wildKeys; //window -> get_panda_framework() -> define_key

	vector <string> keybindItems; //all actions ("reload", "use", etc)
	vector <PGButton*> keybindMenu;

	vector<ButtonHandle> allKeys;


	map <std::string, PGButton*> buttonIndex;
private:

};

#endif
