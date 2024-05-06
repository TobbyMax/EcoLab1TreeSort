#ifndef __UTILS_H__
#define __UTILS_H__

#include "CEcoLab1.h"

#ifdef WIN32
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

#define RED_NODE "RED"
#define BLACK_NODE "BLACK"
#define SELECTED_NODE "SELECTED"
#define INSETED_NODE "INSERTED"
#define CONTINUE 'c'

void sleep(int32_t millis);

int getch_(void);

void waitForEnterOrCPressed();

#endif /* __UTILS_H__ */
