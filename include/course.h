#ifndef COURSE_H
#define COURSE_H

    #include "include/help_fun.h"
    #include "assignment.h"

class User;
class Assignment;

class Course
{
    private:
        
        int id ;
        int creditHoure ;
        string name , code , descreption ;
        
        // UsertTable[0] -> Doctor
        // UsertTable[1] -> Student
        map < int , User * > UsertTable [2] ;

        map < int , Assignment * > AssignmentTable ;

        static map < int , Course * > CourseTable ;
        static int id_cnt ;

    public:
        
        Course ( string name , string code , string descreption , int creditHoure , User * ptr ) ;

        static int read_id () ;
        static bool used_id ( int id ) ;
        static int read_id ( User * ptr ) ;
        static Course * get_pointer ( int id ) ;

        bool had_a_permission ( User * ptr ) ;

        const string & get_name () ;
        const string & get_code () ;
        const string & get_descreption () ;
        const int & get_creditHoure () ;
        const int & get_id () ;

        void change_name ( string name ) ;
        void change_code ( string code ) ;
        void change_descreption ( string descreption ) ;
        void change_creditHoure ( int creditHoure ) ;

        // mode -> ( 1 for User , 0 for database )
        static void print_all_Courses ( ) ;

        // mode -> ( 1 for User , 0 for database )
        void print_curr_course ( ) ;
        void print_all_doctors ( ) ;
        void print_all_Students ( ) ;
        void print_all_Assignment ( User * user_ptr = nullptr ) ;

        void add_Assignment ( Assignment * ptr ) ;
        void Print_Assignments ( ) ;
        void add_User ( User * ptr ) ;
        void Review_Assignments() ;

        void submit_assignment ( int user_id ) ;

        void delete_User ( User * ptr ) ;
        void delete_User_Assignment ( User * ptr ) ;

        ~Course() ;

        

};



#endif