# HashedTree
A data structure that combines the hash table and the search tree, to have both of their advantages.
i.e. 
 - random acccess in O(1) of hash table.
 - retrieve the minimal element in O(1).
 - insertion and deletion in O(logN), in contract to O(1) of hash table. This is a small price to pay, to have the above two benefits.

Hash table is a powerful data structure, since it provides a random acess in constant time. Yet one of limitations is that the elements are NOT sorted, it would require a complete traverse O(N) to retrieve the minimal/maximal element.

As to the search tree, we place the elements in the right order in O(logN) for each insertion, and the benefit is that we could have a constant time for the operations get_min / get_max.

It would be useful and interesting to have these two data structures combined.

We could regard the combined data structure as a versatile container providing two quick ways to retrieve the elements, i.e. random_acess, given a key; get_min/get_max among the values of all elements.


