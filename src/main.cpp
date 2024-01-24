////////////////////
// INCLUDES
////////////////////

#include "canvas.cpp"
#include "keys.cpp"

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

new_canvas canvas;

/*
class box{
public:
	int x,y,w,h;
	box(int x_val, int y_val, int w_val, int h_val) : x(x_val), y(y_val), w(w_val), h(h_val){
	};
	void render(){
		for(int i = 0){}; //NOTE TO FUTURE SELF: (i = offset) do matrix iteration and canvas.draw(i + box.x);
	};
};*/

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
			canvas.draw(5,5,'H');
		};

		canvas.render();
		system("sleep 0.01s");
	};
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
