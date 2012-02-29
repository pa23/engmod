/*
    engmod
    Calculation of engine modes distribution field.

    File: main.cpp

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

#include <iostream>
#include <memory>

#include "const.h"
#include "field.h"

using std::cout;
using std::string;
using std::unique_ptr;

void about() {

    cout << "\n" << "engmod " << VERSION;

    cout << "\n\nCopyright (C) 2012 Artem Petrov <pa2311@gmail.com>"
        "\n\nAuthor's blog (RU): http://pa2311.blogspot.com\n\n"
        "This program is free software: you can redistribute it and/or modify\n"
        "it under the terms of the GNU General Public License as published by\n"
        "the Free Software Foundation, either version 3 of the License, or\n"
        "(at your option) any later version.\n"
        "This program is distributed in the hope that it will be useful,\n"
        "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\n"
        "GNU General Public License for more details.\n"
        "You should have received a copy of the GNU General Public License\n"
        "along with this program. If not, see <http://www.gnu.org/licenses/>.\n\n"
        "Usage:\n    engmod <data-file>\n"
        "Notes:\n    Data file must containt 3 columns.\n"
        "    Columns 2 and 3 will be used in calculation.\n"
        "    TAB is values separator (ascii format by ETAS MDA).\n\n";
}

int main(int argc, char** argv) {

    if ( argc != 2 ) {

        about();
        return 0;
    }

    //

    unique_ptr<Field> field(new Field(argv[1]));

    if ( !field->readData() ) {

        cout << "\nErrors during reading data file.\n\n";
        return 1;
    }

    field->createMatrix();

    if ( !field->saveMatrix() ) {

        cout << "\nErrors during writing data file.\n\n";
        return 1;
    }

    //

    return 0;
}
