/*
 * BlockNode.h
 *
 *      Author: jc
 */

#pragma once

#include "Node.h"

namespace RedZone {

class BlockNode : public Node {
public:
	inline BlockNode();

	inline virtual void render(Writer * stream, Context * context) const;
	inline  virtual void processFragment(Fragment const * fragment);
	inline virtual void exitScope(std::string const & endTag);

	inline virtual std::string name() const;
	inline  std::string blockName() const;

	inline  virtual ~BlockNode();

protected:
   std::string m_blockName;
};

} /* namespace RedZone */

#include <Node/BlockNode.cpp>