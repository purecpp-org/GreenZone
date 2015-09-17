/*
 * EachNode.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include "Node.h"

namespace RedZone {

class Writer;

class EachNode: public Node {
public:
	inline EachNode();

	inline virtual void render(Writer * stream, Context * context) const;
	inline virtual void processFragment(Fragment const * fragment);
	inline virtual void exitScope(std::string const & endTag);
	inline virtual std::string name() const;

	inline virtual ~EachNode();

protected:
    std::string m_container;
    std::vector< std::string > m_vars;
};

} /* namespace RedZone */

#include <Node/EachNode.cpp>