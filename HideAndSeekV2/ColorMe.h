#pragma once

#include <Windows.h>

#define COLOR_BLACK   0
#define COLOR_GRAY    8

#define COLOR_MAROON  4 
#define COLOR_GREEN   2
#define COLOR_NAVY    1

#define COLOR_RED     12
#define COLOR_LIME    10
#define COLOR_BLUE    9

#define COLOR_TEAL    (COLOR_NAVY | COLOR_GREEN)
#define COLOR_PURPLE  (COLOR_MAROON | COLOR_NAVY)
#define COLOR_OLIVE   (COLOR_MAROON | COLOR_GREEN)

#define COLOR_AQUA    (COLOR_BLUE | COLOR_LIME)
#define COLOR_FUCHSIA (COLOR_RED | COLOR_BLUE)
#define COLOR_YELLOW  (COLOR_RED | COLOR_LIME)

#define COLOR_SILVER  7
#define COLOR_WHITE   15


inline void colorMe(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
