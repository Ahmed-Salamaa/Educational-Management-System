#include "include/user.h"
#include "include/course.h"
#include "include/assignment.h"


    map < int , User * > User::UserTable ;
    int User::id_cnt = 1'000'000'0 ;

User::User ( const string & username , const string & password , const string & email , const string & name , const int & type , int id )
{
    this->username = username ;
    this->password = hash_string ( password ) ;
    this->email = email ;
    this->type = type ;

    if ( id != -1 ) this->id = id ;
    else this->id = id_cnt ++ ;
    
    change_name ( name ) ;

    UserTable[this->id] = this ;
}

int User::read_id ()
{
    int id ;
    while ( true )
    {
        id = read_int ( "Enter Your ID: " ) ;
        if ( id == -1 ) return -1 ;
        if ( User::used_id( id ) ) break;
        cout << "Invalid ID. Please try again.\n" ;
    }
    return id ;
}

const string & User::get_username () { return username ; }

const string & User::get_email () { return email ; }

const string & User::get_password () { return password ; }

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
    cout << "\n=============== MY COURSES ===============\n" ;
    if ( CourseTable.empty() )
    {
        cout << "You are not enrolled in any courses.\n" ;
    }
    else
    {
        cout << "Total Enrolled Courses: " << CourseTable.size() << "\n" ;
        cout << "-------------------------------------------\n" ;
        for ( const auto & [ name , ptr ] : CourseTable ) 
            ptr->print_curr_course() ;
    }
    cout << "==========================================\n" ;
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
    cout << "\n============== ASSIGNMENT REPORT ==============\n" ;
    cout << "Course: " << Course_ptr->get_name() << " (" << Course_ptr->get_code() << ")\n" ;
    cout << "------------------------------------------------\n" ;
    
    int user_degree = 0 , Totall = 0 ;
    int assignment_count = 0 ;
    
    for ( auto & [ id , ptr ] : AssignmentTable[0] )
    {
        if ( Course_ptr->get_id() != ptr->get_course_id() ) continue;
        cout << "Assignment ID: " << ptr->get_id() << " | Score: " << ptr->get_user_degree( get_id() ) << " / " << ptr->get_degree() << "\n" ;
        user_degree += ptr->get_user_degree( get_id() ) ;
        Totall += ptr->get_degree() ;
        assignment_count++ ;
    }

    for ( auto & [ id , ptr ] : AssignmentTable[1] )
    {
        if ( Course_ptr->get_id() != ptr->get_course_id() ) continue;
        cout << "Assignment ID: " << ptr->get_id() << " | Score: " << ptr->get_user_degree( get_id() ) << " / " << ptr->get_degree() << "\n" ;
        user_degree += ptr->get_user_degree( get_id() ) ;
        Totall += ptr->get_degree() ;
        assignment_count++ ;
    }
    
    cout << "------------------------------------------------\n" ;
    if ( assignment_count > 0 ) {
        cout << "Total Course Score: " << user_degree << " / " << Totall ;
        cout << " (" << (double)user_degree/Totall*100 << "%)\n" ;
    } else {
        cout << "No assignments found for this course.\n" ;
    }
    cout << "===============================================\n" ;
}


bool User::login ( string pass ) { return hash_string ( pass ) == this->password ; }

void User::register_course ()
{
    int id = Course::read_id() ;
    if ( id == -1 ) return ;

    Course * ptr = Course::get_pointer( id ) ;
    CourseTable[ ptr->get_id() ] = ptr ;

    ptr->add_User( this ) ;
    cout << "Successfully registered for the course.\n" ;
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
    if ( UserTable.empty() )
    {
        cout << "No users in the system.\n" ;
    }
    else
    {
        cout << "Total Users in System: " << UserTable.size() << "\n" ;
        cout << "------------------------------------------------\n" ;

        for ( const auto & [ name , ptr ] : UserTable )
            ptr->print_self( ) ;
    }
    
    cout << "================================================\n\n" ;
}

void User::print_self ( )
{
    cout << "  User: " << username << " | ID: " << id << " | Type: " << ( type == 1 ? "Doctor" : "Student" ) << "\n" ;
    cout << "  Name: " ;
    for ( int i = 0 ; i < name.size() ; i++ ) {
        cout << name[i] ;
        if ( i < name.size() - 1 ) cout << " " ;
    }
    cout << " | Email: " << email << "\n" ;
    cout << "  --------------------------------------------------\n" ;
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

void User::Data_Base_Save ( ofstream & out )
{
    out << id_cnt << " " << UserTable.size() << "\n" ;
    for ( const auto & [ id , ptr ] : UserTable )
    {
        out << ptr->get_id() << "," ;
        out << ptr->get_email() << "," ;
        out << ptr->get_password() << "," ;
        for ( int i = 0 ; i < ptr->get_name().size() ; i ++ ) 
        {
            out << ptr->get_name()[i] ;
            if ( i < ptr->get_name().size() - 1 ) out << " " ;
        }
        out << "," ;
        out << ptr->get_type() << "," ;
        out << ptr->get_username() << "\n" ;
    }
}

void User::Data_Base_Load ( ifstream & in )
{
    for ( const auto & [ id , ptr ] : UserTable )
    {
        if ( ptr != nullptr ) delete ptr ;
    }

    UserTable.clear() ;

    int n ;
    in >> id_cnt >> n ;
    in.ignore() ;

    while ( n -- )
    {
        string id ; getline ( in , id , ',' ) ;
        string email ; getline ( in , email , ',' ) ;
        string password ; getline ( in , password , ',' ) ;
        string name ; getline ( in , name , ',' ) ; 
        string type ; getline ( in , type , ',' ) ; 
        string username ; getline ( in , username , '\n' ) ;

        User * ptr = new User ( username , "" , email , name , stoi( type ) , stoi( id ) ) ;
        ptr->password = password ;
    }
}


void User::delete_all ()
{
    for ( const auto & [ id , ptr ] : UserTable )
    {
        if ( ptr != nullptr ) delete ptr ;
    }
}