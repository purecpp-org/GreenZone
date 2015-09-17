/*
 * Exception.h
 *
 *  Created on: 2014
 *      Author: jc
 */
#pragma once

#include <stdexcept>
#include <string>

namespace RedZone
{
	class Exception : public std::exception
	{
	public:
		inline Exception(std::string const & message);
		inline virtual ~Exception();

		inline virtual const char * what() const throw();

	protected:
		std::string m_message;
	};

} /* namespace RedZone */

#include <Exception/Exception.cpp>