#ifndef STUDENT_H
#define STUDENT_H


#include "include/user.h"

class Student : public User
{
    private:

        

    public:

        Student ( const string & username , const string & password , const string & email , const string & name , const int & type ) ;
        
        void edit_course ( Course * ptr ) ;
        void edit_course ( int ptr ) ;

};





#endif