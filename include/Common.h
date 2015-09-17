/*
 * Common.h
 *
 *      Author: jc
 */

#pragma once

#include <string>

namespace RedZone
{
	// Taken from here http://stackoverflow.com/a/15167203/2080453
	inline std::string dbl2str(double d);

	inline std::string replaceString(std::string subject, const std::string & search, const std::string & replace);

	inline void trimString(std::string & str);

	inline bool isReadableFile(std::string const & filePath);

	typedef std::string(*StrConcat)(std::string const &, std::string const &);
	static StrConcat strConcat = std::operator+;

} /* namespace RedZone */

#include <Common.cpp>