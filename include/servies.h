#ifndef SERVICES_H 
#define SERVICES_H

#include "include/user.h"

    #ifdef _WIN32
        const std::string PATH = "database\\";
    #elif __linux__
        const std::string PATH = "database/";
    #elif __APPLE__
        const std::string PATH = "database/";
    #else
        const std::string PATH = "database/";
    #endif

class Services
{
    private :

        User * curr_user ;

        string user_path = PATH + "user" ;
        string course_path = PATH + "course" ;
        string assignment_path = PATH + "assignment" ;

        bool sign_in () ;
        bool sign_up () ;
        bool sign_out () ;
        bool is_log_in () ;

        void sign_menu () ;
        void main_menu () ;
        void user_menu () ;
        void courses_menu () ;

    public :

        Services () ;

        void Data_Base_Save () ;
        void Data_Base_Load () ;

        void run () ;

        ~Services () ;
};


#endif