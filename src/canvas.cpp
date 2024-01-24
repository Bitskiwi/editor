///////////////////
// INCLUDES
///////////////////

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
		//matrix[10][10] = std::to_string(cycles);
	};
};

