/*
 * StringWriter.h
 *
 *      Author: jc
 */

#pragma once

#include <string>

#include "Writer.h"

namespace RedZone
{

	class StringWriter : public Writer
	{
	public:
		inline StringWriter(std::string & string);

		inline virtual void write(std::string const & data);
		inline virtual void flush();

		inline virtual ~StringWriter();

	protected:
		std::string & m_string;
	};

} /* namespace RedZone */

#include <IO/StringWriter.cpp>
