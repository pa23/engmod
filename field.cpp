/*
  engmod
  Calculation of engine modes distribution field.

  File: field.cpp

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

#include "field.h"
#include "const.h"
#include "strop.h"

#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::setfill;
using std::setw;
using std::right;
using std::setprecision;
using std::fixed;

Field::Field(string str) {

    datafilename = str;

    vector<double> tmp(DIMENSION, 0);
    for ( size_t i=0; i<DIMENSION; i++ ) matrix.push_back(tmp);
}

Field::~Field() {
}

bool Field::readData() {

    ifstream fin(datafilename.c_str());
    if ( !fin ) return false;

    string s;
    vector<string> selements;

    while ( !fin.eof() ) {

        getline(fin, s);
        
        if ( !s.empty() ) {

            splitString(s, selements, CSVDELIM);

            vx.push_back(stringToDouble(selements[1]));
            vy.push_back(stringToDouble(selements[2]));
            
            selements.clear();
        }
    }

    fin.close();

    if ( vx.size() != vy.size() ) return false;

    return true;
}

void Field::createMatrix() {

    setAxis(ax, vx);
    setAxis(ay, vy);

    double tmpmin_x = ax.minval;
    double tmpmax_x = tmpmin_x + ax.step;
    double tmpmin_y = ay.minval;
    double tmpmax_y = tmpmin_y + ay.step;

    size_t num = vx.size();
    bool brk = false;

    for ( size_t n=0; n<num; n++ ) {

        for ( size_t i=0; i<DIMENSION; i++ ) {

            for ( size_t j=0; j<DIMENSION; j++ ) {

                if ( (vx[n]>tmpmin_x && vx[n]<=tmpmax_x) &&
                     (vy[n]>tmpmin_y && vy[n]<=tmpmax_y) ) {

                    matrix[i][j]++;
                    brk = true;
                    break;
                }

                tmpmin_x += ax.step;
                tmpmax_x += ax.step;
            }

            if ( brk ) {

                brk = false;
                break;
            }

            tmpmin_x = ax.minval;
            tmpmax_x = tmpmin_x + ax.step;

            tmpmin_y += ay.step;
            tmpmax_y += ay.step;
        }

        tmpmin_x = ax.minval;
        tmpmax_x = tmpmin_x + ax.step;

        tmpmin_y = ay.minval;
        tmpmax_y = tmpmin_y + ay.step;
    }

    for ( size_t i=0; i<DIMENSION; i++ ) {
    
        for ( size_t j=0; j<DIMENSION; j++ ) {

            matrix[i][j] = matrix[i][j] / num * 100.0;
        }
    }
}

bool Field::saveMatrix() const {

    time_t t = time(0);

    string filename = intToString(t) + ".txt";

    ofstream fout(filename.c_str());
    if ( !fout ) return false;

    fout << "\nengmod " << VERSION << "\n";

    fout << "\n"
         << "x_min = "
         << ax.minval
         << "\n"
         << "x_max = "
         << ax.maxval
         << "\n"
         << "x_step = "
         << ax.step
         << "\n\n"
         << "y_min = "
         << ay.minval
         << "\n"
         << "y_max = "
         << ay.maxval
         << "\n"
         << "y_step = "
         << ay.step
         << "\n";

    double curr_x = ax.minval + ax.step;
    double curr_y = ay.maxval;

    for ( size_t i=DIMENSION; i>0; i-- ) {

        fout << "\n"
             << fixed
             << right
             << setw(5)
             << setfill(' ')
             << setprecision(0)
             << curr_y
             << "|"
             << setw(81)
             << setfill('-')
             << "|\n"
             << setw(6)
             << setfill(' ')
             << "|";

        for ( size_t j=0; j<DIMENSION; j++ ) {

            fout << fixed
                 << right
                 << setw(6)
                 << setfill(' ')
                 << setprecision(1)
                 << matrix[i-1][j]
                 << " |";
        }

        curr_y -= ay.step;
    }

    fout << "\n"
         << fixed
         << right
         << setw(5)
         << setfill(' ')
         << setprecision(0)
         << curr_y
         << "|";

    for ( size_t j=0; j<DIMENSION; j++ ) {

        fout << setw(8)
             << setfill('-')
             << "|";
    }

    fout << "\n"
         << setw(6)
         << setfill(' ')
         << " ";

    for ( size_t j=1; j<=DIMENSION; j++ ) {

        fout << fixed
             << right
             << setw(8)
             << setfill(' ')
             << setprecision(0)
             << curr_x;

        curr_x += ax.step;
    }

    fout << "\n\n";

    fout.close();

    //

    return true;
}

void Field::setAxis(axis_t &a, const vector<double> &v) {

    a.minval = v[0];
    a.maxval = v[0];

    for ( size_t i=1; i<v.size(); i++ ) {

        if ( v[i]<a.minval ) a.minval = v[i];
        if ( v[i]>a.maxval ) a.maxval = v[i];
    }

    a.step = (a.maxval-a.minval) / DIMENSION;
}
