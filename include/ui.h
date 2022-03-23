#pragma once

#include <ncurses.h>

#define ui_KEY_ESC 27
#define ui_POSY (getcury(stdscr))
#define ui_POSX (getcurx(stdscr))

typedef struct ui_State ui_State;
struct ui_State {
  int ch;
};

typedef struct ui_Position ui_Position;
struct ui_Position {
  int x;
  int y;
};

ui_Position ui_savePosition();

ui_State ui_initialize();

void ui_readInput(ui_State *state);

void ui_moveCursorPosition(ui_Position pos);

void ui_appendCharacter(char character);

void ui_addCharacter(char character);

void ui_deleteCharacter();

bool ui_isOnLeft();

bool ui_isOnTop();

void ui_moveTop();

void ui_moveDown();

void ui_moveRight();

void ui_moveLeft();

void ui_appendString(char const *string);
