/*
 * TextNode.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include "Node.h"

namespace RedZone {

class Writer;

class TextNode: public Node {
public:
	inline TextNode();

	inline virtual void render(Writer * stream, Context * context) const;
	inline virtual void processFragment(Fragment const * fragment);

	inline virtual std::string name() const;

	inline virtual ~TextNode();

protected:
    std::string m_text;
};

} /* namespace RedZone */

#include <Node/TextNode.cpp>