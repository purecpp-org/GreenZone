/*
 * FileReader.h
 *
 *      Author: jc
 */

#pragma once

#include <fstream>
#include <iterator>
#include <string>

#include "Reader.h"

namespace RedZone
{

	class FileReader : public Reader
	{
	public:
		inline FileReader(std::string const & fileName);

		inline virtual std::string read(size_t nBytes);
		inline virtual std::string readAll();
		inline virtual std::string id() const;

		inline virtual ~FileReader();

	protected:
		std::ifstream m_file;
		std::string m_path;

	private:
		FileReader(FileReader const &) { }
	};

} /* namespace RedZone */

#include <IO/FileReader.cpp>