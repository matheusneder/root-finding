/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * main.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * main.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding-console-interface/src/main.c
 * @file /root-finding-console-interface/src/main.c
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#include <stdio.h>
#include <string.h>
#include <muParserDLL.h>
#include <stdlib.h>
#include <RootFindingBase.h>
#include "Util.h"
#include "BissecaoUI.h"
#include "CordasUI.h"
#include "PegasoUI.h"
#include "NewtonRhapsonUI.h"
#include <StringUtilities.h>
RootFindingBaseT* rootsObj;
double tolerance = 1e-9;
unsigned maxIterations = 10;

int toleranceSet = 1, maxIterationSet = 1;

enum
{
	INITIAL, FUNCTION_SET, RANGE_SET
} state;

#define SAVE_FILENAME "root-finding-console-interface.dat"
#define SAVE_FILE_EXPR_MAX_SIZE 1024

struct
{
	double a, b, tolerance;
	unsigned maxIterations;
	char expr[SAVE_FILE_EXPR_MAX_SIZE];
	int state;
	int toleranceSet, maxIterationSet;
} saveFileObj;


void evaluateFunction();
void printMenu();
void modifyFunction(muParserHandle_t mupObj);
void defineMaxIterations();
void defineTolerance();
void defineRange();
void interactiveInterface();
int openSaveFile();
void saveFile();

int main()
{
	printf("Algoritmos para encontrar raizes de funcoes\n ");
	printf("\n");
	printf("  Autor:      Matheus Neder\n");
	printf("  Orientacao: Prof. Paulo Fernando Braga Carvalho\n");
	interactiveInterface();
	return 0;
}

void saveFile()
{
	if (rootsObj != NULL && !RootFindingBaseHasError(rootsObj))
	{
		saveFileObj.expr[0] = '\0';
		strncat(saveFileObj.expr, mupGetExpr(rootsObj->mupObj),
				SAVE_FILE_EXPR_MAX_SIZE);
		int i = strlen(saveFileObj.expr) - 1;

		for (; i >= 0; i--)
			if (saveFileObj.expr[i] == ' ')
				saveFileObj.expr[i] = '\0';
			else
				break;

		saveFileObj.a = rootsObj->a;
		saveFileObj.b = rootsObj->b;
		saveFileObj.tolerance = tolerance;
		saveFileObj.maxIterations = maxIterations;
		saveFileObj.state = state;
		saveFileObj.maxIterationSet = maxIterationSet;
		saveFileObj.toleranceSet = toleranceSet;
		FILE* pFile;
		pFile = fopen(SAVE_FILENAME, "w");

		if (pFile != NULL)
		{
			fwrite((void *) &(saveFileObj), sizeof(saveFileObj), 1, pFile);
			fclose(pFile);
		}
	}
}

int openSaveFile()
{
	int ret = 0;
	FILE* pFile;
	pFile = fopen(SAVE_FILENAME, "r");

	if (pFile != NULL)
	{
		if (fread((void*) &(saveFileObj), sizeof(saveFileObj), 1, pFile) == 1)
		{
			ret = 1;
		}
		fclose(pFile);
	}

	return ret;
}

void interactiveInterface()
{
	double x = 1;
	muParserHandle_t mupObj;
	unsigned option;
	int invalidOption = 0;
	state = INITIAL;
	mupObj = mupCreate();
	mupDefineVar(mupObj, "x", &x);
	int saveFileOpened = 0;

	if (openSaveFile())
	{
		mupSetExpr(mupObj, saveFileObj.expr);
		//TODO: verificar errors
		rootsObj = RootFindingBaseCreate(mupObj, &x);
		if (!RootFindingBaseHasError(rootsObj))
		{
			tolerance = saveFileObj.tolerance;
			toleranceSet = saveFileObj.toleranceSet;
			maxIterations = saveFileObj.maxIterations;
			maxIterationSet = saveFileObj.maxIterationSet;
			state = saveFileObj.state;
			saveFileOpened = 1;
			if (state == RANGE_SET)
			{
				if (!RootFindingBaseSetRange(rootsObj, saveFileObj.a, saveFileObj.b))
				{
					saveFileOpened = 0;
				}
			}
		}
		if (!saveFileOpened)
		{
			RootFindingBaseDelete(rootsObj);
		}
	}

	if (!saveFileOpened)
	{
		printf("\n");
		modifyFunction(mupObj);
		//TODO: verificar errors
		rootsObj = RootFindingBaseCreate(mupObj, &x);
		saveFile();
	}

	do
	{
		printf("\n");
		printMenu();

		do
		{
			invalidOption = 0;
			option = getUInt("", "A opcao deve ser um valor inteiro"
				" positivo, tente novamente: ");
			switch (option)
			{
			case 0:
				break;
			case 1:
				printf("\n");
				modifyFunction(rootsObj->mupObj);
				saveFile();
				break;
			case 2:
				printf("\n");
				defineRange();
				saveFile();
				break;
			case 3:
				printf("\n");
				defineTolerance();
				saveFile();
				break;
			case 4:
				printf("\n");
				defineMaxIterations();
				saveFile();
				break;
			case 5:
				printf("\n");
				evaluateFunction();
				break;
			default:
				if (state >= RANGE_SET && toleranceSet && maxIterationSet)
				{
					switch (option)
					{
					case 6:
						printf("\n");
						BissecaoUI(rootsObj, tolerance, maxIterations);
						break;
					case 7:
						printf("\n");
						CordasUI(rootsObj, tolerance, maxIterations);
						break;
					case 8:
						printf("\n");
						PegasoUI(rootsObj, tolerance, maxIterations);
						break;
					case 9:
						printf("\n");
						NewtonRhapsonUI(rootsObj, tolerance, maxIterations);
						break;
					default:
						invalidOption = 1;
					}
				}
				else
				{
					invalidOption = 1;
				}
			}
			if (invalidOption)
				printf("Opcao invalida, tente novamente: ");

		} while (invalidOption);
	} while (option != 0);

	RootFindingBaseDelete(rootsObj);
	mupRelease(mupObj);
}

