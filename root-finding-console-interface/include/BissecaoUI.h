/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * BissecaoUI.h
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * BissecaoUI.h is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BissecaoUI.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding-console-interface/include/BissecaoUI.h
 * @file /root-finding-console-interface/include/BissecaoUI.h
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#ifndef BISSECAOUI_H_
#define BISSECAOUI_H_

#include <RootFindingBase.h>

void BissecaoUI(RootFindingBaseT* rootsObj, double tolerance, unsigned maxIterations);

#endif /* BISSECAOUI_H_ */
