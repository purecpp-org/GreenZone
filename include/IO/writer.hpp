/*
 * Writer.h
 *
 *      Author: jc
 */

#pragma once

#include <string>

namespace GreenZone
{

	class Writer
	{
	public:
		virtual void write(std::string const & data) = 0;
		virtual void flush() = 0;

		virtual ~Writer(){}

	protected:
		Writer(){}
	};

} /* namespace RedZone */

