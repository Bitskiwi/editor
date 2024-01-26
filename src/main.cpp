////////////////////
// INCLUDES
////////////////////

#include "canvas.cpp"
#include "keys.cpp"

///////////////////
// ANSI CODES
///////////////////

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

////////////////////
// MAIN
////////////////////

int main(){
	struct termios oldt, newt;                                                 // save terminal settings so we can fuck around and find out (make non-blocking input)
	char key;                                                                  // define a variable for storing the key that has been pressed

	tcgetattr(STDIN_FILENO, &oldt);                                            // more terminal crap
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	while(1){
		canvas.reset();
		key = get_key();

		if(key == 'q'){
			break;
		};

		test.handle(key);

		canvas.render();
		system("sleep 0.01s");
	};
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
