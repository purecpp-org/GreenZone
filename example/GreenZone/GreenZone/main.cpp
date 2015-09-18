/*
 * main.cpp
 *
 *  Created on: 2014.
 *      Author: jc
 */

#include <Context/Context.hpp>
#include <Template/FileTemplate.hpp>

#include <fstream>
#include <iostream>
#include <string>


int main( int argc, char ** argv )
{
    RedZone::FileTemplate tpl( "test.tpl" );

    std::ifstream jsonIn( "test.json" );
    if( !jsonIn.good() ) {
       return 1;
    }

    std::string err;

	json11::Json json(json11::Json::parse(
       std::string(
          std::istreambuf_iterator< char >( jsonIn ),
          std::istreambuf_iterator< char >() ),
          err ) );

    if( err.length() ) {
       std::cerr << err << std::endl;
       return 1;
    }

    RedZone::Context * cont( new RedZone::Context( json ) );

    std::cout << tpl.render( cont ) << std::endl;

    return 0;
}
