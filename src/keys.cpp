///////////////////
// INCLUDES
///////////////////

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

///////////////////
// GET KEY FUNCTION
///////////////////

char get_key() {
	struct termios oldt, newt;                                                 // terminal settings
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);                                            // terminal stuff
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();                                                            // not sure where getchar is from I feel like I blacked out while writing this code

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);                                   // i dont fuckin know
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF) {                                                            // if the char is a keyboard character then return char
		ungetc(ch, stdin);
		return getchar();
	}

	return '\0';
}
