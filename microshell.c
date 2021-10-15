#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/wait.h> 

#define MAX_LENGTH 1024

int main() {

    char line[MAX_LENGTH];
    char cwd[1024];
    while (1) {

        getcwd(cwd, sizeof(cwd));
        printf("[%s]> ", cwd);

        if (!fgets(line, MAX_LENGTH, stdin)){
            break;
        } 
        size_t length = strlen(line);
        if (line[length - 1] == '\n')
            line[length - 1] = '\0';

        char *args[10] = {};
        args[0] = strtok(line, " ");
        int i = 0;
        while (args[i] != NULL)
        {
          i++;
          args[i] = strtok(NULL, " ");
        }

        if (strcmp(args[0], "exit") == 0) {
            exit(0);
        }

        int childpid = fork();
        if (childpid == 0) //If child
        {
          if ((execvp(args[0], args)) < 0)
          {
            printf("Invalid command.\n");
          }
          exit(1);
        }
        else if (childpid > 0) //If parent
        {
          wait(&childpid);
        }
        else 
        {
          printf("Error creating child process.\n");
          exit(1);
        }

    }

  return 0;
}