/*
 * CacheNode.h
 *
 *  Created on: 2015
 *      Author: jc
 */
#pragma once

#include "Node.h"

#include <chrono>
#include <unordered_map>

namespace RedZone {

class CacheNode: public Node {
public:
	inline CacheNode();

	inline virtual void render(Writer * stream, Context * context) const;
	inline virtual void processFragment(Fragment const * fragment);
	inline virtual void exitScope(std::string const & endTag);
	inline  virtual std::string name() const;

	inline  virtual ~CacheNode();

    typedef std::tuple< std::chrono::time_point< 
       std::chrono::system_clock>, std::string > CacheRow;

protected:
    uint64_t m_cacheTime;
    std::vector< std::string > m_vars;
    static std::unordered_map< size_t, CacheRow > s_cached;
};

} /* namespace RedZone */

#include <Node/CacheNode.cpp>