/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Util.h
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * Util.h is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Util.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding-console-interface/include/Util.h
 * @file /root-finding-console-interface/include/Util.h
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <muParserDLL.h>

#define ENTER_CODE 10

void readExpr(muParserHandle_t mupObj, const char* inputMsg,
		const char* retryMsg);

void getLine(char str[]);

double getDouble(const char* inputMsg, const char* retryMsg);

int getInt(const char* inputMsg, const char* retryMsg);

unsigned getUInt(const char* inputMsg, const char* retryMsg);

void pause();

void printNChars(char c, unsigned n);

void formatDouble(char* s, double num, int width, int precision);

#endif /* UTIL_H_ */
