#ifndef HEADEREXPLODER_H
#define HEADEREXPLODER_H
/*  HeaderExploder.h

    Copyright (c) 2010 Patrick MacArthur

    This file is part of HeadExploder

    HeadExploder is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HeadExploder is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HeadExploder.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <istream>
#include <ostream>
#include <fstream>
#include <string>

/*
 * The HeaderExploder class takes a C++ header file and creates a C++
 * source file with the header comment, method comments, and method
 * stubs duplicated.
 */

class HeaderExploder
{
    public:
        // Constructs a header exploder with the given input and output
        // files.
        HeaderExploder(const std::string & infile, const std::string & outfile);

        // Destroys the header exploder and closes associated files
        ~HeaderExploder();

        // Explodes the header into the specified source file.
        void explode();

    private:
        // Gets the class name from a given line of code.
        std::string getClassName( const std::string & line );

        // Returns a string containing the function prototype
        // (including scope and return value) in the current line.
        std::string getFunctionPrototype( const std::string & className,
                                          const std::string & line );

        std::ifstream m_header;
        std::ofstream m_source;
};

/* vi: set shiftwidth=4 textwidth=80: */
#endif
