/*
 * Context.h
 *
 *  Created on: 21 ���� 2014 �.
 *      Author: jc
 */
#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>


#include "json11.hpp"

namespace RedZone
{
	class Context
	{
	public:
		typedef std::function< json11::Json(json11::Json const &, json11::Json const &) > BinaryOperator;
		typedef std::vector< std::tuple< std::string, int, BinaryOperator > > BinaryOperators;

		typedef std::function< json11::Json(std::vector< json11::Json > const &) > Function;
		typedef std::map< std::string, Function > Functions;

		inline Context(std::string const & json);

		inline Context(json11::Json const & json);

		inline json11::Json json() const;
		inline void setJson(json11::Json const & json);

		inline json11::Json resolve(std::string const & name) const;

		inline BinaryOperators const & binaryOperators() const;
		inline Functions const & functions() const;

		inline virtual ~Context();

	protected:
		inline Context();

	protected:
		json11::Json m_json;
		BinaryOperators m_binaryOperations;
		Functions m_functions;
	};

} /* namespace RedZone */

#include <Context/Context.cpp>