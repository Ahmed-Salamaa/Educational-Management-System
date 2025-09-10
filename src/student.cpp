#include "include/student.h"
#include "include/course.h"

Student::Student ( const string & username , const string & password , const string & email , const string & name , const int & type ) 
    : User ( username , password , email , name , type ) {} ;



void Student::edit_course( int id )
{
    edit_course( Course::get_pointer(id) ) ;
} 

void Student::edit_course( Course * ptr ) 
{
    if (ptr == nullptr) {
        // Handle the error, e.g., by logging or throwing an exception
        return;
    }

    vector <string> menu = 
    {
        "Submit Assignment" ,
        "Unregister from Course" ,
        "Grades Report" ,
        "Return to Main menu"
    } ;

    int type = print_menu( menu ) ;

    switch ( type )
    {
        case 1 :
        {    
            ptr->submit_assignment( get_id() ) ;
            break;
        }
        case 2 :
        {
            
            ptr->delete_User( this ) ;

            break;
        }
        case 3 :
        {
            Assignment_Report( ptr ) ;
            break;
        }
        default:
            break;
    }
}