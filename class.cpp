#include "class.h"
#include <memory>

Class::Class() : time_viewed(0), time_order_tree_ptr(NULL) {}

int Class::getTime() const {
    return time_viewed;
}


shared_ptr<Node<Time>> Class::getTimeOrderTreePtr() const {
    return time_order_tree_ptr;
}

void Class::setTime(int new_time) {
    time_viewed += new_time;
}

void Class::setTimeOrderTreePtr(shared_ptr<Node<Time>> new_time_order_tree_ptr) {
    time_order_tree_ptr = new_time_order_tree_ptr;
}

std::ostream& operator<<(std::ostream& os, const Class& curr_class) {
    if (curr_class.getTimeOrderTreePtr() == NULL)
        os << " ";
    else 
        os << (curr_class.getTimeOrderTreePtr())->getData();
    return os;
}

Class::~Class(){
    time_order_tree_ptr = NULL;
}


// #endif //CLASS_H