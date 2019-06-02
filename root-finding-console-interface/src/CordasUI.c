/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * CordasUI.c
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * CordasUI.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CordasUI.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding-console-interface/src/CordasUI.c
 * @file /root-finding-console-interface/src/CordasUI.c
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#include "CordasUI.h"
#include <RootFindingBase.h>
#include <RootFindingCordas.h>
#include <stdio.h>
#include "Util.h"
#include <ConsoleTable.h>
#include "RootUI.h"

static const int NUM_PRECISION = 16;

void CordasUI(RootFindingBaseT* rootsObj, double tolerance,
		unsigned maxIterations)
{
	RootFindingCordasT* cordasObj;
	ConsoleTableT* tableObj;
	RootFindingBaseReset(rootsObj);

	if (!RootFindingBaseHasError(rootsObj))
	{
		cordasObj = RootFindingCordasCreate(rootsObj);

		cordasObj->maxIterations = maxIterations;
		cordasObj->tolerance = tolerance;

		if (RootFindingCordasInit(cordasObj))
		{
			printf("Calculo da raiz de 'f(x) = %s', "
				"no intervalo [%lf, %lf], "
				"utilizando o Metodo das Cordas\n",
					mupGetExpr(rootsObj->mupObj), rootsObj->a, rootsObj->b);
			printf("\n");
			tableObj
					= RootUICreateConsoleTable(maxIterations, NUM_PRECISION, 0);
			ConsoleTablePrintHeader(tableObj);
			do
			{
				RootUIPrintTableLine(tableObj, cordasObj->rootsObj,
						cordasObj->i, 0);
			} while (RootFindingCordasPerformIteration(cordasObj));

			ConsoleTableDelete(tableObj);

			printf("\n");
			printf("\n");
			if (RootFindingBaseGetStateCode(rootsObj) == ROOTS_EXACT_ROOT_FOUND)
			{
				printf("%s\n", RootFindingBaseGetStateMessage(rootsObj));
			}
			else
			{
				if(RootFindingCordasHasError(cordasObj))
				{
					printf("%s\n", RootFindingCordasGetErrorMessage(cordasObj));
				}
				else
				{
					printf("%s\n", RootFindingCordasGetStateMessage(cordasObj));
				}
			}
		}
		else
		{
			if (RootFindingCordasGetErrorCode(cordasObj) == CORDAS_2NDIFF_TEST_ERROR)
			{
				printf("ERRO: O teste da segunda derivada "
					"falhou para ambos os extremos do intervalo [%lf, %lf].\n",
						cordasObj->rootsObj->a, cordasObj->rootsObj->b);
				printf("\n");
				printf("Portanto, nao eh possivel aplicar o Metodo das "
					"Cordas para o funcao 'f(x) = %s' no "
					"intervalo [%lf, %lf]\n", mupGetExpr(
						cordasObj->rootsObj->mupObj), cordasObj->rootsObj->a,
						cordasObj->rootsObj->b);
			}
		}
		RootFindingCordasDelete(cordasObj);
	}
	else
	{
		//Esse erro nao deve acontecer... mas por via das duvidas esta aqui para debugar
		printf("%s\n", RootFindingBaseGetErrorMessage(rootsObj));
	}

	printf("\n");
	
	pause();
}
