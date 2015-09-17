/*
 * ExpressionException.h
 *
 *      Author: jc
 */

#pragma once

#include "Exception.h"

namespace RedZone
{

class ExpressionException : public Exception
{
public:
   using Exception::Exception;

   inline ExpressionException(std::string const & expr, std::string const & err);

   inline virtual ~ExpressionException();
};

} /* namespace RedZone */

#include <Exception/ExpressionException.cpp>