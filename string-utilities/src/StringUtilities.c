/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * StringUtilities.c
 * Copyright (C) Matheus Neder 2010 <matheusneder@gmail.com>
 *
 * StringUtilities.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * StringUtilities.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @brief /string-utilities/src/StringUtilities.c
 * @file /string-utilities/src/StringUtilities.c
 * @date 22/03/2010
 * @author Matheus Neder <matheusneder@gmail.com>
 */

#include "StringUtilities.h"
#include <string.h>

const char* StringAbbreviate(const char* str, size_t size)
{
	static char summary[255];
	if (size > 6)
	{
		if (strlen(str) > size)
		{
			summary[0] = '\0';
			strncat(summary, str, size - 4);
			strcat(summary, " ...");
			return summary;
		}
	}
	else
	{
		summary[0] = '\0';
		strncat(summary, str, size);
		return summary;
	}
	return str;
}
