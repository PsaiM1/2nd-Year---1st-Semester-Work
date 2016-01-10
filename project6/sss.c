#include "sss.h"
#include "split.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/*
Author: PrasannaSai Meruga
Section: Majeed 10AM

The purpose of this program is to act like a simple shell.
It will take commands and read them and process both
compilation commands and test commands based on what the
user wants. 
 */

/*
This function creates a command structure by allocating
memory for the structure and its fields and puts the
compile commands in its compile list and test commands in
its test list

Returns: A Command struct.
 */
Commands read_commands(const char *compile_cmds, const char *test_cmds) {
  int n = 1;
  FILE *compile;
  FILE *test;
  char *temp;
  struct commands readcmds;
  
  if (compile_cmds != NULL && test_cmds != NULL) {
    compile = fopen(compile_cmds, "r");
    test = fopen(test_cmds, "r");
    if (compile != NULL && test != NULL) {
      readcmds.cmplist = NULL;
      readcmds.testlist = NULL;
      /*put commands in compile list*/
      while (!feof(compile)) {
	temp = malloc(sizeof(char) * 256);
	fgets(temp, 256, compile);
	readcmds.cmplist = realloc(readcmds.cmplist, sizeof(char *) * n);
	readcmds.cmplist[n-1] = temp;
	n++;
      }
      free(temp);
      readcmds.cmplist = realloc(readcmds.cmplist, sizeof(char *) * (n-2));
      readcmds.cmplength = n-2;
      
      n = 1; /* reset n to 1*/
      /*put test commands in test list*/
      while (!feof(test)) {
	temp = malloc(sizeof(char) * 256);
	fgets(temp, 256, test);
	readcmds.testlist = realloc(readcmds.testlist, sizeof(char *) * n);
	readcmds.testlist[n-1] = temp;
	n++;
      }
      free(temp);
      readcmds.testlist = realloc(readcmds.testlist, sizeof(char *) * (n-2));
      readcmds.testlength = n-2;
      
      fclose(compile);
      fclose(test);
      return readcmds;
    } else {
      if (compile != NULL) {
	fclose(compile);
      }

      if (test != NULL) {
	fclose(test);
      }
      exit(0);
    }
  } else {
    exit(0);
  }
}

/*
The purpose of this function is to free all the
memory allocated by the read_commands function.
Users must use this in order to avoid leaking memory.

Returns nothing.
 */
void clear_commands(Commands *commands) {
  int i;
  if (commands != NULL) {
    /*loop through each array and free it all*/
    for (i = 0; i < commands->cmplength; i++) {
      free(commands->cmplist[i]);
      commands->cmplist[i] = NULL;
    }

    free(commands->cmplist);
    commands->cmplist = NULL;
    for (i = 0; i < commands->testlength; i++) {
	free(commands->testlist[i]);
	commands->testlist[i] = NULL;
    }
    free(commands->testlist);
    commands = NULL;
  } else {
    return;
  }
}

/*
This function takes a command struct and then
takes each individual compile command into a 
new child process and executes the command

Returns 1 if success or there were no commands
Returns 0 if fork failed or child didn't 
execute or exit properly
 */
int compile_program(Commands commands) {
  int pid;
  int status;
  char **cmds;
  int i, j;

  if (commands.cmplist == NULL) {
    return 1;
  }

  for (i = 0; i < commands.cmplength; i++) {
    cmds = split(commands.cmplist[i]);
    j = 0;
    pid = fork();
    if (pid < 0) { /* forked failed*/
      while (cmds[j] != NULL) {
	free(cmds[j]);
	cmds[j] = NULL;
	j++;
      }
      free(cmds[j]);
      free(cmds);
      cmds = NULL;
      return 0;
    } else if (pid == 0) { /*for the child*/
      execvp(cmds[0], cmds);
    } else { /*for the parent*/
      wait(&status);
      if (WIFEXITED(status)) {
	if (WEXITSTATUS(status)) {
	  while (cmds[j] != NULL) {
	    free(cmds[j]);
	    cmds[j] = NULL;
	    j++;
	  }
	  free(cmds[j]);
	  free(cmds);
	  cmds = NULL;
	  return 0; /*did exit but with nonzero status*/
	} else {
	  while (cmds[j] != NULL) {
	    free(cmds[j]);
	    cmds[j] = NULL;
	    j++;
	  }
	  free(cmds[j]);
	  free(cmds);
	  cmds = NULL;
	  /*did exit sucessfully with status 0*/
	}
      } else {
	while (cmds[j] != NULL) {
	  free(cmds[j]);
	  cmds[j] = NULL;
	  j++;
	}
	free(cmds[j]);
	free(cmds);
	cmds = NULL;
	return 0; /*child didnt exit properly*/
      }
    }
  }
  /*all commands exited successfully so return 1*/
  return 1;
}

