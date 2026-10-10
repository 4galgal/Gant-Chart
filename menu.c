#include <stdio.h>
#include "menu.h"
#include "editTask.h"
#include "display.h"

#include "sampleGanttTable.h"
#include "quit.h"
#include "test.h"


//A function that takes in the input of users choice and sets the enum int the corresponding status
//The function will return a pointer enum type that contains the choice of the user
void menuInput( enum MenuChoice *current_choice);


void show_menu(inputParameters *input, int taskCount) {

    // Menu Setup
    char user_choice[50]; // A blank space to hold the word the user types

    // An endless loop so the menu keeps asking until user chooses "quit"
    while (1) {

        //Assume the value of current choice is always unknown unless entered a valid operation
        enum MenuChoice current_choice=UNKNOWN;

        printf("\nIf you wish to edit the Gantt, please type 'edit' / If you wish to run a test, type 'test' / If you wish to display the chart, type 'display' / If you wish to exit, type 'quit' and then press enter to execute your option.\n");
        printf("Your choice: ");

        //Function that takes in the user input
        menuInput( &current_choice);

        switch (current_choice) {
            case EDIT:  //if the user chose edit task then the function to edit a task is called
                editTask(input, taskCount);
                break;
            case TEST:  //If the user chose to test a task then the testTask function is called
                testTask(input);
                break;
            case DISPLAY: //if user chose the display function then we print the gantt chart
                printChart(input, taskCount);
                break;
            case QUIT: //If the user chose quit then the program terminates
                quit_program();

                break;
            case UNKNOWN:  //if no valid operation was entered by the user the status remains unknown and will print a message
                printf("Sorry, I did not recognize that command.\n");
                break;

        }

        }
    }





void menuInput( enum MenuChoice *current_choice ) {

    //An array to contain the users choice input
    char user_choice[50];

    // Read what the user types using fgets
    if (fgets(user_choice, 50, stdin) != NULL) {

        //remove newline character which stays at the end - cannot compare the words otherwise
        user_choice[strcspn(user_choice, "\n")] = '\0';

        //Check the word entered by the user using strcmp and change the status of the enum current_choice
        if (strcasecmp(user_choice, "edit") == 0) {
            *current_choice = EDIT;
        }
        else if (strcasecmp(user_choice, "test") == 0) {
            *current_choice = TEST;
        }
        else if (strcasecmp(user_choice, "display") == 0) {
            *current_choice = DISPLAY;
        }
        else if (strcasecmp(user_choice, "quit") == 0) {
            *current_choice = QUIT;
        }
    }
}




