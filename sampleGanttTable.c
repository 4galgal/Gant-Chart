#include <stdio.h>
#include <string.h>
#include "sampleGanttTable.h"
#include "input.h"
#include "display.h"
#include "menu.h"


//function that prints the sample table by initializing the struct with sample data and then calling the function printChart from display.h
int printSample(inputParameters *input) {


//copying the task names each individually- cannot assign an array of string all at once to the struct
    strcpy(input->tasks[0],"Planning");
    strcpy(input->tasks[1],"Research");
    strcpy(input->tasks[2],"Strategy");
    strcpy(input->tasks[3],"Design");
    strcpy(input->tasks[4],"Executive Meeting");
    strcpy(input->tasks[5],"Cash flow analysis");
    strcpy(input->tasks[6],"Raise Investors");
    strcpy(input->tasks[7],"General Meeting");
    strcpy(input->tasks[8],"Implementation");
    strcpy(input->tasks[9],"Execution");

//Initialising all the sample months - using the struct start and end month
    input->startMonth[0]=1;
    input->endMonth[0]=2;
    input->startMonth[1]=2;
    input->endMonth[1]=4;
    input->startMonth[2]=3;
    input->endMonth[2]=5;
    input->startMonth[3]=4;
    input->endMonth[3]=8;
    input->startMonth[4]=6;
    input->endMonth[4]=8;
    input->startMonth[5]=7;
    input->endMonth[5]=9;
    input->startMonth[6]=8;
    input->endMonth[6]=10;
    input->startMonth[7]=8;
    input->endMonth[7]=11;
    input->startMonth[8]=9;
    input->endMonth[8]=11;
    input->startMonth[9]=10;
    input->endMonth[9]=12;


    //initializing all the dependencies to 0
    for (int i=0;i<10;i++) {
        for (int j=0;j<10;j++) {
            input->dependencies[i][j]=0;
        }
    }
//initializing a sample flag array of the dependencies
    input->dependencies[1][0]=1;
    input->dependencies[2][1]=1;
    input->dependencies[3][2]=1;
    input->dependencies[5][3]=1;
    input->dependencies[6][3]=1;
    input->dependencies[6][5]=1;
    input->dependencies[7][6]=1;
    input->dependencies[9][7]=1;


    //printing sample chart with sample data
    printChart( input,10);


    return 0;


}

