#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "dynamic_array.h"
#include "linkedlist.h"
// #include "course.h"
#include <memory>
using std::shared_ptr;

template <class T>
class HashTable {
    DynamicArray<LinkedList<T>> hash_table;
    T not_found;

    void increaseArraySize();
    void decreaseArraySize();

    public:
    HashTable();
        
    HashTable(const HashTable& hash_table_new);

    // HashTable& operator=(const HashTable& hash_table_new);

    T& operator[](const int courseID);

    void insert(T& data);

    void remove(T& data_to_remove);

    void printHash();

    int getK();

    ~HashTable();
};

    template <class T>
    HashTable<T>::HashTable() : hash_table(), not_found(-1) { }

    template <class T>
    void HashTable<T>::insert(T& data) {
        int key = data.getKey();
        int index = key %  hash_table.getSize();
        // add data to linked list
        if (!hash_table[index].getHead()){
            hash_table.setK(hash_table.getK() + 1);
        }
        else if (!hash_table[index].getHead()->getNext()){
            hash_table.setK(hash_table.getK() + 1);
        }
        hash_table[index].addNodeBegin(data);
        if (hash_table.getK() >= hash_table.getSize()){
            increaseArraySize();
        }
    }

    template <class T>
    void HashTable<T>::remove(T& data_to_remove) {
        int key = data_to_remove.getKey();
        int index = key %  hash_table.getSize();
        shared_ptr<ListNode<T>> node_to_remove = hash_table[index].find(data_to_remove);
        if (!node_to_remove)
            throw Failure();
        hash_table[index].removeNode(node_to_remove);
        if (!hash_table[index].getHead()->getNext()) { 
            hash_table.setK(hash_table.getK() - 1);
            if (hash_table.getK() <= hash_table.getSize()/4 && hash_table.getSize() > 2)
                decreaseArraySize();
        }
    }

    template <class T>
    void HashTable<T>::increaseArraySize() {
        int new_size = (hash_table.getSize())*2;
        // T* new_hash_table = new T[new_size];
        DynamicArray<LinkedList<T>> new_hash_table(new_size);
        new_hash_table.setSize(new_size);
        new_hash_table.setK(hash_table.getK());
        // copy hash_table:
        for (int i=0; i<new_size/2; i++){
            shared_ptr<ListNode<T>> current_node = hash_table[i].getHead();
            //delete if the list contains only dummy
            if (current_node){
                if (!current_node->getNext()){
                    hash_table[i].removeAllList();
                    continue;
                }
            }
            else
                continue;
            current_node = current_node->getNext();
            while (current_node){
                int key = (current_node->getData()).getKey(); 
                int index = key % new_size;
                new_hash_table[index].addNodeBegin(current_node->getData());
                current_node = current_node->getNext();
            }
            hash_table[i].removeAllList();
        }
        hash_table = new_hash_table;
    }

    // CHANGE THIS TO MATCH INCREASE
    template <class T>
    void HashTable<T>::decreaseArraySize() {
        int new_size = (hash_table.getSize())/2;
        DynamicArray<LinkedList<T>> new_hash_table(new_size);
        // copy hash_table:
        for (int i = 0; i < new_size*2; i++){
            shared_ptr<ListNode<T>> current_node = hash_table[i].getHead();
            if (current_node) {
                if (!current_node->getNext()){
                    hash_table[i].removeAllList();
                    continue;
                }
            }
            else
                continue;
            current_node = current_node->getNext();
            while (current_node) {
                int key = current_node->getData().getKey();
                int index = key % new_size;
                if (!new_hash_table[index].getHead()){
                    new_hash_table.setK(new_hash_table.getK() + 1);
                }
                new_hash_table[index].addNodeBegin(current_node->getData());
                current_node = current_node->getNext();
            }
            hash_table[i].removeAllList();
        }
        hash_table = new_hash_table;
        // hash_table.setSize(new_size);
    }

    // template <class T>
    // Course& HashTable<T>::operator[](const int courseID){
    //     int index = courseID % hash_table.getSize();
    //     Course course_to_find(courseID);
    //     shared_ptr<ListNode<T>> found = hash_table[index].find(course_to_find);
    //     if (found)
    //         return found->getDataReference();
    //     return course_not_found;
    // }

    template <class T>
    T& HashTable<T>::operator[](const int key){
        int index = key % hash_table.getSize();
        T to_find(key);
        shared_ptr<ListNode<T>> found = hash_table[index].find(to_find);
        if (found)
            return found->getDataReference();
        return not_found;
    }

    template <class T>
    void HashTable<T>::printHash(){
        for (int i=0; i<hash_table.getSize(); i++) {
            std::cout << i << ": "; 
            hash_table[i].printLinkedList();
            std::cout << std::endl;
        }
    }

    template <class T>
    HashTable<T>::~HashTable() { 
        for (int i=0; i<hash_table.getSize(); i++) {
            if (hash_table[i].getHead())
                hash_table[i].removeAllList();
        }
        // delete[] hash_table;
    }

#endif