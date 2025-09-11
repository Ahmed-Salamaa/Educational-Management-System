#ifndef USER_H
#define USER_H

#include "include/help_fun.h"

class Course;
class Assignment;

class User
{
    private:
        
        string username ;
        string password ;
        string email ;
        vector < string > name ;
        // Doctor: 1 , Student: 2
        int type ;
        int id ;

        // CourseTable -> ( student , registerd )  ( doctor , teach it )
        map < int , Course * > CourseTable ;


        // AssignmentTable[0] -> none Finised
        //                      ( student , not submited )
        //                      ( doctor , not give a degree )
        //
        // AssignmentTable[1] -> Finised 
        //                      ( student , submited )
        //                      ( doctor , have a degree )
        map < int , Assignment * > AssignmentTable [2] ;

        static map < int , User * > UserTable ;
        static int id_cnt ;

    public:        

        User ( const string & username , const string & password , const string & email , const string & name , const int & type , int id = -1 ) ;

        static int read_id () ;

        const string & get_username () ;
        const string & get_email () ;
        const string & get_password () ;
        const vector < string > & get_name () ;
        const int & get_id () ;
        // Doctor: 1 , Student: 2 
        int get_type () ;

        void change_username ( const string & username ) ;
        void change_password ( const string & password ) ;
        void change_email ( const string & email ) ;
        void change_name ( const string & name ) ;

        static bool used_id ( int id ) ;
        static User * get_pointer ( int id ) ;

        virtual void edit_course ( Course * ptr ) {}
        virtual void edit_course ( int ptr ) {}
        void delete_course ( int id ) ;
        void delete_Assignment ( int id ) ;
        void register_course ( ) ;
        void add_course ( Course * ptr ) ;
        void print_my_course () ;
        void print_my_Assignment () ;
        void print_all_User () ;
        void Assignment_Report ( Course * Course_ptr ) ;

        bool login ( string pass ) ;

        void print_self ( ) ;

        static void delete_all () ;
        static void Data_Base_Save ( ofstream & out ) ;
        static void Data_Base_Load ( ifstream & in ) ;


        ~User () ;
};




#endif