#ifndef LISTNODE_H
#define LISTNODE_H
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
    class ListNode{
        T data;
        shared_ptr<ListNode<T>> next_node;
        shared_ptr<ListNode<T>> previous_node;

        public: 
        /** Node C'tor:   Creates a Node in the dimensions given with value given in each entry.
        *                  If no value was given, each entry is constructed with the default T C'tor
        * @assumptions: default c'tor for T, = operator for T
        * */
        ListNode();

        ListNode(T data_in);
        
        /** Node's Copy C'tor:  Creates a Node with the same values as the Node given
        * @assumptions: = operator for T
        * */
        ListNode(const ListNode& node);

        ListNode& operator=(const ListNode& node);

        shared_ptr<ListNode<T>> getNext() const;
        
        shared_ptr<ListNode<T>> getPrevious() const;

        const T& getData() const;

        T& getDataReference();

        void setNext(shared_ptr<ListNode<T>> new_next);
        
        void setPrevious(shared_ptr<ListNode<T>> new_previous);

        void setData(const T& new_data);

        friend std::ostream& operator<<(std::ostream& os, const ListNode& node) {
            os << (node.data);  //assuming operator<< exists for T
            return os;
        };

        /** Node's Destructor: frees the data stored in the Node and destroys the Node.
        * @assumptions: destructor for T * */
        ~ListNode()=default;
   
    };
     
    template <class T>
    ListNode<T>::ListNode() : data(T()), next_node(NULL), previous_node(NULL) {}

    template <class T>
    ListNode<T>::ListNode(T data_in) : data(data_in), next_node(NULL), previous_node(NULL) {}
    
   
    // assuming that T has copy c'tor and "=" operator for copying the data
    template <class T>
    ListNode<T>::ListNode(const ListNode<T>& list_node) : data(list_node.data), next_node(NULL), previous_node(NULL) {  }   
    
    template <class T>
    ListNode<T>& ListNode<T>::operator=(const ListNode<T>& list_node)
    {
        if(this == &list_node){
            return *this;
        }
        data = list_node.data; //assuming operator= exists for T
        next_node = NULL;
        previous_node = NULL;
        return *this;
    }

    template <class T>
    const T& ListNode<T>::getData() const
    {
        return data;
    }

    template <class T>
    T& ListNode<T>::getDataReference() {
        return data;
    }

    template <class T>
    shared_ptr<ListNode<T>> ListNode<T>::getNext() const 
    {
        return next_node;
    }

    template <class T>
    shared_ptr<ListNode<T>> ListNode<T>::getPrevious() const
    {
        return previous_node;
    }

    template <class T>
    void ListNode<T>::setData(const T& new_data)
    {
        data = new_data;
    }

    template <class T>
    void ListNode<T>::setNext(shared_ptr<ListNode<T>> new_next) 
    {
        next_node = new_next;
    }

    template <class T>
    void ListNode<T>::setPrevious(shared_ptr<ListNode<T>> new_previous) 
    {
        previous_node = new_previous;
    }

#endif //ListNode_H

