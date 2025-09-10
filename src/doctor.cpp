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
        cout << "Error: Invalid course pointer. Course not found.\n";
        return;
    }

    vector <string> menu = 
    {
        "Edit Course Name" ,
        "Edit Course Code" ,
        "Edit Course Description" ,
        "Edit Course Credit Hours" ,
        "Add Assignment" ,
        "Review Assignments" ,
        "List All Students in Course" ,
        "Delete Course" ,
        "Return to Main Menu"
    } ;

    int type = print_menu( menu ) ;

    switch ( type )
    {
        case 1 :
        {    
            string name = read_name() ;
            if ( name != "-1" ) {
                ptr->change_name( name ) ;
                cout << "Course name updated successfully.\n" ;
            }
            break;
        }
        case 2 :
        {
            string code = read_code() ;
            if ( code != "-1" ) {
                ptr->change_code( code ) ;
                cout << "Course code updated successfully.\n" ;
            }
            break;
        }
        case 3 :
        {
            string descreption = read_descreption() ;
            if ( descreption != "-1" ) {
                ptr->change_descreption( descreption ) ;
                cout << "Course description updated successfully.\n" ;
            }
            break;
        }
        case 4 :
        {
            int creditHoure = read_creditHoure() ;
            if ( creditHoure != -1 ) {
                ptr->change_creditHoure( creditHoure ) ;
                cout << "Course credit hours updated successfully.\n" ;
            }
            break;
        }
        case 5 :
        {
            string question = read_string( "Enter the question: " ) ;
            if ( question == "-1" ) return ;

            int degree = read_int( "Enter the degree in range (1, 100): " , 1 , 100 ) ;
            if ( degree == -1 ) return ;

            new Assignment ( ptr , degree , question ) ;
            cout << "Assignment created successfully.\n" ;
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
            cout << "Course deleted successfully.\n" ;
            return ;
        }
        default:
            return ;
            break;
    }

    edit_course( ptr ) ;


}