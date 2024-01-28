#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	struct termios oldt, newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	
	while(1){
		int key = getchar();

		std::cout << key << "\n";
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
