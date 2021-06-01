#include "course.h"
#include "hash_table.h"

Course::Course() : courseID(-1), numOfClasses(0), classes_arr() {}

Course::Course(int course_id) : courseID(course_id), numOfClasses(0), classes_arr() { }

int Course::getCourseID() const {
    return courseID;
}

int Course::getKey() const {
    return courseID;
}

void Course::setCourseID(int course_id) {
    courseID = course_id;
}

int Course::getNumOfClasses() const {
    return numOfClasses;
}

Class& Course::operator[](int classID) {
    return classes_arr[classID];
}

void Course::setNumOfClasses(int num_of_classes) {
    numOfClasses = num_of_classes;
}

void Course::removeTimePointers() {
    for (int i = 0; i < numOfClasses; i++)
    {
        classes_arr[i].setTimeOrderTreePtr(NULL);
    }
}

int Course::addClass() {
    Class class_to_add;
    classes_arr.insert(class_to_add);
    numOfClasses = classes_arr.getK();
    return numOfClasses-1;
}

void Course::removeAllClasses(AVL_Tree<Time>& time_order_tree, HashTable<Course>& courses_hash_table){
    // go through each of the classes in the array
    // printTimeForClass();
    for (int i=0; i<numOfClasses; i++) {
        // for each class, get the pointer to the node in time_order_tree
        // get the data and remove the time from the tree
        if (courses_hash_table[courseID][i].getTimeOrderTreePtr()){
            Time time_data = (courses_hash_table[courseID][i].getTimeOrderTreePtr())->getData();
            // if (classes_arr[i].getTimeOrderTreePtr()->getNumOfChildren() == 2) {
            if (courses_hash_table[courseID][i].getTimeOrderTreePtr()->getNumOfChildren() == 2) {
                shared_ptr<Node<Time>> to_swap = time_order_tree.findSmallestNode(courses_hash_table[courseID][i].getTimeOrderTreePtr()->getRightChild());
                Time to_swap_data = to_swap->getData();
                int course_id = to_swap_data.getCourseID();
                int class_id = to_swap_data.getClassID();
                courses_hash_table[course_id][class_id].setTimeOrderTreePtr(courses_hash_table[courseID][i].getTimeOrderTreePtr());
                // time_order_tree.removeNode(time_data);
            }
            time_order_tree.removeNode(time_data);
        }
    }
}

//time_order_tree.find(to_swap_data, time_order_tree.getRoot())

void Course::printTimeForClass(){
    std::cout << "{";
    for (int i=0; i < numOfClasses; i++) {
        Class curr_class = classes_arr[i];
        std::cout << i << ":" << curr_class << ", ";
    }
    std::cout << "}" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Course& course) {
    os << course.getCourseID() <<std::endl;
    return os;
}

bool operator==(const Course& course1, const Course& course2) {
    if(course1.getCourseID() == course2.getCourseID()) 
        return true;
    return false;
}

bool operator!=(const Course& course1, const Course& course2) {
    if(course1.getCourseID() == course2.getCourseID()) 
        return false;
    return true;
}

bool operator<(const Course& course1, const Course& course2) {
    if(course1.getCourseID() < course2.getCourseID()) 
        return true;
    return false;
}

bool operator<=(const Course& course1, const Course& course2) {
    if((course1 == course2) || (course1 < course2))
        return true;
    return false;
}

bool operator>(const Course& course1, const Course& course2) {
    if(!(course1 <= course2))
        return true;
    return false;
}

bool operator>=(const Course& course1, const Course& course2) {
    if((course1 == course2) || (course1 > course2))
        return true;
    return false;
}
