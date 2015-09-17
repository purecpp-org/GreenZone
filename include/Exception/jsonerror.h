/*
 * JsonError.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include "Exception.h"

#include <Common.h>

namespace RedZone
{

class JsonError: public Exception
{
public:
	inline JsonError( std::string const & message ) : Exception( message ) 
	{
	}
    inline virtual ~JsonError();
};

} /* namespace RedZone */

#include <Exception/jsonerror.cpp>