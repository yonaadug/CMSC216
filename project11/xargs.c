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
void free_file_args (char **file_args);
int count_size (char **arr);


int main (int argc, char *argv[]) {

    int pid, line_pid = -1;
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

            while (read_line(line) != EOF && line_pid != 0) {

                if (getpid() == line_pid) {
                    wait(NULL);
                    free(file_args);
                    free_file_args(file_args2);
                }
                
                
                /*free section after argv in file_args*/
                file_args2 = split(line);
                file_args = merge_arr(argv + 2, file_args2, argc-2);
                line_pid = safe_fork();
            }
            
            execv(argv[2], file_args);
            


        } else if (argc == 2 && !strcmp(argv[1], "-i")) {
            /* Run one line at a time mode with without 
            target-program */

            while (read_line(line) != EOF && line_pid != 0) {
                /* Read line then fork, then let child exit loop while parent continues
                in the loop */

                if (line_pid == getpid()) {
                    wait(NULL); 

                    /* free memory from the file_args and temp 
                    from parent */
                    free_file_args(file_args);
                    free(temp);
                }

                temp = malloc(sizeof(char) * 11);
                strcpy(temp, "/bin/echo ");
                
                file_args = merge_arr(&temp, split(line), 1);
                line_pid = safe_fork();
            }
            
            execv(file_args[0], file_args);

            
        } else if (argc >= 2 && strcmp(argv[1], "-i")) {
            /* Standard mode and just target-program with 
            possible target_args */

            read_input(line);
            file_args2 = split(line);
            file_args = merge_arr(argv + 1, file_args2, argc - 1);
	    
            execv(file_args[0], file_args);
            
        } else {
            /* Standard mode with no target-program */


            read_input(line);
            temp = malloc(sizeof(char) * (strlen(line) + 12));
            strcpy(temp, "/bin/echo ");
            strncat(temp, line, strlen(line) + 12);
            
            file_args = split(temp);
            
            execv(file_args[0], file_args);

        }

    } else {
        /*Parent will be responsible for freeing everthing*/

        /*Wait for all children to free all allocated*/
        wait(NULL);

        /*free literally everything, because 1st ammendment :) */
        free(line);
        free(temp);
        free_file_args(file_args);

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

    line[index-1] = '\n';

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
    input[index] = '\0';
}

/* Takes two string arrays and takes the elemnts and puts it in one 
 merged array. The int variable indicates the size of the first
 array of strings to copy into new array of strings*/
char **merge_arr(char **first_arr, char **second_arr, int size_first) {

    int index,
        size_second = count_size(second_arr),
        new_size = sizeof(char *) * (size_first + size_second);
   
    char **merged_arr = malloc(new_size);

    printf("%d",size_second);

    for (index = 0; index < size_first; index++) {
        merged_arr[index] = first_arr[index];
    }

    for (index = 0; index < size_second; index++) {   
        merged_arr[index + size_first] = second_arr[index];
    }
    
    return merged_arr;
}

/*Frees every element in file_args and also file_args*/
void free_file_args(char **file_args) {

    /*Variable holds number of elements in file_args*/
    int i, size = count_size(file_args);

    /*Variable of size used to free the elements*/
    for (i = 0; i < size-1; i++) {
        free(file_args[i]);
    }

    free(file_args);
}

/*Counts size of the array including the NULL at the end*/
int count_size(char *arr[]) {
    /*int i = 0;
    while (arr + i != NULL) {
        i++;
    }
    return i+1;*/
    printf("%d, %d hsda", (int) sizeof(arr), (int) sizeof(char *));
    return (sizeof(arr) / sizeof(char *));
}
