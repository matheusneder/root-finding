/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * StringUtilities.h
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * StringUtilities.h is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * StringUtilities.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /string-utilities/include/StringUtilities.h
 * @file /string-utilities/include/StringUtilities.h
 * @date 22/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#ifndef STRINGUTILITIES_H_
#define STRINGUTILITIES_H_

#include <stddef.h>

const char* StringAbbreviate(const char* str, size_t size);

#endif /* STRINGUTILITIES_H_ */
