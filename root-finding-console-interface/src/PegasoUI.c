/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * PegasoUI.c
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * PegasoUI.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PegasoUI.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding-console-interface/src/PegasoUI.c
 * @file /root-finding-console-interface/src/PegasoUI.c
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#include "PegasoUI.h"

#include <RootFindingBase.h>
#include <RootFindingPegaso.h>
#include <stdio.h>
#include "Util.h"
#include <ConsoleTable.h>
#include "RootUI.h"

static const int NUM_PRECISION = 16;

void PegasoUI(RootFindingBaseT* rootsObj, double tolerance,
		unsigned maxIterations)
{
	RootFindingPegasoT* pegasoObj;
	ConsoleTableT* tableObj;
	RootFindingBaseReset(rootsObj);

	if (!RootFindingBaseHasError(rootsObj))
	{
		pegasoObj = RootFindingPegasoCreate(rootsObj);

		pegasoObj->maxIterations = maxIterations;
		pegasoObj->tolerance = tolerance;

		if (RootFindingPegasoInit(pegasoObj))
		{
			printf("Calculo da raiz de 'f(x) = %s', "
				"no intervalo [%lf, %lf], "
				"utilizando o Metodo de Pegaso\n",
					mupGetExpr(rootsObj->mupObj), rootsObj->a, rootsObj->b);
			printf("\n");
			tableObj
					= RootUICreateConsoleTable(maxIterations, NUM_PRECISION, 0);
			ConsoleTablePrintHeader(tableObj);
			do
			{
				RootUIPrintTableLine(tableObj, pegasoObj->rootsObj,
						pegasoObj->i, 0);
			} while (RootFindingPegasoPerformIteration(pegasoObj));

			ConsoleTableDelete(tableObj);

			printf("\n");
			printf("\n");
			if (RootFindingBaseGetStateCode(rootsObj) == ROOTS_EXACT_ROOT_FOUND)
			{
				printf("%s\n", RootFindingBaseGetStateMessage(rootsObj));
			}
			else
			{
				if(RootFindingPegasoHasError(pegasoObj))
				{
					printf("%s\n", RootFindingPegasoGetErrorMessage(pegasoObj));
				}
				else
				{
					printf("%s\n", RootFindingPegasoGetStateMessage(pegasoObj));
				}
			}
		}
		else
		{
			printf("%s\n", RootFindingPegasoGetErrorMessage(pegasoObj));
		}
		RootFindingPegasoDelete(pegasoObj);
	}
	else
	{
		//Esse erro nao deve acontecer... mas por via das duvidas esta aqui para debugar
		printf("%s\n", RootFindingBaseGetErrorMessage(rootsObj));
	}

	printf("\n");
	
	pause();
}
