/**
* @file  gmstreamdecoder.cpp
* @brief Source implementing a wrapper class for Game Maker formatted stream decoding.
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

#include "gmstreamdecoder.h"

namespace ALR {

GmStreamDecoder::GmStreamDecoder(const char* filename, const char* mode)
{
    file = fopen(filename, mode);
}

bool GmStreamDecoder::is_open() {
    return file != nullptr;
}

void GmStreamDecoder::close() {
    fclose(file);
}

void GmStreamDecoder::skip(unsigned length) {
    fseek(file, length, SEEK_CUR);
}

int32_t GmStreamDecoder::read() {
    int32_t res;
    fread(&res, 1, 1, file);
    return res;
}

char* GmStreamDecoder::read(unsigned length) {
    char* res;
    fread(&res, length, 1, file);
    return res;
}

char* GmStreamDecoder::readToEnd() {
    unsigned size, pos;
    pos = ftell(file);
    fseek (file, 0, SEEK_END);   // non-portable
    size = ftell(file);
    fseek (file, pos, SEEK_SET);   // non-portable
    char* res;
    fread(&res, 1, size-pos, file);
    return res;
}

int32_t GmStreamDecoder::read2()
{
    int32_t res;
    fread(&res, 2, 1, file);
    return res;
}

int32_t GmStreamDecoder::read3()
{
    int32_t res;
    fread(&res, 3, 1, file);
    return res;
}

int32_t GmStreamDecoder::read4()
{
    int32_t res;
    fread(&res, 4, 1, file);
    return res;
}

bool GmStreamDecoder::readBool()
{
    int val = read4();
    if (val != 0 && val != 1)
    {
        //String error = Messages.format("GmStreamDecoder.INVALID_BOOLEAN",val,getPosString()); //$NON-NLS-1$
        //throw new IOException(error);
    }
    return val == 0 ? false : true;
}

string GmStreamDecoder::readStr() {
    string res;
    fread(&res, read4(), 1, file);
    return res;
}

string GmStreamDecoder::readStr1() {
    string res;
    fread(&res, read(), 1, file);
    return res;
}

}
