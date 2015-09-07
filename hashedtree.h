#ifndef _HASHED_TREE_H_
#define _HASHED_TREE_H_

#include <utility>

#include <boost/tuple/tuple.hpp>
#include <boost/unordered_map.hpp>

#include <algorithm>
#include <boost/intrusive/rbtree.hpp>

using namespace boost::intrusive;

/**
 * \brief The HashedTree is a combined data structure of the hash table and the
 *  search tree.
 * 
 *  The data structure allows us to have insertion and deletion in O(lgN). In
 *  addition, we could still have a constant time O(1) like the hash table to
 *  access the minimal element of nodes, since we maintain the order of elements
 *  during the insertion.
 *
 *  In other words, the data structure has two indices, one as the key of hashing
 *  to have a constant-time random access, the other serves as the key for
 *  sorting so that we could have a constant-time access of the minimal element.
 */
template <typename ValueType>
class HashedTree
{

private:
    // container related types
    typedef boost::unordered_map<size_t, ValueType> container_t;
    typedef typename container_t::iterator   container_iterator_t;
    typedef typename container_t::value_type container_entry_t;

    // container index related types
    typedef typename boost::intrusive::rbtree<ValueType> container_sorted_index_t;
    typedef typename container_sorted_index_t::const_iterator const_node_ref; 

private:

    //! The container for all elements, which is indexed by the key.
	container_t _container;

    //! The sorted indices based on value of each element,
    // which allows us to have a constant time access on the minimal element.
    // Note: this view only contain the reference to the elements in
    //   the container, instead of the copy of elements.
    container_sorted_index_t _container_quick_view;

    size_t _nextKeyValue;

    //! Null value.
    ValueType _nullValue;

public:
    HashedTree(const ValueType& iNullValue)
        : _nextKeyValue(1),  // ID=0 is reserved for the null value.
          _nullValue(iNullValue)
    {}

    bool empty(void) const { return _container.empty(); }

    size_t size(void) const { return _container.size(); }


    /**
     *  \brief add a new entry into the container,
     *  \return the key associated with the newly added entry.
     */
	size_t add(const ValueType& iNewElem)
	{
        std::pair<container_iterator_t, bool> aRet =
            _container.insert(container_entry_t(_nextKeyValue, iNewElem));

        // put the new node into the quick view, so that it would be ordered.
        _container_quick_view.insert_equal((aRet.first)->second);

        // keep the _id in the value for the reverse query.
        (aRet.first)->second._id = _nextKeyValue;

        // Return the newly-created timer ID and increment the key value.
		return _nextKeyValue ++;
	}

    /**
     * \brief Find the value that is associated with the specified key.
     * \return a NullValue would be returned if no value is found.
     */
    const ValueType & find(uint64_t iKey)
    {
        container_iterator_t aIter = _container.find(iKey);
        if(aIter == _container.end()){
            return _nullValue;
        } else {
            return aIter->second;
        }
    }

    /**
     * \brief Remove the entry from both the container and the quick view.
     * \return if there is no value found that is associated with the key,
     *   a null value would be returned.
     */
	ValueType remove(uint64_t iKey)
	{
        container_iterator_t aIter = _container.find(iKey);

		if (aIter == _container.end()) {
            // Did not find the specified timer, return a empty timer.
			return _nullValue;
		} else {
            // Retrieve the associated object before removing it.
            ValueType aRet = (aIter->second);
 
            // Remove the timer from the both the quick view and the container.
            _container_quick_view.erase(aIter->second);
            _container.erase(aIter);

			return aRet;
		}
	}

    /**
     *  \brief return the value that is at the head/top of the container,
     *    according to the order of values in the container.
     *  \return a NULL value is returned if the container is empty.
     *
     *  Note: The values are ordered in the ascendent order.
     */
    const ValueType& top()
    {
        const_node_ref aTopValue = _container_quick_view.begin();
        if(aTopValue == _container_quick_view.end())
            return _nullValue;
        else
            return (*aTopValue);
    }

    /**
     * \brief pop the top value in the container.
     * \return if the container is empty, a null value would be returned.
     */
    ValueType pop()
    {
        const_node_ref aTopValuePtr = _container_quick_view.begin();
        if(aTopValuePtr == _container_quick_view.end()) {
            return _nullValue;
        } else {
            // make a copy of the value to return, before removing.
            ValueType aValueCopy(*aTopValuePtr);

            // remove the value from both the container and the quick view.
            _container_quick_view.erase(aTopValuePtr);
            _container.erase(aTopValuePtr->_id);

            return aValueCopy;
        }
    }

};




#endif /* _HASHED_TREE_H_ */
