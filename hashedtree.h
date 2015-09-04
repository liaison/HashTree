#ifndef _HASHED_TREE_H_
#define _HASHED_TREE_H_

#include <utility>
#include <stdexcept>

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

public:
    HashedTree() : _nextKeyValue(1)
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

        _container_quick_view.insert_equal((aRet.first)->second);

        // Return the newly-created timer ID and increment the key value.
		return _nextKeyValue ++;
	}

};


#endif /* _HASHED_TREE_H_ */
