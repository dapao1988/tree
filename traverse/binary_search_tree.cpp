/*================================================================
 *   Copyright (C) 2020 All rights reserved.
 *
 *   File Name     ：binary_search_tree.cpp
 *   Author        ：Wenbing.Wang
 *   Created Time  ：2020-12-07
 *   Description   ：
 *
 ================================================================*/


#include <stdio.h>
#include <stdarg.h>
#include <cassert>
#include <stack>
#include "binary_search_tree.h"

using std::stack;

template<typename T>
Tree<T>::Tree(const T &item) {
    if (root_ == nullptr) {
        this->root_ = new Node(item);

        assert(root_ != nullptr);
    }

}

template<typename T>
Tree<T>::~Tree() {
    Clear();
}


/**
 * insert @elem using non-recurse way
 */
template<typename T>
void Tree<T>::Insert(const T &elem) {
    Node *elem_node = nullptr;
    Node *node_cursor = root_;
    Node *pre_node = root_;

    while (node_cursor) {
        if (node_cursor->value > elem) {
            pre_node = node_cursor;
            node_cursor = node_cursor->left;
        } else if (elem > node_cursor->value) {
            pre_node = node_cursor;
            node_cursor = node_cursor->right;
        } else {
            //no need to process equal value for binary search tree
            goto exit;
        }
    }

    elem_node = new Node(elem);
    /* find the place for insert */
    if (pre_node->value > elem) {
        assert(pre_node->left == nullptr);
        pre_node->left = elem_node;
    } else {
        assert(pre_node->right == nullptr);
        pre_node->right = elem_node;
    }

exit:
    return ;
}

/**
 * use recurse way to search
 */
template<typename T>
bool Tree<T>::Search(const T &elem) const {
    Node *node = Search_l(elem, root_);
    if (node == nullptr) {
        return false;
    } else {
        Print("%s\n", "Find");
        return true;
    }
}
template<typename T>
void Tree<T>::Remove(const T &elem) {
    Remove_l(elem, root_);
}

/**
 * clear the tree, free every node
 */
template<typename T>
void Tree<T>::Clear() {
    Clear_l(root_);
}

template<typename T>
void Tree<T>::PreOrder() const {
    PreOrder_l(root_);
}

template<typename T>
void Tree<T>::MiddleOrder() const {
    MiddleOrder_l(root_);
}

template<typename T>
void Tree<T>::PostOrder() const {
    PostOrder_l(root_);
}


/**
 * use recurse way to do pre-traverse
 */
template<typename T>
void Tree<T>::PreOrder_l(Node *node) const {
    if (node != nullptr) {
        Print(node);
        PreOrder_l(node->left);
        PreOrder_l(node->right);
    }
}

/**
 * use non-recurse way to do middle-traverse
 */
template<typename T>
void Tree<T>::MiddleOrder_l(Node *node) const {
    stack<Node*>  stack;

    while(node == nullptr && stack.empty()) {
        while (node != nullptr) {
            stack.push(node);
            node = node->left;
        }

        if (!stack.empty()) {
            node = stack.top();
            Print(node);
            stack.pop();
            node = node->right;
        }
    }
}

/**
 * use non-recurse way to do post-traverse
 * attention to that:
 * the node cannot be print until all of its child been printed
 * therefore, set a flag for the last visit node
 * if "last_visit_node == node->right", then "print"
 */
template<typename T>
void Tree<T>::PostOrder_l(Node *node) const {
    stack<Node*>  stack;
    Node *last_visit_node = nullptr;

    while(node == nullptr && stack.empty()) {
        while (node != nullptr) {
            stack.push(node);
            node = node->left;
        }

        if (!stack.empty()) {
            node = stack.top();

            if (node->right == nullptr 
                    || last_visit_node == node) {
                Print(node);
                last_visit_node = node;
                stack.pop();
            } else {
                node = node->right;
            }
        }
    }
}

template<typename T>
void Tree<T>::Print(Node *node) const {
    printf("%d ", node->value);
}

template<typename T>
void Tree<T>::Print(const char* format, ...) const {
    va_list ap;
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);
}

/**
 * Just using recurse way to free
 * If not recurse, the same as post order to free,
 * set the flag to ensure all of its child being free,
 * and then, free the node itself.
 */
template<typename T>
void Tree<T>::Clear_l(Node* node) {
    if (node != nullptr) {
        Clear_l(node->left);
        Clear_l(node->right);
        delete node;
        node = nullptr;
    }
}

template<typename T>
typename Tree<T>::Node* Tree<T>::Search_l(const T &elem, Node* node) const {
    if (node != nullptr) {
        if (elem == node->value) {
            return node;
        }
        else if (elem < node->value) {
            return Search_l(elem, node->left);
        } else {
            return Search_l(elem, node->right);
        }
    }
}
template<typename T>
void Tree<T>::Remove_l(const T &elem, Node* &node) {
    if (node == nullptr)
        return ;

    /**
     * check if node exists in the binary search tree
     */
    if (!Search(elem)) {
        Print("%s\n", "Warning: not find elem");
        return ;
    }

    /**
     * case 1: the node to delete has no child;
     * case 2: the node to delete has only left child;
     * case 3: the node to delete has only right child;
     * case 4: the node to delete has only right child;
     */
    if (elem < node->value) {
        Remove_l(elem, node->left);
    } else if (elem > node->value) {
        Remove_l(elem, node->right);
    } else if (node->left != nullptr && node->right != nullptr) {
        /**
         * 1. find the most left child(node_right_min) in its right tree
         * 2. just swap the value node_right_min with the node to delete
         * 3. delete the node_right_min node
         */
        Node *right_min = Min(node->right);
        node->value = right_min->value;
        delete right_min;
    } else {
        Node *old_node = node;
        node = node->left ? node->left : node->right;
 
        /**
         * check if the node to delete is root node,
         * ensure the root node point to its child
         */
        if (old_node == root_) {
            root_ = node;
        }
        delete old_node;
    }
}

/**
 * find the minimized node under the @node.
 */
template<typename T>
typename Tree<T>::Node* Tree<T>::Min(Node* node) const {
    Node *min_node = nullptr;

    while (node != nullptr) {
        min_node = node;
        node = node->left;
    }

    return min_node;
}
/**
 * find the maximized node under the @node.
 */
template<typename T>
typename Tree<T>::Node* Tree<T>::Max(Node* node) const {
    Node *max_node = nullptr;

    while (node != nullptr) {
        max_node = node;
        node = node->right;
    }

    return max_node;
}

template class Tree<int>;
template class Tree<double>;
template class Tree<float>;
