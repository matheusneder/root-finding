/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * RootFindingCommon.c
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * RootFindingCommon.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RootFindingCommon.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding/src/RootFindingCommon.c
 * @file /root-finding/src/RootFindingCommon.c
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#include "RootFindingCommon.h"
#include <string.h>
#include <math.h>

RootFindingBoolT getAxisVarPtr(muParserHandle_t mupObj, const char* axis,
		RootFindingDoubleT** varPtr)
{
	const char* varName;
	RootFindingDoubleT* tmpVarPtr;
	int varNum;
	unsigned i;
	varNum = mupGetVarNum(mupObj);

	for (i = 0; i < varNum; i++)
	{
		mupGetVar(mupObj, i, &varName, &tmpVarPtr);
		if (strcmp(varName, axis) == 0)
		{
			*varPtr = tmpVarPtr;
			return TRUE;
		}
	}

	return FALSE;
}

//RootFindingBoolT isInfinity(RootFindingDoubleT value)
//{
//	return ((1/value) == 0);
//}

RootFindingDoubleT infinity()
{
	RootFindingDoubleT zero = 0;

	return 1.0 / zero;
}

RootFindingDoubleT Mup2ndDiff(muParserHandle_t mupObj,
		RootFindingDoubleT* varPtr)
{
	RootFindingDoubleT fXPlusEpsilon, fX, fXMinusEpsilon, xValueBackup;
	RootFindingDoubleT epsilon = (*varPtr == 0) ? (RootFindingDoubleT) 1e-7
			: (RootFindingDoubleT) (1e-7 * *varPtr);
	xValueBackup = *varPtr;
	fX = mupEval(mupObj);
	*varPtr = *varPtr + epsilon;
	fXPlusEpsilon = mupEval(mupObj);
	*varPtr = xValueBackup - epsilon;
	fXMinusEpsilon = mupEval(mupObj);
	*varPtr = xValueBackup;
	
	return (fXPlusEpsilon - 2 * fX + fXMinusEpsilon) / pow(epsilon, 2);
}

RootFindingDoubleT MupDiff(muParserHandle_t mupObj, RootFindingDoubleT* varPtr)
{
	RootFindingDoubleT f[4] =
	{ 0, 0, 0, 0 };
	RootFindingDoubleT position = *varPtr;
	RootFindingDoubleT epsilon;
	epsilon = (position == 0) ? (RootFindingDoubleT) 1e-10 : 1e-7 * position;
	*varPtr = position + 2 * epsilon;
	f[0] = mupEval(mupObj);
	*varPtr = position + 1 * epsilon;
	f[1] = mupEval(mupObj);
	*varPtr = position - 1 * epsilon;
	f[2] = mupEval(mupObj);
	*varPtr = position - 2 * epsilon;
	f[3] = mupEval(mupObj);
	*varPtr = position; // restore variable

	return (-f[0] + 8 * f[1] - 8 * f[2] + f[3]) / (12 * epsilon);
}

RootFindingBoolT isInfOrNan(RootFindingDoubleT num)
{
	return (isinf(num) || isnan(num));
}
