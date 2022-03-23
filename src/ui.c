#include <stdlib.h>

#include "ui.h"

ui_Position ui_savePosition() { return (ui_Position){ui_POSX, ui_POSY}; }

ui_State ui_initialize() {
  initscr();
  raw();
  keypad(stdscr, true);
  noecho();
  return (ui_State){0};
}

void ui_readInput(ui_State *state) { state->ch = getch(); }

void ui_moveCursorPosition(ui_Position pos) { move(pos.y, pos.x); }

void ui_appendCharacter(char character) { addch(character); }

void ui_addCharacter(char character) {
  insch(character);
  ui_moveRight();
}

void ui_deleteCharacter() { delch(); }

bool ui_isOnLeft() { return ui_POSX == 0; }

bool ui_isOnTop() { return ui_POSY == 0; }

void ui_moveTop() { move(ui_POSY - 1, ui_POSX); }

void ui_moveDown() { move(ui_POSY + 1, ui_POSX); }

void ui_moveRight() { move(ui_POSY, ui_POSX + 1); }

void ui_moveLeft() { move(ui_POSY, ui_POSX - 1); }

void ui_appendString(char const *string) {
  for (size_t i = 0; string[i]; ++i) {
    ui_appendCharacter(string[i]);
  }
}
