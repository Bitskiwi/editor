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
			std::cout << "\n";                                                 // CRLF to print the next row
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
		std::function<void()> task_defaults;                                   // variable holds basic upkeep functions that are ran every cycle
		window(int pos_x, int pos_y, int size_w, int size_h, void (*keypress)(char key), void (*defaults)()){      // constructor
			x = pos_x;                                                         // pos and size
			y = pos_y;
			w = size_w;
			h = size_h;
			task_keypress = keypress;                                          // keypress function
			task_defaults = defaults;
		}
		void window_defaults(){
			for(int draw_y = y; draw_y < y + (h + 1); draw_y += h){            // iterate from top (y) to bottom (y + h)
				for(int draw_x = x; draw_x < x + w; draw_x++){                 // iterate to draw a line from (x) to (x + w)
					canvas.draw(draw_x,draw_y,'-');                            // draw at x, y
				}
			}
			for(int draw_x = x; draw_x < x + (w + 1); draw_x += w){            // iterate from left (x) to right (x + w)
				for(int draw_y = y; draw_y < y + h; draw_y++){                 // iterate to draw a line from (y) to (y + h)
					canvas.draw(draw_x,draw_y,'|');                            // draw at x, y
				}
			}
			canvas.draw(x,y,'+');
			canvas.draw(x + w,y,'+');
			canvas.draw(x,y + h,'+');
			canvas.draw(x + w,y + h,'+');
		}
		void handle(char key){                                                 // handle calls keypress, loop, etc.
			window_defaults();                                                 // does things that all windows should
			task_defaults();                                                   // does things this window should
			task_keypress(key);                                                // does things this window should but only when a certain key is pressed
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
	if(key == '>'){
		canvas.draw(10,10,'>');
	}
}

void test_loop(){
	/*
	for(int i = 0; i < 10; i++){
		canvas.draw(i,i,'#');
	} */
}

///////////////////
// WINDOW TYPES
///////////////////

window test(0,0,10,10,&test_keypress,&test_loop);                                // make the window
