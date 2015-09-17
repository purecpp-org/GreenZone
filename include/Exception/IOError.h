/*
 * IOError.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include "Exception.h"

namespace RedZone
{
	class IOError : public RedZone::Exception
	{
	public:
		inline IOError(std::string const & message);
		inline virtual ~IOError();
	};

} /* namespace RedZone */

#include <Exception/IOError.cpp>