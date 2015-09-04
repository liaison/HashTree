#include "timer_node.h"
#include "hashedtree.h"

#include <iostream>

int main(int argc, char** argv)
{
    HashedTree<timer_node_t> hashOrderedTimerQueue;

    std::cout << "size:" << hashOrderedTimerQueue.size() << std::endl;

    return 0;
}

