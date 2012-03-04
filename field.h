/*
  engmod
  Calculation of engine modes distribution field.

  File: field.h

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

#ifndef FIELD_H
#define	FIELD_H

#include <string>
#include <vector>

struct axis_t {

    double minval;
    double maxval;
    double step;
};

class Field {

public:

    Field(std::string);
    ~Field();

    bool readData();
    void createMatrix();
    bool saveMatrix() const;

private:

    std::string datafilename;
    axis_t ax;
    axis_t ay;
    std::vector<double> vx;
    std::vector<double> vy;
    std::vector< std::vector<double> > matrix;

    void setAxis(axis_t &, const std::vector<double> &);
};

#endif	/* FIELD_H */
