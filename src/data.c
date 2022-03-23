#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "data.h"

data_Row data_newRow() {
  return (data_Row){(char *)calloc(data_MAX_ROW_SIZE, sizeof(char)), 0};
}

data_Text data_initialize(char const *filename) {
  data_Text text = {0};
  data_addRow(&text, 0);
  data_readFile(&text, filename);
  return text;
}

void data_freeRow(data_Row data_Row) { free(data_Row.string); }

void data_addRow(data_Text *text, data_u16 numOfRow) {
  for (data_u16 i = text->len; i > numOfRow; --i) {
    text->rows[i] = text->rows[i - 1];
  }
  text->rows[numOfRow] = data_newRow();
  text->len += 1;
}

void data_deleteRow(data_Text *text, data_u16 numOfRow) {
  data_freeRow(text->rows[numOfRow]);
  for (data_u16 i = numOfRow; i < text->len - 1; ++i) {
    text->rows[i] = text->rows[i + 1];
  }
  text->rows[text->len - 1] = (data_Row){0};
  text->len -= 1;
}

void data_addChar(data_Text *text, data_u16 x, data_u16 y, int ch) {
  for (data_u16 i = data_getLenOfRow(text, y); i > x; --i) {
    data_setCharacter(text, y, i, data_getCharacter(text, y, i - 1));
  }
  data_setCharacter(text, y, x, ch);
  text->rows[y].len += 1;
}

void data_deleteChar(data_Text *text, data_u16 x, data_u16 y) {
  for (data_u16 i = x; i < text->rows[y].len - 1; ++i) {
    data_setCharacter(text, y, i, data_getCharacter(text, y, i + 1));
  }
  data_setCharacter(text, y, data_getLenOfRow(text, y) - 1, 0);
  text->rows[y].len -= 1;
}

void data_joinTwoRows(data_Text *text, data_u16 numOfJoinedRow,
                      data_u16 numOfJoinRow) {
  for (data_u16 i = 0; data_getCharacter(text, numOfJoinRow, i); ++i) {
    text->rows[numOfJoinedRow]
        .string[data_getLenOfRow(text, numOfJoinedRow) + i] =
        data_getCharacter(text, numOfJoinRow, i);
  }
  text->rows[numOfJoinedRow].len += data_getLenOfRow(text, numOfJoinRow);
  data_setCharacter(text, numOfJoinedRow,
                    data_getLenOfRow(text, numOfJoinedRow), 0);
  data_deleteRow(text, numOfJoinRow);
}

void data_splitRow(data_Text *text, data_u16 numOfRow, data_u16 splitPosition) {
  data_addRow(text, numOfRow + 1);
  for (data_u16 i = 0; i < data_getLenOfRow(text, numOfRow) - splitPosition;
       ++i) {
    data_setCharacter(text, numOfRow + 1, i,
                      data_getCharacter(text, numOfRow, splitPosition + i));
    text->rows[numOfRow + 1].len += 1;
  }
  data_setCharacter(text, numOfRow, splitPosition, 0);
  text->rows[numOfRow].len = splitPosition;
}

void data_freeText(data_Text *text) {
  for (data_u16 i = 0; i < text->len; ++i) {
    data_freeRow(text->rows[i]);
  }
}

void data_readFile(data_Text *text, char const *filename) {
  int ch;
  FILE *fp = fopen(filename, "r");
  if (fp != NULL) {
    data_u16 x = {0};
    data_u16 y = {0};
    while (true) {
      ch = fgetc(fp);
      if (ch == EOF) {
        break;
      } else if (ch == '\n') {
        data_addRow(text, y + 1);
        x = 0;
        ++y;
        continue;
      }
      data_addChar(text, x, y, ch);
      ++x;
    }
    fclose(fp);
  }
}

void data_writeFile(data_Text *text, char const *filename) {
  FILE *fp = fopen(filename, "w");
  for (data_u16 i = 0; i < text->len; ++i) {
    if (i) {
      fputc('\n', fp);
    }
    for (int j = 0; data_getCharacter(text, i, j); ++j) {
      fputc(data_getCharacter(text, i, j), fp);
    }
  }
  fclose(fp);
}

data_u16 data_getLenOfRow(data_Text const *text, data_u16 numOfRow) {
  return text->rows[numOfRow].len;
}

char data_getCharacter(data_Text const *text, data_u16 numOfRow,
                       data_u16 characterPosition) {
  return text->rows[numOfRow].string[characterPosition];
}

void data_setCharacter(data_Text *text, data_u16 numOfRow,
                       data_u16 characterPosition, char character) {
  text->rows[numOfRow].string[characterPosition] = character;
}

char *data_getRowString(data_Text *text, data_u16 numOfRow) {
  return text->rows[numOfRow].string;
}
