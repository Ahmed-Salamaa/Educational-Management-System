#include "include/user.h"
#include "include/course.h"
#include "include/assignment.h"


    map < int , User * > User::UserTable ;
    int User::id_cnt = 1'000'000'0 ;

User::User ( const string & username , const string & password , const string & email , const string & name , const int & type )
{
    this->username = username ;
    this->password = hash_string ( password ) ;
    this->email = email ;
    this->type = type ;
    this->id = id_cnt ++ ;
    change_name ( name ) ;

    UserTable[this->id] = this ;
}

int User::read_id ()
{
    int id ;
    while ( true )
    {
        id = read_int ( "Enter Your ID : " ) ;
        if ( id == -1 ) return -1 ;
        if ( User::used_id( id ) ) break;
        cout << "Invaild ID. Please try again.\n" ;
    }
    return id ;
}

const string & User::get_username () { return username ; }

const string & User::get_email () { return email ; }

const vector < string > & User::get_name () { return name ; }

const int & User::get_id () { return this->id ; }

void User::change_username ( const string & username )
{ 
    UserTable.erase( this->id ) ;
    UserTable[id] = this ;
}

int User::get_type() { return type ; }

void User::change_password ( const string & password ) { this->password = hash_string ( password ) ; }

void User::change_email ( const string & email ) { this->email = email ; }

void User::change_name ( const string & name )
{
    vector < string > arr ;

    stringstream ss (name) ;

    string curr ;
    while ( ss >> curr ) arr.push_back( curr ) ;

    this->name = arr ;
}

bool User::used_id ( int id ) { return ( UserTable.find( id ) != UserTable.end() ) ; }

User * User::get_pointer ( int id )
{
    if ( used_id ( id ) ) return UserTable[ id ] ;
    else return nullptr ;
}

void User::add_course ( Course * ptr )
{
    CourseTable[ ptr->get_id() ] = ptr ;
}

void User::print_my_course ()
{
    for ( const auto & [ name , ptr ] : CourseTable ) 
        ptr->print_curr_course() ;
}


void User::print_my_Assignment ()
{
    for ( const auto & [ id , ptr ] : AssignmentTable[0] )
    {
        ptr->print_self( this ) ;   
    }
}

void User::Assignment_Report ( Course * Course_ptr )
{
    int user_degree = 0 , Totall = 0 ;
    for ( auto & [ id , ptr ] : AssignmentTable[0] )
    {
        if ( Course_ptr->get_id() != ptr->get_course_id() ) continue;
        cout << "Assignment ID : " << ptr->get_id() << " , Assignment Degree : " << ptr->get_user_degree( get_id() ) << " / " << ptr->get_degree() << "\n" ;
        user_degree += ptr->get_user_degree( get_id() ) ;
        Totall += ptr->get_degree() ;
    }

    for ( auto & [ id , ptr ] : AssignmentTable[1] )
    {
        if ( Course_ptr->get_id() != ptr->get_course_id() ) continue;
        cout << "Assignment ID : " << ptr->get_id() << " , Assignment Degree : " << ptr->get_user_degree( get_id() ) << " / " << ptr->get_degree() << "\n" ;
        user_degree += ptr->get_user_degree( get_id() ) ;
        Totall += ptr->get_degree() ;
    }

    cout << "Course Degree : " << user_degree << " / " << Totall << "\n" ;
}


bool User::login ( string pass ) { return hash_string ( pass ) == this->password ; }

void User::register_course ()
{
    int id = Course::read_id() ;
    if ( id == -1 ) return ;

    Course * ptr = Course::get_pointer( id ) ;
    CourseTable[ ptr->get_id() ] = ptr ;

    ptr->add_User( this ) ;
}

void User::delete_course ( int id )
{
    CourseTable.erase( id ) ;
}

void User::delete_Assignment ( int id )
{
    AssignmentTable[0].erase( id ) ;
    AssignmentTable[1].erase( id ) ;
}

void User::print_all_User ( )
{
    cout << "\n==================== USERS ====================\n" ;
    cout << "There are " << UserTable.size() << " User(s) in the system.\n" ;

    for ( const auto & [ name , ptr ] : UserTable )
        ptr->print_self( ) ;
    
    cout << "================================================\n\n" ;
}

void User::print_self ( )
{
    cout << "  User: " << username << " | ID: " << id << " | Type: " << ( type ? "Student" : "Doctor" ) << "\n" ;
    cout << "  Name: " << name << " | Email: " << email << "\n" ;
}

User::~User ()
{
    for ( const auto & [ id , ptr ] : CourseTable )
    {
        ptr->delete_User( this ) ;
    }

    for ( const auto & [ id , ptr ] : AssignmentTable[0] )
    {
        ptr->delete_User( this ) ;
    }

    for ( const auto & [ id , ptr ] : AssignmentTable[1] )
    {
        ptr->delete_User( this ) ;
    }

    UserTable.erase( id ) ;

}