void evaluateFunction()
{
	printf("Digite um ponto em que deseja avaliar a funcao: ");
	*(rootsObj->varPtr) = getDouble("", "Tente novamente: ");
	printf("\n");
	printf("f(%lf) = %lf\n", *(rootsObj->varPtr), mupEval(rootsObj->mupObj));
	printf("\n");
	pause();
}

void printMenu()
{
	printf("Opcoes: \n");
	printf("\n");
	printf("1 - Alterar a funcao definida [ %s]\n", StringAbbreviate(mupGetExpr(
			rootsObj->mupObj), 40));

	if (state < RANGE_SET)
		printf("2 - *Definir um intervalo [A, B]\n");
	else
		printf("2 - Alterar o intervalo definido [%lf, %lf]\n", rootsObj->a,
				rootsObj->b);
	if (!toleranceSet)
		printf("3 - *Definir a tolerancia\n");
	else
		printf("3 - Alterar a tolerancia definida [ %lg ]\n", tolerance);
	if (!maxIterationSet)
		printf("4 - *Definir o limite de iteracoes\n");
	else
		printf("4 - Alterar o limite de iteracoes definido [ %u ]\n",
				maxIterations);
	printf("5 - Avaliar a funcao em um ponto\n");

	if (state >= RANGE_SET && toleranceSet && maxIterationSet)
	{
		printf("\n");
		printf("Calcular aproximacao para raiz utilizando:\n");
		printf("\n");
		printf("6 - Metodo da Bissecao\n");
		printf("7 - Metodo das Cordas\n");
		printf("8 - Metodo de Pegaso\n");
		printf("9 - Metodo de Newton-Rhapson\n");
	}

	printf("0 - Sair\n");
	printf("\n");
	printf("Digite uma opcao: ");
}

void modifyFunction(muParserHandle_t mupObj)
{
	readExpr(mupObj, "Digite uma funcao de x: ", "Tente novamente: ");
	state = FUNCTION_SET;
}

void defineMaxIterations()
{
	maxIterations = getUInt("Digite o limite maximo de iteracoes: ",
			"O limite maximo de iteracoes deve ser "
				"um numero inteiro positivo, tente novamente: ");
	maxIterationSet = 1;
}

void defineTolerance()
{
	printf("Digite a tolerancia desejada: ");

	for (;;)
	{
		tolerance = getDouble("", "Tente novamente: ");
		if (tolerance <= 0)
		{
			printf("O valor para tolerancia deve ser maior que zero,"
				" tente novamente: ");
		}
		else
		{
			break;
		}
	}

	toleranceSet = 1;
}

void defineRange()
{
	double a, b;
	a = getDouble("Digite A: ", "Tente novamente: ");
	b = getDouble("Digite B: ", "Tente novamente: ");
	
	if (RootFindingBaseSetRange(rootsObj, a, b))
	{
		state = RANGE_SET;
	}
	else
	{
		printf("\n");
		printf("%s\n", RootFindingBaseGetErrorMessage(rootsObj));
		printf("\n");
		printf("Para avaliar a funcao em um dado ponto, pode-se "
			"utilizar a opcao 5 do menu principal.\n");
		printf("\n");
		pause();
	}
}
