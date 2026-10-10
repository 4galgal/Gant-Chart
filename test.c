#include <stdio.h>
#include "input.h"
#include "test.h"
#include <stdbool.h>



void testTask(inputParameters *input) {

    //sequenceArray is an array to store each possible path of tasks - used to track circular depencies
    int sequenceArray[10]={0};
    //index is use in the function that find the task - store the index of the task we are testing
    int index;
    printf("enter task you want to test for circular dependency: \n");
    //a function that finds which the task index based on the input given - takes in name of task as input and find the task in the struct
    //The function returns 0 if the task was found - if it was then we check for circular dependency of that task
    //If the function does not return 0 it means either the input wasnt read or the task not found, The function prints a message alerting the user and we do not check for circular dependency -> go back to menu
    if (findTask(input, &index) ==0) {
        sequenceArray[0]=index; //initializing the first task in the path to be the task found by taking in the input

        //Checking for circular dependency and if it is found then printing its found
        if (circular(input, sequenceArray, index, 1)) {
            printf("Circular Dependency found");
        } //count starts from 1 because already adding a task in arr[0]
        else {
            printf("No circular dependency found");
        }
    }

}



bool circular(inputParameters *input, int sequenceArray[10], int task, int count) {


    //have the task now need to check for circular dependencies
    //need to have a recursive function - goes to previous dependent task and so on

    //find dependencies of the task
    //a loop that goes through all flag array of the dependencies for that task
    for (int i=0; i<10; i++) {

        //If a dependency in the flag array of a specific struct is 1 it means the dependency exists for that task
        if (input->dependencies[task][i]== 1) {

            for (int j=0; j<count; j++) { //checking the path if I is already found in the sequence-> circular dependency
                if (sequenceArray[j]==i) {
                    //need to print out all the sequence before returning true
                    for (int k=0; k<count; k++) {
                        printf("%s -> ", input->tasks[sequenceArray[k]]);
                    }
                    printf("%s\n", input->tasks[sequenceArray[0]]);
                    return true;
                }
            }
            //creating a local copy of the sequence array that we can pass into circular to track the path (because cannot copy an array so need to create a local array)
            //creating a local path for this branch
            int localSequence[10];
            for (int x = 0; x < count; x++) {
                localSequence[x] = sequenceArray[x];  // copy existing path
            }

            //if no circular dependency found for that task then we add the task into the path
            localSequence[count] = i;  // add new task to this branch's copy

            //Copying sequence array into new array to pass to circular - recursion
            //This way all the possible paths are checked by passing all the path and adding new tasks to each path
            //Each time a circular dependency is checked is the same task is repeated twice in that specific path
            if (circular(input, localSequence, i, count+1)) {
                return true;
            }

        }
        }

//if no cycle was found return false
    return false;

}




//The function returns 0 is the task was read correctly from the consule and was found in the task array
//if the task wasnt found or the input was not read then the function will return 1;
//this function is also used in editTask.c to take in users input and find the task entered
int findTask(inputParameters *input, int *index) {

    //creating an array to store the name of the task we are looking for
    char oldTask[30];
    //Checking if nothing is read from the consule
    if (! fgets(oldTask, 80, stdin)) {
        printf("Error reading input");
        return 1;
    }
    //index is initialized to -1 so that if the task was not found we can print a message
    *index= -1; //used to find what tasks in input->tasks we want to edit
    //removing the new line charcter from the input received so we could compare with the task names in the strcut
    oldTask[strcspn(oldTask, "\n")] = '\0';

    //Searching through the task until the task is found and then saving the index of the task
    for (int i=0; i<10; i++) {
        if ((strcmp(oldTask, input->tasks[i]))==0) {
            *index=i;
            return 0;
        }
    }

    //if no task was entered printing a message that the edit was cancelled
    if (strcmp(oldTask, "\n")==0) {
        printf("No task entered, edit cancelled\n");
        return 1;
    }
    //If no task is found the index remains -1 and can print that the task wasnt found
    if (*index == -1) {
        printf("Task not found\n");
        return 1;
    }

    return 0;

}