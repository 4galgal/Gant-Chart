# Gant-Chart
Overview:
The program offers the user to either display a sample gantt chart or create its own, a struct
called inputParameters is used to store all the tasks and its corresponding months and
dependencies. After the chart is printed in the console the users menu is displayed in which
the user can perform operations on the gantt chart such as editing a task, testing for the
tasks circular dependency, displaying the chart, and quitting the program which clears the
screen.
Data Structures:
Struct
The struct is used to store all the tasks with their corresponding start and months and
dependencies.
To store the tasks the struct contains a two dimensional array that stores the name of each
task.
Two int arrays are used in the struct to store the start and end months of each task, they are
stored at the same index in the array as the task they belong to.
To store the dependencies:
The struct contains a two dimensional array for dependencies that is used as a flag array.
First the user inputs how many dependencies the task has and then the user enters the
dependent tasks. The dependencies array is initialized to 0, and the dependent tasks
changes the flag array to 1 at the position of the task-1.
If a dependent task is 3 for example then dependencies[taskNumber][2]=1 (because the flag
array starts from 0, so the index of dependent task -1 will be initialized to 1 as an indication
that this task is part of the dependencies of another task).
typedef struct{
char tasks[10][80];
int startMonth[10];
int endMonth[10];
int dependencies[10][10];
} inputParameters;
The struct below is in ‘input.h’
, and it holds separate lists for different types of information:
‘tasks’ for the names,
‘startMonth’
‘endMonth’
,
, and ‘dependencies’ for the actual tasks.The
programme should map all the data together by giving every single piece of information
about a single task the exact same slot number.
So when the user enters their first task, the programme uses the number ‘0’
. The name will
be saved to input->tasks[0], the start month to input->startMonth[0], the end month to
input->endMonth[0], number of dependencies to input->numDep[0] and the dependencies to
input->dependencies[0]. This way, the programme can easily pull the full profile of the task
just by asking for slot 0.
Enum
We are using enum type for the menu. The enum type contains 5 values. For editing a task,
testing a task, displaying a task, quitting the program and the default value which is
unknown.
enum MenuChoice {
EDIT = 1, TEST , DISPLAY , QUIT , UNKNOWN
//to edit a task
//to test a task
//to display the chart
//to quit the program- clear the screen
};
The value of the enum changes based on the user's choice when entering an operation.
After the user enters an operation the current
_
choice variable which is an enum type is
changed according to the operation requested by the user. Afterwards the value of the
current
choice is checked in a switch case to determine which function to call. The enum
_
type is declared in menu.h and used in menu.c as the menu calls all the operations
requested by the user according to the status of current
choice.
_
This helps keep the code easy to read and use enum type to keep a clear status on what
operation is requested by the user.
Taking input
The input is handled in input.c / input.h
The input entered by the user when creating their own gantt chart is stored in the struct
inputParameters.
takeInput
This function uses two helper function inputMonths and inputDependencies to take in all the
tasks from the user.
First the user needs to enter the number of tasks they wish to have in the gantt chart. Then
the program collects that amount of tasks from the user using a for loop which keeps
collecting until the number of tasks specified by the user were collected. The names of the
tasks are collected using fgets to read the space characters.
After the task name was read the function calls inputMonths and inputDependencies .
inputMonths
The function takes in the input start month and end month of a given task, it is using scanf to
take in an integer. There are two do while loops one for taking in the start month and the
other for the end month. We are using do while loops for validation to ensure that the start
and end months are valid- within the interval 1-13 which is the equivalent of
January-December. For the end month we are also validating that it is greater or equal to the
start month. If an invalid month was entered then the program prints a message informing
the user that the month is invalid and keep collecting a month repeating the process.
inputDependencies
First the flag array of dependencies for that task is initialized to 0.
To take in the dependencies first the user enters the number of dependencies the task has
this is done by using scanf, and it is inside a do while loop to ensure that the number of
dependencies this task has is not greater than the number of tasks -1 (because a task
cannot be dependent on itself in the program).Then the program collects this number of
dependencies.
To collect the dependencies a do while loop is used to ensure that the task number is not
less than 1 which is the first task, not greater than the taskCount while is the last task, and
that the dependency is not the same as the task that is dependent on it (task is not
dependent on itself). Once a valid dependency was entered the flag array is initialised to 1 at
the position of that task given as a dependency -1 (since the array starts at 0 the order is
shifted).
The way we initialize the flag array: input->dependencies[task][dependencyTask-1]=1
Displaying Gantt chart
printChart
The function is using 2 helper functions print
_
line and print
rows
_
The function starts by printing the top border and laying out the headers. It prints a blank
space for the task names, and to print the month we created a pointer array to store all the
months names, we are using a for loop to print each month a 22 spaces wide section, and
another header is for the dependencies.
The function then calls the function print
_
rows that prints all the rows of the chart.
Print
line
_
Function that is used to print a line and the borders of the gantt chart, through a for loop that
prints a dash consistently.
Print
rows
_
The function uses the input from the struct that contains all the tasks and prints the rows
according to the appropriate months.
The task data is then passed to print
_
rows ,which goes through the task one by one in a for
loop that runs the number of tasks given by the user.
For each task, the code counts from 1 to 12 and checks if the current month number falls
between the task’s starting month and ending month. If the month fits within the timeframe, it
will print ‘XXX’ to represent work being done. If the month doesn’t fit, it will print an empty
space.
To print the dependencies of a task a for loop is used to iterate through the dependencies
flag array of the each task at a time, and if 1 is found in the array then we print the index of it
+1 (since the flag array is shifted starting from 0, when given task 1 it will be the first element
of the array which is [0] so to print the first task we need index+1), we print it underneath the
dependencies header.
Then, it prints another line of dashes to close the row and moves on to the next task.
Sample gantt chart
To create the sample gantt chart the struct is initialized with sample data in gantChart, the
struct is passed as an argument into the function printSample inside the file
sampleGanttChart.c, all the tasks, their months and dependencies are manually defined
sample data. After the struct is initialized the function calls the function printChart which is in
display.c and the function displays the gantt chart with the data that was previously stored in
the struct.
Menu
The menu is used to offer the user to perform an operation on the gantt chart.
The menu is displayed in an endless loop until the user chooses quit which
terminates the program and clears the screen.
The menu uses an enum type variable called current_choice, first the status of
current_choice is updated according to the user's choice and then the status is
checked using a switch case. The status can be edit, test, display, quit or unknown
and based on it, the menu will call a function for each status of the current_choice.
show_menu
The function show menu defines a variable called current_choice to be an enum type
MenuChoice. Then the function runs in an endless loop calling the function
menu_input which takes in users input and sets the value of current_choice
according to the input. Then based on the value of current_choice a switch case is
used to call a function that corresponds to current_choice.
If the user entered edit then the function editTask is called, if the user entered test
then the function testTask is called, if the function entered display the function
printChart is called which prints the Gantt chart, if the user entered quit the function
quit_program is called which clears the screen and terminates the program. If none
of the above was entered then the value current_choice remains unknown (which is
the default value) and a message is printed that the command was not recognized.
After each function or message the process keeps repeating and the menu
continues asking the user to enter an operation and then calling the functions.
menu_input
menu_input takes in the users input and checks if the input is any valid operation
(edit, test, display, quit) if it is then the value of current_choice changes
correspondingly. The current_choice can be used in the function show_menu as it
contains the value entered by the user.
The purpose of menu_input function is to take input from the user and check if it is a
request that can be performed, if it is the current_choices changes value to the
status of the users request.
Edit Tasks
The function editTask is used to edit the task.
First the function calls findTask (A function that is declared in test.h and used in both test.c
and editTask.c), which collects input from the user of the previous task name they wish to
change and then uses the variable index to find the position of the task in the struct. The
task name is compared with each task name in the array tasks[][] inside the struct that stores
all the structs, using strcmp which compares the two strings. After the task is found the
variable index is set to the current position in the array.
Then a new task name is entered by the user in the editTask function, the input is read using
fgets to read spaces, the new task is added into the struct with all the tasks and replaces the
one entered by the user.
The index is used in the function editTask to take new input into the array in the position of
the old task. To collect the months of that task we use the index of the task in the array to
collect the months of the task again. This will replace the old task name and months by the
new ones taken as input.
The dependency array of that task is first initialized to 0 and then the dependent tasks are
taken as input, the flag array is then changed to 1 in the corresponding dependencies.
It is the same process as taking in input from the user when creating a gantt only first the
task the user wishes to change needs to be found and then it can be modified.
Testing circular Dependency
testTask:
The function test task is used to test for circular dependency. It calls two functions: findTask
which finds the task that is to be tested, and circular which is a recursive function that checks
for circular dependencies. The function prints a message if a circular dependency was found
(if the function circular returns true then it means the circular dependency was found, if it
returns false then it wasn't found).
findTask:
A function that is used to collect the input of the task that the user wants to test, it finds the
position of the task in the tasks array by comparing each task with the name entered by the
user, when the task is found the index of the task in the array is stored in the variable called
index, and now the dependencies of the task the user entered can be found since the task
was found in the struct.
Circular:
A boolean function that returns true if a circular dependency is found or false if it is not
found.
the function takes in:
the struct with the tasks and dependencies stored in it, an array that stores the path
sequence of the tasks dependent on each other, this array is used to store each task name
each time the function is called again, creating a path of all the dependent tasks. The array
is used to check for circular dependencies by checking if a task already appears in the path
and if it does then this leads to circular recursion, since the same task cannot appear twice
in the same path without causing a loop.
A task index which is the position of the task in the tasks array. This is the position of the
task that has its dependencies tested, we need to know what task we are testing each time
the function runs which is why we are storing the index of the task we are looking for.
To pass the sequence array each time, before the recursive call we create a local array and
manually copy the sequence array that was previously passed into the function, into the local
array. This is because in c arrays are passed as pointers not by value, so if several recursive
calls will be at the same path then the tasks would overwrite each other since we have one
sequence array so the several paths cannot be stored. By using a local array we are able to
create a new path each time a dependency is found, as a new local array is created each
time we detect a dependency and this way we add this dependency into the path and pass
the local array into the function. This method of using a local array acts the same as copying
the arrays each time by values and passing them to the recursive function.
A loop inside the function goes through the entire flag array of the task tested, if the task has
a dependency then that dependency will be checked to see if it is already in the path.
It is tested by going through the sequence array and comparing each task in the path to the
new dependency found, if it is already in the path then it means a circular dependency
occurs since the task is its own dependency. In that case each dependency in the path will
be printed to alert the user of a circular dependency warning. If a circular dependency was
found then the function will return true.
If the dependency is not yet in the path then it will be added and the function circular is
called again recursively this time with the sequence array containing another task in the
path. This way each time a task is added to the path a copy of the sequence array is passed
to the circular array and that task name is also passed as the new task to be tested. This
method also allows to have different paths since each time a copy of the previous array is
passed to the recursive function and if several dependencies are found then several
pathways will be created and so on until all the possible sequences will be tested for circular
dependency. The function will test for the dependencies of that task and the process will
continue until a task has no more dependencies to check for which in that case the circular
function will return false, meaning no circular dependency was found.
ASCII art
We weren’t quite sure at first what kind of ASCII art we wanted to use first, so we were
looking at pictures of flowers and decided to try and make a sunflower of our own.
Git repository
https://csgitlab.ucd.ie/GalBaskin/G-assignment2.git
Files:
Main.c
Check if user wants to use sample gantt chart or create their own, then calls the
appropriate function either printSample of takeInput, then calling show_menu.
input.c / input.h
Contains: struct inputParameters
sampleGanttChart.c / sampleGanttChart.h
Initialises all the sample data inside the struct and then prints the sample gantt chart
display.c / display.h
Prints a gantt chart
Contains function: print_line , print_rows, print_chart
menu.c / menu.h
Displays the menu with the possible operations the users can choose from to work
with the gantt chart created. The menu will keep displaying until the user terminates
the program by choosing quit.
Enum definition: MenuChoice
test.c / test.h
Tests for a circular dependency of a task entered by the user
editTask.c / editTask.h
Edits a task chosen by the user
quit.c / quit.h
Clears the screen and quits the the program
