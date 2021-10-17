/* myexec.c */

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<string.h>

extern char **environ;		/* environment info */

main(int argc, char **argv)
     /* argc -- number of arguments */
     /* argv -- an array of strings */
{

    char *argvNew[argc];
    int pid;
	char* prompt = "==>";
	
struct timeval start_time;
struct rusage start, end;
gettimeofday(&start_time, NULL);
getrusage(RUSAGE_SELF, &start);

	if(argc < 2){
	cnt:;
	while(1){
	gettimeofday(&start_time, NULL);
	getrusage(RUSAGE_SELF, &start);
	
			char str[128];
			char* input[32];
			
			fprintf(stderr,"%s",prompt);
			if(!fgets(str,128,stdin)){break;}
			if(strcmp(str, "exit\n")==0){break;}
			char strcp[128];
			
			
		str[strcspn(str, "\n")] = 0;
		char *ptr = strtok(str, " ");

		int i = 0;
		while(ptr != NULL)
		{
			input[i] = ptr;
			i++;
			ptr = strtok(NULL, " ");
		}
		input[i] = NULL;

		if((strcmp(input[0], "set") == 0) &&
			(strcmp(input[1], "prompt") == 0) &&
			(strcmp(input[2], "=") == 0)){
			prompt = input[3];
			goto cnt;
		}


	if ((pid = fork()) < 0) {
        fprintf(stderr, "Fork error\n");
        exit(1);
    }
    else if (pid == 0) {
        /* child process */
	if(strcmp(input[0],"cd") == 0){
		chdir(input[1]);
	} else if (execvp(input[0], input) < 0) {
            fprintf(stderr, "Execvp error\n");
            exit(1);
        }
    }
    else {
	if(strcmp(input[0],"cd") == 0){
		chdir(input[1]);
	}
	
        /* parent */
	wait(0);
		/* wait for the child to finish */
	struct timeval end_time;
	gettimeofday(&end_time, NULL);
	getrusage(RUSAGE_SELF, &end);
	displayStats(start_time,end_time,start,end);
	

    }
	}

	}



    if ((pid = fork()) < 0) {
        fprintf(stderr, "Fork error\n");
        exit(1);
    }
    else if (pid == 0) {
        /* child process */
	for(int i = 1; i < argc; i++){
		argvNew[i-1] = argv[i];
	}
	argvNew[argc-1] = NULL;

        if (execvp(argvNew[0], argvNew) < 0) {
            fprintf(stderr, "Execvp error\n");
            exit(1);
        }
    }
    else {
        /* parent */
	
  
	
	wait(0);
	
		/* wait for the child to finish */
	struct timeval end_time;
	gettimeofday(&end_time, NULL);
	getrusage(RUSAGE_SELF, &end);
	displayStats(start_time,end_time,start,end);
	

    }
}

void displayStats(struct timeval start_time, struct timeval end_time, struct rusage start, struct rusage end){

	fprintf(stderr, "CPU Time: %f seconds \n",
		((end.ru_stime.tv_sec - start.ru_stime.tv_sec) + 
		1e-6*(end.ru_stime.tv_usec - start.ru_stime.tv_usec)+
		(end.ru_utime.tv_sec - start.ru_utime.tv_sec) +
		1e-6*(end.ru_utime.tv_usec - start.ru_utime.tv_usec)));
	fprintf(stderr, "Involuntary Context Switched: %ld \n",end.ru_nivcsw);
	fprintf(stderr, "Voluntary Context Switched: %ld \n",end.ru_nvcsw);
	fprintf(stderr,"Wallclock Time: %f seconds \n",((end_time.tv_sec - start_time.tv_sec) + (1e-6*(end_time.tv_usec - start_time.tv_usec))));
	fprintf(stderr, "Major Faults: %ld \n",end.ru_majflt);
	fprintf(stderr, "Minor Faults: %ld \n",end.ru_minflt);
	fprintf(stderr, "Set Size: %ld Kilobytes \n",end.ru_maxrss);

}
