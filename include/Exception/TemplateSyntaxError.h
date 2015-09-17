/*
 * TemplateSyntaxError.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include "Exception.h"

namespace RedZone
{

	class TemplateSyntaxError : public Exception
	{
	public:
		inline TemplateSyntaxError(std::string const & wrongSyntax);
		inline virtual ~TemplateSyntaxError();
	};

} /* namespace RedZone */

#include <Exception/TemplateSyntaxError.cpp>