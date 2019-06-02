/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * RootFindingBissecao.c
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * RootFindingBissecao.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RootFindingBissecao.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding/src/RootFindingBissecao.c
 * @file /root-finding/src/RootFindingBissecao.c
 * @date 26/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#include "RootFindingBissecao.h"
#include "messages/RootFindingMessages.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/**
 * @private
 * @brief Set error code and change state to BISSECAO_ERROR_FOUND
 * @param bissecaoObj Ponteiro para objeto RootFindingBissecaoT
 * @param errorCode Codigo de erro
 * \ingroup _bissecao
 */
static void setError(RootFindingBissecaoT* bissecaoObj, int errorCode);

/**
 * @private
 * \ingroup _bissecao
 */
static void resetError(RootFindingBissecaoT* bissecaoObj);

RootFindingBissecaoT* RootFindingBissecaoCreate(RootFindingBaseT* rootsObj)
{
	RootFindingBissecaoT* bissecaoObj;
	bissecaoObj = (RootFindingBissecaoT*) malloc(sizeof(RootFindingBissecaoT));

	if (bissecaoObj != NULL)
	{
		bissecaoObj->rootsObj = rootsObj;
		bissecaoObj->maxIterations = BISSECAO_DEFAULT_MAX_ITERATIONS;
		bissecaoObj->tolerance = BISSECAO_DEFAULT_TOLERANCE;
		bissecaoObj->state = BISSECAO_NOT_INIT;
		//bissecaoObj->errorCode = BISSECAO_NO_ERROR;
		resetError(bissecaoObj);
	}

	return bissecaoObj;
}

/**
 * @private
 * @brief Calcula o X baseado no intervalo [a, b]
 * @param bissecaoObj Ponteiro para o objeto RootFindingBissecao
 * @return O X calculado
 * \ingroup _bissecao
 */
static RootFindingDoubleT computeX(RootFindingBissecaoT* bissecaoObj)
{
	const RootFindingDoubleT a = bissecaoObj->rootsObj->a;
	const RootFindingDoubleT b = bissecaoObj->rootsObj->b;
	return ((a + b) / 2);
}

RootFindingBoolT RootFindingBissecaoInit(RootFindingBissecaoT* bissecaoObj)
{
	bissecaoObj->i = 0;
	bissecaoObj->rootsObj->x = computeX(bissecaoObj);
	bissecaoObj->rootsObj->fX = RootFindingBaseEval(bissecaoObj->rootsObj,
			bissecaoObj->rootsObj->x);
	bissecaoObj->rootsObj->e = infinity();
	bissecaoObj->state = BISSECAO_INITIALIZED;
	resetError(bissecaoObj);

	return TRUE;
}

void RootFindingBissecaoDelete(RootFindingBissecaoT* obj)
{
	free(obj);
}

RootFindingBoolT RootFindingBissecaoPerformIteration(
		RootFindingBissecaoT* bissecaoObj)
{
	RootFindingBoolT ret;
	RootFindingDoubleT nextX;

	if (bissecaoObj->rootsObj->fX == 0)
	{
		//bissecaoObj->state = BISSECAO_EXACT_ROOT_FOUND;
		bissecaoObj->rootsObj->state = ROOTS_EXACT_ROOT_FOUND;
		ret = FALSE;
	}
	else if (bissecaoObj->i >= bissecaoObj->maxIterations)
	{
		bissecaoObj->state = BISSECAO_MAX_ITERATIONS_LIMIT_REACHED;
		ret = FALSE;
	}
	else if ((bissecaoObj->rootsObj->e <= bissecaoObj->tolerance) && (fabs(
			bissecaoObj->rootsObj->fX) <= bissecaoObj->tolerance))
	{
		bissecaoObj->state = BISSECAO_APPROXIMANTION_ROOT_FOUND;
		ret = FALSE;
	}
	else
	{
		RootFindingBissecaoFindNewRange(bissecaoObj->rootsObj);
		nextX = computeX(bissecaoObj);

		if (isInfOrNan(nextX))
		{
			setError(bissecaoObj, BISSECAO_X_ISINF_OR_ISNAN_ERROR);
			ret = FALSE;
		}
		else
		{
			(bissecaoObj->i)++;
			bissecaoObj->rootsObj->e = fabs(bissecaoObj->rootsObj->x - nextX);
			bissecaoObj->rootsObj->x = nextX;
			bissecaoObj->rootsObj->fX = RootFindingBaseEval(
					bissecaoObj->rootsObj, bissecaoObj->rootsObj->x);
			ret = TRUE;
		}
	}

	return ret;
}

