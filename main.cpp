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
        char key = getchar();
        return key;
    }

    return '\0';
}

////////////////////
// CANVAS
////////////////////

class new_canvas {
public:
    std::vector<std::vector<std::string>> matrix = {};
    int w;
    int h;
    void generate(){
        struct winsize size;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        w = size.ws_row;
        h = size.ws_col;
        for(int y = 0; y < w; y++){
            std::vector<std::string> row = {};
            matrix.push_back(row);
            for(int x = 0; x < h; x++){
                matrix[y].push_back("$");
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
        get_key();

        canvas.generate();
        canvas.render();

        system("sleep 0.001s");
    };
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
