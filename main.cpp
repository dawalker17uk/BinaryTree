#include <iostream>

// include header for out btree object.
#include "btree.h"

void treesEqual(btree& treeOne, btree& treeTwo)
{
    if (treeOne == treeTwo)
    {
        std::cout << "trees equal :) " << std::endl;
    }
    else
    {
        std::cout << "trees not equal :) " << std::endl;
    }
}

int main()
{
    btree treeOne, treeTwo;
        treesEqual(treeOne, treeTwo);

    // Test 1
    /*
    treeOne.add(5);
        treesEqual(treeOne, treeTwo);
    treeTwo.add(5);
        treesEqual(treeOne, treeTwo);
    treeOne.add(6);
        treesEqual(treeOne, treeTwo);
    treeTwo.add(6);
        treesEqual(treeOne, treeTwo);
    */

    // Test 2
    /*
    treeOne.add(5);
    treeOne.add(2);
    treeOne.add(8);
    treeOne.add(1);
    treeOne.add(3);
    treeOne.add(7);
    treeOne.add(9);
    treeOne.add(4);

    treeTwo.add(8);
    treeTwo.add(5);
    treeTwo.add(2);
    treeTwo.add(1);
    treeTwo.add(3);
    treeTwo.add(7);
    treeTwo.add(9);
    treeTwo.add(4);
            treesEqual(treeOne, treeTwo);
    */


    // Test 3
    /*
    treeOne.add(5);
    treeOne.add(2);
    treeOne.add(8);
    treeOne.add(1);
    treeOne.add(3);
    treeOne.add(7);
    treeOne.add(9);
    treeOne.add(4);

    treeTwo.add(5);
    treeTwo.add(2);
    treeTwo.add(8);
    treeTwo.add(1);
    treeTwo.add(3);
    treeTwo.add(7);
    treeTwo.add(9);
    treeTwo.add(4);
            treesEqual(treeOne, treeTwo);
    */



    return 0;
}
