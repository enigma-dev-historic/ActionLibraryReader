/**
* @file  libmanager.cpp
* @brief Source implementing a class for a Library Manager.
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

#include "libmanager.h"

namespace LGL {

LibManager::LibManager()
{
}

LibAction* LibManager::getLibAction(int libraryId, int libActionId)
{
    for (Library* l : libs) {
        if (l->id == libraryId) {
            LibAction* act = l->getLibAction(libActionId);
            if (act != nullptr) return act;
        }
    }
    return nullptr;
}

bool LibManager::passFilter(string fn)
{
    const string exts[] = { ".lib", ".lgl" };
    for (string ext : exts)
        if (fn.substr(fn.length() - ext.length(), ext.length()).compare(ext) == 0) return true;
    return false;
}

/**
 * Loads a library file of given fileName of either LIB or LGL format
 * @param filename
 * @return the library
 * @throws LibFormatException
 */
Library* LibManager::loadFile(string filename)
{
    GmStreamDecoder stream(filename,ios::in|ios::binary);
    if (!stream.is_open()) {
        return nullptr;
    }
    return loadFile(&stream,filename);
}

/**
 * Loads a library file of given fileName of either LIB or LGL format
 * @param in
 * @param filename for error reporting
 * @return the library
 * @throws LibFormatException
 */
Library* LibManager::loadFile(GmStreamDecoder* in, string filename)
{
    Library* lib = nullptr;

    int header = in->read3();
    if (header == (('L' << 16) | ('G' << 8) | 'L'))
        lib = loadLgl(in);
    else if (header == 500 || header == 520)
        lib = loadLib(in);
    else
        return nullptr;
    libs.push_back(lib);

    if (in != nullptr) in->close();
    return lib;
}

/**
 * Workhorse for constructing a library out of given StreamDecoder of LIB format
 * @param in
 * @return the library (not yet added to the libs list)
 * @throws LibFormatException
 * @throws IOException
 */
Library* LibManager::loadLib(GmStreamDecoder* in)
{
    if (in->read() != 0)
        return nullptr;
    Library* lib = new Library();
    lib->tabCaption = in->readStr();
    lib->id = in->read4();
    in->skip(in->read4());
    in->skip(4);
    in->skip(8);
    in->skip(in->read4());
    in->skip(in->read4());
    lib->advanced = in->readBool();
    in->skip(4); // no of actions/official lib identifier thingy
    int acts = in->read4();
    for (int j = 0; j < acts; j++)
    {
        int ver = in->read4();
        if (ver != 500 && ver != 520)
        {
            //TODO: Add exception handling
            //throw new LibFormatException(Messages.format("LibManager.ERROR_INVALIDACTION",j,"%s",ver));
        }

        LibAction* act = lib->addLibAction();
        act->parent = lib;
        act->name = in->readStr();
        act->id = in->read4();

        act->actImage = in->read(in->read4());

        act->hidden = in->readBool();
        act->advanced = in->readBool();
        if (ver == 520) act->registeredOnly = in->readBool();
        act->description = in->readStr();
        act->listText = in->readStr();
        act->hintText = in->readStr();
        act->actionKind = (ActionKind) in->read4();
        act->interfaceKind = (InterfaceKind) in->read4();
        act->question = in->readBool();
        act->canApplyTo = in->readBool();
        act->allowRelative = in->readBool();
        int args = in->read4();
        for (int k = 0; k < args; k++)
        {
            if (k < act->libArguments.size())
            {
                LibArgument* arg = new LibArgument();
                arg->caption = in->readStr();
                arg->kind = (ArgumentKind) in->read4();
                arg->defaultVal = in->readStr();
                arg->menu = in->readStr();
                act->libArguments.push_back(arg);
            } else {
                in->skip(in->read4());
                in->skip(4);
                in->skip(in->read4());
                in->skip(in->read4());
            }
        }
        act->execType = (ExecutionKind) in->read4();
        if (act->execType == EXEC_FUNCTION)
            act->execInfo = in->readStr();
        else
            in->skip(in->read4());
        if (act->execType == EXEC_CODE)
            act->execInfo = in->readStr();
        else
            in->skip(in->read4());
        }
    return lib;
}

