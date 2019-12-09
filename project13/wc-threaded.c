/**
 * Name: Yonathan A Kebede
 * UID: 115659780
 * TerpConnect: ykebed12
 * Section: 0302
 * 
 * Description: This program replicates the Unix program "wc"
 *              that calculates the total word count, character
 *              count and line count in the arguments, or files
 *              given.
 * 
 * I pledge on my honor that I have not given or recieved
 * any unauthorized assistance on this examination or assignment.
 */ 

#include <stdio.h>
#include <ctype.h>
#include <pthread.h>
#include <stdlib.h>

/*
 * This function counts the words, lines and
 * characters in each file passed to this program
 * and returns it through the argument passed
 * 
 */ 
void *count(void *file_and_args);

/*
 * Struct for the arguments passed into
 * the thread
 */
struct thread_args {
    int lines;
    int words;
    int chars;
    char *file;
       
};

/* Main Function */
int main (int argc, char *argv[]) {

    /* variables that will hold total words, lines and chars*/
    int total_lines = 0, total_words = 0, total_chars = 0;

    /* arg_num is used for keeping track of argument used in argv*/
    int arg_num = 1, i;
    pthread_t *thread_id;

    if (argc > 1) {

        /* Allocate memory for multiple args */
        struct thread_args **t_args = 
            malloc(sizeof(struct thread_args *) * (argc-1));

        /* Allocate memory for thread id's for different files */
        thread_id = malloc(sizeof(pthread_t) * (argc-1));


        /* Loop through each argument in argv to pass into thread */
        while (arg_num < argc) {

            /* Allocate memory for struct*/
            t_args[arg_num-1] = malloc(sizeof(struct thread_args));
            t_args[arg_num-1]->file = argv[arg_num];
            

            /* Create thread*/
            pthread_create(&thread_id[arg_num-1], NULL, &count, t_args[arg_num-1]);
            
            arg_num++;
            
        }

        /* Get results from each thread */
        for (i = 0; i < argc-1; i++) {
            pthread_join(thread_id[i], NULL);

            /* Increment totals */
            total_lines += t_args[i]->lines;
            total_chars += t_args[i]->chars;
            total_words += t_args[i]->words;
            
            free(t_args[i]);
        }

        /* Free all allocated memory */
        free(thread_id);
        free(t_args);

    }

    /* print results */
    printf("%4d %4d %4d\n", total_lines, total_words, total_chars);
    

    return 0;
}
 

void *count(void *file_and_args){

    FILE *fp;

    /* Get the struct args*/
    struct thread_args *t_args = file_and_args; 
    char *filename = t_args->file;
    

    char ch, next_ch;
    /*Variables used for counting lines words and chars*/
    int lines = 0, words = 0, chars = 0;

    fp= fopen(filename, "r");  /* open that file */

    /* silently ignore any problems trying to open files */
    if (fp != NULL) {

        /* read each file one character at a time, until EOF */
        ch= fgetc(fp);

        while (!feof(fp)) {
            next_ch= fgetc(fp);  /* look ahead and get the next character */
            ungetc(next_ch, fp);  /* unread the next character (see Chapter 15) */

            /* update the counts as needed every time a character is read */

            /* a newline means the line count increases */
            if (ch == '\n') {
                lines++;
            }

            /* if the current character is not whitespace but the next character
            is, or if the current character is not whitespace and it is the
            last character in the input, the word count increases */
            if (!isspace(ch) && (isspace(next_ch) || feof(fp))) {
                words++;
            }

            /* increasing the character count is a no-brainer */
            chars++;

            ch = fgetc(fp);
        }

        /* close the file */
        fclose(fp);
    }

    /*Return the lines, words and chars in the file*/
    t_args->lines = lines;
    t_args->words = words;
    t_args->chars = chars;

    return NULL;
}