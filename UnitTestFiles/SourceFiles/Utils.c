#include "Utils.h"

/* Не стал использовать - сделал вывод по нажатию Enter или 'c' */
void sleep(int32_t millis) {
#ifdef WIN32
    Sleep(millis);
#else
    sleep((unsigned) millis / 1000);
#endif
}

int getch_(void) {
#ifdef WIN32
    return _getch();
#else
    int ch;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}

void waitForEnterOrCPressed(){
    int c = getch_();
    while (c != CONTINUE && c != '\r'
    && c != '\n' && c != EOF) {
    c = getch_();
    }
}