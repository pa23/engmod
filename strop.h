/*
  engmod
  Calculation of engine modes distribution field.

  File: strop.h

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

#ifndef STROP_H
#define	STROP_H

#include <string>
#include <vector>

void splitString(const std::string &,
                 std::vector<std::string> &,
                 const std::string &);
std::string intToString(std::ptrdiff_t);
double stringToDouble(const std::string &);

#endif	/* STROP_H */
