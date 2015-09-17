/*
 * TemplateSyntaxError.cpp
 *
 *  Created on: 2014
 *      Author: jc
 */


namespace RedZone
{

	TemplateSyntaxError::TemplateSyntaxError(std::string const & wrongSyntax)
		: Exception("'" + wrongSyntax + "' seems like invalid syntax.")
	{

	}

	TemplateSyntaxError::~TemplateSyntaxError()
	{
	}

} /* namespace RedZone */
