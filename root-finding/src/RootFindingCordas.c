/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * RootFindingCordas.c
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * RootFindingCordas.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RootFindingCordas.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding/src/RootFindingCordas.c
 * @file /root-finding/src/RootFindingCordas.c
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#include "RootFindingCordas.h"
#include "messages/RootFindingMessages.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/**
 * @private
 * @brief Set error code and change state to CORDAS_ERROR_FOUND
 * @param cordasObj Ponteiro para objeto RootFindingCordasT
 * @param errorCode Codigo de erro
 * \ingroup _cordas
 */
static void setError(RootFindingCordasT* cordasObj, int errorCode);

/**
 * @private
 * \ingroup _cordas
 */
static void resetError(RootFindingCordasT* cordasObj);

RootFindingCordasT* RootFindingCordasCreate(RootFindingBaseT* rootsObj)
{
	RootFindingCordasT* cordasObj;
	cordasObj = (RootFindingCordasT*) malloc(sizeof(RootFindingCordasT));

	if (cordasObj != NULL)
	{
		cordasObj->rootsObj = rootsObj;
		cordasObj->maxIterations = CORDAS_DEFAULT_MAX_ITERATIONS;
		cordasObj->tolerance = CORDAS_DEFAULT_TOLERANCE;
		cordasObj->state = CORDAS_NOT_INIT;
		//cordasObj->errorCode = CORDAS_NO_ERROR;
		resetError(cordasObj);
	}

	return cordasObj;
}

RootFindingBoolT RootFindingCordasInit(RootFindingCordasT* cordasObj)
{
	//TODO: ver o que acontece se a 2a. dif no ponto for infinito
	RootFindingBoolT success = TRUE;
	RootFindingDoubleT f, f2nDiff;
	f = RootFindingBaseEval(cordasObj->rootsObj, cordasObj->rootsObj->a);
	f2nDiff = RootFindingBase2nDiffEval(cordasObj->rootsObj,
			cordasObj->rootsObj->a);

	//TODO: ver se pode ser igual a zero e avaliar o caso de infinito
	if ((f * f2nDiff) > 0)
	{
		cordasObj->c = cordasObj->rootsObj->a;
		cordasObj->rootsObj->x = cordasObj->rootsObj->b;
	}
	else
	{
		f = RootFindingBaseEval(cordasObj->rootsObj, cordasObj->rootsObj->b);
		f2nDiff = RootFindingBase2nDiffEval(cordasObj->rootsObj,
				cordasObj->rootsObj->b);
		//TODO: ver se pode ser igual a zero e avaliar o caso de infinito
		if ((f * f2nDiff) > 0)
		{
			cordasObj->c = cordasObj->rootsObj->b;
			cordasObj->rootsObj->x = cordasObj->rootsObj->a;
		}
		else
		{
			//erro
			//cordasObj->errorCode = CORDAS_2NDIFF_TEST_ERROR;
			setError(cordasObj, CORDAS_2NDIFF_TEST_ERROR);
			success = FALSE;
		}
	}

	if (success)
	{
		cordasObj->fC = RootFindingBaseEval(cordasObj->rootsObj, cordasObj->c);
		cordasObj->rootsObj->fX = RootFindingBaseEval(cordasObj->rootsObj,
				cordasObj->rootsObj->x);
		cordasObj->i = 0;
		cordasObj->rootsObj->e = infinity();
		cordasObj->state = CORDAS_INITIALIZED;
		resetError(cordasObj);
	}

	return success;
}

/**
 * @private
 * @brief Obtem o valor para o proximo x
 * @param cordasObj Ponteiro para objeto struct RootFindingCordas
 * @return Valor do proximo x
 * \ingroup _cordas
 */
static RootFindingDoubleT getNextX(RootFindingCordasT* cordasObj)
{
	const RootFindingDoubleT xi = cordasObj->rootsObj->x;
	const RootFindingDoubleT c = cordasObj->c;
	const RootFindingDoubleT fC = cordasObj->fC;
	const RootFindingDoubleT fXi = cordasObj->rootsObj->fX;

	return (xi - fXi / (fXi - fC) * (xi - c));
}

void RootFindingCordasDelete(RootFindingCordasT* obj)
{
	free(obj);
}

