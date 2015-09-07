#ifndef _HASHED_TREE_ENTRY_H
#define _HASHED_TREE_ENTRY_H

#include <stdint.h>

/**
 *  A common interface for all the entry values in the HashedTree.
 *  This interface holds a _id for each value, so that we could query the entry
 *  in the container from a value.
 */
struct hashed_tree_entry_t
{
    uint64_t _id;

    hashed_tree_entry_t() {};
};


#endif  // _HASHED_TREE_ENTRY_H
