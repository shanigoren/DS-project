#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "listnode.h"
#include <iostream>
#include <memory>
using std::shared_ptr;

    /** class Node<T>
    * general assumptions on type T:
    * default c'tor, = operator, copy c'tor, d'tor.
    * function specific assumptions are listed per each function
    */

    template <class T>
    class LinkedList{
        shared_ptr<ListNode<T>> head;
        shared_ptr<ListNode<T>> end;
        
        public:
        /** AVL Tree C'tor:   Creates a Node<T> in the dimensions given with value given in each entry.
        *                  If no value was given, each entry is constructed with the default T C'tor
        * @assumptions: default c'tor for T, = operator for T
        * */
        LinkedList();
        
        /** Node<T>'s Copy C'tor:  Creates a Node<T> with the same values as the Node<T> given
        * @assumptions: = operator for T
        * */
        LinkedList(const LinkedList& list)=default;

        LinkedList& operator=(const LinkedList& list)=default;

        void addNodeBegin(T new_data);

        void addNodeSorted(T new_data);

        void removeNode(shared_ptr<ListNode<T>> node_to_remove);

        void removeAllList();

        shared_ptr<ListNode<T>> find(const T& to_find);

        shared_ptr<ListNode<T>> getHead() const;

        shared_ptr<ListNode<T>> getEnd() const;

        void printLinkedList();

        /** Node<T>'s Destructor: frees the data stored in the Node<T> and destroys the Node<T>.
        * @assumptions: destructor for T * */
        ~LinkedList()=default;
   
    };
    
    template <class T>
    LinkedList<T>::LinkedList() : head(NULL), end(NULL) { }

    template <class T>
    void LinkedList<T>::addNodeBegin(T new_data)
    {
        shared_ptr<ListNode<T>> new_node(new ListNode<T>(new_data));
        if (head == NULL) {
            shared_ptr<ListNode<T>> new_head(new ListNode<T>());
            head = new_head;
        }
        //first case: list is empty
        if (head->getNext() == NULL){
            head->setNext(new_node);
            new_node->setPrevious(head);
            end = new_node;
            return;
        }
        // second case: there are other nodes in the tree, connect new to head
        shared_ptr<ListNode<T>> temp_node = head->getNext();
        head->setNext(new_node);
        new_node->setPrevious(head);
        new_node->setNext(temp_node);
        temp_node->setPrevious(new_node);
    }

    template <class T>
    void LinkedList<T>::removeAllList() {
        // shared_ptr<ListNode<T>> iterator = head->getNext();
        while(head->getNext()) {
            removeNode(head->getNext());
        }
        head = NULL;
        end = NULL;
    }

    template <class T>
    void LinkedList<T>::addNodeSorted(T new_data)
    {
        shared_ptr<ListNode<T>> new_node(new ListNode<T>(new_data));
        //first case: list is empty
        shared_ptr<ListNode<T>> current_node = head->getNext();
        if (head->getNext() == NULL){
            head->setNext(new_node);
            new_node->setPrevious(head);
            end = new_node;
            return;
        }
        if (current_node->getData() > new_data) { //second case: the data is the minimum among the list
            head->setNext(new_node);            
            new_node->setPrevious(head);
            new_node->setNext(current_node);
            current_node->setPrevious(new_node);
            return;
        }
        while(current_node->getData() < new_data && (current_node->getNext())) { 
            if (current_node->getNext()->getData() > new_data)
                break;
            else
                current_node = current_node->getNext();
        }
        if (current_node->getData() == new_data) // third case: if the data is already in the list, do nothing
            return;
        shared_ptr<ListNode<T>> current_node_next = current_node->getNext();
        current_node->setNext(new_node);
        new_node->setPrevious(current_node);
        new_node->setNext(current_node_next);
        if (current_node_next) 
            current_node_next->setPrevious(new_node);
        else
            end = new_node;
    }

    template <class T>
    void LinkedList<T>::removeNode(shared_ptr<ListNode<T>> node_to_remove) {
        // list is empty - do nothing
        if(head->getNext() == NULL || !node_to_remove)
            return;
        shared_ptr<ListNode<T>> prev_node = node_to_remove->getPrevious();
        shared_ptr<ListNode<T>> next_node = node_to_remove->getNext();
        // case of previous + next
        if (prev_node && next_node){
            prev_node->setNext(next_node);
            next_node->setPrevious(prev_node);
            // node_to_remove.reset();
        }
        // remove the last node in the list
        else if (prev_node && !next_node){
            prev_node->setNext(NULL);
            end = NULL;
        }
        node_to_remove->setPrevious(NULL);
        node_to_remove->setNext(NULL);
    }
 
    template <class T>
    shared_ptr<ListNode<T>> LinkedList<T>::find(const T& to_find)
    {
        if (!head){
            return nullptr;
        }
        shared_ptr<ListNode<T>> current_node = head;
        if (!current_node->getNext())
            return nullptr;
        while(current_node)
        { 
            if(current_node->getData() == to_find) {
                return current_node;
            }
            else 
                current_node = current_node->getNext();
        }
        return nullptr;
    }

    template <class T>
    shared_ptr<ListNode<T>> LinkedList<T>::getHead() const {
        return head;
    }

    template <class T>
    shared_ptr<ListNode<T>> LinkedList<T>::getEnd() const {
        return end;
    }

    template <class T>
    void LinkedList<T>::printLinkedList() {
        if (!head)
            return;
        shared_ptr<ListNode<T>> iterator = head->getNext();
        while(iterator != NULL) {
            std::cout << iterator->getData() << " ";
            iterator = iterator->getNext();
        }
    }

#endif //LINKEDLIST