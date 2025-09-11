#include "include/assignment.h"
#include "include/course.h"
#include "include/user.h"
#include "include/help_fun.h"

    int Assignment::id_cnt = 1'000'000'0 ;
    map < int , Assignment * > Assignment::AssignmentTable ;

Assignment::Assignment ( Course * ptr , int degree , string question , int id )
{

    this->course_id = ptr->get_id() ;
    this->degree = degree ;
    this->question = question ;

    if ( id == -1 ) this->id = id_cnt ++ ;
    else this->id = id ;

    ptr->add_Assignment( this ) ;
    AssignmentTable[this->id] = this ;
}

int Assignment::read_id ()
{
    int id ;
    while ( true )
    {
        id = read_int ( "Enter Assignment ID: " ) ;
        if ( id == -1 ) return -1 ;
        if ( Assignment::used_id( id ) ) break;
        cout << "Invalid Assignment ID. Please try again.\n" ;
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
    cout << "\n================ ASSIGNMENT DETAILS ================\n" ;
    cout << "Question: " << question << "\n" ;
    cout << "Maximum Degree: " << degree << "\n" ;
    cout << "===================================================\n" ;

    if ( answers.empty() )
    {
        cout << "No student submissions yet.\n" ;
    }
    else
    {
        cout << "Total Submissions: " << answers.size() << "\n" ;
        cout << "---------------------------------------------------\n" ;

        for ( const auto & [ id , ans ] : answers )
        {
            cout << "Student ID: " << id << "\n" ; 
            cout << "Answer: " << ( ans.first.empty() ? "No Answer Yet" : ans.first ) << "\n" ;
            cout << "Score: " <<  ans.second << " / " << degree << "\n" ;
            cout << "---------------------------------------------------\n" ;
        }
    }
    
    cout << "===================================================\n" ;
}

void Assignment::Give_degree ( int user_id , int degree )
{
    answers[ user_id ].second = degree ;
}

int Assignment::read_user_id()
{
    int id ;
    while ( true )
    {
        id = User::read_id() ;
        if ( id == -1 ) return -1 ;
        if ( answers.count(id) ) break;
        cout << "Student has not submitted an answer. Please try again.\n" ;
    }
    return id ;
}

void Assignment::menu ( )
{
    vector <string> menu = 
    {
        "Edit Question" ,
        "Edit Degree" ,
        "Review Student Answers" ,
        "Delete Assignment" ,
        "Return to Main Menu"
    } ;

    int type = print_menu( menu ) ;

    switch ( type )
    {
    case 1:
    {
        string question = read_string( "Enter the question: " ) ;
        if ( question == "-1" ) return ;

        change_question( question ) ;
        cout << "Assignment question updated successfully.\n" ;
        break;
    }
    case 2:
    {
        int degree = read_int( "Enter the degree in range (1, 100): " , 1 , 100 ) ;
        if ( degree == -1 ) return ;

        change_degree( degree ) ;
        cout << "Assignment degree updated successfully.\n" ;
        break;
    }
    case 3:
    {
        print_assignment() ;
        int id = read_user_id() ;
        if ( id == -1 ) return ;
        
        int degree = read_int( "Enter the degree: " , 1 , this->degree ) ;
        if ( degree == -1 ) return ;

        Give_degree( id , degree ) ;
        cout << "Student grade updated successfully.\n" ;
        break;
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
            cout << "    Your Answer: " << it->second.first ;
            cout << " | Score: " << it->second.second << " / " << degree << "\n" ;
        }
        else 
        {
            cout << "    Status: Not answered yet\n" ;
        }
    }
}

void Assignment::Data_Base_Save ( ofstream & out )
{
    out << id_cnt << " " << AssignmentTable.size() << "\n" ;
    for ( const auto & [ id , ptr ] : AssignmentTable )
    {
        out << ptr->get_id() << "," ;
        out << ptr->get_course_id() << "," ;
        out << ptr->get_degree() << "," ;
        out << ptr->get_question() << "," ;
        
        out << ptr->answers.size() << "\n" ;
        for ( const auto & [ user_id , ans ] : ptr->answers )
        {
            out << user_id << "," << ans.first << "," << ans.second << "\n" ;
        }
    }
}

void Assignment::Data_Base_Load ( ifstream & in )
{
    for ( const auto & [ id , ptr ] : AssignmentTable )
    {
        if ( ptr != nullptr ) delete ptr ;
    }

    AssignmentTable.clear() ;

    int n ;
    in >> id_cnt >> n ;
    in.ignore() ;

    while ( n -- )
    {
        string id ; getline ( in , id , ',' ) ;
        string course_id ; getline ( in , course_id , ',' ) ;
        string degree ; getline ( in , degree , ',' ) ;
        string question ; getline ( in , question , ',' ) ;

        Assignment * ptr = new Assignment ( Course::get_pointer( stoi ( course_id ) ) , stoi ( degree ) , question , stoi ( id ) ) ;
        
        int m ; in >> m ;
        in.ignore() ;

        while ( m -- )
        {
            string user_id_str ; getline( in , user_id_str , ',' ) ;
            string user_ans ; getline( in , user_ans , ',' ) ;
            string user_degree_str ; getline( in , user_degree_str , '\n' ) ;

            int user_id = stoi( user_id_str ) ;
            int user_degree = stoi( user_degree_str ) ;

            ptr->add_user_answer( user_id , user_ans ) ;
            ptr->Give_degree( user_id , user_degree ) ;
        }
    }
}


void Assignment::delete_all ()
{
    for ( const auto & [ id , ptr ] : AssignmentTable )
    {
        if ( ptr != nullptr ) delete ptr ;
    }
}