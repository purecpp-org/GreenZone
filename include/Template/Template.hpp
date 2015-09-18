/*
 * Template.h
 *
 *  Created on: 21 ���� 2014 �.
 *      Author: jc
 */
#pragma once

#include <Node/Root.hpp>
#include <IO/stringwriter.hpp>
#include <Parser/Parser.hpp>

#include <memory>
#include <string>
#include <vector>


namespace GreenZone
{

	class Context;
	class Reader;
	class Root;
	class Writer;

	class Template
	{
	public:
		virtual ~Template()
		{}

		void renderToStream(Writer * stream, Context * context) const
		{
			m_root->render(stream, context);
		}
		std::string render(Context * context) const
		{
			std::string result;
			StringWriter stringWriter(result);
			renderToStream(&stringWriter, context);
			return result;
		}

	protected:
		Template()
		{}
		void loadFromStream(Reader * stream)
		{
			Parser parser;
			m_root.reset(parser.loadFromStream(stream));
		}

	protected:
		std::shared_ptr< Root const > m_root;
	};

} /* namespace RedZone */

