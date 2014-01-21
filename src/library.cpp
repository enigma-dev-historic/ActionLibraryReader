/**
* @file  libargument.cpp
* @brief Source implementing a class for an Action Library.
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

#include "library.h"

namespace LGL {

Library::Library()
{
}

LibAction* Library::addLibAction()
{
    LibAction* act = new LibAction();
    libActions.push_back(act);
    return act;
}

LibAction* Library::getLibAction(int id)
{
    for (LibAction* act : libActions)
        if (act->id == id) return act;
    return nullptr;
}

}
