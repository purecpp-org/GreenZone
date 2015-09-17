/*
 * ElseNode.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include <Node/Node.hpp>
#include <Context/Context.hpp>
#include <Parser/Fragment.hpp>

namespace RedZone
{
	class Writer;

	class ElseNode : public Node
	{
	public:
		virtual void render(Writer * stream, Context * context) const
		{
		}

		virtual std::string name() const { return "Else"; }

		virtual ~ElseNode(){}
	};

} /* namespace RedZone */

