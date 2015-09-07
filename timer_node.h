#ifndef _TIMER_NODE_H
#define _TIMER_NODE_H

#include "hashedtree_entry.h"

#include <boost/intrusive/set.hpp>

using namespace boost::intrusive;

struct timer_node_t : public hashed_tree_entry_t,
                      public set_base_hook<optimize_size<true> >
{
    uint64_t _value;

    timer_node_t(uint64_t value) : _value(value)
    {}

    //! comparitor used for sorting based on the time value.
    friend bool operator < (const timer_node_t& a, const timer_node_t& b)
    { return a._value  < b._value; }

    friend bool operator > (const timer_node_t& a, const timer_node_t& b)
    { return a._value  > b._value; }

    friend bool operator == (const timer_node_t& a, const timer_node_t& b)
    { return a._value == b._value; }

    friend bool operator != (const timer_node_t& a, const timer_node_t& b)
    { return !(a == b); }

};


#endif  // _TIMER_NODE_H

