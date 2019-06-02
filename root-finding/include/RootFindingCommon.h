/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * RootFindingCommon.h
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * RootFindingCommon.h is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RootFindingCommon.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding/include/RootFindingCommon.h
 * @file /root-finding/include/RootFindingCommon.h
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#ifndef ROOTFINDINGCOMMONS_H_
#define ROOTFINDINGCOMMONS_H_

#include <muParserDLL.h>

typedef double RootFindingDoubleT;

typedef int RootFindingBoolT;

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/**
 * @brief Obtem o endereco para a variavel do eixo onde deve-se
 * @param mupObj Ponteiro para objeto muParser contendo a expressao
 * @param axis Eixo em qual a raiz deve ser procurada
 * @param [out] varPtr Ponteiro para onde o endereco deve ser atribuido
 * @return TRUE em caso de sucesso FALSE em caso de falha
 */
RootFindingBoolT getAxisVarPtr(muParserHandle_t mupObj, const char* axis,
		RootFindingDoubleT** varPtr);

/**
 * @brief Aproximacao da segunda diferencial no ponto utilizando
 * 	"Finite difference"
 * @param mupObj Objeto muParser (ponteiro)
 * @param varPtr Ponteiro para a variavel relacionada a expressao no objeto
 * 	muParser referente a qual variavel deve ser diferenciado
 * @return Valor da segunda diferencial no ponto
 */
RootFindingDoubleT Mup2ndDiff(muParserHandle_t mupObj, RootFindingDoubleT* varPtr);

/**
 * @brief Aproximacao da diferencial no ponto utilizando "regard to a variable"
 * 	O codigo foi adaptado para C c/ base no metodo Diff da classe muParser (C++),
 * 	infelizmente a API para C do muParser nao disbonibiliza o metodo Diff
 * @param mupObj Objeto muParser (ponteiro)
 * @param varPtr Ponteiro para a variavel relacionada a expressao no objeto
 * 	muParser referente a qual variavel deve ser diferenciado
 * @return Valor da diferencial no ponto
 */
RootFindingDoubleT MupDiff(muParserHandle_t mupObj, RootFindingDoubleT* varPtr);

/**
 * @brief Obtem o valor infinito
 * @return inf
 */
RootFindingDoubleT infinity();

/**
 * @brief Verifica se um dado numero \ref RootFindingDoubleT eh infinito ou "Not a Number"
 * @param num Numero a verificado
 * @return TRUE se isinf(num) ou isnan(num)
 */
RootFindingBoolT isInfOrNan(RootFindingDoubleT num);

#endif /* ROOTFINDINGCOMMONS_H_ */
