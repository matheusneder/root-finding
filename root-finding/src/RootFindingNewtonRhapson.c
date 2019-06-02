/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * RootFindingNewtonRhapson.c
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * RootFindingNewtonRhapson.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RootFindingNewtonRhapson.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding/src/RootFindingNewtonRhapson.c
 * @file /root-finding/src/RootFindingNewtonRhapson.c
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#include "RootFindingNewtonRhapson.h"
#include "messages/RootFindingMessages.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/**
 * @private
 * @brief Set error code and change state to NEWTON_ERROR_FOUND
 * @param newtonObj Ponteiro para objeto RootFindingNewtonRhapson
 * @param errorCode Codigo de erro
 * \ingroup _newton
 */
static void setError(RootFindingNewtonRhapsonT* newtonObj, int errorCode);

/**
 * @private
 * \ingroup _newton
 */
static void resetError(RootFindingNewtonRhapsonT* newtonObj);

RootFindingNewtonRhapsonT* RootFindingNewtonRhapsonCreate(
		RootFindingBaseT* rootsObj)
{
	RootFindingNewtonRhapsonT* newtonObj;
	newtonObj = (RootFindingNewtonRhapsonT*) malloc(
			sizeof(RootFindingNewtonRhapsonT));
	if (newtonObj != NULL)
	{
		newtonObj->rootsObj = rootsObj;
		newtonObj->maxIterations = NEWTON_DEFAULT_MAX_ITERATIONS;
		newtonObj->tolerance = NEWTON_DEFAULT_TOLERANCE;
		newtonObj->state = NEWTON_NOT_INIT;
		resetError(newtonObj);
	}

	return newtonObj;
}

RootFindingBoolT RootFindingNewtonRhapsonInit(
		RootFindingNewtonRhapsonT* newtonObj)
{
	//TODO: tratar os casos de fA, fB, f'A, f'B, f''A, f''B forem infinito
	RootFindingBoolT success = TRUE;
	RootFindingDoubleT fA, fB, f2ndDiffA, f2ndDiffB;
	fA = RootFindingBaseEval(newtonObj->rootsObj, newtonObj->rootsObj->a);
	f2ndDiffA = RootFindingBase2nDiffEval(newtonObj->rootsObj,
			newtonObj->rootsObj->a);
	fB = RootFindingBaseEval(newtonObj->rootsObj, newtonObj->rootsObj->b);
	f2ndDiffB = RootFindingBase2nDiffEval(newtonObj->rootsObj,
			newtonObj->rootsObj->b);

	if ((f2ndDiffA * f2ndDiffB) > 0)
	{
		if ((fA * f2ndDiffA) > 0)
		{
			newtonObj->rootsObj->x = newtonObj->rootsObj->a;
		}
		else
		{
			if ((fB * f2ndDiffB) > 0)
			{
				newtonObj->rootsObj->x = newtonObj->rootsObj->b;
			}
			else
			{
				//newtonObj->errorCode = NEWTON_2NDIFF_TEST_ERROR;
				setError(newtonObj, NEWTON_2NDIFF_TEST_ERROR);
				success = FALSE;
			}
		}
	}
	else
	{
		//newtonObj->errorCode = NEWTON_2NDIFFA_2NDIFFB_SIGN_NOT_EQUALS_ERROR;
		setError(newtonObj, NEWTON_2NDIFFA_2NDIFFB_SIGN_NOT_EQUALS_ERROR);
		success = FALSE;
	}

	if (success)
	{
		newtonObj->i = 0;
		newtonObj->rootsObj->fX = RootFindingBaseEval(newtonObj->rootsObj,
				newtonObj->rootsObj->x);
		newtonObj->rootsObj->e = infinity();
		newtonObj->state = NEWTON_INITIALIZED;
		newtonObj->state = NEWTON_NO_ERROR;
	}

	return success;
}

void RootFindingNewtonRhapsonDelete(RootFindingNewtonRhapsonT* newtonObj)
{
	free(newtonObj);
}

/**
 * @private
 * @brief Obtem o valor para o proximo x
 * @param newtonObj Ponteiro para objeto struct RootFindingNewtonRhapson
 * @return Valor do proximo x
 * \ingroup _newton
 */
static RootFindingDoubleT getNextX(RootFindingNewtonRhapsonT* newtonObj)
{
	const RootFindingDoubleT xi = newtonObj->rootsObj->x;
	const RootFindingDoubleT fXi = newtonObj->rootsObj->fX;
	const RootFindingDoubleT fDiffXi = RootFindingBaseDiffEval(
			newtonObj->rootsObj, xi);

	return (xi - fXi / fDiffXi);
}

static void setError(RootFindingNewtonRhapsonT* newtonObj, int errorCode)
{
	newtonObj->errorCode = errorCode;
	newtonObj->state = NEWTON_ERROR_FOUND;
}

