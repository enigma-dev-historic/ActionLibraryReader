/**
* @file  gmstreamdecoder.h
* @brief Header implementing a wrapper class for Game Maker formatted stream decoding.
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

#ifndef GMSTREAMDECODER_H
#define GMSTREAMDECODER_H

#include <iostream>
#include <fstream>
using namespace std;

namespace LGL {

class GmStreamDecoder
{
public:
    GmStreamDecoder(string& filename, ios_base::openmode mode = ios_base::in);
    bool is_open();
    void close();
    void skip(unsigned length);
    int32_t read();
    char* read(unsigned length);
    int32_t read2();
    int32_t read3();
    int32_t read4();
    bool readBool();
    string readStr();
    string readStr1();
private:
    ifstream file;
};

}

#endif // GMSTREAMDECODER_H
