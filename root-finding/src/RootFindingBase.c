/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * RootFindingBase.c
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * RootFindingBase.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RootFindingBase.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding/src/RootFindingBase.c
 * @file /root-finding/src/RootFindingBase.c
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#include "RootFindingBase.h"
#include "messages/RootFindingMessages.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

RootFindingBaseT* RootFindingBaseCreate(muParserHandle_t mupObj,
		RootFindingDoubleT* varPtr)
{
	RootFindingBaseT* rootsObj;
	rootsObj = (RootFindingBaseT*) malloc(sizeof(RootFindingBaseT));

	if (rootsObj != NULL)
	{
		rootsObj->varPtr = varPtr;
		rootsObj->mupObj = mupObj;
		RootFindingBaseReset(rootsObj);
	}

	return rootsObj;
}

void RootFindingBaseReset(RootFindingBaseT* rootsObj)
{
	RootFindingDoubleT fX;
	rootsObj->errorCode = ROOTS_NO_ERROR;
	rootsObj->state = ROOTS_RANGE_NOT_SET;
	rootsObj->e = infinity();
	
	//validar a expressao
	fX = RootFindingBaseEval(rootsObj, 1);

	if (mupError(rootsObj->mupObj))
	{
		rootsObj->errorCode = ROOTS_MUP_EVAL_ERROR;
	}
}

void RootFindingBaseDelete(RootFindingBaseT* obj)
{
	free(obj);
}

/**
 * @private
 * @brief Verify if errorCode is a RangeError
 * \ingroup _roots
 */
static RootFindingBoolT isRangeError(RootFindingBaseT* rootsObj)
{
	return (rootsObj->errorCode > RANGE_ERRORS_START && rootsObj->errorCode
			< RANGE_ERRORS_END);
}

RootFindingBoolT RootFindingBaseSetRange(RootFindingBaseT* rootsObj,
		RootFindingDoubleT a, RootFindingDoubleT b)
{
	RootFindingBoolT success = FALSE;
	if (!RootFindingBaseHasError(rootsObj) || isRangeError(rootsObj))
	{
		rootsObj->errorCode = ROOTS_NO_ERROR;
		RootFindingDoubleT fA, fB;
		fA = RootFindingBaseEval(rootsObj, a);
		fB = RootFindingBaseEval(rootsObj, b);

		if (isinf(fA) || isinf(fB))
		{
			success = FALSE;
			rootsObj->errorCode = ROOTS_RANGE_ERROR_FA_OR_FB_ISINFINITY;
		}

		//TODO: ver se (fA * fB) pode ser 0
		else if (((fA * fB) >= 0))
		{
			success = FALSE;
			rootsObj->errorCode = ROOTS_RANGE_ERROR_PROD_FA_FB_NOT_LT_0;
		}
		else
		{
			success = TRUE;
			rootsObj->a = a;
			rootsObj->b = b;
			rootsObj->state = ROOTS_READY;
		}
	}

	return success;
}

RootFindingDoubleT RootFindingBaseEval(RootFindingBaseT* rootsObj,
		RootFindingDoubleT value)
{
	*(rootsObj->varPtr) = value;

	return mupEval(rootsObj->mupObj);
}

RootFindingDoubleT RootFindingBase2nDiffEval(RootFindingBaseT* rootsObj,
		RootFindingDoubleT value)
{
	*(rootsObj->varPtr) = value;

	return Mup2ndDiff(rootsObj->mupObj, rootsObj->varPtr);
}

RootFindingDoubleT RootFindingBaseDiffEval(RootFindingBaseT* rootsObj,
		RootFindingDoubleT value)
{
	*(rootsObj->varPtr) = value;
	
	return MupDiff(rootsObj->mupObj, rootsObj->varPtr);
}

int RootFindingBaseGetErrorCode(RootFindingBaseT* rootsObj)
{
	return rootsObj->errorCode;
}

int RootFindingBaseGetStateCode(RootFindingBaseT* rootsObj)
{
	return rootsObj->state;
}

static char msg[255];

const char* RootFindingBaseGetErrorMessage(RootFindingBaseT* rootsObj)
{
	switch (rootsObj->errorCode)
	{
	case ROOTS_NO_ERROR:
		return MSG_ROOTS_NO_ERROR;
	case ROOTS_MUP_EVAL_ERROR:
		return MSG_ROOTS_MUP_EVAL_ERROR;
	case ROOTS_RANGE_ERROR_PROD_FA_FB_NOT_LT_0:
		sprintf(msg, MSG_ROOTS_RANGE_ERROR_PROD_FA_FB_NOT_LT_0, rootsObj->a,
				rootsObj->b);
		return msg;
	case ROOTS_RANGE_ERROR_FA_OR_FB_ISINFINITY:
		sprintf(msg, MSG_ROOTS_RANGE_ERROR_FA_OR_FB_ISINFINITY, rootsObj->a,
				rootsObj->b);
		return msg;
	default:
		return MSG_ROOTS_UNKNOW_ERROR;
	}
}

const char* RootFindingBaseGetStateMessage(RootFindingBaseT* rootsObj)
{
	switch (rootsObj->state)
	{
	case ROOTS_RANGE_NOT_SET:
		return MSG_ROOTS_RANGE_NOT_SET;
	case ROOTS_READY:
		return MSG_ROOTS_READY;
	case ROOTS_EXACT_ROOT_FOUND:
		sprintf(msg, MSG_ROOTS_EXACT_ROOT_FOUND, rootsObj->x);
		return msg;
	default:
		return MSG_ROOTS_UNKNOW_STATE;
	}
}

RootFindingBoolT RootFindingBaseHasError(RootFindingBaseT* rootsObj)
{
	return (rootsObj->errorCode != ROOTS_NO_ERROR);
}
