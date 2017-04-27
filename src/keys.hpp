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
	map <std::string, pair<ButtonHandle, bool> > keybinds;
	vector <string> keybindItems;
	vector <PGButton*> keybindMenu;


	vector<ButtonHandle> allKeys;
	
	map <std::string, PGButton*> buttonIndex;
private:

};

#endif
