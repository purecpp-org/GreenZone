/*
 * ExtendsNode.h
 *
 *      Author: jc
 */

#pragma once

#include "Node.h"

namespace RedZone {

class Root;

class ExtendsNode : public Node {
public:
	inline ExtendsNode();

	inline virtual void render(Writer * stream, Context * context) const;
	inline virtual void processFragment(Fragment const * fragment);
	inline virtual void exitScope(std::string const & endTag);

	inline virtual std::string name() const;

	inline virtual ~ExtendsNode();

protected:
   std::string m_path;
   std::vector< std::shared_ptr< Node > > m_nodesToRender;
   std::shared_ptr< Root > m_parentRoot;
};

} /* namespace RedZone */

#include <Node/ExtendsNode.cpp>