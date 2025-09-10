#include "include/servies.h"
#include "include/student.h"
#include "include/doctor.h"
#include "include/course.h"
#include "include/assignment.h"

bool Services::sign_in ()
{
    if ( is_log_in() ) { cout << ( "You cant sign in , there are a User Log in !" ) ; exit (1) ; }

    int id = User::read_id() ;
    if ( id == -1 ) return 0 ;

    User * temp = curr_user->get_pointer( id ) ;
    string password ;

    while ( true )
    {
        if ( password == "-1" ) return 0 ;
        password = read_string( "Enter Your Password : " ) ;
        if ( temp->login( password ) ) break ;
        cout << "Incorrect password. Please try again.\n" ;
    }
    
    curr_user = temp ;
    cout << "Login successful. Welcome : " << curr_user->get_name() << " !\n" ;
    return 1 ;
}

bool Services::sign_up ()
{
    if ( is_log_in() ) {cout << "You cant sign up , there are a User Log in !" ; exit(1) ; }

    string username = read_username() ;
    if ( username.empty() ) return 0 ;

    string password = read_password() ;
    if ( password.empty() ) return 0 ;

    string email = read_email() ;
    if ( email.empty() ) return 0 ;

    string name = read_name() ;
    if ( name.empty() ) return 0 ;

    int type = read_type() ;
    if ( !type ) return 0 ;
    
    User * temp ;
    if ( type == 1 ) temp = new Doctor ( username , password , email , name , type ) ;
    else temp = new Student ( username , password , email , name , type ) ;

    cout << "Your account with ID : " << temp->get_id() << " successfully created.\n" ;
    cout << "Please login with your new account.\n" ;
    return 1 ;
}

bool Services::sign_out ()
{
    curr_user = nullptr ;
    return 1 ;
}

bool Services::is_log_in()
{
    return curr_user != nullptr ;
}

void Services::sign_menu ()
{
    vector <string> menu = 
    { 
        "Login" ,
        "Sign Up" ,
        "Shutdown System"
    } ;

    int type = print_menu( menu ) ;

    switch ( type )
    {
        case 1 :
        
            if ( sign_in () ) main_menu () ;
            else sign_menu () ;
        
            break;

        case 2 :

            sign_up () ;
            sign_menu () ;
        
            break;

        case 3 :

            return ;
            break;
        
        default:
            break;
    }
}

void Services::main_menu ()
{
    if ( curr_user == nullptr ) sign_in() ;

    if ( curr_user->get_type() == 1 ) // Doctor
    {
        vector <string> menu =
        {
            "List All Courses" ,
            "Create New Course" ,
            "Join at New Course" ,
            "List My Courses" ,
            "Edit Courses" ,
            "User Menu" ,
            "Log Out"
        } ;

        int type = print_menu( menu ) ;

        switch ( type )
        {
            case 1 :
                
                Course::print_all_Courses() ;
                main_menu() ;
                break;

            case 2 :
            {
                string name = read_name() ;
                if ( name.empty() ) break ;

                string code = read_code() ;
                if ( code.empty() ) break ;

                string descreption = read_descreption() ;
                if ( descreption.empty() ) break ;

                int creditHoure = read_creditHoure() ;
                if ( creditHoure == -1 ) break ;

                auto tt = new Course ( name , code , descreption , creditHoure , curr_user ) ;
                cout << "New course with ID : " << tt->get_id() << " has been created successfully." ;

                main_menu() ;
                break;
            }
            case 3 :

                curr_user->register_course() ;
                main_menu() ;
                break;
            
            case 4 :
                
                curr_user->print_my_course() ;
                main_menu() ;
                break;
            case 5 :

                courses_menu() ;
                main_menu() ;
                break;
            case 6 :
                user_menu() ;
                main_menu() ;
                break;
            default:

                sign_out() ;
                return sign_menu() ;
                break;
        }
    }
    else if ( curr_user->get_type() == 2 ) // Student
    {
        vector <string> menu =
        {
            "List All Courses" ,
            "Register in a New Course" ,
            "List My Courses" ,
            "Edit Courses" ,
            "User Menu" ,
            "Log Out"
        } ;

        int type = print_menu( menu ) ;

        switch ( type )
        {
            case 1 :
                
                Course::print_all_Courses() ;
                main_menu() ;
                break;

            case 2 :
            {
                curr_user->register_course() ;
                main_menu() ;
                break;
            }
            case 3 :
                
                curr_user->print_my_course() ;
                main_menu() ;
                break;
            case 4 :

                courses_menu() ;
                main_menu() ;
                break;
            case 5 :
                user_menu() ;
                main_menu() ;
                break;
            default:

                sign_out() ;
                return sign_menu() ;
                break;
        }
    }

    

}

void Services::user_menu ()
{
    vector <string> menu = 
    {
        "Change Name" ,
        "Change User Name" ,
        "Change Email" ,
        "Change password" ,
        "Delete User" ,
        "User Data" ,
        "Return to Main menu"
    } ;

    int type = print_menu( menu ) ;

    switch ( type )
    {
        case 1 :
        {    
            string name = read_name () ;
            if ( name.empty() ) user_menu() ;
            else curr_user->change_name ( name ) ;
            break;
        }
        case 2:
        {    
            string username = read_username () ;
            if ( username.empty() ) user_menu() ;
            else curr_user->change_username ( username ) ;
            break;
        }
        case 3 :
        {   
            string email = read_email () ;
            if ( email.empty() ) user_menu() ;
            else curr_user->change_email ( email ) ;
            break;
        }
        case 4 :
        {    
            string password = read_password () ;
            if ( password.empty() ) user_menu() ;
            else curr_user->change_password( password ) ;
            break;
        }
        case 5 :
        {
            delete curr_user ;
            cout << "User Had been deleted successfully\n" ;
        }
        case 6 :
        {
            
            curr_user->print_self() ;
            main_menu() ;
            break;
        }

    
        default:
            main_menu() ;
            break;
    }
}

void Services::courses_menu ()
{
    vector <string> menu = 
    {
        "Select Course to edit " ,
        "Return to Main menu"
    } ;

    int type = print_menu( menu ) ;

    switch ( type )
    {
    case 1 :
    {
        int id = Course::read_id( curr_user ) ;
        if ( id == -1 ) break;
        curr_user->edit_course( id ) ;
        break;
    }
    default:
        break;
    }
}

void Services::run ()
{
    sign_menu() ;
}