///////////////////
// INCLUDES
///////////////////

#include <functional>
#include <iostream>
#include <vector>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

////////////////////
// CANVAS
////////////////////

class new_canvas {
public:
	std::vector<std::vector<std::string>> matrix;
	int w;
	int h;
	void reset(){
		matrix.clear();
		struct winsize size;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		w = size.ws_row - 2;
		h = size.ws_col - 2;
		for(int y = 0; y < w; y++){
			std::vector<std::string> row;
			matrix.push_back(row);
			for(int x = 0; x < h; x++){
				matrix[y].push_back(" ");
			};
		};
	};
	void render(){
		system("clear");
		for(int y = 0; y < w; y++){
			for(int x = 0; x < h; x++){
				std::cout << matrix[y][x];
			};
			if(y != 0 && y != w){
				std::cout << "\n";
			};
		};
	};
	void draw(int x, int y, char symbol){
		matrix[y][x] = symbol;
	};
};

new_canvas canvas;

///////////////////
// WINDOW CLASS
///////////////////

class window{
	public:
		int x;
		int y;
		int w;
		int h;
		std::function<void(char key)> task_keypress;
		//std::function<void(window)> task_loop;
		window(int pos_x, int pos_y, int size_w, int size_h, void (*keypress)(char key)){
			x = pos_x;
			y = pos_y;
			w = size_w;
			h = size_h;
			task_keypress = keypress;
		}
		void handle(char key){
			task_keypress(key);
		}
};

///////////////////
//
///////////////////

void test_keypress(char key){
	if(key == 'd'){
		canvas.draw(5,5,'H');
		canvas.draw(6,5,'i');
	}
}

void test_loop(){
	
}

///////////////////
// WINDOW TYPES
///////////////////

window test(0,0,0,0,&test_keypress);
