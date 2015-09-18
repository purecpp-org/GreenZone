/*
 * TextNode.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include <Node/Node.hpp>
#include <IO/Writer.hpp>
#include <Parser/Fragment.hpp>

namespace GreenZone
{
	class Writer;

	class TextNode : public Node
	{
	public:
		TextNode() : Node(){}

		virtual void render(Writer * stream, Context * context) const
		{
			(void)context;
			stream->write(m_text);
		}

		virtual void processFragment(Fragment const * fragment)
		{
			m_text = fragment->raw();
		}

		virtual std::string name() const{ return "Text"; }

		virtual ~TextNode(){}

	protected:
		std::string m_text;
	};

} /* namespace RedZone */

