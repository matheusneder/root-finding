/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * CordasUI.h
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * CordasUI.h is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CordasUI.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /root-finding-console-interface/include/CordasUI.h
 * @file /root-finding-console-interface/include/CordasUI.h
 * @date 25/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#ifndef CORDASUI_H_
#define CORDASUI_H_

#include <RootFindingBase.h>

void CordasUI(RootFindingBaseT* rootsObj, double tolerance, unsigned maxIterations);

#endif /* CORDASUI_H_ */
