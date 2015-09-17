/*
 * TemplateContextError.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include "Exception.h"

namespace RedZone
{

	class TemplateContextError : public Exception
	{
	public:
		inline TemplateContextError(std::string const & contextVar);
		inline virtual ~TemplateContextError();
	};

} /* namespace RedZone */

#include <Exception/templatecontexterror.cpp>