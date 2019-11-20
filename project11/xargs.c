/* Name: Yonathan Adugna Kebede
 * TerpID: ykebed12
 * UID: 115659780
 *
 * I pledge on my honor that I have not given or recieved
 * any unauthorized assistance on this examination or assignment.
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

char read_line (char *line);
void read_input (char *input);
char ** merge_arr (char **first_arr, char **second_arr, int size);
int count_size (char **arr);
void free_args (char **arr);


int main (int argc, char *argv[]) {

    int pid, line_pid, status;
    char *line, *temp = NULL, **file_args = NULL, **file_args2 = NULL;    
    
    line = malloc(sizeof(char) * 1000);

    pid = safe_fork();

    /* if fork unsuccessful, exit program */
    if (pid < 0) {
        exit(1);
    }


    if (pid == 0) { 
        /*Child process*/
        

        if (argc > 2 && !strcmp(argv[1], "-i") ) {
            /* Run one line at a time mode with target-program and 
            target-args */

            while (read_line(line) != EOF ) {


                line_pid = safe_fork();
                
                if (line_pid > 0) {

                    wait(&status);

                    free(file_args);
                    free_args(file_args2);

                    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                        exit(1);
                    }

                } else {

                    
                    file_args2 = split(line);
                    file_args = merge_arr(argv + 2, file_args2, argc-2);
                    execvp(argv[2], file_args);

                }
                
                
                /*free section after argv in file_args*/
                
                
            }
            
            
            


        } else if (argc == 2 && !strcmp(argv[1], "-i")) {
            /* Run one line at a time mode with without 
            target-program */

            temp = malloc(sizeof(char) * 5);
            strcpy(temp, "echo");

            while (read_line(line) != EOF) {
                /* Read line then fork, then let child exit loop while parent continues
                in the loop */


                line_pid = safe_fork();

                if (line_pid > 0) {
                    wait(&status);

                    free_args(file_args2);         

                    
 
                } else {
                    file_args2 = split(line);
                    
                    file_args = merge_arr(&temp, file_args2, 1);
                    execvp(temp, file_args);
                }
            }

            free(temp);
            
        } else if (argc >= 2 && strcmp(argv[1], "-i")) {
            /* Standard mode and just target-program with 
            possible target_args */

            read_input(line);

            
            file_args2 = split(line);
            file_args = merge_arr(argv + 1, file_args2, argc - 1);

            line_pid = safe_fork();

            if (line_pid > 0) {
                wait(&status);
                free_args(file_args2);
            } else {
                execvp(file_args[0], file_args);
            }
            
            
            
        } else {
            /* Standard mode with no target-program */


            read_input(line);
            temp = malloc(sizeof(char) * (strlen(line) + 12));
            strcpy(temp, "/bin/echo ");
            strcat(temp, line);
            
            file_args = split(temp);
            
            execv(file_args[0], file_args);

        }

    } else {
        /*Parent will be responsible for freeing everthing*/

        /*Wait for all children to free all allocated*/
        wait(&status);


        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            exit(1);
        }

        /*free literally everything, because 1st ammendment :) */
        free(line);
        free(temp);

        exit(0);
    }

    return 0;
}

char read_line(char *line) {

    int index = 0;
    char c;

    while ((c = getchar()) != '\n' && c != EOF) {
        line[index] = c;
        index += 1;
    }

    line[index] = '\n';
    line[index+1] = '\0';

    return c;
}

/**/
void read_input(char *input) {
    char c;
    int index = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
	        c = ' ';
	    }
	    
        input[index] = c;
        index += 1;
    }

    input[index] = '\n';
    input[index + 1] = '\0';
}

/* Takes two string arrays and takes the elemnts and puts it in one 
 merged array. The int variable indicates the size of the first
 array of strings to copy into new array of strings*/
char **merge_arr(char **first_arr, char **second_arr, int size_first) {

    int index,
        size_second = count_size(second_arr),
        new_size = sizeof(char *) * (size_first + size_second);
   
    char **merged_arr = malloc(new_size);


    for (index = 0; index < size_first; index++) {
        merged_arr[index] = first_arr[index];
    }

    for (index = 0; index < size_second; index++) {   
        merged_arr[index + size_first] = second_arr[index];
    }
    
    return merged_arr;
}

/*Counts size of the array including the NULL at the end*/
int count_size(char **arr) {
    int i = 0;

    while (arr[i]) {
        i++;
    }

    return i+1;
}

void free_args(char **arr) {
    int size = count_size(arr), i;

    for (i = 0; i < size; i++) {
        free(arr[i]);
    }

    free(arr);
}
