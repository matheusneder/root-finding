/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ConsoleTable.h
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * ConsoleTable.h is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ConsoleTable.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /console-utilities/include/ConsoleTable.h
 * @file /console-utilities/include/ConsoleTable.h
 * @date 22/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#ifndef CONSOLETABLE_H_
#define CONSOLETABLE_H_

#define CONSOLE_TABLE_FIELD_NAME_MAXLEN 80
//linePrepend, lineApend, delimiter
#define CONSOLE_TABLE_MAX_SEPARATOR_LEN 10

#define CONSOLE_TABLE_DEFAULT_COL_DELIMITER "|"

enum ConsoleTableAlignment
{
	CONSOLE_TABLE_ALIGNMENT_LEFT,
//	CONSOLE_TABLE_ALIGNMENT_CENTER,
	CONSOLE_TABLE_ALIGNMENT_RIGHT
};

struct ConsoleTable
{
	struct Field
	{
		unsigned width;
		char name[CONSOLE_TABLE_FIELD_NAME_MAXLEN];
		enum ConsoleTableAlignment alignment;
	}* fields;
	char linePrepend[CONSOLE_TABLE_MAX_SEPARATOR_LEN];
	char lineAppend[CONSOLE_TABLE_MAX_SEPARATOR_LEN];
	char colDelimiter[CONSOLE_TABLE_MAX_SEPARATOR_LEN];
	unsigned padding;
	unsigned numFields;
};

typedef struct ConsoleTable ConsoleTableT;

ConsoleTableT* ConsoleTableCreate();

int ConsoleTableAddField(ConsoleTableT* tableObj, unsigned width,
		const char* name, enum ConsoleTableAlignment alignment);

void ConsoleTableDelete(ConsoleTableT* tableObj);

void ConsoleTablePrintHeader(ConsoleTableT* tableObj);

void ConsoleTableFillCell(ConsoleTableT* tableObj, const char* content);

void ConsoleTableSetLinePrepend(ConsoleTableT* tableObj, const char* prependstr);

void ConsoleTableSetLineAppend(ConsoleTableT* tableObj, const char* appendStr);

void ConsoleTableSetColDelimiter(ConsoleTableT* tableObj, const char* colDelimiterStr);

void ConsoleTableSetPadding(ConsoleTableT* tableObj, unsigned padding);

#endif /* CONSOLETABLE_H_ */