/**
 * Convenience method to retrieve whether the given bit is masked in bits,
 * That is, if given flag is set.
 * E.g.: to find out if the 3rd flag from right is set in 00011*0*10, use mask(26,4);
 * @param bits - A cluster of flags/bits
 * @param bit - The desired (and already shifted) bit or bits to mask
 * @return Whether bit is masked in bits
 */
bool mask(int bits, int bit)
{
    return (bits & bit) == bit;
}

/**
 * Workhorse for constructing a library out of given StreamDecoder of LGL format
 * @param in
 * @return the library (not yet added to the libs list)
 * @throws LibFormatException
 * @throws IOException
 */
Library* LibManager::loadLgl(GmStreamDecoder* in)
{
    if (in->read2() != 160)
    {
       //TODO: Add exception handling
       // String invalidFile = Messages.getString("LibManager.ERROR_INVALIDFILE"); //$NON-NLS-1$
       // throw new LibFormatException(invalidFile);
    }
    Library* lib = new Library();
    lib->id = in->read3();
    lib->tabCaption = in->readStr1();
    in->skip(in->read());
    in->skip(4);
    in->skip(8);
    in->skip(in->read4());
    in->skip(in->read4());
    int acts = in->read();
    lib->advanced = mask(acts,128);
    acts &= 127;
    for (int j = 0; j < acts; j++)
    {
        //TODO: Add exception handling
        //if (in->read2() != 160)
           // throw new LibFormatException(Messages.format("LibManager.ERROR_INVALIDACTION",j,"%s",160));
        LibAction* act = lib->addLibAction();
        act->parent = lib;
        act->id = in->read2();
        act->name = in->readStr1();
        act->description = in->readStr1();
        act->listText = in->readStr1();
        act->hintText = in->readStr1();
        int tags = in->read();
        act->hidden = mask(tags,128);
        act->advanced = mask(tags,64);
        act->registeredOnly = mask(tags,32);
        act->question = mask(tags,16);
        act->canApplyTo = mask(tags,8);
        act->allowRelative = mask(tags,4);
        act->execType = (ExecutionKind) (tags & 3);
        act->execInfo = in->readStr();
        tags = in->read();
        act->actionKind = (ActionKind) (tags >> 4);
        act->interfaceKind = (InterfaceKind) (tags & 15);
        for (int k = 0; k < act->libArguments.size(); k++)
        {
            LibArgument* arg = new LibArgument();
            arg->caption = in->readStr1();
            arg->kind = (ArgumentKind) in->read();
            arg->defaultVal = in->readStr1();
            arg->menu = in->readStr1();
            act->libArguments.push_back(arg);
        }

        if (act->actionKind == ACT_CODE && act->execType == EXEC_CODE
                && act->interfaceKind == INTERFACE_CODE) codeAction = act;
    }
    //TODO: Fix me
    BufferedImage icons = ImageIO.read(in->getInputStream());
    int i = 0;
    int cc = icons.getWidth() / 24;
    for (LibAction* a : lib->libActions)
    {
        if (a->actionKind < 8)
        {
            a->actImage = icons.getSubimage(24 * (i % cc),24 * (i / cc),24,24);
            i++;
        }
    }
    return lib;
}

LibAction* LibManager::makeCodeAction()
{
    LibAction* act = new LibAction();
    act->name = "Code";
    act->description = "Execute a piece of code";
    act->listText = "Execute a piece of code";
    act->hintText = "Execute code:##@0";
    act->canApplyTo = true;
    act->execType = EXEC_CODE;
    act->actionKind = ACT_CODE;
    act->interfaceKind = INTERFACE_CODE;

    LibArgument* arg = new LibArgument();
    arg->kind = ARG_STRING;
    act->libArguments.push_back(arg);

    return act;
}

}
