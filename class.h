#ifndef CLASS_H
#define CLASS_H
#include "listnode.h"
#include "node.h"
#include "time.h"
#include <memory>
using std::shared_ptr;

class Class{
    int time_viewed;
    //shared_ptr<ListNode<int>> zero_time_viewed_ptr;
    shared_ptr<Node<Time>> time_order_tree_ptr;

    public:
    Class();
        
    Class(const Class& c)=default; //we would always use a ptr to Class once created, never copying by_value

    Class& operator=(const Class& c)=default;

    int getTime() const;

    //shared_ptr<ListNode<int>> getZeroPtr() const;

    shared_ptr<Node<Time>> getTimeOrderTreePtr() const;
    
    void setTime(int new_time);

    //void setZeroPtr(shared_ptr<ListNode<int>> new_zero_ptr);

    void setTimeOrderTreePtr(shared_ptr<Node<Time>> new_time_order_tree_ptr);

    friend std::ostream& operator<<(std::ostream& os, const Class& curr_class);

    ~Class();
};


#endif //CLASS_H