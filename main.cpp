////////////////////
// INCLUDES
////////////////////

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

std::string FG_RED = "\033[31m"; 
std::string FG_YELLOW = "\033[33m"; 
std::string FG_GREEN = "\033[32m";
std::string FG_BLUE = "\033[34m";
std::string FG_BLACK = "\033[30m";
std::string FG_WHITE = "\033[97";
std::string FG_GRAY = "\033[37";
std::string FG_RESET = "\033[0m";

std::string BG_RED = "\033[41";
std::string BG_YELLOW = "\033[43m";
std::string BG_GREEN = "\033[42m";
std::string BG_BLUE = "\033[44m";
std::string BG_BLACK = "\033[40m";
std::string BG_WHITE = "\033[107";
std::string BG_GRAY = "\033[47";
std::string BG_RESET = "\033[49m";

char get_key() {
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF) {
		ungetc(ch, stdin);
		return getchar();
	}

	return '\0';
}

int cycles = 0;

////////////////////
// CANVAS
////////////////////

class new_canvas {
public:
	std::vector<std::vector<std::string>> matrix = {};
	int w;
	int h;
	void reset(){
		matrix.clear();
		struct winsize size;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		w = size.ws_row;
		h = size.ws_col;
		for(int y = 0; y < w; y++){
			std::vector<std::string> row = {};
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
	void draw(int x, int y, std::string FG, std::string BG, char symbol){
		matrix[y][x] = symbol;
		//matrix[10][10] = std::to_string(cycles);
	};
};

////////////////////
// MAIN
////////////////////

int main(){
	struct termios oldt, newt;
	char key;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	new_canvas canvas;

	while(1){
		canvas.reset();
		key = get_key();
		
		if(key == 'q'){
			break;
		};

		if(key == 'd'){
			canvas.draw(5,5,FG_GREEN,BG_RED,'H');
		};

		canvas.render();
		system("sleep 0.001s");
	};
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
