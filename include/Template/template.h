/*
 * Template.h
 *
 *  Created on: 21 ���� 2014 �.
 *      Author: jc
 */
#pragma once

#include <memory>
#include <string>
#include <vector>

namespace RedZone
{

	class Context;
	class Reader;
	class Root;
	class Writer;

	class Template
	{
	public:
		inline virtual ~Template();

		inline void renderToStream(Writer * stream, Context * context) const;
		inline std::string render(Context * context) const;

	protected:
		inline Template();
		inline void loadFromStream(Reader * stream);

	protected:
		std::shared_ptr< Root const > m_root;
	};

} /* namespace RedZone */

#include <Template/template.cpp>
