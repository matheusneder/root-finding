/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * RootUI.c
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * RootUI.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RootUI.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding-console-interface/src/RootUI.c
 * @file /root-finding-console-interface/src/RootUI.c
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#include "RootUI.h"

static unsigned numWidthGlobal, numPrecicionGlobal;

ConsoleTableT* RootUICreateConsoleTable(unsigned iMax, unsigned numPrecicion,
		int includeABCols)
{
	ConsoleTableT* tableObj = ConsoleTableCreate();
	unsigned numWidthLocal, iColWidth;
	int aux;

	if (tableObj != NULL)
	{
		ConsoleTableSetPadding(tableObj, 1);
		ConsoleTableSetLinePrepend(tableObj, " ");
		iColWidth = 0;
		aux = iMax;
		do
		{
			aux /= 10;
			iColWidth++;
		} while (aux > 0);
		numWidthLocal = (64 - iColWidth) / ((includeABCols) ? 5 : 3);
		numWidthGlobal = numWidthLocal;
		numPrecicionGlobal = numPrecicion;
		ConsoleTableAddField(tableObj, iColWidth, "i",
				CONSOLE_TABLE_ALIGNMENT_RIGHT);

		if (includeABCols)
		{
			ConsoleTableAddField(tableObj, numWidthLocal, "A",
					CONSOLE_TABLE_ALIGNMENT_RIGHT);
		}
		ConsoleTableAddField(tableObj, numWidthLocal, "Xi",
				CONSOLE_TABLE_ALIGNMENT_RIGHT);
		if (includeABCols)
		{
			ConsoleTableAddField(tableObj, numWidthLocal, "B",
					CONSOLE_TABLE_ALIGNMENT_RIGHT);
		}
		ConsoleTableAddField(tableObj, numWidthLocal, "f(Xi)",
				CONSOLE_TABLE_ALIGNMENT_RIGHT);
		ConsoleTableAddField(tableObj, numWidthLocal, "E",
				CONSOLE_TABLE_ALIGNMENT_LEFT);
	}

	return tableObj;
}

void RootUIPrintTableLine(ConsoleTableT* tableObj, RootFindingBaseT* rootsObj,
		unsigned i, int includeABCols)
{
	static char cellContent[255];
	sprintf(cellContent, "%u", i);
	ConsoleTableFillCell(tableObj, cellContent);

	if (includeABCols)
	{
		formatDouble(cellContent, rootsObj->a, numWidthGlobal,
				numPrecicionGlobal);
		ConsoleTableFillCell(tableObj, cellContent);
	}
	formatDouble(cellContent, rootsObj->x, numWidthGlobal, numPrecicionGlobal);
	ConsoleTableFillCell(tableObj, cellContent);

	if (includeABCols)
	{
		formatDouble(cellContent, rootsObj->b, numWidthGlobal,
				numPrecicionGlobal);
		ConsoleTableFillCell(tableObj, cellContent);
	}
	formatDouble(cellContent, rootsObj->fX, numWidthGlobal, numPrecicionGlobal);
	ConsoleTableFillCell(tableObj, cellContent);

	if (i == 0)
	{
		strcpy(cellContent, "-");
	}
	else
	{
		formatDouble(cellContent, rootsObj->e, numWidthGlobal,
				numPrecicionGlobal);
	}
	
	ConsoleTableFillCell(tableObj, cellContent);
}
