#include <stdlib.h>

#include "logic.h"

void logic_initializeScreen(data_Text *text) {
  if (text->len) {
    for (data_u16 i = 0; i < text->len; ++i) {
      if (i) {
        ui_appendCharacter('\n');
      }
      ui_appendString(data_getRowString(text, i));
    }
    refresh();
  }
}

void logic_redrawScreenFromARow(data_Text *text, data_u16 numOfRow) {
  for (data_u16 i = numOfRow; i < text->len; ++i) {
    if (i-numOfRow) {
      ui_appendCharacter('\n');
    }
    ui_appendString(data_getRowString(text, i));
  }
  refresh();
}

void logic_joinTwoRows(data_Text *text, data_u16 numOfJoinedRow,
                       data_u16 numOfJoinRow) {
  ui_Position tmp = {data_getLenOfRow(text, numOfJoinedRow), numOfJoinedRow};
  data_joinTwoRows(text, numOfJoinedRow, numOfJoinRow);
  ui_moveTop();
  clrtobot();
  logic_redrawScreenFromARow(text, ui_POSY);
  ui_moveCursorPosition(tmp);
}

void logic_splitRow(data_Text *text, data_u16 numOfRow,
                    data_u16 splitPosition) {
  data_splitRow(text, numOfRow, splitPosition);
  ui_moveCursorPosition((ui_Position){0, ui_POSY});
  clrtobot();
  logic_redrawScreenFromARow(text, ui_POSY);
  ui_moveCursorPosition((ui_Position){0, numOfRow + 1});
}

void logic_addChar(data_Text *text, char character) {
  data_addChar(text, ui_POSX, ui_POSY, character);
  ui_addCharacter(character);
}