static void setError(RootFindingCordasT* cordasObj, int errorCode)
{
	cordasObj->errorCode = errorCode;
	cordasObj->state = CORDAS_ERROR_FOUND;
}

RootFindingBoolT RootFindingCordasPerformIteration(
		RootFindingCordasT* cordasObj)
{
	RootFindingBoolT ret;
	RootFindingDoubleT nextX;

	if (cordasObj->rootsObj->fX == 0)
	{
		//cordasObj->state = CORDAS_EXACT_ROOT_FOUND;
		cordasObj->rootsObj->state = ROOTS_EXACT_ROOT_FOUND;
		ret = FALSE;
	}
	else if (cordasObj->i >= cordasObj->maxIterations)
	{
		cordasObj->state = CORDAS_MAX_ITERATIONS_LIMIT_REACHED;
		ret = FALSE;
	}
	else if ((cordasObj->rootsObj->e <= cordasObj->tolerance) && (fabs(
			cordasObj->rootsObj->fX) <= cordasObj->tolerance))
	{
		cordasObj->state = CORDAS_APPROXIMANTION_ROOT_FOUND;
		ret = FALSE;
	}
	else
	{
		nextX = getNextX(cordasObj);
		if (isInfOrNan(nextX))
		{
			setError(cordasObj, CORDAS_X_ISINF_OR_ISNAN_ERROR);
			ret = FALSE;
		}
		else
		{
			(cordasObj->i)++;
			cordasObj->rootsObj->e = fabs(cordasObj->rootsObj->x - nextX);
			cordasObj->rootsObj->x = nextX;
			cordasObj->rootsObj->fX = RootFindingBaseEval(cordasObj->rootsObj,
					cordasObj->rootsObj->x);
			ret = TRUE;
		}
	}

	return ret;
}

int RootFindingCordasGetErrorCode(RootFindingCordasT* cordasObj)
{
	return cordasObj->errorCode;
}

static void resetError(RootFindingCordasT* cordasObj)
{
	cordasObj->errorCode = CORDAS_NO_ERROR;
	
	if (cordasObj->state == CORDAS_ERROR_FOUND)
	{
		cordasObj->state = CORDAS_NOT_INIT;
	}
}

int RootFindingCordasGetStateCode(RootFindingCordasT* cordasObj)
{
	return cordasObj->state;
}

static char msg[255];

const char* RootFindingCordasGetErrorMessage(RootFindingCordasT* cordasObj)
{
	switch (cordasObj->errorCode)
	{
	case CORDAS_NO_ERROR:
		return MSG_CORDAS_NO_ERROR;
	case CORDAS_2NDIFF_TEST_ERROR:
		sprintf(msg, MSG_CORDAS_2NDIFF_TEST_ERROR, cordasObj->rootsObj->a,
				cordasObj->rootsObj->b);
		return msg;
	case CORDAS_X_ISINF_OR_ISNAN_ERROR:
		return MSG_CORDAS_X_ISINF_OR_ISNAN_ERROR;
	default:
		return MSG_ROOTS_UNKNOW_ERROR;
	}
}

const char* RootFindingCordasGetStateMessage(RootFindingCordasT* cordasObj)
{
	switch (cordasObj->state)
	{
	case CORDAS_NOT_INIT:
		return MSG_CORDAS_NOT_INIT;
	case CORDAS_INITIALIZED:
		return MSG_CORDAS_INITIALIZED;
	case CORDAS_MAX_ITERATIONS_LIMIT_REACHED:
		sprintf(msg, MSG_CORDAS_MAX_ITERATIONS_LIMIT_REACHED,
		cordasObj->tolerance, cordasObj->maxIterations, cordasObj->rootsObj->x,
				cordasObj->rootsObj->e);
		return msg;
	case CORDAS_APPROXIMANTION_ROOT_FOUND:
		sprintf(msg, MSG_CORDAS_APPROXIMANTION_ROOT_FOUND,
		cordasObj->rootsObj->x, cordasObj->rootsObj->e);
		return msg;
	case CORDAS_ERROR_FOUND:
		return MSG_CORDAS_ERROR_FOUND
		;
	default:
		return MSG_ROOTS_UNKNOW_STATE;
	}
}

RootFindingBoolT RootFindingCordasHasError(RootFindingCordasT* cordasObj)
{
	return (cordasObj->errorCode != CORDAS_NO_ERROR);
}
