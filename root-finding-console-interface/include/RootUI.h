/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * RootUI.h
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * RootUI.h is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RootUI.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding-console-interface/include/RootUI.h
 * @file /root-finding-console-interface/include/RootUI.h
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#ifndef ROOTUI_H_
#define ROOTUI_H_

#include <stdio.h>
#include "Util.h"
#include <ConsoleTable.h>
#include <RootFindingBase.h>
#include <string.h>

ConsoleTableT* RootUICreateConsoleTable(unsigned iMax, unsigned numPrecicion,
		int includeABCols);

void RootUIPrintTableLine(ConsoleTableT* tableObj, RootFindingBaseT* rootsObj,
		unsigned i, int includeABCols);


#endif /* ROOTUI_H_ */
