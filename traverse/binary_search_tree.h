/*================================================================
*   Copyright (C) 2020 All rights reserved.
*
*   File Name     ：binary_search_tree.hpp
*   Author        ：Wenbing.Wang
*   Created Time  ：2020-12-07
*   Description   ：
*
================================================================*/


#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H
//#ifdef __cplusplus
//extern "C"
//{
//#endif

template <typename T=int>
struct Tree {
    Tree() = default;
    Tree(const Tree &) = delete;
    explicit Tree(const T &elem);

    ~Tree();

    /**
     * common operations
     */
    void Insert(const T &elem);
    bool Search(const T &elem) const;
    void Remove(const T &elem);
    void Clear();

    void PreOrder() const;
    void MiddleOrder() const;
    void PostOrder() const;


private:
    struct Node {
        T value;
        struct Node *left;
        struct Node *right;

        Node(const T &elem)
            : value(elem), left(nullptr), right(nullptr) {};
        Node(const T &elem, Node *l, Node *r)
            : value(elem), left(l), right(r) {};
        Node(const Node &node)
            : value(node.value), left(node.left), right(node.right) {};
    };

    Node *root_;

    void Remove_l(const T &elem, Node * &node);
    void PreOrder_l(Node* root) const;
    void MiddleOrder_l(Node* root) const;
    void PostOrder_l(Node* root) const;
    void Clear_l(Node* node);
    Node* Search_l(const T &elem, Node* node) const;
    Node* Min(Node* node) const;
    Node* Max(Node* node) const;
    /**
     * print function
     */
    void Print(Node *node) const;
    void Print(const char* format, ...) const;

};

//#ifdef __cplusplus
//}
//#endif
#endif //BINARY_SEARCH_TREE_H
