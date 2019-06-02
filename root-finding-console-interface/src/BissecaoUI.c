/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * BissecaoUI.c
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * BissecaoUI.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BissecaoUI.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding-console-interface/src/BissecaoUI.c
 * @file /root-finding-console-interface/src/BissecaoUI.c
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#include "BissecaoUI.h"
#include <RootFindingBase.h>
#include <RootFindingBissecao.h>
#include <stdio.h>
#include "Util.h"
#include <ConsoleTable.h>
#include "RootUI.h"

static const int NUM_PRECISION = 6;

void BissecaoUI(RootFindingBaseT* rootsObj, double tolerance,
		unsigned maxIterations)
{
	RootFindingBissecaoT* bissecaoObj;
	ConsoleTableT* tableObj;
	RootFindingBaseReset(rootsObj);
	double aBackup, bBackup;

	if (!RootFindingBaseHasError(rootsObj))
	{
		aBackup = rootsObj->a;
		bBackup = rootsObj->b;
		bissecaoObj = RootFindingBissecaoCreate(rootsObj);

		bissecaoObj->maxIterations = maxIterations;
		bissecaoObj->tolerance = tolerance;

		if (RootFindingBissecaoInit(bissecaoObj))
		{
			printf("Calculo da raiz de 'f(x) = %s', "
				"no intervalo [%lf, %lf], "
				"utilizando o Metodo de Bissecao\n", mupGetExpr(
					rootsObj->mupObj), rootsObj->a, rootsObj->b);
			printf("\n");
			tableObj
					= RootUICreateConsoleTable(maxIterations, NUM_PRECISION, 1);
			ConsoleTablePrintHeader(tableObj);

			do
			{
				RootUIPrintTableLine(tableObj, bissecaoObj->rootsObj,
						bissecaoObj->i, 1);
			} while (RootFindingBissecaoPerformIteration(bissecaoObj));

			ConsoleTableDelete(tableObj);

			printf("\n");
			printf("\n");

			if (RootFindingBaseGetStateCode(rootsObj) == ROOTS_EXACT_ROOT_FOUND)
			{
				printf("%s\n", RootFindingBaseGetStateMessage(rootsObj));
			}
			else
			{
				if(RootFindingBissecaoHasError(bissecaoObj))
				{
					printf("%s\n", RootFindingBissecaoGetErrorMessage(bissecaoObj));
				}
				else
				{
					printf("%s\n", RootFindingBissecaoGetStateMessage(bissecaoObj));
				}
			}
		}
		else
		{
			printf("%s\n", RootFindingBissecaoGetErrorMessage(bissecaoObj));
		}
		RootFindingBissecaoDelete(bissecaoObj);
		rootsObj->a = aBackup;
		rootsObj->b = bBackup;
	}
	else
	{
		//Esse erro nao deve acontecer... mas por via das duvidas esta aqui para debugar
		printf("%s\n", RootFindingBaseGetErrorMessage(rootsObj));
	}
	
	printf("\n");

	pause();
}
