#include <iostream>
#include <cmath>

#include "pandaFramework.h"
#include "pandaSystem.h"

#include "mouseWatcher.h"
#include "keyboardButton.h"


void test1(const Event* eventPtr, void* dataPtr);
void test2(const Event* eventPtr, void* dataPtr);

int main(int argc, char* argv[]){
	PandaFramework fw;
	fw.open_framework(argc, argv);
	fw.set_window_title("Nope");
	
	PT(WindowFramework) window = fw.open_window();
	window -> enable_keyboard();
	
	PT(MouseWatcher) mw = (MouseWatcher*)window -> get_mouse().node();
	
	fw.define_key("a", "test", test1, NULL);
	fw.get_event_handler().remove_hook("a", &test1, NULL);
	fw.define_key("a", "test", test2, NULL);
	
	Thread *c_thr = Thread::get_current_thread();
	while (fw.do_frame(c_thr))
	{
		if (mw -> is_button_down(KeyboardButton::escape()))
			break;
	}
	fw.close_framework();
	return 0;
}

void test1(const Event* eventPtr, void* dataPtr){
	cout << "Hello!" << endl;
}
void test2(const Event* eventPtr, void* dataPtr){
	cout << "World!" << endl;
}

