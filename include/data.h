#pragma once

#include <stdint.h>

#define data_MAX_ROW_SIZE 1 << 7
#define data_MAX_ROW_NUMBER 1 << 14

typedef uint16_t data_u16;

typedef struct data_Row data_Row;
struct data_Row {
  char *string;
  data_u16 len;
};

typedef struct data_Text data_Text;
struct data_Text {
  data_Row rows[data_MAX_ROW_NUMBER];
  data_u16 len;
};

data_Row data_newRow();

data_Text data_initialize(char const *filename);

void data_freeRow(data_Row data_Row);

void data_addRow(data_Text *text, data_u16 numOfRow);

void data_deleteRow(data_Text *text, data_u16 numOfRow);

void data_addChar(data_Text *text, data_u16 x, data_u16 y, int ch);

void data_deleteChar(data_Text *text, data_u16 x, data_u16 y);

void data_joinTwoRows(data_Text *text, data_u16 numOfJoinedRow,
                      data_u16 numOfJoinRow);

void data_splitRow(data_Text *text, data_u16 numOfRow, data_u16 splitPosition);

void data_freeText(data_Text *text);

void data_readFile(data_Text *text, char const *filename);

void data_writeFile(data_Text *text, char const *filename);

data_u16 data_getLenOfRow(data_Text const *text, data_u16 numOfRow);

char data_getCharacter(data_Text const *text, data_u16 numOfRow,
                       data_u16 characterPosition);

void data_setCharacter(data_Text *text, data_u16 numOfRow,
                       data_u16 characterPosition, char character);

char *data_getRowString(data_Text *text, data_u16 numOfRow);
