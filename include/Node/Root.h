/*
 * Root.h
 *
 *  Created on: 2014
 *      Author: jc
 */

#pragma once

#include <string>

#include "Node.h"

namespace RedZone
{

	class Writer;

	class Root : public Node
	{
	public:
		inline Root(std::string id);

		inline virtual void render(Writer * stream, Context * context) const;

		inline virtual std::string name() const;

		inline std::string id() const { return m_id; }

		inline virtual ~Root();

	protected:
		std::string m_id;
	};

} /* namespace RedZone */

#include <Node/Root.cpp>