#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <string.h>


typedef struct{
    char tasks[10][80];
    int startMonth[10];
    int endMonth[10];
    int dependencies[10][10]; //for storing the dependencies- can have 5(?) dependencies each stores the number of task it is dependent on


} inputParameters;



void inputMonths(inputParameters *input, int i);

void inputDependencies(inputParameters *input, int i, int taskCount);

void takeInput(inputParameters *input, int *taskCount) ;


#endif