#ifndef TEST_H
#define TEST_H
#include <stdbool.h>
#include <stdio.h>
#include "input.h"


void testTask(inputParameters *input);

int findTask(inputParameters *input, int *index);

bool circular(inputParameters *input, int depArray[10], int task, int count);

#endif