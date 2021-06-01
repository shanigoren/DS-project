#ifndef TIME_H
#define TIME_H
#include <memory>
#include "avl_tree.h"
#include "avl_tree.h"
using std::shared_ptr;

class Time{ //this class is a friend class of courses_manager, so we don't need get
    int courseID;
    int classID;
    int timeWatched;

    public:
    Time(int courseID, int classID, int time_in);

    Time();
        
    Time(const Time& t)=default; //we would always use a ptr to Class once created, never copying by_value

    Time& operator=(const Time& t)=default;

    int getCourseID() const;

    const int& getCourseIDRefrence() const;

    const int& getClassIDRefrence() const;

    int getClassID() const;

    int getTimeWatched() const;

    void addWatchTime(int courseID, int classID);

    friend std::ostream& operator<<(std::ostream& os, const Time& time);
 
    ~Time()=default;
};

    bool operator==(const Time& time1, const Time& time2);

    bool operator!=(const Time& time1, const Time& time2);

    bool operator<(const Time& time1, const Time& time2);

    bool operator>(const Time& time1, const Time& time2);

    bool operator>=(const Time& time1, const Time& time2);
    
    bool operator<=(const Time& time1, const Time& time2);


#endif //TIME_H