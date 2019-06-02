/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * RootFindingBase.h
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * RootFindingBase.h is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RootFindingBase.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding/include/RootFindingBase.h
 * @file /root-finding/include/RootFindingBase.h
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#ifndef ROOTFINDINGBASE_H_
#define ROOTFINDINGBASE_H_

#include "RootFindingCommon.h"

/**
 * \defgroup _roots Parte Generica
 * @{
 */

/**
 * @brief Estrutura de dados para RootFindingBase
 */
struct RootFindingBase
{
	RootFindingDoubleT a;
	RootFindingDoubleT b;
	RootFindingDoubleT x;
	RootFindingDoubleT fX;
	RootFindingDoubleT e;
	muParserHandle_t mupObj;
	RootFindingDoubleT* varPtr;

	/**
	 * @brief Codigo de erro: nao acessar diretamente. Veja \ref RootFindingBaseGetErrorCode
	 * 	e \ref RootFindingBaseGetErrorMessage
	 */
	enum
	{
		ROOTS_NO_ERROR = 0,
		ROOTS_MUP_EVAL_ERROR,
		// just to mark RANGE_ERRORS_START
		RANGE_ERRORS_START,
		/* range errors */
		ROOTS_RANGE_ERROR_PROD_FA_FB_NOT_LT_0,
		ROOTS_RANGE_ERROR_FA_OR_FB_ISINFINITY,
		/* end range errors */
		RANGE_ERRORS_END
		// just to mark RANGE_ERRORS_END

	} errorCode;

	/**
	 * @brief Codigo de estado: nao acessar diretamente. Veja \ref RootFindingBaseGetStateCode
	 * 	e \ref RootFindingBaseGetStateMessage
	 */
	enum
	{
		ROOTS_RANGE_NOT_SET = 0,
		ROOTS_READY,
		ROOTS_EXACT_ROOT_FOUND
	} state;
};

/**
 * @brief Apelido para struct RootFindingBase
 */
typedef struct RootFindingBase RootFindingBaseT;

/**
 * @brief Cria o objeto RootFindingBase
 * @param mupObj Ponteiro para o objeto muParser contendo a expressao
 * @param varPtr Pontero para a variavel relacionada a expressao no objeto
 * 	muParser referente a qual eixo deve se procurar a raiz
 * @return Ponteiro para o objeto criado
 */
RootFindingBaseT* RootFindingBaseCreate(muParserHandle_t mupObj, RootFindingDoubleT* varPtr);

/**
 * @brief Apaga o objeto RootFindingBase
 * @param obj Ponteiro para o objeto RootFindingBase
 */
void RootFindingBaseDelete(RootFindingBaseT* obj);

/**
 * @brief Define o intervalo para procura da raiz
 * @param rootsObj Ponteiro para o objeto RootFindingBase
 * @param a
 * @param b
 * @return TRUE em caso de sucesso, quando f(a) * f(b) < 0 'e' f(a),
 * 	f(b) sejam ambos diferentes de infinito
 */
RootFindingBoolT RootFindingBaseSetRange(RootFindingBaseT* rootsObj, RootFindingDoubleT a, RootFindingDoubleT b);

/**
 * @brief Avalia a funcao em um ponto
 * @param rootsObj Ponteiro para o objeto struct RootFindingBase
 * @param value Valor do ponto a ser avaliado
 * @return Avaliacao da funcao no ponto
 */
RootFindingDoubleT RootFindingBaseEval(RootFindingBaseT* rootsObj, RootFindingDoubleT value);

/**
 * @brief Avalia a 2a. diferencial da funcao em um ponto
 * @param rootsObj Ponteiro para o objeto struct RootFindingBase
 * @param value Valor do ponto a ser avaliado
 * @return Avaliacao da 2a. dif da funcao no ponto
 */
RootFindingDoubleT RootFindingBase2nDiffEval(RootFindingBaseT* rootsObj, RootFindingDoubleT value);

/**
 * @brief Avalia a diferencial da funcao em um ponto
 * @param rootsObj Ponteiro para o objeto struct RootFindingBase
 * @param value Valor do ponto a ser avaliado
 * @return Avaliacao da dif da funcao no ponto
 */
RootFindingDoubleT RootFindingBaseDiffEval(RootFindingBaseT* rootsObj, RootFindingDoubleT value);

/**
 * @brief Reinicializa o objeto struct RootFindingBase
 * @param rootsObj Ponteiro para o objeto struct RootFindingBase
 */
void RootFindingBaseReset(RootFindingBaseT* rootsObj);

/**
 * @brief Obtem o codigo de erro
 */
int RootFindingBaseGetErrorCode(RootFindingBaseT* rootsObj);

/**
 * @brief Obtem o codigo referente ao estado do objeto
 */
int RootFindingBaseGetStateCode(RootFindingBaseT* rootsObj);

/**
 * @brief Obtem a mensagem de erro
 */
const char* RootFindingBaseGetErrorMessage(RootFindingBaseT* rootsObj);

/**
 * @brief Obtem a mensagem referente ao estado do objeto
 */
const char* RootFindingBaseGetStateMessage(RootFindingBaseT* rootsObj);

/**
 * @brief Verifica se ha erros
 * @return TRUE caso haja erro
 */
RootFindingBoolT RootFindingBaseHasError(RootFindingBaseT* rootsObj);

/** @} */

#endif /* ROOTFINDINGBASE_H_ */
