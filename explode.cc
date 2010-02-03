/*  explode.cc

    Copyright (c) 2010 Patrick MacArthur

    This file is part of HeadExploder

    HeadExploder is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    HeadExploder is distributed in the hope that it will be
    useful, but WITHOUT ANY WARRANTY; without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HeadExploder.  If not, see <http://www.gnu.org/licenses/>.
 */

/* vi: set shiftwidth=4 textwidth=80: */

#include "HeaderExploder.h"

#include <cstdlib>
#include <iostream>
using std::cout;
using std::cerr;

/*
 * HeadExploder takes a C++ header file and converts it into a
 * series of C++ method stubs.  Currently it is very naive and does not
 * support template classes or any kind of advanced syntax.  It will be
 * added to as necessary in order for me to have to do far less typing
 * for CS assignments.
 */
int main( int argc, char *argv[] )
{
    if ( argc != 3 )
    {
        cerr << "Usage: " << argv[0] << " <header-file> <output-file>\n";
        exit( EXIT_FAILURE );
    }

    HeaderExploder exploder( argv[1], argv[2] );
    exploder.explode();

    return EXIT_SUCCESS;
}
