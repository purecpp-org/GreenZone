/*
 * Variable.h
 *
 *  Created on: 2014
 *      Author: jc
 */
#pragma once

#include "Node.h"

namespace RedZone {

class Fragment;

class Variable: public Node {
public:
    Variable();

    virtual void render( Writer * stream, Context * context ) const;

    virtual void processFragment( Fragment const * fragment );

    virtual std::string name() const;

    virtual ~Variable();

protected:
    std::string m_expression;
};

} /* namespace RedZone */

#include <Node/Variable.cpp>