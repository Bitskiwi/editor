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
#include <cmath>

////////////////////
// CANVAS
////////////////////

class Canvas{
public:
	std::vector<std::vector<std::string>> matrix;                              // make a matrix to store the canvas that will be rendered
	int w;                                                                     // width
	int h;                                                                     // height
	Canvas(){
		this->reset();
	}
	void reset(){                                                              // function to reset the canvas and update it's size
		matrix.clear();
		struct winsize size;                                                   // window size
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		w = size.ws_col - 2;
		h = size.ws_row - 2;
		for(int y = 0; y < h; y++){                                            // iterate two dimensionally to create the new matrix
			std::vector<std::string> row;                                             // make the a row for the matrix
			matrix.push_back(row);                                             // push the row
			for(int x = 0; x < w; x++){
				matrix[y].push_back(" ");                                      // append blank chars into the row
			};
		};
	};
	void render(){                                                             // draw the canvas function
		system("clear");                                                       // clear the screen
		for(int y = 0; y < h; y++){                                            // iterate
			for(int x = 0; x < w; x++){
				std::cout << matrix[y][x];                                     // print the character that is at coordinates: x, y
			};
			std::cout << "\n";                                                 // CRLF to print the next row
		};
	};
	void draw(int x, int y, std::string symbol){                               // draw a char at x, y to canvas
		matrix[y][x] = symbol;                                                 // x, y is char now
	};
};

Canvas canvas;                                                                 // create the canvas


///////////////////
// WINDOW CLASS
///////////////////

class Window{                                                                  // windows are like mini-canvases
public:
	int x;                                                                     // positions and size
	int y;
	int w;
	int h;
	void (*task)(Window&,int);                                                 // variable holds the task to be ran in window ie. editor, dir viewer, etc.
	Window(int pos_x, int pos_y, int size_w, int size_h, void (*task_ptr)(Window&,int)){      // constructor
		x = pos_x;                                                             // pos and size
		y = pos_y;
		w = size_w;
		h = size_h;
		task = task_ptr;                                                       // point task to task function
	}
	void handle(int key){
		for(int draw_y = y; draw_y < y + (h + 1); draw_y += h){                // iterate from top (y) to bottom (y + h)
			for(int draw_x = x; draw_x < x + w; draw_x++){                     // iterate to draw a line from (x) to (x + w)
				canvas.draw(draw_x,draw_y,"\u2500");                                // draw at x, y
			}
		}
		for(int draw_x = x; draw_x < x + (w + 1); draw_x += w){                // iterate from left (x) to right (x + w)
			for(int draw_y = y; draw_y < y + h; draw_y++){                     // iterate to draw a line from (y) to (y + h)
				canvas.draw(draw_x,draw_y,"\u2502");                           // draw at x, y
			}
		}
		canvas.draw(x,y,"\u250c");                                             // corners
		canvas.draw(x + w,y,"\u2510");
		canvas.draw(x,y + h,"\u2514");
		canvas.draw(x + w,y + h,"\u2518");
		task(*this,key);                                                       // execute the task
	}
};

///////////////////
// WINDOW TASKS
///////////////////

// testing tasks

void testTask(Window &parent,int key){                                         // example task parent is for modifing the window ie: editing window.content when that is implemented

	// KEY ACTIONS

	if(key == 'd'){
		canvas.draw(5,5,"H");
		canvas.draw(6,5,"i");
	}
	if(key == 'x'){
		parent.x += 1;
	}
	if(key == 'X'){
		parent.x -= 1;
	}
}

///////////////////
// WINDOW TYPES
///////////////////

//Window test(0,0,10,10,&testTask);                                            // make the window

///////////////////
// WINDOW MANAGER
///////////////////


class WindowManager{                                                           // window manager
public:
	std::vector<Window> windows;                                               // vector to hold the windows
	Window (*hovered);                                                         // window pointer for hovered window
	Window (*focused);                                                         // window pointer for focused window
	WindowManager(){
		this->newWindow(&testTask);                                            // on construction create a new window
	};
	void handle(int key){
		for(int i = 0; i < windows.size(); i++){
			windows[i].handle(key);                                            // fix this later only the focused window should get keypress priveledges
		}
	}
	void newWindow(void (*task_ptr)(Window&,int)){
		windows.push_back(Window(0,0,10,10,task_ptr));                  // push a new window to windows vector with
		int win_w = std::floor(canvas.w / windows.size());                     // width for each window should be equal to fit the canvas
		for(int i = 0; i < windows.size(); i++){                               // iterate windows vector
			windows[i].w = win_w;                                              // update width
			windows[i].x = i * win_w;                                          // move to fit
		}
	}/*
	void hoverWindow(){}
	void closeWindow(){}
	void focusWindow(){}*/
};

WindowManager wm;                                                              // make the window manager
