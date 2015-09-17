/*
 * IfNode.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include <Context/json11.hpp>

#include "Node.h"

namespace RedZone
{

	class Writer;

	class IfNode : public Node
	{
	public:
		inline IfNode();

		inline virtual void render(Writer * stream, Context * context) const;

		inline virtual void processFragment(Fragment const * fragment);
		inline virtual void exitScope(std::string const & endTag);

		inline virtual std::string name() const;

		inline virtual ~IfNode();

	protected:
		std::string m_expression;
		std::vector< std::shared_ptr< Node > > m_ifNodes;
		std::vector< std::shared_ptr< Node > > m_elseNodes;
	};

} /* namespace RedZone */

#include <Node/IfNode.cpp>