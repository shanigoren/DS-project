#ifndef BOOM_H
#define BOOM_H
#include <memory>
#include "linkedlist.h"
#include "course.h"
#include "hash_table.h"
#include "time.h"
#include "avl_tree.h"
#include "node.h"
using std::shared_ptr;
#define COURSE_HASH_TABLE 1
#define TIME_TREE 2

class CoursesManager{
    HashTable<Course> course_hash_table;
    AVL_Tree<Time> time_order_tree;

    public:
    CoursesManager();

    void addCourse(int courseID);

    int addClass(int courseID);

    // int addClass(int courseID, Class class_to_add);

    void removeCourse(int courseID);

    void printBoom();

    void watchClass(int courseID, int classID, int time);

    int timeViewed(int courseID, int classID);

    void GetIthWatchedClass(int numOfClasses, int* courseID, int* classID);

    void print(int num);

    void printTimeForCourse(int courseID);

    ~CoursesManager()=default;

};

#endif 