/*
 * IncludeNode.h
 *
 *      Author: jc
 */

#pragma once

#include <string>
#include <vector>

#include "Node.h"

namespace RedZone {

class Root;

class IncludeNode : public Node {
public:
	inline IncludeNode();

	inline virtual void render(Writer * stream, Context * context) const;

	inline virtual void processFragment(Fragment const * fragment);

	inline virtual std::string name() const;

	inline virtual ~IncludeNode();

protected:
   std::string m_includeExpr;
};

} /* namespace RedZone */

#include <Node/IncludeNode.cpp>