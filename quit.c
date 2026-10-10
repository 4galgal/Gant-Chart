// Should clear the screen whenever the user types in 'quit'

#include <stdio.h>
#include <stdlib.h>

void quit_program() {
    // #ifdef is a preprocessor directive that checks the operating system at compile time
    // If the computer is a Windows machine
    #ifdef _WIN32
        system("cls");
    #else //if not windows
        system("clear");
    #endif

    // Shut down the program - terminates
    //exit(0) terminates the entire program immediately from any position in the call stack - no need to return to main first
    exit(0);
}
