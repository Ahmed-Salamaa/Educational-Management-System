#include "include/course.h"
#include "include/user.h"
#include "include/assignment.h"


    int Course::id_cnt = 1'000'000'0 ;
    map < int , Course * > Course::CourseTable ;

Course::Course ( string name , string code , string descreption , int creditHoure , User * ptr )
{
    this->name = name ;
    this->code = code ;
    this->descreption = descreption ;
    this->creditHoure = creditHoure ;
    this->id = id_cnt ++ ;
    if ( ptr != nullptr ) {
        UsertTable[0][ ptr->get_id() ] = ptr ;
        ptr->add_course( this ) ;
    }

    CourseTable[this->id] = this ;
}

int Course::read_id ()
{
    int id ;
    while ( true )
    {
        id = read_int ( "Enter Course ID: " ) ;
        if ( id == -1 ) return -1 ;
        if ( Course::used_id( id ) ) break;
        cout << "Invalid Course ID. Please try again.\n" ;
    }
    return id ;
}

int Course::read_id ( User * ptr )
{
    int id ;
    while ( true )
    {
        id = read_id () ;
        if ( id == -1 ) return -1 ;
        if ( Course::get_pointer( id )->had_a_permission ( ptr ) ) break;
        cout << "Access denied: You are not registered for this course. Please register first or try another course.\n" ;
    }
    return id ;
}

bool Course::used_id ( int id ) { return CourseTable.find( id ) != CourseTable.end() ; }

Course * Course::get_pointer ( int id )
{
    auto it = CourseTable.find( id ) ;
    if ( it != CourseTable.end() ) return it->second ;
    else return nullptr ;
}

bool Course::had_a_permission ( User * ptr )
{
    return UsertTable[ ptr->get_type() - 1 ].find( ptr->get_id() ) != UsertTable[ ptr->get_type() - 1 ].end() ;
}

const string & Course::get_name () { return this->name ; }

const string & Course::get_code () { return this->code ; }

const string & Course::get_descreption () { return this->descreption ; }

const int & Course::get_creditHoure () { return this->creditHoure ; }

const int & Course::get_id () { return this->id ; }

void Course::change_name ( string name ) { this->name = name ; }

void Course::change_code ( string code ) { this->code = code ; }

void Course::change_descreption ( string descreption ) { this->descreption = descreption ; }

void Course::change_creditHoure ( int creditHoure ) { this->creditHoure = creditHoure ; }

void Course::print_all_Courses ( )
{
    cout << "\n==================== COURSES ====================\n" ;
    cout << "Total Courses in System: " << CourseTable.size() << "\n" ;
    cout << "==================================================\n" ;

    if ( CourseTable.empty() )
    {
        cout << "No courses available in the system.\n" ;
    }
    else
    {
        for ( const auto & [ id , ptr ] : CourseTable )
            ptr->print_curr_course( ) ;
    }
    
    cout << "==================================================\n\n" ;
}

void Course::print_curr_course ( )
{
    cout << "  Course ID: " << id << " | Name: " << name << " | Code: " << code ;
    cout << " | Credits: " << creditHoure << "\n" ;
    cout << "  Description: " << descreption << "\n" ;
    cout << "  --------------------------------------------------\n" ;
}

void Course::print_all_doctors ( )
{
    cout << "\n================== DOCTORS ==================\n" ;
    if ( UsertTable[0].size() > 0 )
    {
        cout << "Total Doctors for this Course: " << UsertTable[0].size() << "\n" ;
        cout << "----------------------------------------------\n" ;

        for ( const auto & [ name , ptr ] : UsertTable[0] )
        {
            if ( ptr != nullptr ) ptr->print_self( ) ;
        }
    }
    else 
    {
        cout << "No doctors assigned to this course.\n" ;
    }
    
    cout << "==============================================\n" ;
}

void Course::print_all_Students ( )
{
    cout << "\n================== STUDENTS ==================\n" ;
    if ( UsertTable[1].size() > 0 )
    {
        cout << "Total Students for this Course: " << UsertTable[1].size() << "\n" ;
        cout << "-----------------------------------------------\n" ;

        for ( const auto & [ name , ptr ] : UsertTable[1] )
        {
            if ( ptr != nullptr ) ptr->print_self( ) ;
        }
    }
    else 
    {
        cout << "No students enrolled in this course.\n" ;
    }
    
    cout << "===============================================\n" ;
}

void Course::print_all_Assignment ( User * user_ptr )
{
    cout << "\n================ ASSIGNMENTS ================\n" ;
    if ( AssignmentTable.size() > 0 )
    {
        cout << "Total Assignments for this Course: " << AssignmentTable.size() << "\n" ;
        cout << "----------------------------------------------\n" ;

        for ( const auto & [ id , ptr ] : AssignmentTable )
        {
            ptr->print_self( user_ptr ) ;
            cout << "----------------------------------------------\n" ;
        }
    }
    else 
    {
        cout << "No assignments available for this course.\n" ;
    }
    
    cout << "==============================================\n" ;
}


