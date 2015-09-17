/*
 * Fragment.h
 *
 *  Created on: 2014
 *      Author: jc
 */
#pragma once

#include <string>

#include "Parser.h"

namespace RedZone {

class Fragment {
public:
	inline Fragment(std::string const & rawText);

	inline std::string cleanFragment() const;

	inline ElementType type() const;

	inline std::string raw() const;
	inline std::string clean() const;

	inline virtual ~Fragment();

protected:
    std::string m_rawText;
    std::string m_cleanText;
};

} /* namespace RedZone */

#include <Parser/Fragment.cpp>