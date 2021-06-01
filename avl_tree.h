#ifndef AVL_H
#define AVL_H
#define DEBUG 
#include "node.h"
#include "exceptions.h"
#include <iostream>
#include <memory>
using std::shared_ptr;
// #include <string>
#include <assert.h>


    /** class Node<T>
    * general assumptions on type T:
    * default c'tor, = operator, copy c'tor, d'tor.
    * function specific assumptions are listed per each function
    */

    template <class T>
    class AVL_Tree{
        shared_ptr<Node<T>> root;
        shared_ptr<Node<T>> smallest_node;
        static int calcBalanceFactor(shared_ptr<Node<T>> node);
        static void copy_helper(shared_ptr<Node<T>> tree_to_copy, shared_ptr<Node<T>>& new_tree);
        void delete_helper();

        shared_ptr<Node<T>> findParent(T data);
        shared_ptr<shared_ptr<Node<T>>> getRoute(T data, int height);
        void removeLeaf(shared_ptr<Node<T>> to_remove);
        void removeOneChild(shared_ptr<Node<T>> to_remove, shared_ptr<Node<T>> right_child, shared_ptr<Node<T>> left_child);
        void removeTwoChildren(shared_ptr<Node<T>> node_to_remove, shared_ptr<Node<T>> right_child, shared_ptr<Node<T>> left_child);
        
        shared_ptr<Node<T>> rotateTree(shared_ptr<Node<T>> v, int v_bf); // int right_child_bf, int left_child_bf);
        shared_ptr<Node<T>> rotateRight(shared_ptr<Node<T>> b);
        shared_ptr<Node<T>> rotateLeft(shared_ptr<Node<T>> a);  

        void printTreeAux(shared_ptr<Node<T>> root, int space); 

        void fillArrayInOrderAux(shared_ptr<Node<T>> temp_root, T* arr, int& counter, int length) const;
        // void fillArrayInOrderAux(shared_ptr<Node<T>> temp_root, shared_ptr<T> arr, int& counter, int length) const;

        public: 
        void printTree(int space);

        AVL_Tree();
        
        AVL_Tree(const AVL_Tree& avl_tree);

        AVL_Tree& operator=(const AVL_Tree& avl_tree);

        void printInOrder() const;

        shared_ptr<Node<T>> getRoot() const;

        shared_ptr<Node<T>> getSmallestNode() const;    

        void setSmallestNode(shared_ptr<Node<T>> smallest_node_new);      

        void printInOrderAux(shared_ptr<Node<T>> temp_root, int& counter, int length) const;
    
        void printFromSmallest(int length) const;

        shared_ptr<Node<T>> findSmallestNode(shared_ptr<Node<T>> root);
        
        void addNode(shared_ptr<Node<T>> new_node);
        
        void removeNode(T data_to_remove);

        void updateHeight(const T& to_find, shared_ptr<Node<T>> cur_root, int delta);

        void updateHeightAux(shared_ptr<Node<T>> cur_root, int delta);

        shared_ptr<Node<T>> find(const T& to_find, shared_ptr<Node<T>> cur_root);

        int fillArrayFromSmallest(int length, T* arr) const;
        // int fillArrayFromSmallest(int length, shared_ptr<T> arr) const;

        shared_ptr<Node<T>> select(int k, shared_ptr<Node<T>> temp_root);

        ~AVL_Tree();
    };
    
    template <class T>
    AVL_Tree<T>::AVL_Tree() : root(NULL), smallest_node(NULL) {}


    template <class T>
    void AVL_Tree<T>::copy_helper(shared_ptr<Node<T>> tree_to_copy, shared_ptr<Node<T>>& new_tree) {
        if (tree_to_copy->getLeftChild()) {
            shared_ptr<Node<T>> left(new Node<T>((tree_to_copy->getLeftChild())->getData(), (tree_to_copy->getLeftChild())->getHeight(), (tree_to_copy->getLeftChild())->getW()));
            new_tree->setLeftChild(left);
            left->setParent(new_tree);
            copy_helper(tree_to_copy->getLeftChild(), new_tree->left_child);
        } else
            new_tree->setLeftChild(nullptr);
        if (tree_to_copy->getRightChild()) {
            shared_ptr<Node<T>> right(new Node<T>((tree_to_copy->getRightChild())->getData(), (tree_to_copy->getRightChild())->getHeight(), (tree_to_copy->getRightChild())->getW()));
            new_tree->setRightChild(right);
            right->setParent(new_tree);
            copy_helper(tree_to_copy->getRightChild(), new_tree->right_child);
        } else
            new_tree->setRightChild(nullptr);
    }

    template <class T>
    AVL_Tree<T>::AVL_Tree(const AVL_Tree<T>& avl_tree) : root(new Node<T>(avl_tree.root->getData(), avl_tree.root->getHeight(), avl_tree.root->getW())), smallest_node()
    {
        copy_helper(avl_tree.root, root);
        smallest_node = findSmallestNode(root);
    }   

    template <class T>
    void AVL_Tree<T>::delete_helper() {
        while (root != NULL) {
            removeNode(root->getData());
        }
    }

    template <class T>
    AVL_Tree<T>::~AVL_Tree() {
        // shared_ptr<Node<T>> temp_root = root;
        delete_helper();
        smallest_node = NULL;
    }
    
    template <class T>
    AVL_Tree<T>& AVL_Tree<T>::operator=(const AVL_Tree<T>& avl_tree)  
    {
        if(this == &avl_tree){
            return *this;
        }
        shared_ptr<Node<T>> temp_root(avl_tree.root);
        shared_ptr<Node<T>> new_root(new Node<T>(avl_tree.root->getData(), avl_tree.root->getHeight()));
        root = new_root;
        copy_helper(temp_root, root);
        smallest_node = findSmallestNode(root);
        return *this;
    }

    template <class T>
    int AVL_Tree<T>::calcBalanceFactor(shared_ptr<Node<T>> node)
    {
        int height_r, height_l = 0;
        if(node->right_child)
            height_r = (node->getRightChild())->getHeight();
        else {
            height_r = -1;
        }
        if(node->left_child)
            height_l = (node->getLeftChild())->getHeight();
        else {
            height_l = -1;
        }
        return height_l - height_r;
    }

    template <class T>
    shared_ptr<Node<T>> AVL_Tree<T>::find(const T& to_find, shared_ptr<Node<T>> cur_root)
    {
        if (!cur_root)
            return NULL;
        if (to_find == cur_root->getData())
            return cur_root;
        if(to_find < cur_root->getData())
            return find(to_find, cur_root->getLeftChild());
        return find(to_find, cur_root->getRightChild());
    }

    template <class T>
    shared_ptr<Node<T>> AVL_Tree<T>::getRoot() const {
        return root;
    }

    template <class T>
    shared_ptr<Node<T>> AVL_Tree<T>::getSmallestNode() const {
        return smallest_node;
    }

     template <class T>
    void AVL_Tree<T>::setSmallestNode(shared_ptr<Node<T>> smallest_node_new)  {
        smallest_node = smallest_node_new;
    }

    template <class T>
    shared_ptr<shared_ptr<Node<T>>> AVL_Tree<T>::getRoute(T data, int height) {
        shared_ptr<shared_ptr<Node<T>>> route_arr;
        route_arr.reset(new shared_ptr<Node<T>>[root->getHeight()-height+1], [](shared_ptr<Node<T>> * p) {delete [] p;});
        route_arr.get()[0] = root;
        if (!root)
            return route_arr;
        shared_ptr<Node<T>> temp_node = root;
        int count = 1;
        if (temp_node->getData() < data) {
            temp_node = temp_node->getRightChild();
        }
        else if (temp_node->getData() > data) {
            temp_node = temp_node->getLeftChild();
        }
        else if (temp_node->getData() == data) {
            return route_arr;
        }
        while (count < root->getHeight() - height + 1)  //imbalance can occur only for the parent and above
        {
           route_arr.get()[count] = temp_node;
            if (temp_node->getData() < data) { 
                temp_node = temp_node->getRightChild();
            }
            else if (temp_node->getData() > data) {
                temp_node = temp_node->getLeftChild();
            }
            count++;
        }
        return route_arr;
    }

    // in case of add: add=1, to_find is the new node
    // in case of remove: add=-1, to_find is the parent of the removed node
    template <class T>
    void AVL_Tree<T>::updateHeight(const T& to_find, shared_ptr<Node<T>> cur_root, int delta)
    {
        if (!cur_root)
            return;
        if (to_find == cur_root->getData()){
            if (delta == -1)
                updateHeightAux(cur_root, delta);
            return;
        }
        if(to_find < cur_root->getData())
            updateHeight(to_find, cur_root->getLeftChild(), delta);
        else
            updateHeight(to_find, cur_root->getRightChild(), delta);
        // in case of only 1 child - update to height of child+1
        // only left child, no right child
        if (cur_root)
            updateHeightAux(cur_root, delta);
    }

    template <class T>
    void AVL_Tree<T>::updateHeightAux(shared_ptr<Node<T>> cur_root, int delta)
    {
        if (cur_root->getLeftChild() && !cur_root->getRightChild())
            cur_root->setHeight(((cur_root->getLeftChild())->getHeight(cur_root->getLeftChild()))+1);
        // only right child, no left child
        else if (!cur_root->getLeftChild() && cur_root->getRightChild())
            cur_root->setHeight((cur_root->getRightChild())->getHeight(cur_root->getRightChild())+1);
        else if (!cur_root->getLeftChild() && !cur_root->getRightChild()){
            cur_root->setHeight(0);
        }
        // in case of 2 children - update to max of children's height +1
        else{
            int left_height = (cur_root->getLeftChild())->getHeight(cur_root->getLeftChild());
            int right_height = (cur_root->getRightChild())->getHeight(cur_root->getRightChild());
            int max = (left_height > right_height) ? left_height : right_height;
            cur_root->setHeight(max+1);
        }
    }

    template <class T>
    void AVL_Tree<T>::addNode(shared_ptr<Node<T>> new_node)
    {
        T new_data = new_node->getData();
        //first case: new node is the first node in the avl_tree
        if (!root){
            root = new_node;
            smallest_node = new_node;
            return;
        }
        //second case: the node given already exists in the avl_tree (do nothing)
        shared_ptr<Node<T>> temp_root = root;
        shared_ptr<Node<T>> found = find(new_data, temp_root);
        if (found)
            throw Failure();
        //242-260: find the parent of the node we're about to add, 
        //make him the left/right child of the parent
        shared_ptr<Node<T>> cur_parent = root;
        while (cur_parent->getLeftChild() || cur_parent->getRightChild()) {
            if(new_data < cur_parent->getData()) {
                if (!cur_parent->getLeftChild())
                    break;
                cur_parent = cur_parent->getLeftChild();
                continue;
            }
            if(new_data > cur_parent->getData()){
                if (!cur_parent->getRightChild())
                    break;
                cur_parent = cur_parent->getRightChild();
            }
        }
        // cur_parent should be the parent of the added node 
        if(new_data < cur_parent->getData()) 
            cur_parent->setLeftChild(new_node);
        else
            cur_parent->setRightChild(new_node);
        new_node->setParent(cur_parent);
        if (new_data < smallest_node->getData())
            smallest_node = new_node;
    //update heights and rotatations
        //function getRoute will return the route (array of pointers) from the root to the new node's parent
        shared_ptr<shared_ptr<Node<T>>> route_arr = getRoute(new_data, 0);
        //third case: the new node is the root's child
        if (cur_parent == root) {
            if (!cur_parent->getRightChild() || !cur_parent->getLeftChild()) {
                cur_parent->setHeight(cur_parent->getHeight(cur_parent) + 1);
            }
            cur_parent->setW(cur_parent->getW(cur_parent)+1);
            return;
        }
        //271-275: calculate the route's length
        int route_height = 0;
        while (route_arr.get()[route_height]->getData() != cur_parent->getData()) {
            route_height++;
        }
        route_height++;
        int curr_height = 1;
        // update w:
        int i = 0;   
        while (i < route_height){
            int cur_w = route_arr.get()[i]->getW(route_arr.get()[i]); 
            route_arr.get()[i]->setW(cur_w + 1);
            i++;
        }   
        while (route_height - curr_height >= 0) { 
            //279-282: calculate the new height of the current parent         
            int h_l = (cur_parent->getLeftChild())->getHeight(cur_parent->getLeftChild());
            int h_r = (cur_parent->getRightChild())->getHeight(cur_parent->getRightChild());
            int parent_height = h_r >= h_l ? h_r + 1 : h_l + 1;
            cur_parent->setHeight(parent_height);
            //284-299: calculate BF for the parent and if neccesary, rotate the sub tree of parent
            int parent_bf = calcBalanceFactor(cur_parent);
            if (parent_bf == 2 || parent_bf == -2) {
                // rotate the root:
                if (route_height - curr_height == 0) {
                    root = rotateTree(cur_parent, parent_bf);
                    root->setParent(NULL);
                    return;
                }
                shared_ptr<Node<T>> connect_to = route_arr.get()[route_height - curr_height - 1];
                shared_ptr<Node<T>> rotate_tree = rotateTree(cur_parent, parent_bf);
                if (connect_to->getData() < rotate_tree->getData()) {
                    connect_to->setRightChild(rotate_tree);
                    rotate_tree->setParent(connect_to);
                }
                else {
                    connect_to->setLeftChild(rotate_tree);
                    rotate_tree->setParent(connect_to);
                }
                return;
            }
            curr_height++;
            if (cur_parent == root) {
                break;
            }
            //update the current parent so that he is the father of the current parent
            cur_parent = route_arr.get()[route_height - curr_height];
        }  
    }

    template <class T>
    shared_ptr<Node<T>> AVL_Tree<T>::rotateTree(shared_ptr<Node<T>> v, int v_bf) { // int right_child_bf, int left_child_bf){ 
        if (v_bf > 0) {
            int left_child_bf = calcBalanceFactor(v->getLeftChild());
            // rotateRight <=> LL
            if (v_bf == 2 && left_child_bf >= 0)
                return rotateRight(v);
            // LR rotate <=> Left Rotate->Right Rotate 
            if (v_bf == 2 && left_child_bf == -1){
                shared_ptr<Node<T>> temp = rotateLeft(v->getLeftChild());
                v->setLeftChild(temp);
                temp->setParent(v);
                return rotateRight(v);
            }
        }
        else {
            int right_child_bf = calcBalanceFactor(v->getRightChild());
            // rotateLeft <=> RR
            if (v_bf == -2 && right_child_bf <= 0) //mistake: should be right <= 0 and not left like written before
                return rotateLeft(v);
            // RL rotate <=> Right Rotate->Left Rotate 
            if (v_bf == -2 && right_child_bf == 1){
                shared_ptr<Node<T>> temp = rotateRight(v->getRightChild());
                v->setRightChild(temp);
                temp->setParent(v);
                return rotateLeft(v);
            }
        }
        //we never reach this point
        return nullptr;
    }

    template <class T>
    shared_ptr<Node<T>> AVL_Tree<T>::findSmallestNode(shared_ptr<Node<T>> root) {
        shared_ptr<Node<T>> cur_root = root;
        while(cur_root->getLeftChild()) {
            cur_root = cur_root->getLeftChild();
        }
        return cur_root;
    }

    template <class T>
    shared_ptr<Node<T>> AVL_Tree<T>::findParent(T data) { // assumption: data is in the avl_tree root is pointing on! (should we do find(data) to make sure?)
        shared_ptr<Node<T>> cur_root = root;
        if (data == cur_root->getData())
            return NULL;
        while (cur_root->getRightChild() || cur_root->getLeftChild()) {
            if (data < cur_root->getData()) {
                if (data == (cur_root->getLeftChild())->getData()) {
                    return cur_root;
                }
                else {
                    cur_root = cur_root->getLeftChild();
                }
            }
            else {
                if (data == (cur_root->getRightChild())->getData()) {
                    return cur_root;
                }
                else {
                    cur_root = cur_root->getRightChild();
                }
            }
        }
        return nullptr;
    }

    template <class T>
    void AVL_Tree<T>::removeLeaf(shared_ptr<Node<T>> to_remove){
        shared_ptr<Node<T>> parent_to_remove = to_remove->getParent();
        if (!parent_to_remove)
            root = NULL;
        // in case to_remove is parent's left child
        else if (parent_to_remove->getData() > to_remove->getData()){
            parent_to_remove->setLeftChild(NULL);
        }
        else if (parent_to_remove->getData() < to_remove->getData()){
            parent_to_remove->setRightChild(NULL);
        }
        to_remove->setParent(NULL);
        to_remove->setRightChild(NULL);
        to_remove->setLeftChild(NULL);
    }

    template <class T>
    void AVL_Tree<T>::removeOneChild(shared_ptr<Node<T>> to_remove, shared_ptr<Node<T>> right_child, shared_ptr<Node<T>> left_child){
        shared_ptr<Node<T>> parent_to_remove = to_remove->getParent();
        if (right_child){
            if (!parent_to_remove){
                right_child->setParent(NULL);
                root = right_child;
            }
            else if (parent_to_remove->getRightChild()->getData() == to_remove->getData()){
                parent_to_remove->setRightChild(right_child);
                right_child->setParent(parent_to_remove);
            }
            else if (parent_to_remove->getLeftChild()->getData() == to_remove->getData()){
                parent_to_remove->setLeftChild(right_child);
                right_child->setParent(parent_to_remove);
            }
        }
        else if (left_child){
            if (!parent_to_remove){
                left_child->setParent(NULL);
                root = left_child;                
            }
            else if (parent_to_remove->getLeftChild()->getData() == to_remove->getData()){
                parent_to_remove->setLeftChild(left_child);
                left_child->setParent(parent_to_remove);
            }
            else if (parent_to_remove->getRightChild()->getData() == to_remove->getData()){
                parent_to_remove->setRightChild(left_child);
                left_child->setParent(parent_to_remove);
            }
        }
        to_remove->setParent(NULL);
        to_remove->setRightChild(NULL);
        to_remove->setLeftChild(NULL);
    }

    template <class T>
    void AVL_Tree<T>::removeTwoChildren(shared_ptr<Node<T>> node_to_remove, shared_ptr<Node<T>> right_child, shared_ptr<Node<T>> left_child){
        //find the next node in order
        shared_ptr<Node<T>> parent_to_remove = node_to_remove->getParent();
        shared_ptr<Node<T>> next_smallest_node = findSmallestNode(right_child);
        //update the w for the route of the removed next smallest node
        shared_ptr<Node<T>> cur_node = next_smallest_node->getParent();
        while (cur_node && cur_node != root){
            cur_node->setW(cur_node->getW(cur_node)-1);
            cur_node = cur_node->getParent();
        }
        cur_node->setW(cur_node->getW(cur_node)-1);
        shared_ptr<Node<T>> next_parent = next_smallest_node->getParent();
        //do the swap here, while keeping the parent!!
        T temp_data = next_smallest_node->getData();
        next_smallest_node->setData(node_to_remove->getData());
        node_to_remove->setData(temp_data);
        // now we need to remove next smallest
        // case of leaf:
        if (next_smallest_node->getNumOfChildren() == 0){
            // in case to_remove is parent's left child
            if (next_parent->getLeftChild()->getData() == next_smallest_node->getData())
                next_parent->setLeftChild(NULL);
            // in case to_remove is parent's right child
            else if (next_parent->getRightChild()->getData() == next_smallest_node->getData())
                next_parent->setRightChild(NULL);
            next_smallest_node->setParent(NULL);
        }
        // case of one child:
        else if (next_smallest_node->getNumOfChildren() == 1){
            removeOneChild(next_smallest_node, next_smallest_node->getRightChild(), next_smallest_node->getLeftChild());    
        }
        // update height here because we need to start updating from the next parent!
        assert(next_parent);
        updateHeight(next_parent->getData(), root, -1);
    }

    template <class T>
    void AVL_Tree<T>::removeNode(T data_to_remove) {
        if(!root)
            return;
        shared_ptr<Node<T>> temp_root = root;
        shared_ptr<Node<T>> node_to_remove = find(data_to_remove, temp_root);
        if (!node_to_remove) {             
            return;
        }
        shared_ptr<Node<T>> node_to_remove_right_child = node_to_remove->getRightChild();
        shared_ptr<Node<T>> node_to_remove_left_child = node_to_remove->getLeftChild();
        shared_ptr<Node<T>> node_to_remove_parent = node_to_remove->getParent(); 
        // case of leaf: make the parent of the leaf point to null
        int children_num = node_to_remove->getNumOfChildren();
        if (children_num == 0){
            removeLeaf(node_to_remove);
        }
        // case of one child: make parent point at the only child
        else if (children_num == 1) {
            removeOneChild(node_to_remove, node_to_remove_right_child, node_to_remove_left_child);    
        }
        // case of 2 children: swap with the next node in order, then remove the node
        else if (children_num == 2) {
            node_to_remove_parent = findSmallestNode(node_to_remove_right_child)->getParent();
            removeTwoChildren(node_to_remove, node_to_remove_right_child, node_to_remove_left_child);
        }
        //if the root was the only node in the tree and he was deleted
        if (!root) {
            smallest_node = NULL;
            return;
        }
        //if we deleted the root and the root had one child, we need to update the node_to_remove_parent
        if (!node_to_remove_parent){
            node_to_remove_parent = root;
            return;
        }
        // if deleted node is a leaf && has no brothers - start to update from parent
        // or if deleted node had one child 
        if (node_to_remove_parent->getNumOfChildren() == 0 || children_num == 1)
            updateHeight(node_to_remove_parent->getData(), root, -1);
        // by now we know that the heights are updated properly
        shared_ptr<shared_ptr<Node<T>>> route_arr = getRoute(node_to_remove_parent->getData(), 0);
        int tree_height = 0;
        while (route_arr.get()[tree_height]->getData() != node_to_remove_parent->getData()) {
            tree_height++;
        }
        tree_height++;
        // update w:
        int i = 0;
        while (i < tree_height && children_num != 2){
            int cur_w = route_arr.get()[i]->getW(route_arr.get()[i]); 
            route_arr.get()[i]->setW(cur_w - 1);
            i++;
        }   
        int curr_height = 1;
        while (tree_height - curr_height >= 0) {          
            int parent_bf = calcBalanceFactor(node_to_remove_parent);
            if (parent_bf == 2 || parent_bf == -2) {
                if (tree_height - curr_height == 0) {
                    root = rotateTree(node_to_remove_parent, parent_bf);
                    root->setParent(NULL);
                    break;
                }
                shared_ptr<Node<T>> connect_to = route_arr.get()[tree_height - curr_height - 1];
                shared_ptr<Node<T>> rotate_tree = rotateTree(node_to_remove_parent, parent_bf);
                if (connect_to->getData() < rotate_tree->getData()) {
                    connect_to->setRightChild(rotate_tree);
                }
                else {
                    connect_to->setLeftChild(rotate_tree);
                }
                rotate_tree->setParent(connect_to);
            }
            curr_height++;
            if (node_to_remove_parent == root) {
                break;
            }
            node_to_remove_parent = route_arr.get()[tree_height - curr_height];
        } 
        smallest_node = findSmallestNode(root);
    }

    template <class T>
    shared_ptr<Node<T>> AVL_Tree<T>::rotateRight(shared_ptr<Node<T>> b){
        shared_ptr<Node<T>> a = b->getLeftChild();
        shared_ptr<Node<T>> b_right = b->getRightChild();
        shared_ptr<Node<T>> a_right = a->getRightChild();
        shared_ptr<Node<T>> a_left = a->getLeftChild();
        b->setLeftChild(a_right);
        a->setRightChild(b);
        if (a_right)
            a_right->setParent(b);
        b->setParent(a);
        // update heights
        int height_b = b_right->getHeight(b_right) >= a_right->getHeight(a_right) ? b_right->getHeight(b_right) + 1 : a_right->getHeight(a_right) + 1;
        int height_a = height_b >= a_left->getHeight(a_left) ? height_b + 1 : a_left->getHeight(a_left) + 1;
        b->setHeight(height_b);
        a->setHeight(height_a);
        // update w:
        int w_b = b->getRightChild()->getW(b->getRightChild()) + b->getLeftChild()->getW(b->getLeftChild()) + 1;
        b->setW(w_b);
        int w_a = a->getRightChild()->getW(a->getRightChild()) + a->getLeftChild()->getW(a->getLeftChild()) + 1;
        a->setW(w_a);
        return a;
    }

    template <class T>
    shared_ptr<Node<T>> AVL_Tree<T>::rotateLeft(shared_ptr<Node<T>> a){
        shared_ptr<Node<T>> b = a->getRightChild();
        shared_ptr<Node<T>> a_left = a->getLeftChild();
        shared_ptr<Node<T>> b_right = b->getRightChild();
        shared_ptr<Node<T>> b_left = b->getLeftChild();
        a->setRightChild(b_left);
        b->setLeftChild(a);
        if (b_left)
            b_left->setParent(a);
        a->setParent(b);
        // update heights:
        int height_a = b_left->getHeight(b_left) >= a_left->getHeight(a_left) ? b_left->getHeight(b_left) + 1 : a_left->getHeight(a_left) + 1;
        int height_b = b_right->getHeight(b_right) >= height_a ? b_right->getHeight(b_right) + 1 : height_a + 1;
        b->setHeight(height_b);
        a->setHeight(height_a);
        // update w:
        int w_a = a->getRightChild()->getW(a->getRightChild()) + a->getLeftChild()->getW(a->getLeftChild()) + 1;
        a->setW(w_a);
        int w_b = b->getRightChild()->getW(b->getRightChild()) + b->getLeftChild()->getW(b->getLeftChild()) + 1;
        b->setW(w_b);
        return b;
    }


    template <class T>
    void AVL_Tree<T>::fillArrayInOrderAux(shared_ptr<Node<T>> temp_root, T *arr, int& counter, int length) const
    {
        if (!temp_root || counter >= length)
            return;
        fillArrayInOrderAux(temp_root->getLeftChild(), arr, counter, length);
        if (counter < length){
            arr[counter] = temp_root->getData();
            counter++;
        }
        fillArrayInOrderAux(temp_root->getRightChild(), arr, counter, length);
    }

    template <class T>
    int AVL_Tree<T>::fillArrayFromSmallest(int length, T *arr) const
    {
        shared_ptr<Node<T>> current_node = smallest_node;
        int counter = 0;
        while(counter<length && current_node){
            arr[counter] = current_node->getData();
            counter++;
            fillArrayInOrderAux(current_node->getRightChild(), arr, counter, length);
            current_node = current_node->getParent();
        }
        return counter;
    }

    template <class T>
    shared_ptr<Node<T>> AVL_Tree<T>::select(int k, shared_ptr<Node<T>> temp_root){
        if (root->getW(root) < k)
            return NULL;
        int w_left_child = temp_root->getLeftChild()->getW(temp_root->getLeftChild());
        if (w_left_child == k-1)
            return temp_root;
        if (w_left_child > k-1){
            return select (k, temp_root->getLeftChild());
        }
        else {//if (w_left_child < k-1){
            return select (k-w_left_child-1, temp_root->getRightChild());
        }
    }

    template <class T>
    void AVL_Tree<T>::printInOrderAux(shared_ptr<Node<T>> temp_root, int& counter, int length) const
    {
        if (!temp_root || counter >= length)
            return;
        printInOrderAux(temp_root->getLeftChild(), counter, length);
        if (counter < length)
            std::cout << *temp_root << " ";
        // print with heights:
        // std::cout << *temp_root << " h:" << temp_root->getHeight(temp_root) << ",  ";
        counter++;
        printInOrderAux(temp_root->getRightChild(), counter, length);
    }

    template <class T>
    void AVL_Tree<T>::printFromSmallest(int length) const
    {
        shared_ptr<Node<T>> current_node = smallest_node;
        int counter = 0;
        while(counter<length && current_node){
            std::cout << *current_node << " ";
            counter++;
            printInOrderAux(current_node->getRightChild(), counter, length);
            current_node = current_node->getParent();
        }
    }

    template <class T>
    void AVL_Tree<T>::printTree(int space) {
        shared_ptr<Node<T>> temp_root = root;
        return printTreeAux(temp_root, space);
    }
    
    template <class T>
    void AVL_Tree<T>::printTreeAux(shared_ptr<Node<T>> root, int space) {
        if(!root)
            return;
        space += 1;
        printTreeAux(root->getRightChild(), space);
        for (int i = 1; i < space; i++)
            std::cout<<"\t";
        std::cout<<root->getData() << ",w:" << root->getW(root) <<"\n";
        printTreeAux(root->getLeftChild(), space);
    }

#endif //AVLTREE