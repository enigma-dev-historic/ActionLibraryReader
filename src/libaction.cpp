/**
* @file  libaction.cpp
* @brief Source implementing a class for a Library Action.
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

#include "libaction.h"

namespace ALR {

LibAction::LibAction()
{
}

int LibAction::hashCode()
{
    const int prime = 31;
    int result = 1;
    result = prime * result + id;
    result = prime * result + ((parent == NULL) ? 0 : parent->hashCode());
    result = prime * result + parentId;
    return result;
}

bool LibAction::equals(LibAction* act)
{
    if (this == act) return true;
    if (act == nullptr) return false;
    if (id != act->id) return false;
    if (parent == nullptr)
    {
        if (act->parent != nullptr) return false;
    }
    else if (act->parent != parent) return false;
    if (parentId != act->parentId) return false;
    return true;
}

}