RootFindingBoolT RootFindingNewtonRhapsonPerformIteration(
		RootFindingNewtonRhapsonT* newtonObj)
{
	RootFindingBoolT ret;
	RootFindingDoubleT nextX;
	if (newtonObj->rootsObj->fX == 0)
	{
		//newtonObj->state = NEWTON_EXACT_ROOT_FOUND;
		newtonObj->rootsObj->state = ROOTS_EXACT_ROOT_FOUND;
		ret = FALSE;
	}
	else if (newtonObj->i >= newtonObj->maxIterations)
	{
		newtonObj->state = NEWTON_MAX_ITERATIONS_LIMIT_REACHED;
		ret = FALSE;
	}
	else if ((newtonObj->rootsObj->e <= newtonObj->tolerance) && (fabs(
			newtonObj->rootsObj->fX) <= newtonObj->tolerance))
	{
		newtonObj->state = NEWTON_APPROXIMANTION_ROOT_FOUND;
		ret = FALSE;
	}
	else
	{
		nextX = getNextX(newtonObj);
		if (isInfOrNan(nextX))
		{
			//newtonObj->errorCode == NEWTON_X_ISINF_OR_ISNAN_ERROR;
			setError(newtonObj, NEWTON_X_ISINF_OR_ISNAN_ERROR);
			ret = FALSE;
		}
		else
		{
			(newtonObj->i)++;
			newtonObj->rootsObj->e = fabs(newtonObj->rootsObj->x - nextX);
			newtonObj->rootsObj->x = nextX;
			newtonObj->rootsObj->fX = RootFindingBaseEval(newtonObj->rootsObj,
					newtonObj->rootsObj->x);
			ret = TRUE;
		}
	}

	return ret;
}

int RootFindingNewtonRhapsonGetErrorCode(RootFindingNewtonRhapsonT* newtonObj)
{
	return newtonObj->errorCode;
}

static void resetError(RootFindingNewtonRhapsonT* newtonObj)
{
	newtonObj->errorCode = NEWTON_NO_ERROR;
	
	if (newtonObj->state == NEWTON_ERROR_FOUND)
	{
		newtonObj->state = NEWTON_NOT_INIT;
	}
}

int RootFindingNewtonRhapsonGetStateCode(RootFindingNewtonRhapsonT* newtonObj)
{
	return newtonObj->state;
}

static char msg[255];

const char* RootFindingNewtonRhapsonGetErrorMessage(
		RootFindingNewtonRhapsonT* newtonObj)
{
	switch (newtonObj->errorCode)
	{
	case NEWTON_NO_ERROR:
		return MSG_NEWTON_NO_ERROR;
	case NEWTON_2NDIFF_TEST_ERROR:
		sprintf(msg, MSG_NEWTON_2NDIFF_TEST_ERROR, newtonObj->rootsObj->a,
				newtonObj->rootsObj->b);
		return msg;
	case NEWTON_2NDIFFA_2NDIFFB_SIGN_NOT_EQUALS_ERROR:
		sprintf(msg, MSG_NEWTON_2NDIFFA_2NDIFFB_SIGN_NOT_EQUALS_ERROR,
				newtonObj->rootsObj->a, newtonObj->rootsObj->b);
		return msg;
	case NEWTON_X_ISINF_OR_ISNAN_ERROR:
		sprintf(msg, MSG_NEWTON_X_ISINF_OR_ISNAN_ERROR, newtonObj->rootsObj->x,
				newtonObj->rootsObj->x, newtonObj->rootsObj->e);
		return msg;
	default:
		return MSG_ROOTS_UNKNOW_ERROR;
	}
}

const char* RootFindingNewtonRhapsonGetStateMessage(
		RootFindingNewtonRhapsonT* newtonObj)
{
	switch (newtonObj->state)
	{
	case NEWTON_NOT_INIT:
		return MSG_NEWTON_NOT_INIT;
	case NEWTON_INITIALIZED:
		return MSG_NEWTON_INITIALIZED;
	case NEWTON_MAX_ITERATIONS_LIMIT_REACHED:
		sprintf(msg, MSG_NEWTON_MAX_ITERATIONS_LIMIT_REACHED,
		newtonObj->tolerance, newtonObj->maxIterations, newtonObj->rootsObj->x,
				newtonObj->rootsObj->e);
		return msg;
	case NEWTON_APPROXIMANTION_ROOT_FOUND:
		sprintf(msg, MSG_NEWTON_APPROXIMANTION_ROOT_FOUND,
		newtonObj->rootsObj->x, newtonObj->rootsObj->e);
		return msg;
	case NEWTON_ERROR_FOUND:
		return MSG_NEWTON_ERROR_FOUND;
	default:
		return MSG_ROOTS_UNKNOW_STATE;
	}
}

RootFindingBoolT RootFindingNewtonRhapsonHasError(RootFindingNewtonRhapsonT* newtonObj)
{
	return (newtonObj->errorCode != NEWTON_NO_ERROR);
}
