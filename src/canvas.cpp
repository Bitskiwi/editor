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
	std::vector<std::vector<char>> matrix;                                     // make a matrix to store the canvas that will be rendered
	int w;                                                                     // width
	int h;                                                                     // height

	void reset(){                                                              // function to reset the canvas and update it's size
		matrix.clear();
		struct winsize size;                                                   // window size
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		w = size.ws_row - 2;
		h = size.ws_col - 2;
		for(int y = 0; y < w; y++){                                            // iterate two dimensionally to create the new matrix
			std::vector<char> row;                                             // make the a row for the matrix
			matrix.push_back(row);                                             // push the row
			for(int x = 0; x < h; x++){
				matrix[y].push_back(' ');                                      // append blank chars into the row
			};
		};
	};

	void render(){                                                             // draw the canvas function
		system("clear");                                                       // clear the screen
		for(int y = 0; y < w; y++){                                            // iterate
			for(int x = 0; x < h; x++){
				std::cout << matrix[y][x];                                     // print the character that is at coordinates: x, y
			};
			if(y != 0 && y != w){                                              // can't remember what this if statement is for but things break when it's not there
				std::cout << "\n";                                             // CRLF to print the next row
			};
		};
	};
	void draw(int x, int y, char symbol){                                      // draw a char at x, y to canvas
		matrix[y][x] = symbol;                                                 // x, y is char now
	};
};

new_canvas canvas;                                                             // create the canvas

///////////////////
// WINDOW CLASS
///////////////////

class window{                                                                  // windows are like mini-canvases
	public: 
		int x;                                                                 // positions and size
		int y;
		int w;
		int h;
		std::function<void(char key)> task_keypress;                           // variable holds key actions
		std::function<void()> task_loop;                                       // variable holds basic upkeep functions that are ran every cycle
		window(int pos_x, int pos_y, int size_w, int size_h, void (*keypress)(char key), void (*loop)()){      // constructor
			x = pos_x;                                                         // pos and size
			y = pos_y;
			w = size_w;
			h = size_h;
			task_keypress = keypress;                                          // keypress function
			task_loop = loop;
		}
		void handle(char key){                                                 // handle calls keypress, loop, etc.
			task_loop();
			task_keypress(key);
		}
};

///////////////////
// WINDOW TASKS
///////////////////

// testing tasks

void test_keypress(char key){
	if(key == 'd'){
		canvas.draw(5,5,'H');
		canvas.draw(6,5,'i');
	}
}

void test_loop(){
	for(int i = 0; i < 10; i++){
		canvas.draw(i,i,'#');
	}
}

///////////////////
// WINDOW TYPES
///////////////////

window test(0,0,0,0,&test_keypress,&test_loop);                                // make the window
