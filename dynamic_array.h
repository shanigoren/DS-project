#ifndef DYNAMICARR_H
#define DYNAMICARR_H

#include <memory>
#include "exceptions.h"
using std::shared_ptr;

template <class T>
class DynamicArray{
    int size;
    int k;
    T* array;

    void increaseArray();

    void decreaseArray();

    public:
    DynamicArray();

    DynamicArray(int size_in);
        
    DynamicArray(const DynamicArray<T>& arr);

    DynamicArray<T>& operator=(const DynamicArray<T>& arr);

    T& operator[](const int index);

    void insert(T& data);
    
    void remove(int index);

    int getSize() const;
    
    void setSize(int size_new);

    int getK() const;

    void setK(int k_new);

    ~DynamicArray();
    
};

    template <class T>
    DynamicArray<T>::DynamicArray() : size(2), k(0) {
        array = new T[size];
    }

    template <class T>
    DynamicArray<T>::DynamicArray(int size_in) : size(size_in), k(0) {
        array = new T[size_in];
    }

    template <class T>
    DynamicArray<T>::DynamicArray(const DynamicArray& arr) : size(arr.size), k(arr.k), array(new T[arr.size]){
        for (int i=0; i<k; i++){
            array[i] = arr.array[i];
        }
    }

    template <class T>
    DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& arr){
        if(this == &arr){
            return *this;
        }
        k = arr.k;
        size = arr.size;
        T* new_array = new T[arr.size];
        for (int i = 0; i < arr.size; ++i) {
            new_array[i] = arr.array[i];
        }
        delete[] array;
        array=new_array;
        return *this;
    }

    template <class T>
    void DynamicArray<T>::insert(T& data) {
        if (k == size){
            increaseArray();
        }
        array[k] = data;
        k++;
    }

    template <class T>
    void DynamicArray<T>::increaseArray() {
        size = size*2;
        T* new_array = new T[size];
        // copy array:
        for (int i=0; i<size/2; i++){
            new_array[i] = array[i];
        }
        delete[] array;
        array = new_array;
    }

    template <class T>
    void DynamicArray<T>::decreaseArray() {
        T* new_array = new T[size/2];
        int j=0;
        // copy array:
        for (int i=0; i < size; i++) {
            if (array[i] != T()) {
                new_array[j] = array[i];
                j++;
            }
        }
        size = size/2;
        delete[] array;
        array = new_array;
    }

    template <class T>
    void DynamicArray<T>::remove(int index) {
        array[index] = T(); // make sure we call removeAllList() in hash table
        // && the course exists in the linekd list
        k--;
        if (k <= size/4){
            decreaseArray();
        }
    }

    template <class T>
    T& DynamicArray<T>::operator[](const int index){
        if (index > size || index < 0)
            throw Failure();
        return array[index];
    }

    template <class T>
    int DynamicArray<T>::getSize() const {
        return size;
    }

    template <class T>
    int DynamicArray<T>::getK() const{
        return k;
    }

    template <class T>
    void DynamicArray<T>::setSize(int size_new) {
        size = size_new;
    }

    template <class T>
    void DynamicArray<T>::setK(int k_new) {
        k = k_new;
    }

    template <class T>
    DynamicArray<T>::~DynamicArray() { 
        delete[] array;
    }

#endif