/*  HeaderExploder.cc

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

#include "HeaderExploder.h"

#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>

using std::string;

const string separator = 
"//-------------------------------------------------------------";

HeaderExploder::HeaderExploder( const string & infile,
                                const string & outfile )
        : m_header( infile.c_str() ),
          m_source( outfile.c_str() )
{
    // TODO: Error checking
}

HeaderExploder::~HeaderExploder()
{
    m_header.close();
    m_source.close();
}

void HeaderExploder::explode()
{
    string line;
    std::stack<string> class_names;
    int in_class = 0;

    getline( m_header, line );
    while ( m_header )
    {
        if ( line[0] == '#' )
        {
            // Don't process preprocessor directives
            getline( m_header, line );
            continue;
        }

        if ( ! in_class && line.find( "/*" ) != string::npos )
        {
            do
            {
                m_source << line << "\n";
                getline( m_header, line );
            }
            while ( m_header && line.find( "*/" ) == string::npos );
            m_source << line << "\n\n";

            continue;
        }

        if ( line.find( "//" ) != string::npos )
        {
            getline( m_header, line );
            continue;
        }

        if ( line.find( "class" ) != string::npos )
        {
            std::cerr << "Found class " << line << '\n';
            ++in_class;
            string name = getClassName( line );
            class_names.push( name );
            m_source << "#include \"" << name << ".h\"\n\n";
        }

        if ( line.find( "};" ) != string::npos && in_class > 0 )
        {
            std::cerr << "Left class\n";
            --in_class;
            class_names.pop();
        }

        if ( line.find( '(' ) != string::npos && in_class > 0 )
        {
            m_source << separator << "\n";
            string fLine = line;
            bool foundComment = false;
            getline( m_header, line );
            if ( line.find( "//" ) != string::npos )
            {
                foundComment = true;
                m_source << "/*\n";
            }

            while ( m_header && line.find( "//" ) != string::npos )
            {
                while ( line.size() > 1 &&
                        ( isspace( line[0] ) || line[0] == '/' ) )
                {
                    line = line.substr( 1 );
                }
                m_source << " * " << line << "\n";
                getline( m_header, line );
            }
            if ( foundComment )
            {
                m_source << " */\n";
            }
            m_source << getFunctionPrototype( class_names.top(), fLine )
                 << "\n{\n}\n\n";
            if ( ! foundComment )
            {
                continue;
            }
        }
        getline( m_header, line );
    }
}

string HeaderExploder::getClassName( const string & line )
{
    string my_class_name;
    string::const_iterator iter = line.begin() + line.find( "class" );

    iter += string( "class" ).size();
    while ( iter != line.end() && isspace( *iter ) )
    {
        ++iter;
    }

    while ( iter != line.end() && ! isspace( *iter ) && isalnum( *iter ) )
    {
        my_class_name.push_back( *iter );
        ++iter;
    }

    return my_class_name;
}

string HeaderExploder::getFunctionPrototype( const string & className,
                                             const string & line )
{
    std::istringstream line_stream( line ); 
    string result;

    string token;
    line_stream >> token;
    bool scopeInserted = false;
    while ( line_stream )
    {
        if ( token == "virtual" )
        {
            line_stream >> token;
            continue;
        }

        if ( ! scopeInserted && ( token.find( "(" ) != string::npos ||
             token.find( "operator" ) != string::npos ) )
        {
            result += className;
            result += "::";
            scopeInserted = true;
        }

        if ( token.find( ";" ) == token.size() - 1 )
        {
            token = token.substr( 0, token.size() - 1 );
        }
        result += token + " ";
        line_stream >> token;
    }

    return result;
}

/* vi: set shiftwidth=4 textwidth=80: */
