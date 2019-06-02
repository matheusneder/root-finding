/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * RootFindingPegaso.c
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * RootFindingPegaso.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RootFindingPegaso.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding/src/RootFindingPegaso.c
 * @file /root-finding/src/RootFindingPegaso.c
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#include "RootFindingPegaso.h"
#include "messages/RootFindingMessages.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @private
 * @brief Set error code and change state to PEGASO_ERROR_FOUND
 * @param pegasoObj Ponteiro para objeto RootFindingPegasoT
 * @param errorCode Codigo de erro
 * \ingroup _pegaso
 */
static void setError(RootFindingPegasoT* pegasoObj, int errorCode);

/**
 * @private
 * \ingroup _pegaso
 */
static void resetError(RootFindingPegasoT* pegasoObj);

RootFindingPegasoT* RootFindingPegasoCreate(RootFindingBaseT* rootsObj)
{
	RootFindingPegasoT* pegasoObj;
	pegasoObj = (RootFindingPegasoT*) malloc(sizeof(RootFindingPegasoT));

	if (pegasoObj != NULL)
	{
		pegasoObj->rootsObj = rootsObj;
		pegasoObj->maxIterations = PEGASO_DEFAULT_MAX_ITERATIONS;
		pegasoObj->tolerance = PEGASO_DEFAULT_TOLERANCE;
		pegasoObj->state = PEGASO_NOT_INIT;
		//pegasoObj->errorCode = PEGASO_NO_ERROR;
		resetError(pegasoObj);
	}

	return pegasoObj;
}

RootFindingBoolT RootFindingPegasoInit(RootFindingPegasoT* pegasoObj)
{
	pegasoObj->prevXi = pegasoObj->rootsObj->a;
	pegasoObj->fPrevXi = RootFindingBaseEval(pegasoObj->rootsObj,
			pegasoObj->prevXi);
	pegasoObj->rootsObj->x = pegasoObj->rootsObj->b;
	pegasoObj->rootsObj->fX = RootFindingBaseEval(pegasoObj->rootsObj,
			pegasoObj->rootsObj->x);
	pegasoObj->i = 1;
	pegasoObj->state = PEGASO_INITIALIZED;
	resetError(pegasoObj);
	pegasoObj->rootsObj->e = fabs(pegasoObj->rootsObj->x - pegasoObj->prevXi);

	//sempre retornara TRUE, o retrno eh para manter
	//a mesma interface de cordas e newton
	return TRUE;
}

void RootFindingPegasoDelete(RootFindingPegasoT* pegasoObj)
{
	free(pegasoObj);
}

/**
 * @private
 * @brief Obtem o valor para o proximo x
 * @param pegasoObj Ponteiro para objeto struct RootFindingPegaso
 * @return Valor do proximo x
 * \ingroup _pegaso
 */
static RootFindingDoubleT getNextX(RootFindingPegasoT* pegasoObj)
{
	const RootFindingDoubleT prevXi = pegasoObj->prevXi;
	const RootFindingDoubleT fPrevXi = pegasoObj->fPrevXi;
	const RootFindingDoubleT xi = pegasoObj->rootsObj->x;
	const RootFindingDoubleT fXi = pegasoObj->rootsObj->fX;

	return (xi - fXi / (fXi - fPrevXi) * (xi - prevXi));
}

static void setError(RootFindingPegasoT* pegasoObj, int errorCode)
{
	pegasoObj->errorCode = errorCode;
	pegasoObj->state = PEGASO_ERROR_FOUND;
}

RootFindingBoolT RootFindingPegasoPerformIteration(
		RootFindingPegasoT* pegasoObj)
{
	RootFindingBoolT ret;
	RootFindingDoubleT nextX;

	if (pegasoObj->rootsObj->fX == 0)
	{
		pegasoObj->rootsObj->state = ROOTS_EXACT_ROOT_FOUND;
		ret = FALSE;
	}
	else if (pegasoObj->i >= pegasoObj->maxIterations)
	{
		pegasoObj->state = PEGASO_MAX_ITERATIONS_LIMIT_REACHED;
		ret = FALSE;
	}
	else if ((pegasoObj->rootsObj->e <= pegasoObj->tolerance) && (fabs(
			pegasoObj->rootsObj->fX) <= pegasoObj->tolerance))
	{
		pegasoObj->state = PEGASO_APPROXIMANTION_ROOT_FOUND;
		ret = FALSE;
	}
	else
	{
		nextX = getNextX(pegasoObj);
		if (isInfOrNan(nextX))
		{
			setError(pegasoObj, PEGASO_X_ISINF_OR_ISNAN_ERROR);
			ret = FALSE;
		}
		else
		{
			(pegasoObj->i)++;
			pegasoObj->rootsObj->e = fabs(nextX - pegasoObj->rootsObj->x);
			pegasoObj->prevXi = pegasoObj->rootsObj->x;
			pegasoObj->fPrevXi = RootFindingBaseEval(pegasoObj->rootsObj,
					pegasoObj->prevXi);
			pegasoObj->rootsObj->x = nextX;
			pegasoObj->rootsObj->fX = RootFindingBaseEval(pegasoObj->rootsObj,
					pegasoObj->rootsObj->x);
			ret = TRUE;
		}
	}

	return ret;
}

int RootFindingPegasoGetErrorCode(RootFindingPegasoT* pegasoObj)
{
	return pegasoObj->errorCode;
}

static void resetError(RootFindingPegasoT* pegasoObj)
{
	pegasoObj->errorCode = PEGASO_NO_ERROR;
	
	if (pegasoObj->state == PEGASO_ERROR_FOUND)
	{
		pegasoObj->state = PEGASO_NOT_INIT;
	}
}

int RootFindingPegasoGetStateCode(RootFindingPegasoT* pegasoObj)
{
	return pegasoObj->state;
}

static char msg[255];

const char* RootFindingPegasoGetErrorMessage(RootFindingPegasoT* pegasoObj)
{
	switch (pegasoObj->errorCode)
	{
	case PEGASO_NO_ERROR:
		return MSG_PEGASO_NO_ERROR;
	case PEGASO_X_ISINF_OR_ISNAN_ERROR:
		return MSG_PEGASO_X_ISINF_OR_ISNAN_ERROR;
	default:
		return MSG_ROOTS_UNKNOW_ERROR;
	}
}

const char* RootFindingPegasoGetStateMessage(RootFindingPegasoT* pegasoObj)
{
	switch (pegasoObj->state)
	{
	case PEGASO_NOT_INIT:
		return MSG_PEGASO_NOT_INIT;
	case PEGASO_INITIALIZED:
		return MSG_PEGASO_INITIALIZED;
	case PEGASO_MAX_ITERATIONS_LIMIT_REACHED:
		sprintf(msg, MSG_PEGASO_MAX_ITERATIONS_LIMIT_REACHED,
		pegasoObj->tolerance, pegasoObj->maxIterations, pegasoObj->rootsObj->x,
				pegasoObj->rootsObj->e);
		return msg;
	case PEGASO_APPROXIMANTION_ROOT_FOUND:
		sprintf(msg, MSG_PEGASO_APPROXIMANTION_ROOT_FOUND,
		pegasoObj->rootsObj->x, pegasoObj->rootsObj->e);
		return msg;
	case PEGASO_ERROR_FOUND:
		return MSG_PEGASO_ERROR_FOUND
		;
	default:
		return MSG_ROOTS_UNKNOW_STATE;
	}
}

RootFindingBoolT RootFindingPegasoHasError(RootFindingPegasoT* pegasoObj)
{
	return (pegasoObj->errorCode != PEGASO_NO_ERROR);
}