void Course::add_Assignment ( Assignment * ptr )
{
    if ( ptr == nullptr ) 
    {
        cout << "Error: Cannot add null assignment pointer.\n" ;
        return ;
    }
    
    AssignmentTable[ ptr->get_id() ] = ptr ;
} 

void Course::Print_Assignments ( )
{
    cout << "\n============== ASSIGNMENT LIST ==============\n" ;
    if ( AssignmentTable.empty() )
    {
        cout << "No assignments available for this course.\n" ;
    }
    else
    {
        for ( const auto & [ id , ptr ] : AssignmentTable )
        {
            cout << "ID: " << id << " | Question: " << ptr->get_question() << "\n" ;
            cout << "----------------------------------------------\n" ;
        }
    }
    cout << "==============================================\n" ;
}

void Course::Review_Assignments()
{
    Print_Assignments () ;
    
    int id = Assignment::read_id() ;
    Assignment::get_pointer( id )->menu() ;
}

void Course::add_User ( User * ptr )
{
    if ( ptr == nullptr ) 
    {
        cout << "Error: Cannot add null user pointer.\n" ;
        return ;
    }
    
    UsertTable[ ptr->get_type() - 1 ][ ptr->get_id() ] = ptr ;
    ptr->add_course( this ) ;
}

void Course::submit_assignment ( int user_id )
{
    print_all_Assignment() ;
    int id = Assignment::read_id(  ) ;

    Assignment * ptr = Assignment::get_pointer( id ) ;

    ptr->add_user_answer( user_id , read_string( "Enter Your Answer: " ) ) ;

    cout << "Assignment submitted successfully.\n" ;
}

void Course::delete_User ( User * ptr )
{
    UsertTable[ ptr->get_type() - 1 ].erase(  ptr->get_id() ) ;
    delete_User_Assignment( ptr ) ;
}

void Course::delete_User_Assignment ( User * ptr )
{
    for ( const auto & [ id , ptr_as ] : AssignmentTable )
    {
        ptr_as->delete_User( ptr ) ;
    }
}

Course::~Course()
{
    // Remove users from this course
    for ( const auto & [ id , ptr ] : UsertTable[0] )
        if ( ptr != nullptr ) ptr->delete_course( this->id ) ;
    for ( const auto & [ id , ptr ] : UsertTable[1] )
        if ( ptr != nullptr ) ptr->delete_course( this->id ) ;

    // Delete all assignments
    for ( const auto & [ id , ptr ] : AssignmentTable )
        delete ptr ;

    // Remove this course from CourseTable
    CourseTable.erase( this->id ) ;
}


void Course::Data_Base_Save ( ofstream & out )
{
    out << id_cnt << " " << CourseTable.size() << "\n" ;
    for ( const auto & [ id , ptr ] : CourseTable )
    {
        out << ptr->get_id() << "," ;
        out << ptr->get_creditHoure() << "," ;
        out << ptr->get_name() << "," ;
        out << ptr->get_code() << "," ;
        out << ptr->get_descreption() << "," ;
        
        out << ptr->UsertTable[0].size() << "\n" ;
        for ( const auto & [ user_id , user_ptr ] : ptr->UsertTable[0] )
        {
            out << user_id << "," ;
        }
        out << "\n" ;

        out << ptr->UsertTable[1].size() << "\n" ;
        for ( const auto & [ user_id , user_ptr ] : ptr->UsertTable[1] )
        {
            out << user_id << "," ;
        }
        out << "\n" ;

        out << ptr->AssignmentTable.size() << "\n" ;
        for ( const auto & [ assign_id , assign_ptr ] : ptr->AssignmentTable )
        {
            out << assign_id << "," ;
        }
        out << "\n" ;
    }
}

void Course::delete_all ()
{
    for ( const auto & [ id , ptr ] : CourseTable )
    {
        if ( ptr != nullptr ) delete ptr ;
    }
}

void Course::Data_Base_Load ( ifstream & in )
{
    delete_all () ;

    CourseTable.clear() ;

    int n ;
    in >> id_cnt >> n ;
    in.ignore() ;

    while ( n -- )
    {
        string id ; getline ( in , id , ',' ) ;
        string creditHoure ; getline ( in , creditHoure , ',' ) ;
        string name ; getline ( in , name , ',' ) ;
        string code ; getline ( in , code , ',' ) ;
        string descreption ; getline ( in , descreption , ',' ) ;

        Course * ptr = new Course ( name , code , descreption , stoi(creditHoure) , nullptr ) ;
        ptr->id = stoi(id) ;
        
        int m ; in >> m ;
        in.ignore() ;
        for ( int i = 0 ; i < m ; i ++ )
        {
            int temp ; in >> temp ;
            ptr->add_User( User::get_pointer( temp ) ) ;
        }
        
        in >> m ;
        in.ignore() ;
        for ( int i = 0 ; i < m ; i ++ )
        {
            int temp ; in >> temp ;
            ptr->add_User( User::get_pointer( temp ) ) ;
        }
        
        in >> m ;
        in.ignore() ;
        for ( int i = 0 ; i < m ; i ++ )
        {
            int temp ; in >> temp ;
            ptr->add_Assignment( Assignment::get_pointer( temp ) ) ;
        }
    }
}