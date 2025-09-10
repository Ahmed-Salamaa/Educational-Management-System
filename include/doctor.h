#ifndef DOCTOR_H
#define DOCTOR_H


#include "include/user.h"

class Doctor : public User
{
    private:

        

    public:

        Doctor ( const string & username , const string & password , const string & email , const string & name , const int & type ) ;
        
    void edit_course ( Course * ptr ) ;
    void edit_course ( int ptr ) ;

};





#endif