#include "course.h"
#include "class.h"
#include "time.h"
#include "linkedlist.h"
#include <memory>


Time::Time(int courseID_in, int classID_in, int time_in) : courseID(courseID_in), classID(classID_in), timeWatched(time_in) { }

Time::Time() : courseID(-1), classID(-1), timeWatched(-1) { }

int Time::getCourseID() const{
    return courseID;
}

const int& Time::getCourseIDRefrence() const{
    return courseID;
}

int Time::getClassID() const{
    return classID;
}

const int& Time::getClassIDRefrence() const{
    return classID;
}

int Time::getTimeWatched() const{
    return timeWatched;
}

bool operator==(const Time& time1, const Time& time2) {
    if((time1.getCourseID() == time2.getCourseID()) && (time1.getClassID() == time2.getClassID()) 
                                && (time1.getTimeWatched() == time2.getTimeWatched())) 
        return true;
    return false;
}

bool operator!=(const Time& time1, const Time& time2) {
    if(!(time1 == time2))
        return true;
    return false;
}

// the order is: the smallest one gets printed first
bool operator<(const Time& time1, const Time& time2) {
    // if the timewatched is smaller:
    if(time1.getTimeWatched() > time2.getTimeWatched()) 
        return true;
    // if the watching times are equal, compare the courseID, and then compare classID
    else if (time1.getTimeWatched() == time2.getTimeWatched()){
        if (time1.getCourseID() < time2.getCourseID())
            return true;
        else if (time1.getCourseID() == time2.getCourseID()){
            if (time1.getClassID() < time2.getClassID())
                return true;
            // no else if, because equal time&course&class is not "<"
        }
    }
    return false;
}

bool operator<=(const Time& time1, const Time& time2) {
    if((time1 == time2) || (time1 < time2))
        return true;
    return false;
}

bool operator>(const Time& time1, const Time& time2) {
    if(!(time1 <= time2))
        return true;
    return false;
}

bool operator>=(const Time& time1, const Time& time2) {
    if((time1 == time2) || (time1 > time2))
        return true;
    return false;
}

std::ostream& operator<<(std::ostream& os, const Time& time) {
    os<< "course:" << time.courseID << "class:" << time.classID << "time:" <<time.timeWatched;
    return os;
}
