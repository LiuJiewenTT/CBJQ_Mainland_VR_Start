#include "program_info.hpp"
#include <stdio.h>
#include <locale>

#ifdef _WIN32 
#include <windows.h> 
#endif


int main() {
    #ifdef _WIN32 
    SetConsoleOutputCP(CP_UTF8); 
    #endif
    setlocale(LC_ALL, "C.UTF-8");
    printf("%s\n", PROGRAM_INFO_STRING);
    return 0;
}
