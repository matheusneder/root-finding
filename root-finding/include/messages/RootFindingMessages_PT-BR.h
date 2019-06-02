/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * RootFindingMessages_PT-BR.h
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * RootFindingMessages_PT-BR.h is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RootFindingMessages_PT-BR.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding/include/messages/RootFindingMessages_PT-BR.h
 * @file /root-finding/include/messages/RootFindingMessages_PT-BR.h
 * @date 02/04/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

/**
 * \defgroup _messages Mensagens de estados e erros
 * @{
 */

#ifndef ROOTFINDINGMESSAGESPTBR_H_
#define ROOTFINDINGMESSAGESPTBR_H_

#define MSG_ROOTS_UNKNOW_ERROR						"Erro desconhecido."
#define MSG_ROOTS_UNKNOW_STATE						"Estado desconhecido."

//Generic messages
#define MSG_GENERIC_APPROXIMANTION_ROOT_FOUND 		"Encontrado uma aproximacao da raiz: %lf "\
													"(com e = %lg)."

#define MSG_GENERIC_MAX_ITERATIONS_LIMIT_REACHED	"Nao pode ser encontrado "\
													"uma aproximacao "\
													"(com t <= %lg) para o limite "\
													"de iteracoes igual a %u.\n"\
													"\n"\
													"O valor obtido foi: %lf (com e = %lg)."

#define MSG_GENERIC_NO_ERROR						"Nao ocorreu erro."
#define MSG_GENERIC_ERROR_FOUND						"Ocorreu erro.";
#define MSG_GENERIC_NOT_INIT						"Nao inicializado."
#define MSG_GENERIC_INITIALIZED						"Inicializado."

#define MSG_GENERIC_X_ISINF_OR_ISNAN_ERROR			"Ocorreu uma indeterminacao do "\
													"tipo (0/0, inf/inf ...) durante o processo."

#define MSG_GENERIC_2NDIFF_TEST_ERROR				"O teste da segunda derivada "\
													"falhou para ambos os extremos"\
													"do intervalo [%lf, %lf]."

//RootFindingBase error messages
#define MSG_ROOTS_NO_ERROR 							MSG_GENERIC_NO_ERROR
#define MSG_ROOTS_MUP_EVAL_ERROR					"Erro c/ expressao do objeto muParser"

#define MSG_ROOTS_RANGE_ERROR_PROD_FA_FB_NOT_LT_0	"f(%lf) * f(%lf) >= 0, portanto nao eh possivel "\
													"procurar raizes no intervalo."

#define MSG_ROOTS_RANGE_ERROR_FA_OR_FB_ISINFINITY	"A funcao nao esta definida para um ou ambos "\
													"dos extremos de [%lf, %lf]."

//RootFindingBase state messages
#define MSG_ROOTS_RANGE_NOT_SET						"Intervalo nao esta definido."
#define MSG_ROOTS_READY								"Objeto RootFindingBase esta pronto."
#define MSG_ROOTS_EXACT_ROOT_FOUND					"Encontrado a raiz exata: %lf."

//RootFindingBissecao error messages
#define MSG_BISSECAO_NO_ERROR						MSG_GENERIC_NO_ERROR
#define MSG_BISSECAO_X_ISINF_OR_ISNAN_ERROR			MSG_GENERIC_X_ISINF_OR_ISNAN_ERROR

//RootFindingBissecao state messages
#define MSG_BISSECAO_NOT_INIT						MSG_GENERIC_NOT_INIT
#define MSG_BISSECAO_INITIALIZED					MSG_GENERIC_INITIALIZED
#define MSG_BISSECAO_MAX_ITERATIONS_LIMIT_REACHED	MSG_GENERIC_MAX_ITERATIONS_LIMIT_REACHED
#define MSG_BISSECAO_APPROXIMANTION_ROOT_FOUND		MSG_GENERIC_APPROXIMANTION_ROOT_FOUND
#define MSG_BISSECAO_ERROR_FOUND					MSG_GENERIC_ERROR_FOUND

