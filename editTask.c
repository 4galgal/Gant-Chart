#include <stdio.h>
#include <strings.h>
#include "input.h"
#include "editTask.h"
#include "test.h" //using the function findTask declared in test.h


void editTask(inputParameters *input, int taskCount) {


    int index=-1; //used to find what tasks in input->tasks we want to edit
    printf("enter the task name you wish to edit: \n");

    //A function that takes in input of task name and finds if this task exists in the gantt chart, if it is it returns the index of the task in the array of all the tasks
   //The function findTask reutrns 0 if the task was found - if it is then we take new input
    if ( findTask(input, &index)==0) {
       //need to clear newline character before using fgets- otherwise interferes with reading
       int c;
       while ((c = getchar()) != '\n' && c != EOF);

       //need Turn into smaller functions - took this from input.c if we can split input.c into functions
       printf("Enter a new task name\n");
       if (! fgets(input->tasks[index], 80, stdin)) {
           printf("Error reading input");
           return;
       }

       if (strcmp(input->tasks[index], "\n")==0) {
           printf("No task entered, edit cancelled\n");
           return;
       }
       input->tasks[index][strcspn(input->tasks[index], "\n")] = '\0';

       inputMonths(input, index);

       //initialise the dependencies of the new task to 0
       for (int j=0; j<10; j++) {
           input->dependencies[index][j]=0;
       }
       //function that takes in the dependencies of a task
       inputDependencies(input,index, taskCount);
   }


}