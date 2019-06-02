/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * RootFindingBissecao.h
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * RootFindingBissecao.h is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RootFindingBissecao.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding/include/RootFindingBissecao.h
 * @file /root-finding/include/RootFindingBissecao.h
 * @date 26/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#ifndef ROOTFINDINGBISSECAO_H_
#define ROOTFINDINGBISSECAO_H_

/**
 * \defgroup _bissecao Metodo da Bissecao
 * @{
 */

#define BISSECAO_DEFAULT_MAX_ITERATIONS 	100
#define BISSECAO_DEFAULT_TOLERANCE 			1e-7

#include "RootFindingBase.h"

/**
 * @brief Estrutura de dados para o Metodo da Bissecao
 */
struct RootFindingBissecao
{
	unsigned i;
	RootFindingBaseT* rootsObj;
	unsigned maxIterations;
	RootFindingDoubleT tolerance;

	/**
	 * @brief Codigo de estado: nao acessar diretamente. Veja \ref RootFindingBissecaoGetStateCode
	 * 	e \ref RootFindingBissecaoGetStateMessage
	 */
	enum
	{
		BISSECAO_NOT_INIT = 0,
		BISSECAO_INITIALIZED,
		BISSECAO_MAX_ITERATIONS_LIMIT_REACHED,
		BISSECAO_APPROXIMANTION_ROOT_FOUND,
		BISSECAO_ERROR_FOUND
	} state;

	/**
	 * @brief Codigo de erro: nao acessar diretamente. Veja
	 * 	\ref RootFindingBissecaoGetErrorCode e \ref RootFindingBissecaoGetErrorMessage
	 */
	enum
	{
		BISSECAO_NO_ERROR = 0,
		BISSECAO_X_ISINF_OR_ISNAN_ERROR
	} errorCode;
};

/**
 * @brief Apelido para struct RootFindingBissecao
 */
typedef struct RootFindingBissecao RootFindingBissecaoT;

/**
 * @brief Cria um objeto do tipo struct RootFindingBissecao
 * @param rootsObj Ponteiro para o objeto do tipo struct RootFindingBase
 * @return Ponteiro para o objeto criado
 */
RootFindingBissecaoT* RootFindingBissecaoCreate(RootFindingBaseT* rootsObj);

/**
 * @brief Inicializa o objeto RootFindingBissecao
 * @param bissecaoObj Ponteiro para o objeto a ser inicializado
 * @return TRUE em caso de sucesso
 */
RootFindingBoolT RootFindingBissecaoInit(RootFindingBissecaoT* bissecaoObj);

/**
 * @brief Apaga a instancia do objeto RootFindingBissecao
 * @param obj Ponteiro para o obj RootFindingBissecao
 */
void RootFindingBissecaoDelete(RootFindingBissecaoT* obj);

/**
 * @brief Realiza a iteracao
 * @param bissecaoObj Ponteiro para o objeto
 * @return TRUE caso haja mais iteracoes a serem realizadas
 */
RootFindingBoolT RootFindingBissecaoPerformIteration(
		RootFindingBissecaoT* bissecaoObj);

/**
 * @brief Encontra um novo intervalo [A, B] e os altera no objeto RootFindingBaseT
 * 	baseado nos [A, B] e x existentes. Utilizado em \ref RootFindingBissecaoPerformIteration
 * 	porem principalmente util para alterar o intervalo quando intercambiando entre
 * 	metodos diferentes
 * @param rootsObj Ponteiro para o objeto RootFindingBase
 */
void RootFindingBissecaoFindNewRange(RootFindingBaseT* rootsObj);

/**
 * @brief Obtem o codigo de erro
 */
int RootFindingBissecaoGetErrorCode(RootFindingBissecaoT* bissecaoObj);

/**
 * @brief Obtem o codigo referente ao estado do objeto
 */
int RootFindingBissecaoGetStateCode(RootFindingBissecaoT* bissecaoObj);

/**
 * @brief Obtem a mensagem de erro
 */
const char* RootFindingBissecaoGetErrorMessage(RootFindingBissecaoT* bissecaoObj);

/**
 * @brief Obtem a mensagem referente ao estado do objeto
 */
const char* RootFindingBissecaoGetStateMessage(RootFindingBissecaoT* bissecaoObj);

/**
 * @brief Verifica se ha erros
 * @return TRUE caso haja erro
 */
RootFindingBoolT RootFindingBissecaoHasError(RootFindingBissecaoT* bissecaoObj);

/** @} */

#endif /* ROOTFINDINGBISSECAO_H_ */
