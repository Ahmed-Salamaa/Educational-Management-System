#include "include/doctor.h"
#include "include/course.h"
#include "include/assignment.h"
#include "include/servies.h"

Doctor::Doctor ( const string & username , const string & password , const string & email , const string & name , const int & type ) 
    : User ( username , password , email , name , type ) {} ;

void Doctor::edit_course( int id )
{
    edit_course( Course::get_pointer(id) ) ;
} 

void Doctor::edit_course( Course * ptr ) 
{
    if (ptr == nullptr) {
        cout << "Invalid course ID!" << endl;
        return;
    }

    vector <string> menu = 
    {
        "Edit Course Name" ,
        "Edit Course Code" ,
        "Edit Course Descreption" ,
        "Edit Course creditHoure" ,
        "Add Assignment" ,
        "Review The Assignments" ,
        "List all Students at course" ,
        "Delete Course" ,
        "Return to Main menu"
    } ;

    int type = print_menu( menu ) ;

    switch ( type )
    {
        case 1 :
        {    
            string name = read_name() ;
            ptr->change_name( name ) ;
            break;
        }
        case 2 :
        {
            string code = read_code() ;
            ptr->change_code( code ) ;
            break;
        }
        case 3 :
        {
            string descreption = read_descreption() ;
            ptr->change_descreption( descreption ) ;
            break;
        }
        case 4 :
        {
            int creditHoure = read_creditHoure() ;
            ptr->change_creditHoure( creditHoure ) ;
            break;
        }
        case 5 :
        {
            string question = read_string( "Enter the question : " ) ;
            if ( question == "-1" ) return ;

            int degree = read_int( "Enter the degree at range ( 1 , 100 ) : " , 1 , 100 ) ;
            if ( degree == -1 ) return ;

            new Assignment ( ptr , degree , question ) ;
            break;
        }
        case 6 :
            ptr->Review_Assignments() ;
            break;
        case 7 :
        {
            ptr->print_all_Students() ;
            break;
        }
        case 8 :
        {
            delete ptr ;
            cout << "Course had been deleted successfully\n" ;
            return ;
        }
        default:
            return ;
            break;
    }

    edit_course( ptr ) ;


}