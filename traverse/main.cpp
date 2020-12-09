/*================================================================
 *   Copyright (C) 2020 All rights reserved.
 *
 *   File Name     ：main.cpp
 *   Author        ：Wenbing.Wang
 *   Created Time  ：2020-12-08
 *   Description   ：
 *
 ================================================================*/


#include <iostream>
#include "binary_search_tree.h"

int main(int argc, char* argv[]) {
    int root = 5;
    int a =1,b=2,c=3,d=4,e=6,f=8;

    /* the pre-traverse test */
    Tree<int> bTree(root);
    bTree.Insert(a);
    bTree.Insert(b);
    bTree.Insert(c);
    bTree.Insert(d);
    bTree.Insert(e);
    bTree.Insert(f);

    /*  bTree.Insert(3);
     *  bTree.Insert(4);
     *  bTree.Insert(5);*/
    bTree.PreOrder();
    std::cout << std::endl;
    bTree.Clear();

    /** the middle test */
    bTree.Insert(a);
    bTree.Insert(b);
    bTree.Insert(c);
    bTree.Insert(d);
    bTree.Insert(e);
    bTree.Insert(f);
    bTree.MiddleOrder();
    std::cout << std::endl;
    bTree.Print("search 3: %d", bTree.Search(3));
    std::cout << std::endl;
    bTree.Print("search 11: %d", bTree.Search(11));
    std::cout << std::endl;

    /** the post test */
    bTree.Clear();
    bTree.Insert(root);
    bTree.Insert(a);
    bTree.Insert(b);
    bTree.Insert(c);
    bTree.Insert(d);
    bTree.Insert(e);
    bTree.Insert(f);
    bTree.PostOrder();
    std::cout << std::endl;
    return 0;
}
