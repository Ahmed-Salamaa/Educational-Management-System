#include "include/assignment.h"
#include "include/course.h"
#include "include/user.h"
#include "include/help_fun.h"

    int Assignment::id_cnt = 1'000'000'0 ;
    map < int , Assignment * > Assignment::AssignmentTable ;

Assignment::Assignment ( Course * ptr , int degree , string question )
{

    this->course_id = ptr->get_id() ;
    this->degree = degree ;
    this->question = question ;
    this->id = id_cnt ++ ;

    ptr->add_Assignment( this ) ;
    AssignmentTable[id] = this ;
}

int Assignment::read_id ()
{
    int id ;
    while ( true )
    {
        id = read_int ( "Enter Assignment ID : " ) ;
        if ( id == -1 ) return -1 ;
        if ( Assignment::used_id( id ) ) break;
        cout << "Invaild ID. Please try again.\n" ;
    }
    return id ;
}

bool Assignment::used_id ( int id ) { return ( AssignmentTable.count( id )  ) ; }

Assignment * Assignment::get_pointer ( int id )
{
    if ( used_id ( id ) ) return AssignmentTable[ id ] ;
    else return nullptr ;
}

int Assignment::get_id () { return id ; } 

int Assignment::get_course_id () { return course_id ; } 

int Assignment::get_degree () { return degree ; }

string Assignment::get_question () { return question ; }

void Assignment::change_course_id ( int course_id ) { this->course_id = course_id ; } 

void Assignment::change_degree ( int degree ) { this->degree = degree ; }

void Assignment::change_question ( string question ) { this->question = question ; }

bool Assignment::is_solved ( int id ) 
{
    return answers.count( id ) ;
}

int Assignment::get_user_degree ( int id )
{
    if ( is_solved ( id )  ) return answers[id].second ;
    else return 0 ;
}

string Assignment::get_user_answer ( int id )
{
    if ( is_solved ( id )  ) return answers[id].first ;
    else return 0 ;
}

string Assignment::add_user_answer ( int id , string user_answer )
{
    answers[id] = { user_answer , 0 } ;
    return "Answer added successfully" ;
}

void Assignment::delete_User ( User * ptr )
{
    if ( ptr == nullptr ) 
    {
        cout << "Error: Cannot delete null user pointer.\n" ;
        return ;
    }
    
    answers.erase( ptr->get_id() ) ;
}

void Assignment::print_assignment ()
{
    cout << " Q : " << question << "\n" ;

   for ( const auto & [ id , ans ] : answers )
   {
        cout << "\tSt ID : " << id << "\n" ; 
        cout << "\tSt An : " << ( ans.first.empty() ? "No Answer Yet" : ans.first ) << "\n" ;
        cout << "\t Degree : " <<  ans.second << " / " << degree << "\n" ;
   }
}

void Assignment::Give_degree ( int user_id , int degree )
{
    answers[ id ].second = degree ;
}

int Assignment::read_user_id()
{
    int id ;
    while ( true )
    {
        id = User::read_id() ;
        if ( id == -1 ) return -1 ;
        if ( used_id( id ) ) break;
        cout << "Student Dosen't submitted an Answer. Please try again.\n" ;
    }
    return id ;
}

void Assignment::menu ( )
{
    vector <string> menu = 
    {
        "Edit Question" ,
        "Edit Degree" ,
        "Review Stiudent Answers" ,
        "Delete Assignment" ,
        "Return to Main menu"
    } ;

    int type = print_menu( menu ) ;

    switch ( type )
    {
    case 1:
    {
        string question = read_string( "Enter the question : " ) ;
        if ( question == "-1" ) return ;

        change_question( question ) ;

        break;
    }
    case 2:
    {
        int degree = read_int( "Enter the degree at range ( 1 , 100 ) : " , 1 , 100 ) ;
        if ( degree == -1 ) return ;

        change_degree( degree ) ;
    }
    case 3:
    {
        print_assignment() ;
        int id = read_user_id() ;
        if ( id == -1 ) return ;
        
        int degree = read_int( "Enter the degree : " , 1 , this->degree ) ;
        if ( degree == -1 ) return ;

        Give_degree( id , degree ) ;
    }
    
        
    
    default:
        break;
    }
}


Assignment::~Assignment ()
{
    for ( const auto & [ id , ans ] : answers )
    {
        User::get_pointer( id )->delete_Assignment( this->id ) ;
    }
    answers.clear() ;
}

void Assignment::print_self ( User * user_ptr )
{
    cout << "  Assignment ID: " << get_id() << " | Question: " << get_question() << "\n" ;
    if ( user_ptr != nullptr )
    {
        auto it = answers.find( user_ptr->get_id() ) ;
        if ( it != answers.end() )
        {
            cout << "    Your Answer : " << it->second.first ;
            cout << " | Degree : " << it->second.second << " / " << degree << "\n" ;
        }
        else 
        {
            cout << "    Status: Not answered yet\n" ;
        }
    }
}

