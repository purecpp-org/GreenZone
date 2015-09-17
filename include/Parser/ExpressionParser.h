/*
 * ExpressionParser.h
 *
 *      Author: jc
 */

#pragma once

#include <functional>
#include <set>
#include <string>

#include <Context/json11.hpp>

namespace RedZone
{

class Context;

class ExpressionParser
{
public:
   typedef std::set< char > charset;

   inline ExpressionParser(Context const * context);

   inline json11::Json parse(std::string expression) const;

   inline virtual ~ExpressionParser();

protected:
	inline json11::Json parseRecursive(std::string expression) const;

protected:
   Context const * m_context;
   charset m_binaryOperatorChars;
};

} /* namespace RedZone */

#include <Parser/ExpressionParser.cpp>