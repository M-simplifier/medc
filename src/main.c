#include <stdbool.h>
#include <stdlib.h>

#include "logic.h"

int main(int argc, char const *argv[]) {
  char const *filename = argv[1];
  data_Text text = data_initialize(filename);
  ui_State state = ui_initialize();
  logic_initializeScreen(&text);
  while (true) {
    ui_readInput(&state);
    if (state.ch == ui_KEY_ESC) {
      break;
    } else if (state.ch == KEY_UP) {
      if (!ui_isOnTop()) {
        ui_moveTop();
        if (ui_POSX > data_getLenOfRow(&text, ui_POSY)) {
          ui_moveCursorPosition(
              (ui_Position){data_getLenOfRow(&text, ui_POSY) - 1, ui_POSY});
        }
      }
    } else if (state.ch == KEY_DOWN) {
      if (ui_POSY < text.len - 1) {
        ui_moveDown();
        if (ui_POSX > data_getLenOfRow(&text, ui_POSY)) {
          ui_moveCursorPosition(
              (ui_Position){data_getLenOfRow(&text, ui_POSY) - 1, ui_POSY});
        }
      }
    } else if (state.ch == KEY_RIGHT) {
      if (ui_POSX < data_getLenOfRow(&text, ui_POSY)) {
        ui_moveRight();
      }
    } else if (state.ch == KEY_LEFT) {
      if (!ui_isOnLeft()) {
        ui_moveLeft();
      }
    } else if (state.ch == KEY_BACKSPACE) {
      if (!ui_isOnLeft()) {
        ui_moveLeft();
        ui_deleteCharacter();
        data_deleteChar(&text, ui_POSX, ui_POSY);
      } else if (!ui_isOnTop()) {
        logic_joinTwoRows(&text, ui_POSY - 1, ui_POSY);
      }
    } else if (state.ch == '\t') {
      for (int i = 0; i < 4; ++i) {
        logic_addChar(&text, ' ');
      }
    } else if (state.ch == '\n') {
      if (ui_POSX == data_getLenOfRow(&text, ui_POSY)) {
        data_addRow(&text, ui_POSY + 1);
        ui_Position savePos = ui_savePosition();
        logic_redrawScreenFromARow(&text, ui_POSY + 1);
        ui_moveCursorPosition((ui_Position){0, savePos.y + 1});
      } else {
        logic_splitRow(&text, ui_POSY, ui_POSX);
      }
    } else {
      logic_addChar(&text, state.ch);
    }
    refresh();
  }

  data_writeFile(&text, filename);

  data_freeText(&text);

  endwin();
  
  return EXIT_SUCCESS;
}
