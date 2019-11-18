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

int main (int argc, char *argv[]) {

    int pid;
    char *line;
    size_t line_size = 1000;
    

    pid = fork();

    /* if fork unsuccessful, exit program */
    if (pid < 0) {
        exit(1);
    }


    if (pid == 0) { 
        /*Child process*/


        if (argc > 2 && !strcmp(argv[1], "-i") ) {
            /* Run one line at a time mode with target-program and 
               target-args */

        } else if (argc == 2 && !strcmp(argv[1], "-i")) {
            /* Run one line at a time mode with without 
               target-program */

            
        } else if (argc >= 2 && strcmp(argv[1], "-i")) {
            /* Standard mode and just target-program with 
               target=args*/


        } else {
            /* Standard mode with no target-program */
            line = malloc(sizeof(char) * 1000);
            fgets (line, line_size-1, stdin);
            execlp("echo", "echo", line, NULL);



        }



    } else {
        /*Parent*/


        exit(0);

    }

    return 0;
}