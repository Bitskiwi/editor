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

	tcgetattr(STDIN_FILENO, &oldt);                                            // assign current terminal settings to oldt
	newt = oldt;                                                               // copy oldt value to newt
	newt.c_lflag &= ~(ICANON | ECHO);                                          // turn off canonical & echo modes in newt
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);                                   // apply newt to terminal settings

	bool first_iteration = true;                                               // when the program starts, getchar() halts the program, and canvas doesn't render so getchar() can't call on first iteration
	int key;

	while(1){                                                                  // begin the operation loop
		canvas.reset();                                                        // reset canvas for new frame
		
		if(first_iteration == true){                                           // program start first iteration shouldn't do getchar()
			first_iteration = false;
			key = 0;
		}else{
			key = getchar();                                                   // store key for input operations
		}

		// global key actions

		if(key == 'q'){                                                        // press q key to quit the program
			break;
		};
		if(key == 'n'){                                                        // press n to create new window
			wm.newWindow(&testTask);
		};
		
		wm.handle(key);                                                        // call the window manager to do its job

		canvas.render();                                                       // draw the interface to the screen
	};
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);                                   // restore terminal settings to stop fucking around
	system("clear");
	std::cout << "Bye! thanks for using the editor!" << "\n";                  // politely thank the user before ending the program
}
