#include"library2.h"
#include"courses_manager.h"
#include"exceptions.h"
#include <memory>

void *Init() {
    CoursesManager *DS = new CoursesManager ();
    return (void*)DS;
}

StatusType AddCourse(void *DS, int courseID) {
    if (!DS || courseID <= 0)
        return INVALID_INPUT;
    try{
        ((CoursesManager *)DS)-> addCourse(courseID);
    }
    catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    catch (Failure& e){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType RemoveCourse(void *DS, int courseID){
    if (!DS || courseID <= 0)
        return INVALID_INPUT;;
    try{
        ((CoursesManager *)DS)-> removeCourse(courseID);
    }
    catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    catch (Failure& e){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType AddClass(void *DS, int courseID, int* classID) {
    if (!DS || courseID <= 0)
        return INVALID_INPUT;
    try{
        classID[0] = ((CoursesManager *)DS)->addClass(courseID);
    }
    catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    catch (Failure& e){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType WatchClass(void *DS, int courseID, int classID, int time){
    if (!DS || courseID <= 0 || classID < 0 || time <= 0)
        return INVALID_INPUT;
    try{
        ((CoursesManager *)DS)-> watchClass(courseID, classID, time);
    }
    catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    catch (InvalidInput& e){
        return INVALID_INPUT;
    }
    catch (Failure& e){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed){
    if (!DS || courseID <= 0 || classID < 0)
        return INVALID_INPUT;
    try{
        *timeViewed = ((CoursesManager *)DS)-> timeViewed(courseID, classID);
    }
    catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    catch (InvalidInput& e){
        return INVALID_INPUT;
    }
    catch (Failure& e){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetIthWatchedClass(void* DS, int i, int* courseID, int* classID) {
     if (!DS || i <= 0)
        return INVALID_INPUT;
    try{
       ((CoursesManager *)DS)-> GetIthWatchedClass(i, courseID, classID);
    }
    catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }
    catch (Failure& e){
        return FAILURE;
    }
    return SUCCESS;
}

void Quit(void **DS){
    delete((CoursesManager *) *DS);
    *DS = nullptr;
}