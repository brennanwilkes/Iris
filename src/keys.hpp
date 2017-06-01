/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
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
	//~Keys();
	float mouseSens;
	bool showFPS;

	map <std::string, pair<ButtonHandle, bool> > keybinds; //world.move
	map <std::string, void(*)(const Event* , void*)> wildKeys; //window -> get_panda_framework() -> define_key
	map <std::string, void*> dataPtrs;

	vector <string> keybindItems; //all actions ("reload", "use", etc)
	vector <PGButton*> keybindMenu;
	
	vector<ButtonHandle> allKeys;

	map <std::string, PGButton*> buttonIndex;
private:

};

#endif
