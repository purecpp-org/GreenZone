/*
 * Context.h
 *
 *  Created on: 21 ���� 2014 �.
 *      Author: jc
 */
#pragma once

#include <Context/json11.hpp>
#include <Common.hpp>
#include <Exception.hpp>

#include <functional>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <random>
#include <regex>


#define ARGS_SIZE_CHECK(SIZE) if( args.size() != SIZE ) { \
   throw Exception( "Got " + std::to_string( args.size() ) + \
                    " arguments, expected " + std::to_string( SIZE ) ); \
										        }
namespace RedZone
{
	class Context
	{
	public:
		typedef std::function< json11::Json(json11::Json const &, json11::Json const &) > BinaryOperator;
		typedef std::vector< std::tuple< std::string, int, BinaryOperator > > BinaryOperators;

		typedef std::function< json11::Json(std::vector< json11::Json > const &) > Function;
		typedef std::map< std::string, Function > Functions;

		Context(std::string const & json)
			: Context()
		{
			std::string err;
			m_json = json11::Json::parse(json, err);
			if (err.size())
			{
				throw JsonError(err);
			}
			if (!m_json.is_object())
			{
				throw JsonError("Context data must be presented in dictionary type.");
			}
		}

		Context(json11::Json const & json)
			: Context()
		{
			m_json = json;
			if (!m_json.is_object())
			{
				throw JsonError("Context data must be presented in dictionary type.");
			}
		}

		json11::Json json() const
		{
			return m_json;
		}
		void setJson(json11::Json const & json)
		{
			if (!m_json.is_object())
			{
				throw JsonError("Context data must be presented in dictionary type.");
			}
			m_json = json;
		}

		json11::Json resolve(std::string const & name) const
		{
			json11::Json result = m_json;
			static const std::regex splitter(R"(\.)");
			std::sregex_token_iterator iter(name.begin(), name.end(), splitter, -1);
			static const std::sregex_token_iterator end;
			for (; iter != end; ++iter)
			{
				json11::Json tmp = result[*iter];
				if (tmp.is_null())
				{
					throw TemplateContextError(name);
				}
				result = tmp;
			}
			return result;
		}

		BinaryOperators const & binaryOperators() const
		{
			return m_binaryOperations;
		}
		Functions const & functions() const
		{
			return m_functions;
		}

		virtual ~Context()
		{}