/*
The purpose of this function is to take
the commands struct given and process through
its test commands. It will take each individual 
command into a new process and execute them

This function also handles I/O redirection
by checking whether the command contains 
redirection syntax and then handles it appropriately

Returns the number of commands that have been
executed.
 */
int test_program(Commands commands) {
  int pid;
  int status;
  char **cmds;
  int i, j;
  int count = 0;
  int cmdssize;
  char *temp;

  if (commands.cmplist == NULL) {
    return 1;
  }

  for (i = 0; i < commands.testlength; i++) {
    cmds = split(commands.testlist[i]);
    j = 0;
    cmdssize = 0;
    while (cmds[j] != NULL) {
      cmdssize++;
      j++;
    }
    cmdssize++;
    /* cmdssize = (sizeof(cmds)/sizeof(char *)); gives size of cmds*/
    temp = malloc(strlen(cmds[cmdssize-2]) * sizeof(char) + 1);
    pid = fork();
    if (pid < 0) { /* forked failed*/
      j = 0;
      while (cmds[j] != NULL) {
	free(cmds[j]);
	cmds[j] = NULL;
	j++;
      }
      free(cmds[j]);
      free(cmds);
      free(temp);
      return 0;
    } else  if (pid == 0) { /*for the child*/
      if (cmdssize == 6) {
	if (strcmp(cmds[cmdssize-3], ">") == 0 && strcmp(cmds[cmdssize-5], "<") 
	    == 0) {
	  strcpy(temp, cmds[cmdssize-2]); /*cpy outfile*/
	  free(cmds[cmdssize-2]);
	  free(cmds[cmdssize-3]);
	  cmds = realloc(cmds, cmdssize-2);
	  dup2(open(temp, O_RDWR), 1); /*redirect output*/
	  temp = malloc(sizeof(cmds[0]) * sizeof(char));
	  strcpy(temp, cmds[0]); /*cpy infile*/
	  dup2(open(temp, O_RDWR), 0); /*redirect input*/
	  free(cmds[0]);
	  free(cmds[1]);
	  cmds+=2;
	  execvp(cmds[0], cmds);
	}
      }

      if (cmdssize >= 4) {
	if (strcmp(cmds[cmdssize-3], "<") == 0) {
	  strcpy(temp, cmds[cmdssize-2]);
	  free(cmds[cmdssize-1]);
	  free(cmds[cmdssize-2]);
	  free(cmds[cmdssize-3]);
	  cmds = realloc(cmds, cmdssize-2);
	  j = 0;
	  cmdssize = 0;
	  while (cmds[j] != NULL) {
	    cmdssize++;
	    j++;
	  }
	  cmdssize++;
	  cmds[cmdssize-1] = NULL;
	  dup2(open(temp, O_RDWR), 0); /*redirect input*/
	  execvp(cmds[0], cmds);
	} else if (strcmp(cmds[cmdssize-3], ">") == 0) {
	  strcpy(temp, cmds[cmdssize-2]);
	  free(cmds[cmdssize-2]);
	  free(cmds[cmdssize-3]);
	  cmds = realloc(cmds, cmdssize-2);
	  j = 0;
	  cmdssize = 0;
	  while (cmds[j] != NULL) {
	    cmdssize++;
	    j++;
	  }
	  cmdssize++;
	  cmds[cmdssize-1] = NULL;
	  dup2(open(temp, O_RDWR), 1); /*redirect output*/
	  execvp(cmds[0], cmds);
	} else {
	  execvp(cmds[0], cmds);
	}
      } else {
	execvp(cmds[0], cmds);
      }
    } else { /*for the parent*/
      wait(&status);
      if (WIFEXITED(status)) {
	if (WEXITSTATUS(status)) { /*did exit but with nonzero status*/
	  free(temp);
	  j = 0;
	  while (cmds[j] != NULL) {
	    free(cmds[j]);
	    cmds[j] = NULL;
	    j++;
	  }
	  free(cmds);
	} else {
	  j = 0;
	  while (cmds[j] != NULL) {
	    free(cmds[j]);
	    cmds[j] = NULL;
	    j++;
	  }
	  free(cmds); /*did exit sucessfully with status 0*/
	  free(temp);
	  count++;
	}
      } else {
	j = 0;
	while (cmds[j] != NULL) {
	  free(cmds[j]);
	  cmds[j] = NULL;
	  j++;
	}
	free(cmds); /*child didnt exit properly*/
	free(temp);
      }
    }
  }
  /*all commands exited successfully so return count*/
  return count;
}
