# Gantt Chart

A console-based Gantt chart program written in C. Users can display a
sample chart or create their own chart, then manage tasks through an
interactive menu.

## Overview

The program lets users:

-   Display a predefined sample Gantt chart.
-   Create a Gantt chart by entering task names, start and end months,
    and dependencies.
-   Edit an existing task.
-   Check a task for circular dependencies.
-   Redisplay the chart.
-   Quit the program.

Task information is stored in a structure so that each task's name,
dates, and dependencies can be accessed using the same array index.

## Data Structures

### `inputParameters` structure

The `inputParameters` structure stores the information associated with
the tasks.

``` c
typedef struct {
    char tasks[10][80];
    int startMonth[10];
    int endMonth[10];
    int dependencies[10][10];
} inputParameters;
```

The structure is declared in `input.h`.

-   `tasks`: stores task names.
-   `startMonth`: stores each task's starting month.
-   `endMonth`: stores each task's ending month.
-   `dependencies`: stores task dependencies in a two-dimensional flag
    array.

The information for a task is stored at the same index across the
arrays. For example, the name at `tasks[0]`, the start month at
`startMonth[0]`, the end month at `endMonth[0]`, and the dependencies at
`dependencies[0]` all belong to the first task.

### Dependency flag array

The dependency array is initialised to `0`. When a task depends on
another task, the corresponding position is set to `1`.

For example:

``` c
input->dependencies[task][dependencyTask - 1] = 1;
```

The dependency task number is reduced by one because C arrays use
zero-based indexing. A dependency on task 3 is therefore stored at index
`2`.

### `MenuChoice` enum

The menu uses an enum declared in `menu.h` to represent the operation
selected by the user.

``` c
enum MenuChoice {
    EDIT = 1,
    TEST,
    DISPLAY,
    QUIT,
    UNKNOWN
};
```

The selected option is stored in an enum variable and checked using a
`switch` statement. This determines which operation the program calls.

## User Input

Input handling is implemented in `input.c` and `input.h`. The user's
task information is stored in an `inputParameters` structure.

### `takeInput`

This function:

1.  Asks how many tasks the user wants to add.
2.  Uses a loop to collect the details for each task.
3.  Reads task names with `fgets`, allowing names to contain spaces.
4.  Calls `inputMonths` and `inputDependencies` to collect the remaining
    information.

### `inputMonths`

This function collects a task's start and end months using `scanf`.

-   `do-while` loops validate the month values.
-   The end month must be greater than or equal to the start month.
-   If a value is invalid, the program displays a message and asks the
    user to enter it again.

### `inputDependencies`

This function collects the dependencies for a task.

1.  Initialises the task's dependency flags to `0`.
2.  Asks how many dependencies the task has.
3.  Validates the number of dependencies.
4.  Collects each dependent task number.
5.  Sets the corresponding dependency flag to `1`.

The validation prevents a task from depending on itself and checks that
entered task numbers are within the available task range.

## Displaying the Gantt Chart

The chart is displayed by `printChart` in `display.c`. It uses two
helper functions: `print_line` and `print_rows`.

### `printChart`

This function prints the chart's borders and headings. It displays the
task-name column, the month headings, and the dependencies column, then
calls `print_rows` to display the task information.

### `print_line`

Prints the horizontal lines and borders of the chart using a loop that
outputs dashes.

### `print_rows`

This function loops through the tasks stored in the structure and prints
one row for each task.

-   It checks each month against the task's start and end months.
-   It prints `XXX` for months when the task is scheduled and leaves
    other months blank.
-   It checks the dependency flag array and prints the numbers of the
    tasks that the current task depends on.
-   It prints a separating line after each task row.

### Sample Gantt chart

The sample chart is defined in `sampleGanttChart.c`. Its task names,
months, and dependencies are initialised as predefined data. The sample
data is passed to `printChart` in `display.c` to be displayed.

## Menu

The menu allows users to manage the chart after it has been created or
displayed. It continues running until the user chooses to quit.

### `show_menu`

This function runs the menu loop. It calls `menu_input` to read the
user's choice and then uses a `switch` statement to call the appropriate
function:

  Option           Operation
  ---------------- ------------------------------------------
  Edit             Calls `editTask`
  Test             Calls `testTask`
  Display          Calls `printChart`
  Quit             Calls `quit_program`
  Invalid choice   Displays an unrecognised-command message

### `menu_input`

Reads the user's menu choice and updates the `MenuChoice` value when a
recognised operation is selected. Otherwise, the choice remains
`UNKNOWN`.

## Editing Tasks

The `editTask` function allows the user to modify an existing task.

1.  Calls `findTask` to locate the task by its current name.
2.  Compares the entered name with the stored task names using `strcmp`.
3.  Uses the matching array index to update the task name.
4.  Collects the task's start and end months again.
5.  Resets its dependency flags and collects its dependencies again.

The task's array index is retained, so the edited information replaces
the old information for that task.

## Checking for Circular Dependencies

The program can test whether a task's dependencies eventually lead back
to the same task.

### `testTask`

Calls `findTask` to locate the task selected by the user, then calls
`circular` to check its dependencies. It reports whether a circular
dependency was found.

### `findTask`

Finds a task by comparing the name entered by the user with the task
names stored in the structure. When a match is found, it returns or
records the task's array index so the program can access that task's
dependencies.

### `circular`

`circular` is a recursive Boolean function. It returns `true` if it
finds a circular dependency and `false` if it does not.

The function:

1.  Receives the task data, the current task index, and an array
    representing the current dependency path.
2.  Checks each dependency of the current task.
3.  Looks for that dependency in the current path.
4.  If the dependency is already in the path, reports a circular
    dependency.
5.  Otherwise, adds the dependency to a local copy of the path and calls
    itself recursively.
6.  Continues until a cycle is found or there are no more dependencies
    to explore.

A local copy of the path is used for recursive calls so that different
dependency paths do not overwrite one another. This is important because
C arrays are passed to functions through pointers rather than copied
automatically.

## Quitting the Program

The `quit_program` function, implemented in `quit.c` and declared in
`quit.h`, clears the screen and terminates the program when the user
selects Quit.

## ASCII Art

The project also includes a sunflower made using ASCII characters.

## Project Files

  -----------------------------------------------------------------------
  File                                Purpose
  ----------------------------------- -----------------------------------
  `main.c`                            Asks whether the user wants the
                                      sample chart or a custom chart,
                                      calls the appropriate function, and
                                      then opens the menu.

  `input.c` / `input.h`               Collects task details and defines
                                      the `inputParameters` structure.

  `sampleGanttChart.c` /              Initialises the predefined sample
  `sampleGanttChart.h`                data and displays the sample chart.

  `display.c` / `display.h`           Prints the Gantt chart using
                                      `print_line`, `print_rows`, and
                                      `printChart`.

  `menu.c` / `menu.h`                 Displays the menu and dispatches
                                      the selected operation. Defines
                                      `MenuChoice`.

  `test.c` / `test.h`                 Locates tasks and checks for
                                      circular dependencies.

  `editTask.c` / `editTask.h`         Edits a task selected by the user.

  `quit.c` / `quit.h`                 Clears the screen and quits the
                                      program.

  `input.h`                           Declares the task data structure
                                      used to store task information.
  -----------------------------------------------------------------------

## How to Use

1.  Run the program.
2.  Choose whether to display the sample Gantt chart or create your own.
3.  If creating a chart, enter the task names, start and end months, and
    dependencies when prompted.
4.  Use the menu to edit a task, test for circular dependencies, display
    the chart again, or quit.
