#ifndef MENU_H
#define MENU_H

#include "input.h"
#include "display.h"
#include "editTask.h"
#include "sampleGanttTable.h"
#include "test.h"


void show_menu(inputParameters *input, int taskCount) ;

enum MenuChoice {
    EDIT = 1,   //to edit a task
    TEST ,      //to test a task
    DISPLAY ,    //to display the chart
    QUIT ,      //to quit the program - clear the screen
    UNKNOWN
};


#endif

