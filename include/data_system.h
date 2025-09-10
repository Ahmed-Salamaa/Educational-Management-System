#ifndef DATA_SYSTEM
#define DATA_SYSTEM

    #include "include/help_fun.h"



    #ifdef _WIN32
        const std::string PATH = "system_files\\user";
    #elif __linux__
        const std::string PATH = "system_files/user";
    #elif __APPLE__
        const std::string PATH = "system_files/user";
    #else
        const std::string PATH = "system_files/user";
    #endif

#endif