	protected:
		Context()
			: m_binaryOperations(
		{
			std::make_tuple("+", 2, [](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
			{
				static std::map< std::tuple< json11::Json::Type, json11::Json::Type >,
					std::function< json11::Json(json11::Json const &, json11::Json const &) > > const possibleOperations
				{
					{
						std::make_tuple(json11::Json::NUMBER, json11::Json::NUMBER),

						[](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
						{
							// Yes-yes, I know about implicit constructors feature
							// but I'd rather to call explicit instead
							return json11::Json(lhs.number_value() + rhs.number_value());
						}
					},

					{
						std::make_tuple(json11::Json::STRING, json11::Json::STRING),
						[](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
						{
							return json11::Json(lhs.string_value() + rhs.string_value());
						}
					},
					{
						std::make_tuple(json11::Json::NUMBER, json11::Json::STRING),
						[](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
						{
							return json11::Json(dbl2str(lhs.number_value()) + rhs.string_value());
						}
					},

					{
						std::make_tuple(json11::Json::STRING, json11::Json::NUMBER),
						[](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
						{
							return json11::Json(lhs.string_value() + dbl2str(rhs.number_value()));
						}
					}
				};
				decltype(possibleOperations)::const_iterator foundOperation;
				if ((foundOperation = possibleOperations.find(
					std::make_tuple(lhs.type(), rhs.type()))) == possibleOperations.end())
				{
					throw Exception("Type mismatch: can not add " + lhs.dump() + " to " + rhs.dump());
				}
				return foundOperation->second(lhs, rhs);
			}),

				std::make_tuple("-", 2, [](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
			{
				static std::map< std::tuple< json11::Json::Type, json11::Json::Type >,
					std::function< json11::Json(json11::Json const &, json11::Json const &) > > const possibleOperations
				{
					{
						std::make_tuple(json11::Json::NUMBER, json11::Json::NUMBER),
						[](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
						{
							return json11::Json(lhs.number_value() - rhs.number_value());
						}
					}
				};
				decltype(possibleOperations)::const_iterator foundOperation;
				if ((foundOperation = possibleOperations.find(
					std::make_tuple(lhs.type(), rhs.type()))) == possibleOperations.end())
				{
					throw Exception("Type mismatch: can not subtract " + lhs.dump() + " from " + rhs.dump());
				}
				return foundOperation->second(lhs, rhs);
			}),

				std::make_tuple("*", 3, [](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
			{
				static std::map< std::tuple< json11::Json::Type, json11::Json::Type >,
					std::function< json11::Json(json11::Json const &, json11::Json const &) > > const possibleOperations
				{
					{
						std::make_tuple(json11::Json::NUMBER, json11::Json::NUMBER),
						[](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
						{
							return json11::Json(lhs.number_value() * rhs.number_value());
						}
					},

					{
						std::make_tuple(json11::Json::STRING, json11::Json::NUMBER),
						[](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
						{
							std::string repeated;
							if (rhs.number_value() < 0.f)
							{
								throw Exception("String multiplier is negative");
							}
							for (auto i = 0; i < rhs.number_value(); ++i)
							{
								repeated += lhs.string_value();
							}
							return json11::Json(repeated);
						}
					},
				};

				decltype(possibleOperations)::const_iterator foundOperation;
				if ((foundOperation = possibleOperations.find(
					std::make_tuple(lhs.type(), rhs.type()))) == possibleOperations.end())
				{
					throw Exception("Type mismatch: can not multiply " + lhs.dump() + " and " + rhs.dump());
				}
				return foundOperation->second(lhs, rhs);
			}),
				std::make_tuple("/", 3, [](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
			{
				static std::map< std::tuple< json11::Json::Type, json11::Json::Type >,
					std::function< json11::Json(json11::Json const &, json11::Json const &) > > const possibleOperations
				{
					{
						std::make_tuple(json11::Json::NUMBER, json11::Json::NUMBER),
						[](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
						{
							return json11::Json(lhs.number_value() / rhs.number_value());
						}
					}
				};
				decltype(possibleOperations)::const_iterator foundOperation;
				if ((foundOperation = possibleOperations.find(
					std::make_tuple(lhs.type(), rhs.type()))) == possibleOperations.end())
				{
					throw Exception("Type mismatch: can not divide " + lhs.dump() + " by " + rhs.dump());
				}
				return foundOperation->second(lhs, rhs);
			}),
				std::make_tuple(">", 1, [](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
			{
				return lhs > rhs;
			}),
				std::make_tuple("<", 1, [](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
			{
				return lhs < rhs;
			}),
				std::make_tuple("==", 1, [](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
			{
				return lhs == rhs;
			}),
				std::make_tuple("!=", 1, [](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
			{
				return lhs != rhs;
			}),
				std::make_tuple("<=", 1, [](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
			{
				return lhs <= rhs;
			}),
				std::make_tuple(">=", 1, [](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
			{
				return lhs >= rhs;
			}),
				std::make_tuple("&&", 0, [](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
			{
				return lhs.bool_value() && rhs.bool_value();
			}),
				std::make_tuple("||", 0, [](json11::Json const & lhs, json11::Json const & rhs) -> json11::Json
			{
				return lhs.bool_value() || rhs.bool_value();
			})
				// we need more gol... operators!
		})
		, m_functions(
			{
				{
					"sin", [](std::vector< json11::Json > const & args) -> json11::Json
					{
						ARGS_SIZE_CHECK(1);
						if (!args[0].is_number())
						{
							throw Exception("Function accepts only numeric arguments");
						}
						return json11::Json(::sin(args[0].number_value()));
					}
				},
				{
					"cos", [](std::vector< json11::Json > const & args) -> json11::Json
					{
						ARGS_SIZE_CHECK(1);
						if (!args[0].is_number()) {
							throw Exception("Function accepts only numeric arguments");
						}
						return json11::Json(::cos(args[0].number_value()));
					}
				},
				{
					"length", [](std::vector< json11::Json > const & args) -> json11::Json
					{
						ARGS_SIZE_CHECK(1);
						json11::Json arg = args[0];
						if (arg.is_array()) {
							return json11::Json(int(arg.array_items().size()));
						}
						else if (arg.is_object())
						{
							return json11::Json(int(arg.object_items().size()));
						}
						else if (arg.is_string())
						{
							return json11::Json(int(arg.string_value().size()));
						}
						else
						{
							throw Exception("Can not calculate length of non-iterable object: " + arg.dump());
						}
					}
				},

				{
					"not", [](std::vector< json11::Json > const & args) -> json11::Json
					{
						ARGS_SIZE_CHECK(1);
						return json11::Json(!args[0].bool_value());
					}
				},
				{
					"get", [](std::vector< json11::Json > const & args) -> json11::Json
					{
						ARGS_SIZE_CHECK(2);
						json11::Json container = args[0];
						json11::Json key = args[1];
						json11::Json result;
						if (container.is_array())
						{
							if (!key.is_number())
							{
								throw Exception("Key must be number, got " + key.dump());
							}
							return container[static_cast<size_t>(key.number_value())];
						}
						else if (container.is_object())
						{
							if (!key.is_string())
							{
								throw Exception("Key must be string, got " + key.dump());
							}
							return container[key.string_value()];
						}
						else if (container.is_string())
						{
							if (!key.is_number())
							{
								throw Exception("Key must be number, got " + key.dump());
							}
							return json11::Json(
								std::string(1, container.string_value()[static_cast<size_t>(key.number_value())]));
						}
						throw Exception("Can not get anything from " + container.dump());
					}
				},
				{
					"lower", [](std::vector< json11::Json > const & args) -> json11::Json
					{
						ARGS_SIZE_CHECK(1);
						if (!args[0].is_string())
						{
							throw Exception("Can not make lower non-string objects");
						}
						std::string arg = args[0].string_value();
						std::string result;
						std::transform(arg.begin(), arg.end(), std::back_inserter(result), ::tolower);
						return json11::Json(result);
					}
				},
				{
					"upper", [](std::vector< json11::Json > const & args) -> json11::Json
					{
						ARGS_SIZE_CHECK(1);
						if (!args[0].is_string())
						{
							throw Exception("Can not make upper non-string objects");
						}
						std::string arg = args[0].string_value();
						std::string result;
						std::transform(arg.begin(), arg.end(), std::back_inserter(result), ::toupper);
						return json11::Json(result);
					}
				},
				{
					"contains", [](std::vector< json11::Json > const & args) -> json11::Json
					{
						ARGS_SIZE_CHECK(2);
						bool result = false;
						if (args[0].is_string() && args[1].is_object())
						{
							if (args[1][args[0].string_value()].type() != json11::Json::NUL)
							{
								result = true;
							}
						}
						else if (args[0].is_string() && args[1].is_string())
						{
							result = args[1].string_value().find(args[0].string_value()) != std::string::npos;
						}
						else if (args[1].is_array())
						{
							auto arrayItems = args[1].array_items();
							result = std::find(arrayItems.begin(), arrayItems.end(), args[0]) != arrayItems.end();
						}
						else
						{
							throw Exception("Can not find appropriate signature");
						}
						return json11::Json(result);
					}
				},
				{
					"to_json", [](std::vector< json11::Json > const & args) -> json11::Json
					{
						ARGS_SIZE_CHECK(1);
						return json11::Json(args[0].dump());
					}
				},
				{
					"random", [](std::vector< json11::Json > const & args) -> json11::Json
					{
						ARGS_SIZE_CHECK(2);
						if (!args[0].is_number() || !args[1].is_number())
						{
							throw Exception("Function accepts only numeric arguments");
						}
						int a = int(args[0].number_value()),
							b = int(args[1].number_value());
						if (a == b)
						{
							return json11::Json(a);
						}
						if (a > b)
						{
							std::swap(a, b);
						}
						std::random_device seed;
						std::default_random_engine generator(seed());
						std::uniform_int_distribution< int > distribution(a, b);
						return json11::Json(distribution(generator));
					}
				},
			})
			{}

	protected:
		json11::Json m_json;
		BinaryOperators m_binaryOperations;
		Functions m_functions;
	};

} /* namespace RedZone */

