#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <memory>
using std::shared_ptr;
// #include <string>
// #include <cassert>


    /** class Node
    * general assumptions on type T:
    * default c'tor, = operator, copy c'tor, d'tor.
    * function specific assumptions are listed per each function
    */

    template <class T>
    class Node{
        

        public: 
        T data;
        int height;
        int w;
        shared_ptr<Node<T>> parent;
        shared_ptr<Node<T>> left_child;
        shared_ptr<Node<T>> right_child;
        /** Node C'tor:   Creates a Node in the dimensions given with value given in each entry.
        *                  If no value was given, each entry is constructed with the default T C'tor
        * @assumptions: default c'tor for T, = operator for T
        * */
        Node(T data_in, int height, int w);

        Node(T data_in);

        Node();
        
        /** Node's Copy C'tor:  Creates a Node with the same values as the Node given
        * @assumptions: = operator for T
        * */
        Node(const Node& node);

        Node& operator=(const Node& node);

        int getHeight(shared_ptr<Node<T>> node) const;

        int getHeight() const;

        int getW() const;

        int getW(shared_ptr<Node<T>> node) const;
        
        shared_ptr<Node<T>> getParent() const;

        shared_ptr<Node<T>> getLeftChild() const;
        
        shared_ptr<Node<T>> getRightChild() const;

        const T& getData() const;

        int getNumOfChildren() const;
        
        void setHeight(const int new_height);

        void setW(const int new_w);

        void setParent(shared_ptr<Node<T>> new_parent);
        
        void setLeftChild(shared_ptr<Node<T>> new_child);
        
        void setRightChild(shared_ptr<Node<T>> new_child);

        void setData(const T& new_data);

        friend std::ostream& operator<<(std::ostream& os, const Node& node) {
            os << (node.data);  //assuming operator<< exists for T
            return os;
        };

        /** Node's Destructor: frees the data stored in the Node and destroys the Node.
        * @assumptions: destructor for T * */
        ~Node()=default;
   
    };
    
    template <class T>
    Node<T>::Node(T data_in, int height, int w) : data(data_in), height(height), w(w), parent(NULL), left_child(NULL), right_child(NULL) {}

    template <class T>
    Node<T>::Node(T data_in) : data(data_in), height(0), w(1), parent(NULL), left_child(NULL), right_child(NULL) {}

    template <class T>
    Node<T>::Node() : data(NULL), height(-1), w(1), parent(NULL), left_child(NULL), right_child(NULL) {}


    // assuming that T has copy c'tor and "=" operator for copying the data
    template <class T>
    Node<T>::Node(const Node<T>& node) : data(node.data), parent(NULL), left_child(NULL), right_child(NULL), height(node.height), w(node.w) { }   
    
    template <class T>
    Node<T>& Node<T>::operator=(const Node<T>& node)
    {
        if(this == &node){
            return *this;
        }
        data = node.data; //assuming operator= exists for T
        parent = NULL;
        left_child = NULL;
        right_child = NULL;
        height = node.height;
        w = node.w;
        return *this;
    }

    template <class T>
    const T& Node<T>::getData() const
    {
        return data;
    }

    template <class T>
    shared_ptr<Node<T>> Node<T>::getRightChild() const 
    {
        return right_child;
    }

    template <class T>
    shared_ptr<Node<T>> Node<T>::getLeftChild() const
    {
        return left_child;
    }

    template <class T>
    shared_ptr<Node<T>> Node<T>::getParent() const
    {
        return parent;
    }

    template <class T>
    int Node<T>::getHeight() const {
        return height;
    }

    template <class T>
    int Node<T>::getW() const {
        return w;
    }
    
    template <class T>
    int Node<T>::getHeight(shared_ptr<Node<T>> node) const
    {
        if (node == nullptr)
        {
            return -1;
        }
        return node->height;
    }

    template <class T>
    int Node<T>::getW(shared_ptr<Node<T>> node) const
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->w;
    }

    template <class T>
    int Node<T>::getNumOfChildren() const
    {
        int num = 0;
        if (getLeftChild())
            num++;
        if (getRightChild())
            num++;
        return num;
    }

    template <class T>
    void Node<T>::setData(const T& new_data)
    {
        data = new_data;
    }

    template <class T>
    void Node<T>::setRightChild(shared_ptr<Node<T>> new_child) 
    {
        right_child = new_child;
    }

    template <class T>
    void Node<T>::setLeftChild(shared_ptr<Node<T>> new_child) 
    {
        left_child = new_child;
    }

    template <class T>
    void Node<T>::setParent(shared_ptr<Node<T>> new_parent) 
    {
        parent = new_parent;
    }

    template <class T>
    void Node<T>::setHeight(const int new_height) 
    {
        height = new_height;
    }

    template <class T>
    void Node<T>::setW(const int new_w) 
    {
        w = new_w;
    }

#endif //Node_H

