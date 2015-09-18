/*
 * Variable.h
 *
 *  Created on: 2014
 *      Author: jc
 */
#pragma once

#include <Node/Node.hpp>

namespace RedZone
{
	class Fragment;

	class Variable : public Node
	{
	public:
		virtual void render(Writer * stream, Context * context) const
		{
			ExpressionParser parser(context);
			json11::Json result = parser.parse(m_expression);
			switch (result.type())
			{
			case json11::Json::NUL:
				stream->write("null");
				break;
			case json11::Json::NUMBER:
				stream->write(dbl2str(result.number_value()));
				break;
			case json11::Json::STRING:
				stream->write(result.string_value());
				break;
			case json11::Json::BOOL:
				stream->write(result.bool_value() ? "true" : "false");
				break;
			case json11::Json::ARRAY:
			case json11::Json::OBJECT:
				stream->write(result.dump());
				break;
			}
		}


		virtual void processFragment(Fragment const * fragment)
		{
			m_expression = fragment->clean();
		}

		virtual std::string name() const
		{
			return "Variable";
		}

		virtual ~Variable()
		{}

	protected:
		std::string m_expression;
	};

} /* namespace RedZone */