void RootFindingBissecaoFindNewRange(RootFindingBaseT* rootsObj)
{
	RootFindingDoubleT fA;
	fA = RootFindingBaseEval(rootsObj, rootsObj->a);

	if ((fA * rootsObj->fX) < 0)
	{
		rootsObj->b = rootsObj->x;
	}
	else
	{
		rootsObj->a = rootsObj->x;
	}
}

static void setError(RootFindingBissecaoT* bissecaoObj, int errorCode)
{
	bissecaoObj->state = BISSECAO_ERROR_FOUND;
	bissecaoObj->errorCode = errorCode;
}

int RootFindingBissecaoGetErrorCode(RootFindingBissecaoT* bissecaoObj)
{
	return bissecaoObj->errorCode;
}

static void resetError(RootFindingBissecaoT* bissecaoObj)
{
	bissecaoObj->errorCode = BISSECAO_NO_ERROR;
	
	if (bissecaoObj->state == BISSECAO_ERROR_FOUND)
	{
		bissecaoObj->state = BISSECAO_NOT_INIT;
	}
}

int RootFindingBissecaoGetStateCode(RootFindingBissecaoT* bissecaoObj)
{
	return bissecaoObj->state;
}

static char msg[255];

const char* RootFindingBissecaoGetErrorMessage(
		RootFindingBissecaoT* bissecaoObj)
{
	switch (bissecaoObj->errorCode)
	{
	case BISSECAO_NO_ERROR:
		return MSG_BISSECAO_NO_ERROR;
	case BISSECAO_X_ISINF_OR_ISNAN_ERROR:
		return MSG_BISSECAO_X_ISINF_OR_ISNAN_ERROR;
	default:
		return MSG_ROOTS_UNKNOW_ERROR;
	}
}

const char* RootFindingBissecaoGetStateMessage(
		RootFindingBissecaoT* bissecaoObj)
{
	switch (bissecaoObj->state)
	{
	case BISSECAO_NOT_INIT:
		return MSG_BISSECAO_NOT_INIT;
	case BISSECAO_INITIALIZED:
		return MSG_BISSECAO_INITIALIZED;
	case BISSECAO_MAX_ITERATIONS_LIMIT_REACHED:
		sprintf(msg, MSG_BISSECAO_MAX_ITERATIONS_LIMIT_REACHED,
		bissecaoObj->tolerance, bissecaoObj->maxIterations,
				bissecaoObj->rootsObj->x, bissecaoObj->rootsObj->e);
		return msg;
	case BISSECAO_APPROXIMANTION_ROOT_FOUND:
		sprintf(msg, MSG_BISSECAO_APPROXIMANTION_ROOT_FOUND,
		bissecaoObj->rootsObj->x, bissecaoObj->rootsObj->e);
		return msg;
	case BISSECAO_ERROR_FOUND:
		return MSG_BISSECAO_ERROR_FOUND
		;
	default:
		return MSG_ROOTS_UNKNOW_STATE;
	}
}

RootFindingBoolT RootFindingBissecaoHasError(RootFindingBissecaoT* bissecaoObj)
{
	return (bissecaoObj->errorCode != BISSECAO_NO_ERROR);
}
