/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * RootFindingNewtonRhapson.h
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * RootFindingNewtonRhapson.h is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RootFindingNewtonRhapson.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding/include/RootFindingNewtonRhapson.h
 * @file /root-finding/include/RootFindingNewtonRhapson.h
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#ifndef ROOTFINDINGNEWTONRHAPSON_H_
#define ROOTFINDINGNEWTONRHAPSON_H_

#include <muParserDLL.h>
#include "RootFindingCommon.h"
#include "RootFindingBase.h"

/**
 * \defgroup _newton Metodo de Newton-Rhapson
 * @{
 */

#define NEWTON_DEFAULT_MAX_ITERATIONS 	100
#define NEWTON_DEFAULT_TOLERANCE 		1e-7

/**
 * @brief Estrutura de dados para o Metodo de Newton-Rhapson
 */
struct RootFindingNewtonRhapson
{
	unsigned i;
	RootFindingBaseT* rootsObj;
	//RootFindingDoubleT xi;
	//RootFindingDoubleT fXi;
	unsigned maxIterations;
	RootFindingDoubleT tolerance;

	/**
	 * @brief Codigo de estado: nao acessar diretamente. Veja
	 * 	\ref RootFindingNewtonRhapsonGetStateCode e
	 * 	\ref RootFindingNewtonRhapsonGetStateMessage
	 */
	enum
	{
		NEWTON_NOT_INIT = 0,
		NEWTON_INITIALIZED,
		//NEWTON_EXACT_ROOT_FOUND,
		NEWTON_MAX_ITERATIONS_LIMIT_REACHED,
		NEWTON_APPROXIMANTION_ROOT_FOUND,//,
		NEWTON_ERROR_FOUND
//		NEWTON_ERROR_FDIFFX_POS_EQ_0
	} state;

	/**
	 * @brief Codigo de erro: nao acessar diretamente. Veja
	 * 	\ref RootFindingNewtonRhapsonGetErrorCode e
	 * 	\ref RootFindingNewtonRhapsonGetErrorMessage
	 */
	enum
	{
		NEWTON_NO_ERROR = 0,
		NEWTON_2NDIFF_TEST_ERROR,
		NEWTON_2NDIFFA_2NDIFFB_SIGN_NOT_EQUALS_ERROR,//,
		NEWTON_X_ISINF_OR_ISNAN_ERROR
//		NEWTON_FDIFFX_POS_EQ_0
	} errorCode;
};

/**
 * @brief Apelido para struct RootFindingNewtonRhapson
 */
typedef struct RootFindingNewtonRhapson RootFindingNewtonRhapsonT;

/**
 * @brief Cria um objeto do tipo struct RootFindingNewtonRhapson
 * @param rootsObj Ponteiro para objeto do tipo struct RootFindingBase
 * @return Ponteiro para o objeto criado
 */
RootFindingNewtonRhapsonT* RootFindingNewtonRhapsonCreate(RootFindingBaseT* rootsObj);

/**
 * @brief Inicializa o objeto RootFindingNewtonRhapson
 * @param newtonObj Ponteiro para o objeto a ser inicializado
 * @return TRUE em caso de sucesso, FALSE caso contrario
 */
RootFindingBoolT RootFindingNewtonRhapsonInit(RootFindingNewtonRhapsonT* newtonObj);

/**
 * @brief Apaga o objeto RootFindingNewtonRhapson
 * @param newtonObj Ponteiro para o objeto
 */
void RootFindingNewtonRhapsonDelete(RootFindingNewtonRhapsonT* newtonObj);

/**
 * @brief Realiza a iteracao
 * @param newtonObj Ponteiro para o objeto
 * @return TRUE caso haja mais iteracoes a serem realizadas
 */
RootFindingBoolT RootFindingNewtonRhapsonPerformIteration(RootFindingNewtonRhapsonT* newtonObj);

/**
 * @brief Obtem o codigo de erro
 */
int RootFindingNewtonRhapsonGetErrorCode(RootFindingNewtonRhapsonT* newtonObj);

/**
 * @brief Obtem o codigo referente ao estado do objeto
 */
int RootFindingNewtonRhapsonGetStateCode(RootFindingNewtonRhapsonT* newtonObj);

/**
 * @brief Obtem a mensagem de erro
 */
const char* RootFindingNewtonRhapsonGetErrorMessage(RootFindingNewtonRhapsonT* newtonObj);

/**
 * @brief Obtem a mensagem referente ao estado do objeto
 */
const char* RootFindingNewtonRhapsonGetStateMessage(RootFindingNewtonRhapsonT* newtonObj);

/**
 * @brief Verifica se ha erros
 * @return TRUE caso haja erro
 */
RootFindingBoolT RootFindingNewtonRhapsonHasError(RootFindingNewtonRhapsonT* newtonObj);

/** @} */

#endif /* ROOTFINDINGNEWTONRHAPSON_H_ */
