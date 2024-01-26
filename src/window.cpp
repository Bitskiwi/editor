///////////////////
// INCLUDES
///////////////////

#include <functional>

///////////////////
// WINDOW TASKS
///////////////////

void test_keypress(char key, window parent){
	if(key == 'd'){
		canvas.draw(5,5,'H');
		canvas.draw(5,6,'i');
	}
}

void test_loop(window parent){
	
}

///////////////////
// WINDOW CLASS
///////////////////

class window{
	public:
		int x;
		int y;
		int w;
		int h;
		std::function<void(char, window)> task_keypress;
		//std::function<void(window)> task_loop;
		window(int pos_x, int pos_y, int size_w, int size_h, void (*keypress)(char, window)){
			x = pos_x;
			y = pos_y;
			w = size_w;
			h = size_h;
			task_keypress = &keypress;
		}
		void handle(char key){
			task_keypress(char key,this);
		}
}

///////////////////
// WINDOW TYPES
///////////////////

window test(0,0,0,0,&test_keypress);
