#ifndef _TIMER_NODE_H
#define _TIMER_NODE_H

#include <boost/intrusive/set.hpp>

using namespace boost::intrusive;

struct timer_node_t : public set_base_hook<optimize_size<true> >
{
    uint64_t _id;
    uint64_t _value;

    timer_node_t(uint64_t id, uint64_t value) : _id(id), _value(value)
    {}

    //! comparitor used for sorting based on the time value.
    friend bool operator < (const timer_node_t& a, const timer_node_t& b)
    { return a._value  < b._value; }


    friend bool operator > (const timer_node_t& a, const timer_node_t& b)
    { return a._value  > b._value; }

    friend bool operator == (const timer_node_t& a, const timer_node_t& b)
    { return a._value == b._value; }

};


#endif  // _TIMER_NODE_H

