/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "keys.hpp"


Keys::Keys(){
	/*keybinds = {
	{"menu", {key, false}}
	} */
	//https://www.panda3d.org/manual/index.php/Keyboard_Support
	mouseSens = 0.0;
	showFPS = true;
	
	keybinds["menu"] = std::make_pair(KeyboardButton::escape(), false);
	keybinds["jump"] = std::make_pair(KeyboardButton::space(), false);
	keybinds["cameraToggle" ] = std::make_pair(KeyboardButton::ascii_key('f'), false);
	keybinds["use" ] = std::make_pair(MouseButton::one(), false);
	keybinds[ "pickup"] = std::make_pair(KeyboardButton::ascii_key('e'), false);
	keybinds["reload"] = std::make_pair(KeyboardButton::ascii_key('r'), false);
	keybinds["drop"] = std::make_pair(KeyboardButton::ascii_key('q'), false);
	keybinds["spider"] =  std::make_pair(KeyboardButton::ascii_key('i'), false);

	keybinds["forward"] = std::make_pair(KeyboardButton::ascii_key('w'),false);
	keybinds["backward"] = std::make_pair(KeyboardButton::ascii_key('s'), false);
	keybinds["left"] = std::make_pair(KeyboardButton::ascii_key('a'), false);
	keybinds["right"] = std::make_pair(KeyboardButton::ascii_key('d'), false);
	keybinds["walk"] = std::make_pair(KeyboardButton::control(), false);
	keybinds["sprint"] = std::make_pair( KeyboardButton::shift(), false);
	keybinds["zoomOut"] = std::make_pair(KeyboardButton::ascii_key('-'), false);
	keybinds["zoomIn"] = std::make_pair(KeyboardButton::ascii_key('='), false);
	keybinds["toggleFPS"] = std::make_pair(KeyboardButton::ascii_key('m'), false);

	string nums = "123456789";
	for (auto i: nums){
		keybinds["inv"+to_string(i-48)] = std::make_pair(KeyboardButton::ascii_key(i), false);
	}
	
	for (auto k: keybinds){
		keybindItems.push_back(k.first);
	}

	allKeys = {
		KeyboardButton::escape(),
		KeyboardButton::space(),
		MouseButton::one(),
		MouseButton::two(),
		MouseButton::three(),
		KeyboardButton::backspace(),
		KeyboardButton::tab(),
		KeyboardButton::enter(),
		KeyboardButton::f1(),
		KeyboardButton::f2(),
		KeyboardButton::f3(),
		KeyboardButton::f4(),
		KeyboardButton::f5(),
		KeyboardButton::f6(),
		KeyboardButton::f7(),
		KeyboardButton::f8(),
		KeyboardButton::f9(),
		KeyboardButton::f10(),
		KeyboardButton::f11(),
		KeyboardButton::f12(),
		KeyboardButton::left(),
		KeyboardButton::right(),
		KeyboardButton::up(),
		KeyboardButton::down(),
		KeyboardButton::page_up(),
		KeyboardButton::page_down(),
		KeyboardButton::home(),
		KeyboardButton::end(),
		KeyboardButton::insert(),
		KeyboardButton::del(),
		KeyboardButton::shift(),
		KeyboardButton::control(),
		KeyboardButton::alt(),
		KeyboardButton::meta(),
		KeyboardButton::caps_lock(),
		KeyboardButton::shift_lock(),
		KeyboardButton::num_lock(),
		KeyboardButton::scroll_lock(),
		KeyboardButton::print_screen(),
	};
	string alphabet = "0qwertyuiop[]asdfghjkl;'zxcvbnm,./-=`\\";
	for (auto i: alphabet){
		allKeys.push_back(KeyboardButton::ascii_key(i));
	}
}
/*
Keys::~Keys(){
	for (unsigned i=0; i<keybindMenu.size(); i++){
		delete keybindMenu.at(i);
	}
}
*/

