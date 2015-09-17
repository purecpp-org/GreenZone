/*
 * Node.h
 *
 *  Created on: 2014
 *      Author: jc
 */
#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

#include <Context/json11.hpp>

namespace RedZone
{

	class Context;
	class Fragment;
	class Writer;

	class Node
	{
	public:
		inline virtual void render(Writer * stream, Context * context) const;

		inline void renderChildren(Writer * stream, Context * context,
			std::vector< std::shared_ptr< Node > > children = {}) const;

		inline virtual void processFragment(Fragment const * fragment);
		inline void addChild(Node * child);

		inline bool createsScope() const;

		inline virtual void enterScope();
		inline virtual void exitScope(std::string const & endTag);

		inline virtual std::string name() const;

		inline std::vector< std::shared_ptr< Node > > const & children();

		template< class T >
		std::vector< std::shared_ptr< T > > childrenByName(std::string const & name)
		{
			std::vector< std::shared_ptr< Node > > nodes;
			std::copy_if(m_children.begin(), m_children.end(), std::back_inserter(nodes),
				std::bind(std::equal_to< std::string >(), std::bind(&Node::name, std::placeholders::_1), name));
			std::vector< std::shared_ptr< T > > result;
			typedef std::shared_ptr< T >(*DynamicPointerCast)(std::shared_ptr< Node > const &);
			DynamicPointerCast caster = std::dynamic_pointer_cast<T>;
			std::transform(nodes.begin(), nodes.end(), std::back_inserter(result), caster);
			return result;
		}

		inline virtual ~Node();

	protected:
		inline Node(bool createsScope = false);
		inline virtual json11::Json resolveInContext(std::string const & name, Context const * context) const;

	protected:
		std::vector< std::shared_ptr< Node > > m_children;
		bool m_createsScope;
	};

} /* namespace RedZone */

#include <Node/Node.cpp>