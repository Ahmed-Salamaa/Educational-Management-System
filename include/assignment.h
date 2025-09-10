#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "include/help_fun.h"


class Course;

class Assignment
{
    private:
        
        int id , course_id , degree ;
        string question ;

        // student id , answer , degree
        map < int , pair < string , int > > answers ;

        static int id_cnt ;
        static map < int , Assignment * > AssignmentTable ;

    public:

        Assignment ( Course * ptr , int degree , string question ) ;

        static int read_id () ;
        static bool used_id ( int id ) ;
        static Assignment * get_pointer ( int id ) ;

        int get_id () ; 
        int get_course_id () ; 
        int get_degree () ;
        string get_question () ;

        void change_course_id ( int course_id ) ; 
        void change_degree ( int degree ) ;
        void change_question ( string question ) ;

        bool is_solved ( int id ) ;
        int get_user_degree ( int id ) ;
        string get_user_answer ( int id ) ;
        string add_user_answer ( int id , string user_answer ) ;

        void print_assignment () ;
        void print_self ( User * user_ptr = nullptr ) ;
        
        void delete_User ( User * ptr ) ;

        int read_user_id() ;

        void Give_degree ( int user_id , int degree ) ;
        void menu ( ) ;


        ~Assignment() ;

};

#endif