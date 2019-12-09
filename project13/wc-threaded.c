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
    int *lines;
    int *words;
    int *chars;
    int id;
    char *file;
       
};

/* Main Function */
int main (int argc, char *argv[]) {

    /* variables that will hold total words, lines and chars*/
    int total_lines = 0, total_words = 0, total_chars = 0;

    int arg_num = 1, i;
    pthread_t *thread_id;

    if (argc > 1) {

        /* Allocate memory for the args into thread*/
        struct thread_args *t_args = malloc(sizeof(struct thread_args));
        t_args->chars = malloc(sizeof(int)* (argc-1));
        t_args->words = malloc(sizeof(int)* (argc-1));
        t_args->lines = malloc(sizeof(int)* (argc-1));

        /* Allocate memory for thread id's for different files */
        thread_id = malloc(sizeof(pthread_t) * (argc-1));


        /* Loop through each argument in argv to pass into thread */
        while (arg_num < argc) {

            /* Pass file name and 'id' index */
            t_args->file = argv[arg_num];
            t_args->id = arg_num-1;
            
            pthread_create(&thread_id[arg_num-1], NULL, &count, t_args);
        
            arg_num++;
            
        }

        /* Get results from each thread */
        for (i = 0; i < argc-1; i++) {
            pthread_join(thread_id[arg_num-1], NULL);

            /* Increment totals */
            total_lines += t_args->lines[i];
            total_chars += t_args->chars[i];
            total_words += t_args->words[i];

        }

        /* Free all allocated memory*/
        free(t_args->chars);
        free(t_args->words);
        free(t_args->lines);
        free(t_args);
        free(thread_id);

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
    int id = t_args->id;

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
    t_args->lines[id] = lines;
    t_args->words[id] = words;
    t_args->chars[id] = chars;

    return NULL;
}