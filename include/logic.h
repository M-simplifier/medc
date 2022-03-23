#pragma once

#include "data.h"
#include "ui.h"

void logic_initializeScreen(data_Text *text);

void logic_joinTwoRows(data_Text *text, data_u16 numOfJoinedRow,
                       data_u16 numOfJoinRow);

void logic_splitRow(data_Text *text, data_u16 numOfRow, data_u16 splitPosition);

void logic_addChar(data_Text *text, char ch);

void logic_redrawScreenFromARow(data_Text *text, data_u16 numOfRow);
