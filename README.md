# Basic-Shell
Creation of a basic shell in C that also reports a number of statistics. Created for WPI CS3013.

I implimented a basic shell program in C to understand linux programming. the program, doit will run any command given to it and upon completion output a number of statistics:

1.  the amount of CPU time used (both user and system time) (in milliseconds),
2.  2.  the elapsed “wall-clock” time for the command to execute (in milliseconds),
3.  3.  the number of times the process was preempted involuntarily (e.g. time slice expired,preemption by higher priority process),
4.  4.  the number of times the process gave up the CPU voluntarily (e.g. waiting for a re-source),
5.  5.  the number of major page faults, which require disk I/O, and
6.  6.  the number of minor page faults, which could be satisfied without disk I/O.
7.  7.  the maximum resident set size used, which is given in kilobytes.

this program takes a command as an input and executed that command, outputing anything the command would normaly output if applicable and returning the statistics listed above. to run the program doit.c should be compiled and ran either with or without arguments. if you wish to only run one command you can simply put that command after ./doit however if you wish for it to run many commands such as a normal shell would, you can simply run ./doit and it will accept many arguments until you give it the command "exit" or manually shut down the program with a keyboard interupt. you can also run the comand set prompt = (prompt) to change the prompt use when running as an open shell. 

./doit wc doit.c
    -will run the wc command (word count) output how many words are in the file and report statistics
    
./doit
    -will run the program as a make-shift shell and accept commands outputing if necessary and reporting statistics
