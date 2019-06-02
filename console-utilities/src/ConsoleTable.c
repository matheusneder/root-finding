/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ConsoleTable.c
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * ConsoleTable.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ConsoleTable.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /console-utilities/src/ConsoleTable.c
 * @file /console-utilities/src/ConsoleTable.c
 * @date 22/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#include "ConsoleTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "StringUtilities.h"

ConsoleTableT* ConsoleTableCreate()
{
	ConsoleTableT* tableObj;
	tableObj = (ConsoleTableT*) malloc(sizeof(ConsoleTableT));

	if (tableObj != NULL)
	{
		tableObj->numFields = 0;
		tableObj->fields = NULL;
		tableObj->linePrepend[0] = '\0';
		tableObj->lineAppend[0] = '\0';
		strcpy(tableObj->colDelimiter, CONSOLE_TABLE_DEFAULT_COL_DELIMITER);
		tableObj->padding = 0;
	}

	return tableObj;
}

int ConsoleTableAddField(ConsoleTableT* tableObj, unsigned width,
		const char* name, enum ConsoleTableAlignment alignment)
{
	unsigned i = tableObj->numFields, newNumFields = tableObj->numFields + 1;
	tableObj->fields = (struct Field*) realloc((void *) tableObj->fields,
			sizeof(struct Field) * newNumFields);

	if (tableObj->fields != NULL)
	{
		tableObj->numFields = newNumFields;
		tableObj->fields[i].width = width;
		tableObj->fields[i].alignment = alignment;
		tableObj->fields[i].name[0] = '\0';
		strncat(
				tableObj->fields[i].name,
				name,
				(width > CONSOLE_TABLE_FIELD_NAME_MAXLEN) ? CONSOLE_TABLE_FIELD_NAME_MAXLEN
						: width);
		return 1;
	}

	return 0;
}

void ConsoleTableSetLinePrepend(ConsoleTableT* tableObj, const char* prependstr)
{
	tableObj->linePrepend[0] = '\0';
	strncat(tableObj->linePrepend, prependstr, CONSOLE_TABLE_MAX_SEPARATOR_LEN);
}

void ConsoleTableSetLineAppend(ConsoleTableT* tableObj, const char* appendStr)
{
	tableObj->lineAppend[0] = '\0';
	strncat(tableObj->lineAppend, appendStr, CONSOLE_TABLE_MAX_SEPARATOR_LEN);
}

void ConsoleTableSetColDelimiter(ConsoleTableT* tableObj, const char* colDelimiterStr)
{
	tableObj->colDelimiter[0] = '\0';
	strncat(tableObj->colDelimiter, colDelimiterStr, CONSOLE_TABLE_MAX_SEPARATOR_LEN);
}

void ConsoleTableSetPadding(ConsoleTableT* tableObj, unsigned padding)
{
	tableObj->padding = padding;
}

static void ConsoleTableFillCellHelper(ConsoleTableT* tableObj,
		const char* content, unsigned i)
{
	char formatedContent[tableObj->fields[i].width];

	if (tableObj->fields[i].alignment == CONSOLE_TABLE_ALIGNMENT_LEFT)
	{
		sprintf(formatedContent, "%-*s", tableObj->fields[i].width, StringAbbreviate(
				content, tableObj->fields[i].width));
	}
	else // assume CONSOLE_TABLE_ALIGNMENT_RIGHT
	{
		sprintf(formatedContent, "%*s", tableObj->fields[i].width, StringAbbreviate(
				content, tableObj->fields[i].width));
	}

	if (i != 0)
	{
		printf("%*s", tableObj->padding, "");
		printf("%s",tableObj->colDelimiter);
		printf("%*s", tableObj->padding, "");
	}

	printf("%s", formatedContent);
}

void ConsoleTableFillCell(ConsoleTableT* tableObj, const char* content)
{
	static unsigned i = 0;

	if(i == 0)
	{
		printf("%s", tableObj->linePrepend);
	}

	ConsoleTableFillCellHelper(tableObj, content, i);
	i++;

	if (i >= tableObj->numFields)
	{
		i = 0;
		printf("%s\n", tableObj->lineAppend);
	}
}

void ConsoleTablePrintHeader(ConsoleTableT* tableObj)
{
	unsigned i;
	printf("%s", tableObj->linePrepend);

	for (i = 0; i < tableObj->numFields; i++)
	{
		ConsoleTableFillCellHelper(tableObj, tableObj->fields[i].name, i);
	}
	
	printf("%s\n", tableObj->lineAppend);
}

void ConsoleTableDelete(ConsoleTableT* tableObj)
{
	free(tableObj->fields);
	free(tableObj);
}
