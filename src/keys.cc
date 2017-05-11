#include "keys.hpp"


Keys::Keys(){
	/*keybinds = {
	{"menu", {key, false}}
	} */
	//https://www.panda3d.org/manual/index.php/Keyboard_Support
	mouseSens = 0.0;

	keybinds["menu"] = std::make_pair(KeyboardButton::escape(), false);
	keybinds["jump"] = std::make_pair(KeyboardButton::space(), false);
	keybinds["cameraToggle" ] = std::make_pair(KeyboardButton::ascii_key('f'), false);
	keybinds["use" ] = std::make_pair(MouseButton::one(), false);
	keybinds[ "pickup"] = std::make_pair(KeyboardButton::ascii_key('e'), false);
	keybinds["reload"] = std::make_pair(KeyboardButton::ascii_key('r'), false);
	keybinds["drop"] = std::make_pair(KeyboardButton::ascii_key('q'), false);
	keybinds["forward"] = std::make_pair(KeyboardButton::ascii_key('w'),false);
	keybinds["backward"] = std::make_pair(KeyboardButton::ascii_key('s'), false);
	keybinds["left"] = std::make_pair(KeyboardButton::ascii_key('a'), false);
	keybinds["right"] = std::make_pair(KeyboardButton::ascii_key('d'), false);
	keybinds["walk"] = std::make_pair(KeyboardButton::control(), false);
	keybinds["sprint"] = std::make_pair( KeyboardButton::shift(), false);
	keybinds["zoomOut"] = std::make_pair(KeyboardButton::ascii_key('-'), false);
	keybinds["zoomIn"] = std::make_pair(KeyboardButton::ascii_key('='), false);

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

