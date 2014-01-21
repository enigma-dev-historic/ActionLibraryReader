/**
* @file  libargument.h
* @brief Header implementing a class for a Library Argument.
*
* @section License
*
* Copyright (C) 2014 Robert B. Colton
* This file is a part of the LGL Reader Library.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef LIBARGUMENT_H
#define LIBARGUMENT_H

#include <string>
using std::string;

namespace LGL {

enum ArgumentKind {
    ARG_EXPRESSION = 0,
    ARG_STRING = 1,
    ARG_BOTH = 2,
    ARG_BOOLEAN = 3,
    ARG_MENU = 4,
    ARG_COLOR = 13,
    //Deprecated
    ARG_FONTSTRING = 15,
    ARG_SPRITE = 5,
    ARG_SOUND = 6,
    ARG_BACKGROUND = 7,
    ARG_PATH = 8,
    ARG_SCRIPT = 9,
    ARG_GMOBJECT = 10,
    ARG_ROOM = 11,
    ARG_FONT = 12,
    ARG_TIMELINE = 14
};

class LibArgument
{
public:
    string caption = "";
    ArgumentKind kind = ARG_EXPRESSION;
    string defaultVal = "";
    string menu = "";

    LibArgument();
};

}

#endif // LIBARGUMENT_H
