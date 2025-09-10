#include "include/help_fun.h"

// Define regex patterns
regex Email_templete ( R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)" ) ;
regex Name_templete ( R"(^[A-Za-z]+(?:\s+[A-Za-z]+)+$)" ) ;

ostream& operator << (ostream &out, const vector < string > &v) { 
    for (const auto &x : v) out << x << ' '; 
    return out;
}

string hash_string ( const string & password ) { return picosha2::hash256_hex_string( password ) ; }

bool vaild_email ( const string & email )
{
    return regex_match ( email , Email_templete ) ;
}

bool vaild_name ( const string & name )
{
    return regex_match ( name , Name_templete ) ;
}

string read_string ()
{
    string temp ;
    
    while ( true )
    {
        getline( cin , temp ) ;
        if ( !temp.empty() ) return temp ;

        cout << "Invalid input. Please enter a valid string.\n" ;
    }
    return temp ;
}


int read_int ()
{
    string temp ;
    int value;
    
    while ( true )
    {
        cin >> temp ;
        
        // Clear the input buffer after reading
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        try {
            // Check if string represents a valid integer
            bool good = true;
            if (temp.empty()) good = false;
            else 
            {
                int start = 0;
                if (temp[0] == '-' || temp[0] == '+')
                {
                    if (temp.length() == 1) good = false;
                    else start = 1;
                }
                
                for (int i = start; i < temp.length() && good; i++)
                    if (!isdigit(temp[i])) good = false;
            }
            
            if (good) {
                value = stoi(temp);
                return value;
            }
        } catch (const exception& e) {
            // stoi failed
        }
        
        cout << "Invalid integer value. Please try again: " ;
    }
}

string read_string ( const string& prompt )
{
    cout << prompt ;
    return read_string() ;
}

int read_int ( int min_ , int max_ )
{
    int temp = read_int() ;

    while ( !( min_ <= temp && temp <= max_ ) )
    {
        cout << "The number must be in range [" << min_ << ", " << max_ << "]. Please try again.\n" ;
        temp = read_int() ;
    }
    
    return temp ;
}

int read_int ( const string& prompt )
{
    cout << prompt ;
    return read_int() ;
}

int read_int ( const string& prompt , int min_ , int max_ )
{
    cout << prompt ;
    return read_int( min_ , max_ ) ;
}

string read_username () 
{
    string username ;
    while ( true )
    {
        username = read_string( "Enter Username (-1 to exit): " ) ;
        if ( username == "-1" ) return "" ;
        if ( !username.empty() ) return username;
        cout << "Username cannot be empty. Please try again.\n";
    }
}
string read_password () 
{
    string password ;
    while ( true )
    {
        password = read_string( "Enter Password (-1 to exit): " ) ;
        if ( password == "-1" ) return "" ;
        if ( !password.empty() ) return password;
        cout << "Password cannot be empty. Please try again.\n";
    }
}

string read_email ()
{
    string email ;
    while ( true )
    {
        email = read_string( "Enter Email (-1 to exit): " ) ;
        if ( email == "-1" ) return "" ;
        if ( vaild_email ( email ) ) return email ;
        cout << "Incorrect Email format. Please try again.\n" ;
    }
}

string read_name ()
{
    string name ;
    while ( true )
    {
        name = read_string( "Enter Name (-1 to exit): " ) ;
        if ( name == "-1" ) return "" ;
        if ( vaild_name ( name ) ) return name ;
        cout << "Invalid Name format. Name should contain at least two words with letters only.\n" ;
    }
}

int read_type ()
{
    int type ;
    type = read_int ( "Enter Your Type (Doctor: 1, Student: 2, Exit: 0): " , 0 , 2 ) ;
    return type ;
}

string read_code () 
{
    string code ;
    code = read_string( "Enter The Code (-1 to exit): " ) ;
    if ( code == "-1" ) return "" ;
    return code ;
}

string read_descreption ()
{
    string desc ;
    desc = read_string( "Enter The Description (-1 to exit): " ) ;
    if ( desc == "-1" ) return "" ;
    return desc ;
}

int read_creditHoure ()
{
    int hours ;
    hours = read_int( "Enter The Credit Hours (1-10): " , 1 , 10 ) ;
    return hours ;
}

int print_menu ( const vector <string> & menu )
{
    cout << "\n=============== MENU ===============\n" ;
    int n = menu.size() ;
    for ( int i = 0 ; i < n ; i++ ) 
        cout << "\t" << i + 1 << ". " << menu[i] << "\n" ;
    cout << "============\n" ;
        return read_int( "Select your operation: " , 1 , n ) ;
}
