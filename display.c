#include <stdio.h>
#include "input.h"


// This prints a line of exactly 185 dashes (can be changed)
void print_line() {
    for (int i = 0; i < 185; i++) {
        printf("-");
    }
    printf("\n");
}


void print_rows(inputParameters *input, int taskCount) {
    // Printing all the Rows
    for (int row = 0; row < taskCount; row++) {
        printf("| %-22s |", input->tasks[row]);

        for (int month = 1; month < 13; month++)  {
            if (input->startMonth[row] <= month && input->endMonth[row] >= month)  {
                // By using the same %-9s, it should match the header
                printf(" %-9s |", "   XXX");
            } else {
                printf(" %-9s |", "");
            }
        }

        //need to add dependencies [i][j]
        for (int j=0; j<10; j++) {
            if (input->dependencies[row][j] == 1) {
                printf(" %d ", j+1);
            }
        }
        printf("\n");
        print_line();

    }

}



void printChart( inputParameters *input, int taskCount) {


    // A pointer array to string each is a month that will be displayed as a heading in the gantt chart
    char *months[] = {
        "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
        };


    // --- PRINTING THE TABLE ---
    // For the top border
    print_line();

    // For top header
    // | are the vertical bars, - tells C to push the text all the way to the left side, 22 makes the box 22 spaces wide, s is the string (text)
    printf("| %-22s |", "");
    for (int i = 0; i < 12; i++) {
        printf(" %-9s |", months[i]);
    }

    printf(" %-12s |\n", "Dependencies");
    print_line();


    print_rows(input, taskCount);




    }




