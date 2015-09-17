/*
 * ElseNode.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include "Node.h"

namespace RedZone {

class Writer;

class ElseNode: public Node
{
public:
    inline ElseNode();

	inline virtual void render(Writer * stream, Context * context) const;

	inline virtual std::string name() const;

	inline virtual ~ElseNode();
};

} /* namespace RedZone */

#include <Node/ElseNode.cpp>