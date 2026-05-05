#ifndef CLEARSCREEN_H
#define CLEARSCREEN_H

#include <cstdlib>

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

#endif