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

char read_line (char *line);
void read_input (char *input);

int main (int argc, char *argv[]) {

    int pid, line_pid;
    char *line, **file_args;
    /*size_t arr_size;*/

    
    
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

            while (read_line(line) != EOF && (line_pid = safe_fork()) != 0) {
                wait();
                free(file_args);
                file_args = split(line);
            }
            
            execv(argv[2], (argv + 2), file_args, NULL);
            


        } else if (argc == 2 && !strcmp(argv[1], "-i")) {
            /* Run one line at a time mode with without 
            target-program */

            while (read_line(line) != EOF && (line_pid = safe_fork()) != 0) {
                wait();
                free(file_args);
                file_args = split(line);
            }
            
            execv("echo", "echo", file_args, NULL);

            
        } else if (argc >= 2 && strcmp(argv[1], "-i")) {
            /* Standard mode and just target-program with 
            target=args */

            read_input(line)
            file_args = split(line);
            execv(argv[1], (argv + 1), line, NULL);
            
        } else {
            /* Standard mode with no target-program */

            read_input(line);
            file_args = split(line);            
            execv("echo", "echo", file_args, NULL);

        }

    } else {
        /*Parent*/
        wait();
        free(line);
        free(file_args);


        exit(0);

    }

    return 0;
}

char read_line (char *line) {

    int index = 0;
    char c;

    while ((c = getchar()) != '\n' && c != EOF) {
        line[index] = c;
        index += 1;
    }

    line[index-1] = '\0';

    return c;
}

void read_input (char *input) {
    char c;
    int index = 0;

    while ((c = getchar()) != EOF) {

        if (c == '\n') {
            c = ' ';
        }
        input[index] = c;
        index += 1;
    }

    input[index-1] = '\0';
}