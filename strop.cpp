/*
    engmod
    Calculation of engine modes distribution field.

    File: strop.cpp

    Copyright (C) 2012 Artem Petrov <pa2311@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <string>
#include <vector>
#include <sstream>

using std::string;
using std::vector;
using std::istringstream;
using std::ostringstream;
using std::ptrdiff_t;

void splitString(const string &fullstr,
                 vector<string> &elements,
                 const string &delimiter) {

    string::size_type lastpos =
        fullstr.find_first_not_of(delimiter, 0);
    string::size_type pos     =
        fullstr.find_first_of(delimiter, lastpos);

    while ( (string::npos != pos) || (string::npos != lastpos) ) {

        elements.push_back(fullstr.substr(lastpos, pos-lastpos));

        lastpos = fullstr.find_first_not_of(delimiter, pos);
        pos = fullstr.find_first_of(delimiter, lastpos);
    }
}

string intToString(ptrdiff_t num) {

    ostringstream stm;
    stm << num;

    return stm.str();
}

double stringToDouble(const string &str) {

    istringstream stm;
    double val = 0;

    stm.str(str);
    stm >> val;

    return val;
}
