#ifndef COURSE_H
#define COURSE_H
#include "listnode.h"
#include "node.h"
#include "avl_tree.h"
#include "dynamic_array.h"
#include "hash_table.h"
#include "time.h"
#include "linkedlist.h"
#include "class.h"
#include <memory>
using std::shared_ptr;

class Course{
    int courseID;
    int numOfClasses;
    DynamicArray<Class> classes_arr;

    public:
    Course();
    
    Course(int course_id);
        
    Course(const Course& c)=default; //we would always use a ptr to Class once created, never copying by_value

    Course& operator=(const Course& c)=default;

    int addClass();
    
    int getKey() const;

    int getCourseID() const;

    void setCourseID(int course_id);

    int getNumOfClasses() const;

    Class& operator[](int classID);

    void setNumOfClasses(int num_of_classes);

    void removeTimePointers();

    void removeAllClasses(AVL_Tree<Time>& time_order_tree, HashTable<Course>& courses_hash_table);

    void printTimeForClass();
    
    static void setTimeOrderTreePtr(shared_ptr<Node<Course>> course, int classID, AVL_Tree<Time>& time_order_tree, Time new_time);
    
    friend std::ostream& operator<<(std::ostream& os, const Course& course);

    ~Course()=default;
    
};

    bool operator==(const Course& course1, const Course& course2);

    bool operator!=(const Course& course1, const Course& course2);

    bool operator<(const Course& course1,  const Course& course2);

    bool operator>(const Course& course1, const Course& course2);

    bool operator>=(const Course& course1, const Course& course2);
    
    bool operator<=(const Course& course1, const Course& course2);

    
#endif //COURSE_H