/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * RootFindingCordas.h
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * RootFindingCordas.h is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RootFindingCordas.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding/include/RootFindingCordas.h
 * @file /root-finding/include/RootFindingCordas.h
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#ifndef ROOTFINDINGCORDAS_H_
#define ROOTFINDINGCORDAS_H_

#include <muParserDLL.h>
#include "RootFindingCommon.h"
#include "RootFindingBase.h"

/**
 * \defgroup _cordas Metodo das Cordas
 * @{
 */

#define CORDAS_DEFAULT_MAX_ITERATIONS 	100
#define CORDAS_DEFAULT_TOLERANCE 		1e-7

/**
 * @brief Estrutura de dados para o Metodo das Cordas
 */
struct RootFindingCordas
{
	unsigned i;
	RootFindingBaseT* rootsObj;
	RootFindingDoubleT c;
	RootFindingDoubleT fC;
	unsigned maxIterations;
	RootFindingDoubleT tolerance;

	/**
	 * @brief Codigo de estado: nao acessar diretamente. Veja
	 * 	\ref RootFindingCordasGetStateCode e \ref RootFindingCordasGetStateMessage
	 */
	enum
	{
		CORDAS_NOT_INIT = 0,
		CORDAS_INITIALIZED,
		//CORDAS_EXACT_ROOT_FOUND,
		CORDAS_MAX_ITERATIONS_LIMIT_REACHED,
		CORDAS_APPROXIMANTION_ROOT_FOUND,
		CORDAS_ERROR_FOUND
	} state;

	/**
	 * @brief Codigo de erro: nao acessar diretamente. Veja
	 * 	\ref RootFindingCordasGetErrorCode e \ref RootFindingCordasGetErrorMessage
	 */
	enum
	{
		CORDAS_NO_ERROR = 0,
		CORDAS_2NDIFF_TEST_ERROR,
		CORDAS_X_ISINF_OR_ISNAN_ERROR
	} errorCode;
};

/**
 * @brief Apelido para struct RootFindingCordas
 */
typedef struct RootFindingCordas RootFindingCordasT;

/**
 * @brief Cria um objeto do tipo struct RootFindingCordas
 * @param rootsObj Ponteiro para o objeto do tipo struct RootFindingBase
 * @return Ponteiro para o objeto criado
 */
RootFindingCordasT* RootFindingCordasCreate(RootFindingBaseT* rootsObj);

/**
 * @brief Inicializa o objeto RootFindingCordas
 * @param cordasObj Ponteiro para o objeto a ser inicializado
 * @return TRUE em caso de sucesso
 */
RootFindingBoolT RootFindingCordasInit(RootFindingCordasT* cordasObj);

/**
 * @brief Apaga a instancia do objeto RootFindingCordas
 * @param obj Ponteiro para o obj RootFindingCordas
 */
void RootFindingCordasDelete(RootFindingCordasT* obj);

/**
 * @brief Realiza a iteracao
 * @param cordasObj Ponteiro para o objeto
 * @return TRUE caso haja mais iteracoes a serem realizadas
 */
RootFindingBoolT RootFindingCordasPerformIteration(RootFindingCordasT* cordasObj);

/**
 * @brief Obtem o codigo de erro
 */
int RootFindingCordasGetErrorCode(RootFindingCordasT* cordasObj);

/**
 * @brief Obtem o codigo referente ao estado do objeto
 */
int RootFindingCordasGetStateCode(RootFindingCordasT* cordasObj);

/**
 * @brief Obtem a mensagem de erro
 */
const char* RootFindingCordasGetErrorMessage(RootFindingCordasT* cordasObj);

/**
 * @brief Obtem a mensagem referente ao estado do objeto
 */
const char* RootFindingCordasGetStateMessage(RootFindingCordasT* cordasObj);

/**
 * @brief Verifica se ha erros
 * @return TRUE caso haja erro
 */
RootFindingBoolT RootFindingCordasHasError(RootFindingCordasT* cordasObj);

/** @} */

#endif /* ROOTFINDINGCORDAS_H_ */
