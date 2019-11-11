#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <errno.h> 
#include <sys/wait.h> 
#include <unistd.h> 

#define MSGSIZE 25

int main () { 
  
    int a[2];
    int count;

  
    pipe(a); 

  
    if(!fork()) 
    { 
        close(1);
        dup(a[1]);
        
        execlp("wc","wc","-w", NULL); 
    } 
    else {

        close(0);
        dup(a[0]);

        scanf("%d",&count);
        if (count >= 200) {
            printf("Long Enough!"); 
            exit(0);
        } else {
            printf("Too Short!");
            exit(1);
        }
        
        
        
    } 

    return 0;
} 