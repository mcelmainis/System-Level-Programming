#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

/*Assnignment for System Level Programming.
This is meant to demonstrate understanding the topic of Signals and Processes.
--This program takes two other programs as parameters. The two programs will execute 
and race to finish. If the first fails, the second wins by default.
*/

int main(int argc, char **argv) {
  // This checks to make sure that 2 programs were supplied.
  if (argc != 3) {
    fprintf(stderr, "usage: race program1 program2\n");
    exit(1);
  }

  // supplied programs
  char *program1 = argv[1];
  char *program2 = argv[2];

  // child process created
  pid_t child1 = fork();
  if (child1 == 0) {
    // execvp runs first programs 
    char *program1PlusArgs[] = {program1, NULL};
    execvp(program1, program1PlusArgs);
  }
  #ifdef DEBUG
    printf("child1 = %d\n", child1);
  #endif

  // second child process created
  pid_t child2 = fork();
  if (child2 == 0) {
    // running second child
    char *program2PlusArgs[] = {program2, NULL};
    execvp(program2, program2PlusArgs);
  }
  #ifdef DEBUG
    printf("child2 = %d\n", child2);
  #endif

  // child processes racing
  int status; // exit status of finished program.
  pid_t winner = wait(&status);
  #ifdef DEBUG
    printf("winner = %d\n", winner);
    printf("status = %d\n", status);
  #endif
  
  char *winName;
  char *loseName;
  if (winner == child1) {
    winName = program1;
    loseName = program2;
    kill(child2, SIGKILL);
  }
  else {
    winName = program2;
    loseName = program1;
    kill(child1, SIGKILL);
  } 

  // If the first process to finish fails, the other wins by default.
  if (status != 0) {
    printf("%s failed, so %s wins by default\n", winName, loseName);
  }
  else {
    printf("%s is the winner!\n", winName);
  }   
} // end 


