#include "timer_node.h"
#include "hashedtree.h"

#include <iostream>

int main(int argc, char** argv)
{
    HashedTree<timer_node_t> hashOrderedTimerQueue;

    timer_node_t aTimer1(0, 100);
    hashOrderedTimerQueue.add(aTimer1);

    std::cout << "size:" << hashOrderedTimerQueue.size() << std::endl;

    
    return 0;
}

