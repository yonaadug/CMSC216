/* Name: Yonathan Kebede
 * TerpID: ykebed12
 * UID: 115659780
 *
 * I pledge on my honor that I have not given or recieved
 * any unauthorized assistance on this examination or assignment.
 * 
 * This program uses piping to count the number of words in a
 * file using a Unix application, wc, with a flag "-w". The child
 * process runs the wc application through execlp, and the the parent
 * process obtains the output, the word count and determines if it is
 * longer than or equal to 200 words, which it will say "Long enough!"
 *  or "Too Short!" if it is less than 200 words.
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <errno.h> 
#include <sys/wait.h> 
#include <unistd.h>
#include "safe-fork.h"


int main() { 
  
    int a[2];
    int count;
    int pid, pipe_num;

    /*Make pipe and fork*/
    pipe_num = pipe(a); 
    pid = safe_fork();

    if (pid < 0 || pipe_num < 0) {
        perror("Fork/Pipe error ");
        exit(1);
    }
  
    if (pid == 0) { 
        /*Child*/

        /*change output*/
        close(1);
        dup(a[1]);
        
        execlp("wc", "wc", "-w", NULL); 
    } else {
        /*Parent*/

        /*Chnage input*/
        close(0);
        dup(a[0]);

        /*Scan number of words*/
        scanf("%d", &count);
        if (count >= 200) {

            printf("Long Enough!\n"); 
            exit(0);
        } else {

            printf("Too Short!\n");
            exit(1);
        }
        
    } 

    return 0;
} 