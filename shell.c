// ACADEMIC INTEGRITY PLEDGE
//
// - I have not used source code obtained from another student nor
//   any other unauthorized source, either modified or unmodified.
//
// - All source code and documentation used in my program is either
//   my original work or was derived by me from the source code
//   published in the textbook for this course or presented in
//   class.
//
// - I have not discussed coding details about this project with
//   anyone other than my instructor. I understand that I may discuss
//   the concepts of this program with other students and that another
//   student may help me debug my program so long as neither of us
//   writes anything during the discussion or modifies any computer
//   file during the discussion.
//
// - I have violated neither the spirit nor letter of these restrictions.
//
//
//
// Signed:_____________________________________ Date:_____________

// 3460:426 Lab 4A - Basic C shell

/* Basic shell */

/*
 * This is a very minimal shell. It finds an executable in the
 * PATH, then loads it and executes it (using execv). Since
 * it uses "." (dot) as a separator, it cannot handle file
 * names like "minishell.h"
 *
 * The focus on this exercise is to use fork, PATH variables,
 * and execv.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS  64
#define MAX_ARG_LEN 16
#define MAX_LINE_LEN  80
#define WHITESPACE  " ,\t\n"

struct command_t {
  char *name;
  int argc;
  char *argv[MAX_ARGS];
};

/* Function prototypes */
int parseCommand(char *, struct command_t *);
void printPrompt();
void readCommand(char *);
void printHelp();

int main(int argc, char *argv[])
{
  int pid;
  int status;
  char cmdLine[MAX_LINE_LEN];
  struct command_t command;

  while (1) {
    printPrompt();
    /* Read the command line and parse it */
    readCommand(cmdLine);

    parseCommand(cmdLine, &command);

    command.argv[command.argc] = NULL;

    if(strcmp(command.name, "Q\0") == 0) {
      return 0;
    }

    /* Create a child process to execute the command */
    if ((pid = fork()) == 0) {
      /* Child executing command */
      char *realCommand = "";
      if(strcmp(command.name, "C\0") == 0) {
        realCommand = "cp";
      }
      else if(strcmp(command.name, "D\0") == 0) {
        realCommand = "rm";
      }
      else if(strcmp(command.name, "M\0") == 0) {
        realCommand = "nano";
      }
      else if(strcmp(command.name, "P\0") == 0) {
        realCommand = "more";
      }
      else if(strcmp(command.name, "S\0") == 0) {
        realCommand = "firefox";
        command.argv[1] = "&";
      }
      else if(strcmp(command.name, "W\0") == 0) {
        realCommand = "clear";
      }
      else if(strcmp(command.name, "X\0") == 0) {
        realCommand = command.argv[1];
      }
      else if(strcmp(command.name, "E\0") == 0) {
        realCommand = "echo";
      }
      else if(strcmp(command.name, "H\0") == 0) {
	printHelp();
      }
      else if(strcmp(command.name, "L\0") == 0) {
        printf("\n");
        int pid2;
        if((pid2 = fork()) == 0) {
          execvp("pwd", command.argv);
        }
        wait(&status);
        printf("\n");
        realCommand = "ls";
        command.argv[1] = "-l";
      }
      execvp(realCommand, command.argv);
    }
    /* Wait for the child to terminate */
    wait(&status);
  }

  /* Shell termination */
  printf("\n\n shell: Terminating successfully\n");
  return 0;
}

/* End basic shell */

/* Parse Command function */

/* Determine command name and construct the parameter list.
 * This function will build argv[] and set the argc value.
 * argc is the number of "tokens" or words on the command line
 * argv[] is an array of strings (pointers to char *). The last
 * element in argv[] must be NULL. As we scan the command line
 * from the left, the first token goes in argv[0], the second in
 * argv[1], and so on. Each time we add a token to argv[],
 * we increment argc.
 */
int parseCommand(char *cLine, struct command_t *cmd)
{
  int argc;
  char **clPtr;
  /* Initialization */
  clPtr = &cLine; /* cLine is the command line */
  argc = 0;
  cmd->argv[argc] = (char *) malloc(MAX_ARG_LEN);
  /* Fill argv[] */
  while ((cmd->argv[argc] = strsep(clPtr, WHITESPACE)) != NULL) {
    cmd->argv[++argc] = (char *) malloc(MAX_ARG_LEN);
  }

  /* Set the command name and argc */
  cmd->argc = argc - 1;
  cmd->name = (char *) malloc(sizeof(cmd->argv[0]));
  strcpy(cmd->name, cmd->argv[0]);
  return 1;
}

/* End parseCommand function */

/* Print prompt and read command functions - pp. 79-80 */

void printPrompt()
{
  /* Build the prompt string to have the machine name,
   * current directory, or other desired information
   */
  char *promptString = "linux alr104>";
  printf("%s ", promptString);
}

void readCommand(char *buffer)
{
  /* This code uses any set of I/O functions, such as those in
   * the stdio library to read the entire command line into
   * the buffer. This implementation is greatly simplified,
   * but it does the job.
   */
  fgets(buffer, 80, stdin);
}

/* End printPrompt and readCommand */

/* Print the help function's information. */

void printHelp()
{
  /* Copy help */
  printf("%s ", "\nC file1 file2      Copy: create file2, copy all bytes of file1 to file2 without deleting file1.");
  /* Delete help */
  printf("%s ", "\nD file             Delete the named file.");
  /* Echo help */
  printf("%s ", "\nE comment          Echo: display comment on screen followed by a new line.");
  /* Help help */
  printf("%s ", "\nH                  Help: display the user manual.");
  /* List help */
  printf("%s ", "\nL                  List the contents of the current directory.");
  /* Make help */
  printf("%s ", "\nM file             Make: create the named text file by launching a text editor.");
  /* Print help */
  printf("%s ", "\nP file             Print: display the contents of the named file on screen.");
  /* Quit help */
  printf("%s ", "\nQ                  Quit the shell.");
  /* Surf the web help */
  printf("%s ", "\nS                  Surf the web by launching a browser.");
  /* Wipe help */
  printf("%s ", "\nW                  Wipe: clear the screen.");
  /* Program help */
  printf("%s ", "\nX program          Execute the named program.");
  
  /* New lines */
  printf("%s ", "\n\n");
}

/* End help function's information. */
