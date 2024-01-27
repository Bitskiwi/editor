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

char get_key() {
	char key;
	read(STDIN_FILENO, &key, 1);
	return key;
}
