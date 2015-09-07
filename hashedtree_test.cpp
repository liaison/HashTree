#include "timer_node.h"
#include "hashedtree.h"

#include <iostream>

void testAdd(uint64_t iQueueSize)
{
    timer_node_t aNullTimer(0);
    HashedTree<timer_node_t> hashOrderedTimerQueue(aNullTimer);

    for(uint64_t i=1; i <= iQueueSize; ++i) {
        timer_node_t aTimer(i*100);
        hashOrderedTimerQueue.add(aTimer);
    }
    
    assert(hashOrderedTimerQueue.size() == iQueueSize);
    
    std::cout << "add() API testing success." << std::endl;
}

void testFind()
{
    timer_node_t aNullTimer(0);
    HashedTree<timer_node_t> hashOrderedTimerQueue(aNullTimer);

    timer_node_t aTimer(345);
    uint64_t aTimerKey = hashOrderedTimerQueue.add(aTimer);

    assert(hashOrderedTimerQueue.find(aTimerKey) != aNullTimer);

    uint64_t aRandomKey = 12345;
    assert(hashOrderedTimerQueue.find(aRandomKey) == aNullTimer);

    std::cout << "find() API testing success." << std::endl;
}

void testRemove()
{
    timer_node_t aNullTimer(0);
    HashedTree<timer_node_t> hashOrderedTimerQueue(aNullTimer);

    timer_node_t aTimer(345);
    uint64_t aTimerKey = hashOrderedTimerQueue.add(aTimer);

    assert(hashOrderedTimerQueue.find(aTimerKey) != aNullTimer);

    timer_node_t aRemovedTimer = hashOrderedTimerQueue.remove(aTimerKey);  

    assert(aRemovedTimer != aNullTimer);
    assert(aRemovedTimer == aTimer);

    std::cout << "remove() API testing success." << std::endl;
}

void testTop()
{
    timer_node_t aNullTimer(0);
    HashedTree<timer_node_t> hashOrderedTimerQueue(aNullTimer);

    timer_node_t aTimer1(100);
    timer_node_t aTimer2(200);
    timer_node_t aTimer3(300);

    // add the timer in the reserver order.
    hashOrderedTimerQueue.add(aTimer3);
    hashOrderedTimerQueue.add(aTimer2);
    hashOrderedTimerQueue.add(aTimer1);

    assert(hashOrderedTimerQueue.top() == aTimer1);

    std::cout << "top() API testing success." << std::endl;    
}

void testPop()
{
    timer_node_t aNullTimer(0);
    HashedTree<timer_node_t> hashOrderedTimerQueue(aNullTimer);

    timer_node_t aTimer1(100);
    timer_node_t aTimer2(200);
    hashOrderedTimerQueue.add(aTimer1);
    hashOrderedTimerQueue.add(aTimer2);

    timer_node_t aPopTimer = hashOrderedTimerQueue.pop();
    assert(aPopTimer == aTimer1);

    assert(hashOrderedTimerQueue.size() == 1);
    std::cout << "pop() API testing success." << std::endl;    

}

int main(int argc, char** argv)
{
    testAdd(100);

    testFind();

    testRemove();

    testTop();

    testPop();
    return 0;
}


