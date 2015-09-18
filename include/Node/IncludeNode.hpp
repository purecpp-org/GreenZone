/*
 * IncludeNode.h
 *
 *      Author: jc
 */

#pragma once

#include <Common.hpp>
#include <Exception.hpp>
#include <IO/FileReader.hpp>
#include <Parser/ExpressionParser.hpp>
#include <Parser/Fragment.hpp>
#include <Parser/Parser.hpp>
#include <Node/Root.hpp>
#include <Node/IncludeNode.hpp>
#include <Node/Node.hpp>


#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>
#include <regex>

namespace GreenZone
{
	class Root;

	class IncludeNode : public Node
	{
	public:
		IncludeNode() : Node(false){}

		virtual void render(Writer * stream, Context * context) const
		{
			ExpressionParser exprParser(context);
			json11::Json paths = exprParser.parse(m_includeExpr);
			std::vector< std::string > const & allParserPaths = Parser::paths();
			std::string const wrongArgumentError =
				"Include expression \"" + m_includeExpr + "\" must be single string or array of strings.";
			auto rootCreator = [&](std::string path) -> std::shared_ptr< Root >
			{
				auto found = std::find_if(allParserPaths.begin(), allParserPaths.end(),
					std::bind(&isReadableFile, std::bind(
					std::function< std::string(std::string const &, std::string const &) >(strConcat), std::placeholders::_1, path)));
				if (found == allParserPaths.end())
				{
					throw Exception("Include failed. Cannot open template file " + path);
				}
				path = *found + path;
				FileReader reader(path);  // FIXME: get rid of specific Reader creating
				static Parser parser;
				return std::shared_ptr< Root >(parser.loadFromStream(&reader));
			};
			std::vector< std::shared_ptr< Root > > roots;
			if (paths.is_string())
			{
				roots.push_back(rootCreator(paths.string_value()));
			}
			else if (paths.is_array())
			{
				json11::Json::array const & allPaths = paths.array_items();
				if (std::any_of(allPaths.begin(), allPaths.end(),
					std::bind(std::equal_to< bool >(), std::bind(&json11::Json::is_string, std::placeholders::_1), false)))
				{
					throw Exception(wrongArgumentError); // Some elements in array do not have string type
				}
				std::transform(allPaths.begin(), allPaths.end(), std::back_inserter(roots),
					std::bind(rootCreator, std::bind(&json11::Json::string_value, std::placeholders::_1)));
			}
			else
			{
				throw Exception(wrongArgumentError);
			}
			std::for_each(roots.begin(), roots.end(), std::bind(&Root::render, std::placeholders::_1, stream, context));
		}

		virtual void processFragment(Fragment const * fragment)
		{
			static std::regex splitter(R"(^include\s+(.+))");
			std::smatch match;
			std::string cleaned = fragment->clean();
			if (!std::regex_match(cleaned, match, splitter))
			{
				throw TemplateSyntaxError(fragment->clean());
			}
			m_includeExpr = match[1];
		}


		virtual std::string name() const{ return "Include"; }

		virtual ~IncludeNode(){}

	protected:
		std::string m_includeExpr;
	};

} /* namespace RedZone */

