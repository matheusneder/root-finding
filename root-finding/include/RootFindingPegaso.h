/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * RootFindingPegaso.h
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * RootFindingPegaso.h is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RootFindingPegaso.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding/include/RootFindingPegaso.h
 * @file /root-finding/include/RootFindingPegaso.h
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#ifndef ROOTFINDINGPEGASO_H_
#define ROOTFINDINGPEGASO_H_

#include <muParserDLL.h>
#include "RootFindingCommon.h"
#include "RootFindingBase.h"

/**
 * \defgroup _pegaso Metodo de Pegaso
 * @{
 */

#define PEGASO_DEFAULT_MAX_ITERATIONS 	100
#define PEGASO_DEFAULT_TOLERANCE 		1e-7

/**
 * @brief Estrutura de dados para o Metodo de Pegaso
 */
struct RootFindingPegaso
{
	unsigned i;
	RootFindingBaseT* rootsObj;
	RootFindingDoubleT prevXi;
	RootFindingDoubleT fPrevXi;
	RootFindingDoubleT tolerance;
	unsigned maxIterations;

	/**
	 * @brief Codigo de estado: nao acessar diretamente. Veja
	 * 	\ref RootFindingPegasoGetStateCode e \ref RootFindingPegasoGetStateMessage
	 */
	enum
	{
		PEGASO_NOT_INIT = 0,
		PEGASO_INITIALIZED,
		PEGASO_MAX_ITERATIONS_LIMIT_REACHED,
		PEGASO_APPROXIMANTION_ROOT_FOUND,
		PEGASO_ERROR_FOUND
	} state;

	/**
	 * @brief Codigo de erro: nao acessar diretamente. Veja
	 * 	\ref RootFindingPegasoGetErrorCode e \ref RootFindingPegasoGetErrorMessage
	 */
	enum
	{
		PEGASO_NO_ERROR = 0,
		PEGASO_X_ISINF_OR_ISNAN_ERROR
	} errorCode;

};

/**
 * @brief Apelido para struct RootFindingPegaso
 */
typedef struct RootFindingPegaso RootFindingPegasoT;

/**
 * @brief Cria um objeto do tipo struct RootFindingPegaso
 * @param rootsObj Ponteiro para o objeto do tipo struct RootFindingBase
 * @return Ponteiro para o objeto criado
 */
RootFindingPegasoT* RootFindingPegasoCreate(RootFindingBaseT* rootsObj);

/**
 * @brief Inicializa o objeto RootFindingPegaso
 * @param pegasoObj Ponteiro para o objeto a ser inicializado
 * @return TRUE em caso de sucesso
 */
RootFindingBoolT RootFindingPegasoInit(RootFindingPegasoT* pegasoObj);

/**
 * @brief Apaga a instancia do objeto RootFindingPegaso
 * @param obj Ponteiro para o obj RootFindingPegaso
 */
void RootFindingPegasoDelete(RootFindingPegasoT* obj);

/**
 * @brief Realiza a iteracao
 * @param pegasoObj Ponteiro para o objeto
 * @return TRUE caso haja mais iteracoes a serem realizadas
 */
RootFindingBoolT RootFindingPegasoPerformIteration(RootFindingPegasoT* pegasoObj);

/**
 * @brief Obtem o codigo de erro
 */
int RootFindingPegasoGetErrorCode(RootFindingPegasoT* pegasoObj);

/**
 * @brief Obtem o codigo referente ao estado do objeto
 */
int RootFindingPegasoGetStateCode(RootFindingPegasoT* pegasoObj);

/**
 * @brief Obtem a mensagem de erro
 */
const char* RootFindingPegasoGetErrorMessage(RootFindingPegasoT* pegasoObj);

/**
 * @brief Obtem a mensagem referente ao estado do objeto
 */
const char* RootFindingPegasoGetStateMessage(RootFindingPegasoT* pegasoObj);

/**
 * @brief Verifica se ha erros
 * @return TRUE caso haja erro
 */
RootFindingBoolT RootFindingPegasoHasError(RootFindingPegasoT* pegasoObj);

/** @} */

#endif /* ROOTFINDINGPEGASO_H_ */
