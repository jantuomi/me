#include "utils.h"
#include <unistd.h>   //_getch
#include <termios.h>  //_getch
#include <stdio.h>
#include <sys/ioctl.h>
#include <iostream>

/* Thanks to StackOverflow user mf_ */
char Utils::getch(){
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    //printf("%c\n",buf);
    return buf;
}

int Utils::window_height() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    return w.ws_row;
}

void Utils::clear_screen() {
    int height = window_height();
    for (int i = 0; i < height; i++) {
        std::cout << '\n';
    }
}

int Utils::count_digits(int num) {
    std::string repr = std::to_string(num);
    return repr.size();
}
