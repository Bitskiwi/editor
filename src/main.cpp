////////////////////
// INCLUDES
////////////////////

#include <termios.h>
#include "canvas.cpp"

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
	struct termios oldt, newt;                                                 // terminal settings

	tcgetattr(STDIN_FILENO, &oldt);                                            // terminal stuff
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	while(1){                                                                  // begin the operation loop
		canvas.reset();                                                        // reset canvas for new frame
		int key = getchar();                                                   // store key for input operations

		// global key actions

		if(key == 'q'){                                                        // press q key to quit the program
			break;
		};

		test.handle(key);                                                      // call the handle method of test window and pass key for window specific actions

		canvas.render();                                                       // draw the interface to the screen
	};
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);                                   // restore terminal settings to stop fucking around
	system("clear");
	std::cout << "Bye! thanks for using the editor!" << "\n";                  // politely thank the user before ending the program
}