//RootFindingCordas error messages
#define MSG_CORDAS_NO_ERROR							MSG_GENERIC_NO_ERROR

#define MSG_CORDAS_2NDIFF_TEST_ERROR				MSG_GENERIC_2NDIFF_TEST_ERROR

#define MSG_CORDAS_X_ISINF_OR_ISNAN_ERROR			MSG_GENERIC_X_ISINF_OR_ISNAN_ERROR

//RootFindingCordas state messages
#define MSG_CORDAS_NOT_INIT							MSG_GENERIC_NOT_INIT
#define MSG_CORDAS_INITIALIZED						MSG_GENERIC_INITIALIZED
#define MSG_CORDAS_MAX_ITERATIONS_LIMIT_REACHED		MSG_GENERIC_MAX_ITERATIONS_LIMIT_REACHED
#define MSG_CORDAS_APPROXIMANTION_ROOT_FOUND		MSG_GENERIC_APPROXIMANTION_ROOT_FOUND
#define MSG_CORDAS_ERROR_FOUND						MSG_GENERIC_ERROR_FOUND

//RootFindingNewtonRhapson error messages
#define MSG_NEWTON_NO_ERROR							MSG_GENERIC_NO_ERROR

#define MSG_NEWTON_2NDIFF_TEST_ERROR				MSG_GENERIC_2NDIFF_TEST_ERROR

#define MSG_NEWTON_2NDIFFA_2NDIFFB_SIGN_NOT_EQUALS_ERROR \
													"O sinal da segunda derivada nos extremos "\
													"do intervalo [%lf, %lf] nao se conserva."

#define MSG_NEWTON_X_ISINF_OR_ISNAN_ERROR			"Nao pode ser encontrada uma aproximacao "\
													"para a raiz. A causa mais provavel "\
													"eh de que a derivada da funcao "\
													"no ponto da iteracao imediatamente posterior "\
													"a do ponto '%lf' "\
													"seja igual a 0.\n"\
													"\n"\
													"O valor encontrado ateh a "\
													"iteracao onde ocorreu o problema foi:"\
													"%lf (com e = %lg)."

//RootFindingNewtonRhapson state messages
#define MSG_NEWTON_NOT_INIT							MSG_GENERIC_NOT_INIT
#define MSG_NEWTON_INITIALIZED						MSG_GENERIC_INITIALIZED
#define MSG_NEWTON_MAX_ITERATIONS_LIMIT_REACHED		MSG_GENERIC_MAX_ITERATIONS_LIMIT_REACHED
#define MSG_NEWTON_APPROXIMANTION_ROOT_FOUND		MSG_GENERIC_APPROXIMANTION_ROOT_FOUND
#define MSG_NEWTON_ERROR_FOUND						MSG_GENERIC_ERROR_FOUND

//RootFindingPegaso error messages
#define MSG_PEGASO_NO_ERROR							MSG_GENERIC_NO_ERROR
#define MSG_PEGASO_X_ISINF_OR_ISNAN_ERROR			MSG_GENERIC_X_ISINF_OR_ISNAN_ERROR

//RootFindingPegaso state messages
#define MSG_PEGASO_NOT_INIT							MSG_GENERIC_NOT_INIT
#define MSG_PEGASO_INITIALIZED						MSG_GENERIC_INITIALIZED
#define MSG_PEGASO_MAX_ITERATIONS_LIMIT_REACHED		MSG_GENERIC_MAX_ITERATIONS_LIMIT_REACHED
#define MSG_PEGASO_APPROXIMANTION_ROOT_FOUND		MSG_GENERIC_APPROXIMANTION_ROOT_FOUND
#define MSG_PEGASO_ERROR_FOUND						MSG_GENERIC_ERROR_FOUND

/** @} */

#endif /* ROOTFINDINGMESSAGESPTBR_H_ */
