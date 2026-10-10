#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "input.h"



void takeInput(inputParameters *input, int *taskCount) {

    //collecting input tasks and their start month and end month
    //using fgets for the tasks because fgets read the space charcter
    //scanf is used to read start/end month since it only reads an integer

    *taskCount=0; //initialize the task count

    printf("Enter the number of tasks you want to enter (1-10):\n");
    scanf("%d", taskCount);

    //Validation that the task number is within the range allowed
    while (*taskCount<0 || *taskCount > 10) {
        printf("Number of tasks must be between 0 and 10\n");
    }

    for (int i=0; i<*taskCount; i++) {
        //Remove leftover new line charcter from scanf
        int c;
        while ((c = getchar()) != '\n' && c != EOF);  // flush before the while loop
        printf("Enter a task\n");
        if (! fgets(input->tasks[i], 80, stdin)) {
            break;
        }

        input->tasks[i][strcspn(input->tasks[i], "\n")] = '\0';

        //Do while loop to collect the start month of the task - only stops collecting when a valid input is entered
        //function that takes in start month and end month of task
        inputMonths(input, i);

        //function that takes in the dependencies of a task
        inputDependencies(input, i, *taskCount);
    }


}

void inputMonths(inputParameters *input, int i) {

    //Taking in the start month of the task
    do {
        printf("Enter the start month of the task:\n");
        scanf("%d", &input->startMonth[i]);
        //printing a message if invalid month was entered
        if (input->startMonth[i] < 1 || input->startMonth[i] > 12 ){
            printf("Invalid month entered\n");
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // remove new line character, removing inside the loop incase it loops around and then the new character is still in the consule- will result in enless loop if the \n is not removed first
    }while (input->startMonth[i] < 1 || input->startMonth[i] > 12 ) ; //a do while loop to keep collecting the start month if it is not a valid month


    //Do while loop to collect the end month of the task - only stops collecting when a valid end month input is entered
    do {
        printf("Enter the end month of the task:\n");
        scanf("%d", &input->endMonth[i]);
        //printing a message if invalid month was entered
        if (input->endMonth[i] < 1 || input->endMonth[i] > 12 || input->endMonth[i] < input->startMonth[i]) {
            printf("Invalid month entered\n");
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // removing left over newline character
    }while (input->endMonth[i] < 1 || input->endMonth[i] > 12 || input->endMonth[i] < input->startMonth[i]); //if the end month is before the start month then the loop will continue taking input of end month (another approach can be to swap the start the end month in such case- up to decision)do



}

//A function that takes all the dependencies as input

void inputDependencies(inputParameters *input, int i, int taskCount) {

    //initializing all the dependencies- to create a flag array
    for (int j=0; j<10; j++) {
        input->dependencies[i][j]=0;
    }

    //initializing a variable that saves the number of dependencies the task has so that the user can enter this number of dependencies in the for loop later on
    int numOfDependencies;
    //entering how many dependencies the task has
    do{
        printf("Enter how many dependencies this task has:\n");
        scanf("%d", &numOfDependencies);
        int c;
        while ((c = getchar()) != '\n' && c != EOF); //Clearing new line character after using fgets
    }while (numOfDependencies<0 || numOfDependencies> taskCount-1); //if the number of dependencies is greater than the number of tasks keep running the while loop, greater than taskCount-1 becuase we are not including the task itself

    //a loop that collects the number of dependencies entered previously by the user
    for (int j=0; j< numOfDependencies; j++) {
        int task;
        do {
            printf("Enter a dependent task:\n");
            scanf("%d", &task);
            int c;
            while ((c = getchar()) != '\n' && c != EOF); //Clearing new line character after using fgets
            //printing a message for the user if the task is not valid
            if (task<1 || task> taskCount || task == i +1) {
                printf("Invalid task entered\n");
            }
        }while (task<1 || task> taskCount || task == i +1); //A do while loop that ensures the task is within the tasks range and it is not dependent on itself
        //in the position of the task -1 (because the array starts from 0) we set the dependency to 1

        input->dependencies[i][task-1] = 1;   //creating a flag array for all the dependencies

    }

}