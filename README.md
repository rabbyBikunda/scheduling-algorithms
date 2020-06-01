# scheduling-algorithms
Application in C that demonstrates the CPU scheduling algorithms FIFO, SJF and STCF.

The application  accepts a list of processes in the format of a single line as command-line arguments when it is run.
It automatically assigns incrementing process IDs in the format:
P1, P2, P3, and so on.
When the application starts, the user is provided with a prompt which allows them to run one of the following
actions: fifo, stcf, sjf, compare or quit.
The actions must be entered in the command line and they are also validated.

The apllication is compiled with GCC on Ubuntu 18.04,
The command to compile the program is:
gcc main.c lib/input-utils.c lib/command-line-validation.c ./lib/application.c -Wall -Wextra -Wpedantic -o build/main
