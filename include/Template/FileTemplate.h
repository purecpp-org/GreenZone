/*
 * FileTemplate.h
 *
 *  Created on: 2014
 *      Author: jc
 */
#pragma once

#include "Template.h"

#include <string>

namespace RedZone
{

	class FileTemplate : public Template
	{
	public:
		inline FileTemplate(std::string const & filePath);
		inline virtual ~FileTemplate();

	private:
		std::string m_filePath;
	};

} /* namespace RedZone */

#include <Template/FileTemplate.cpp>