/* Name: Yonathan Adugna Kebede
 * TerpID: ykebed12
 * UID: 115659780
 *
 * I pledge on my honor that I have not given or recieved
 * any unauthorized assistance on this examination or assignment.
 * 
 * This program implements the xargs UNIX program features
 * 
 */

#include "safe-fork.h"
#include "split.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_SIZE 1000

/* Function prototypes */
char read_line (char *line);
void read_input (char *input);
char ** merge_arr (char **first_arr, char **second_arr, int size);
int count_size (char **arr);
void free_args (char **arr);


/*MAIN FUNCTION*/
int main (int argc, char *argv[]) {

    int pid, line_pid, status;
    char *line, *temp = NULL, **file_args = NULL, **file_args2 = NULL;    
    
    /* Allocate enough memory for each input */
    line = malloc(sizeof(char) * (MAX_SIZE + 1));


    /* CONDITIONS FOR PROGRAM FUNCTIONALITY*/

    if (argc > 2 && !strcmp(argv[1], "-i") ) {
        /* CONDITION: Run one line at a time mode with target-program
        and target-args */

        /* Read each line till EOF is reached then */
        while (read_line(line) != EOF ) {
            
            /* Split stdin line input */
            file_args2 = split(line);
            /* Merge array of arguments and from argv and stdin */
            file_args = merge_arr(argv + 2, file_args2, argc-2);
            /* Run new process to execute arguments*/
            line_pid = safe_fork();
            
            
            if (line_pid > 0) {
                /* Parent */

                /* Wait for child so we can free the
                argument returned by split and the
                merged array */ 
                wait(&status);

                free(file_args);
                free_args(file_args2);
                
                /* Check if child exited successfully*/
                if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                    free(line); /* Free previously allocated memory for
                                   line if child did not exit normally*/
                    exit(1);
                }

            } else {
                /* Child Process*/

                execvp(argv[2], file_args);
                exit(1);
            }
            
        }

        free(line); 

        /* FIRST CONDITION FINISHED */
        
    } else if (argc == 2 && !strcmp(argv[1], "-i")) {
        /* CONDITION: Run one line at a time mode with without 
        target-program */

        temp = malloc(sizeof(char) * 5);
        strcpy(temp, "echo");

        while (read_line(line) != EOF) {
            /* Read line then fork, then let child exit loop 
            while parent continues in the loop */

            /* Split input line*/ 
            file_args2 = split(line);
            /* Merge arguments */
            file_args = merge_arr(&temp, file_args2, 1);
            /* Create a new process for exec*/
            line_pid = safe_fork();

            if (line_pid > 0) {
                /* Parent Process */

                /* Wait for child for freeing memory*/
                wait(&status);
                /* Free memory used after split */
                free_args(file_args2);
                /* Free memory used by merge */
                free(file_args);

                /* Check if child exited normally, else free
                 relevant memory */ 
                if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                    free(temp);
                    free(line);
                    exit(1);
                }

            } else {  
                /* Child Process*/

                execvp(temp, file_args);
                exit(1);
            }
        }

        /* Free previously allocated memory */
        free(line);
        free(temp);

        /* SECOND CONDITION FINISHED */
        
    } else if (argc >= 2 && strcmp(argv[1], "-i")) {
        /* CONDITION: Standard mode and just target-program with 
        possible target_args */

        /* Read all input */
        read_input(line);

        /*Split input arguments*/
        file_args2 = split(line);
        /* Merge arguments into one array */
        file_args = merge_arr(argv + 1, file_args2, argc - 1);
        /* Create new process */
        pid = safe_fork();

        if (pid > 0) {
            /* Parent Process */

            /*Wait for child for freeing memory*/
            wait(&status);

            free_args(file_args2);
            free(line);

            /* Check if child exited */
            if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                exit(1);
            }

        } else {
            /* Child Process */
            execvp(file_args[0], file_args);
            exit(1);
        }
        
        
        /* THIRD CONDITION FINISHED */
    } else {
        /* CONDITION: Standard mode with no target-program */

        /* Read input from stdin*/
        read_input(line);
        /* Allocate enough memory for argument echo*/
        temp = malloc(sizeof(char) * (strlen(line) + 12));
        strcpy(temp, "/bin/echo ");
        strncat(temp, line, strlen(line) + 12);
        
        file_args = split(temp);

        /*Create new process */
        pid = safe_fork();
        
        if (pid > 0) {
            /* Parent process */

            /* Wait for child*/
            wait(&status);

            free_args(file_args);
            free(line);
            
            /* Check if child process exited normally */
            if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                exit(1);
            }
            exit(0);
            
        } else {
            /* Child Process */
            execv(file_args[0], file_args);
            exit(1);
        }
        
        /* LAST CONDITION FINISHED */
    }
    

    return 0;
}

/* This function reads in a line from stdin and 
 returns the last character*/
char read_line(char *line) {

    int index = 0;
    char c;

    /* Loop to read each character in stdin*/
    while ((c = getchar()) != '\n' && c != EOF) {
        line[index] = c;
        index += 1;
    }

    /* Make sure there is a newline character 
    and \0 at the end to work with split*/
    line[index] = '\n';
    line[index + 1] = '\0'; 

    /* Return last read character */
    return c;
}

/* This function reads all input until EOF is reached
 into a string input */
void read_input(char *input) {

    /* Character used for */
    char c;
    int index = 0;

    /* Read every character in stdin */
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
	        c = ' ';
	    }
	    
        input[index] = c;
        index += 1;
    }

    /* Make sure there is a newline character 
    and \0 at the end to work with split*/
    input[index] = '\n';
    input[index + 1] = '\0';
}

/* Takes two string arrays and takes the elements and puts it in one 
 merged array which is returned. The int variable indicates the size
 of the first array of strings to copy into new array of strings.*/
char **merge_arr(char **first_arr, char **second_arr, int size_first) {

    int index,
        size_second = count_size(second_arr),
        new_size = sizeof(char *) * (size_first + size_second);
    
    /* Allocate enough memory for the merge of both arrays*/
    char **merged_arr = malloc(new_size);

    /* Add the first array to the new array*/
    for (index = 0; index < size_first; index++) {
        merged_arr[index] = first_arr[index];
    }

    /* Add the second array to the new array*/
    for (index = 0; index < size_second; index++) {   
        merged_arr[index + size_first] = second_arr[index];
    }
    
    /* Return the new array that has elements from both 
    arrays */
    return merged_arr;
}

/*Counts size of the array including the NULL at the end*/
int count_size(char **arr) {
    int size = 0;

    /*Loop goes through each element until
      it reaches NULL and increments i*/
    while (arr[size]) {
        size++;
    }

    /*return size*/
    return size + 1;
}

/* This function frees memory from an array of strings, 
 used to free the return of **split */
void free_args(char **arr) {
    int i=0;

    /*Loop goes through each element until
      it reaches NULL*/
    while (arr[i]) {
        free(arr[i]);
        i++;
    }

    /* Free the location*/
    free(arr);
}
