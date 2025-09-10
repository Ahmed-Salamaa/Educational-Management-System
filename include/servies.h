#ifndef SERVICES_H 
#define SERVICES_H

#include "include/user.h"

class Services
{
    private :

        User * curr_user = nullptr ;

        bool sign_in () ;
        bool sign_up () ;
        bool sign_out () ;
        bool is_log_in () ;

        void sign_menu () ;
        void main_menu () ;
        void user_menu () ;
        void courses_menu () ;

    public :

        void run () ;
};


#endif