/**
* @file  libaction.h
* @brief Header implementing a class for a Library Action.
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

#ifndef LIBACTION_H
#define LIBACTION_H

class LibAction;

#include "library.h"
#include "libargument.h"

#include <string>
using std::string;

namespace LGL {

enum ActionKind {
    ACT_NORMAL = 0,
    ACT_BEGIN = 1,
    ACT_END = 2,
    ACT_ELSE = 3,
    ACT_EXIT = 4,
    ACT_REPEAT = 5,
    ACT_VARIABLE = 6,
    ACT_CODE = 7,
    ACT_PLACEHOLDER = 8,
    ACT_SEPARATOR = 9,
    ACT_LABEL = 10
};

enum ExecutionKind {
    EXEC_NONE = 0,
    EXEC_FUNCTION = 1,
    EXEC_CODE = 2
};

enum InterfaceKind {
    INTERFACE_NORMAL = 0,
    INTERFACE_NONE = 1,
    INTERFACE_ARROWS = 2,
    INTERFACE_CODE = 5,
    INTERFACE_TEXT = 6
};

class LibAction
{
public:
    int id = 0;
    int parentId = -1; //Preserves the id when library is unknown
    Library* parent = NULL;
    string name = "";
    char actImage[];
    bool hidden = false;
    bool advanced = false;
    bool registeredOnly = false;
    string description = "";
    string listText = "";
    string hintText = "";
    ActionKind actionKind = ACT_NORMAL;
    InterfaceKind interfaceKind = INTERFACE_NORMAL;
    bool question = false;
    bool canApplyTo = false;
    bool allowRelative = false;
    ExecutionKind execType = EXEC_FUNCTION;
    string execInfo = "";
    LibArgument libArguments[];

    LibAction();
};

}

#endif // LIBACTION_H
