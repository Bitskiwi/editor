///////////////////
// INCLUDES
///////////////////

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

///////////////////
// GET KEY FUNCTION
///////////////////

int get_key() {
	int key;
	//key = read(STDIN_FILENO, &key, 1);
	key = getchar();
	return key;
}
