/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Util.c
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * Util.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Util.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding-console-interface/src/Util.c
 * @file /root-finding-console-interface/src/Util.c
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#include "Util.h"

void pause()
{
	printf("Tecle <ENTER> para continuar");
	while (fgetc(stdin) != ENTER_CODE)
		;
}

double getDouble(const char* inputMsg, const char* retryMsg)
{
	double ret;
	muParserHandle_t mupObj = mupCreate();
	readExpr(mupObj, inputMsg, retryMsg);
	ret = mupEval(mupObj);
	mupRelease(mupObj);
	return ret;
}

static char buffer[255];

int getInt(const char* inputMsg, const char* retryMsg)
{
	int multiplier;
	static char strNum[255];
	int error;
	printf("%s", inputMsg);

	do
	{
		multiplier = 1;
		error = 0;
		getLine(buffer);
		int i = 0, j = 0;
		for (; i < strlen(buffer) && (buffer[i] == ' ' || buffer[i] == '0'); i++)
			;
		if (i < strlen(buffer) && (buffer[i] == '-' || buffer[i] == '+'))
		{
			if (buffer[i] == '-')
				multiplier = -1;
			i++;
		}
		for (; i < strlen(buffer); i++)
		{
			if (buffer[i] < '0' || buffer[i] > '9')
			{
				printf("%s", retryMsg);
				error = 1;
				break;
			}
			else
			{
				strNum[j] = buffer[i];
				j++;
			}
		}
		strNum[j] = '\0';
	} while (error);

	return atoi(strNum) * multiplier;
}

unsigned getUInt(const char* inputMsg, const char* retryMsg)
{
	int num;
	printf("%s", inputMsg);

	do
	{
		num = getInt("", retryMsg);
		if (num < 0)
			printf("%s", retryMsg);
	} while (num < 0);

	return (unsigned) num;
}

void getLine(char str[])
{
	size_t i = 0;
	char chr;

	for (;;)
	{
		chr = fgetc(stdin);
		if (chr != ENTER_CODE)
		{
			str[i++] = chr;
		}
		else
		{
			if (i > 0)
			{
				str[i] = '\0';
				break;
			}
		}
	}

}

void readExpr(muParserHandle_t mupObj, const char* inputMsg,
		const char* retryMsg)
{
	static char expr[255];
	int varNum;
	unsigned i;
	double** vars = NULL;
	char** varNames = NULL;
	const char* varName;
	varNum = mupGetVarNum(mupObj);

	if (varNum > 0)
	{
		vars = (double**) malloc(sizeof(double*) * varNum);
		varNames = (char**) malloc(sizeof(char*) * varNum);
		for (i = 0; i < varNum; i++)
		{
			varNames[i] = (char*) malloc(sizeof(char) * 50);
			mupGetVar(mupObj, i, &(varName), &(vars[i]));
			strcpy(varNames[i], varName);
			*(vars[i]) = 1;
		}
	}

	int error;
	printf("%s", inputMsg);

	do
	{
		getLine(expr);
		mupErrorReset(mupObj);
		mupSetExpr(mupObj, expr);
		mupEval(mupObj);
		error = mupError(mupObj);
		if (error)
		{
			printf("* Expressao mal formada!\n");
			if (varNum > 0)
			{
				if (varNum == 1)
				{
					printf("Note que eh esperado uma expressao "
						"em funcao da variavel '%s'\n", varNames[0]);
				}
				else
				{
					printf("Note que eh esperado uma expressao em "
						"funcao das variaveis {");
					for (i = 0; i < varNum; i++)
					{
						if (i != 0)
						{
							printf(", ");
						}
						printf("'%s'", varNames[i]);
					}
					printf("}\n");
				}
			}
			printf("%s", retryMsg);
		}
	} while (error);

	if (varNum > 0)
	{
		free(vars);
		for (i = 0; i < varNum; i++)
		{
			free(varNames[i]);
		}
		free(varNames);
	}
}

void printNChars(char c, unsigned n)
{
	unsigned i = 0;

	for(; i < n; i++)
	{
		printf("%c", c);
	}
}

void formatDouble(char* s, double num, int width, int precision)
{
	sprintf(s, "%-*.*lf", width, precision, num);
	int i = strlen(s) - 1;

	for (; i >= 1; i--)
	{
		if (s[i] == '0' || s[i] == ' ' || s[i] == '.')
			s[i] = '\0';
		else
			break;
	}
	
	if (strcmp(s, "-") == 0)
		s[0] = '0';
}
