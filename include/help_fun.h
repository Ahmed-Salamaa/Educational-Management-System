#ifndef HELP_FUNCTION
#define HELP_FUNCTION

#include "include/picosha2.h"

#include <regex>
#include <iostream>
#include <string>
#include <sstream> 
#include <vector>
#include <map>
#include <set>
#include <limits>
#include <stdexcept>
#include <cctype>
using namespace std;

ostream& operator << (ostream &out, const vector < string > &v) ;

class User ;

string hash_string ( const string & password ) ;
bool vaild_email ( const string & email ) ;
bool vaild_name ( const string & name ) ;

string read_string () ;
string read_string ( const string& prompt ) ;

int read_int () ;
int read_int ( int min_ , int max_ ) ;
int read_int ( const string& prompt ) ;
int read_int ( const string& prompt , int min_ , int max_ ) ;

string read_username () ;
string read_password () ;
string read_email () ;
string read_name () ;
int read_type () ;
int read_id () ;

string read_code () ;
string read_descreption () ;
int read_creditHoure () ;

int print_menu ( const vector <string> & menu ) ;



#endif