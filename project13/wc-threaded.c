/**
 * Name: Yonathan A Kebede
 * UID: 115659780
 * TerpConnect: ykebed12
 * 
 * 
 */ 

#include <stdio.h>
#include <ctype.h>
#include <pthread.h>
#include <stdlib.h>

void *count(void *filename);

pthread_t *thread_id;

struct thread_args {
    int lines;
    int words;
    int chars;
    char *file;
       
};

int main (int argc, char *argv[]) {

    int total_lines = 0, total_words = 0, total_chars = 0;
    int arg_num = 1;

    if (argc > 1) {

        struct thread_args *t_args = malloc(sizeof(struct thread_args));
        thread_id = malloc(sizeof(pthread_t)*(argc-1));

        while (arg_num < argc) {

            t_args->file = argv[arg_num];

            pthread_create(&thread_id[arg_num-1], NULL, &count, t_args);
            pthread_join(thread_id[arg_num-1], NULL);

            total_chars += t_args->chars;
            total_lines += t_args->lines;
            total_words += t_args->words;

            arg_num++;
            
        }

    }

    printf("%4d %4d %4d\n", total_lines, total_words, total_chars);

    return 0;
}



void *count(void *file_and_args){

    FILE *fp;
    struct thread_args *t_args = file_and_args; 
    char ch, next_ch, *filename = t_args->file;
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


        fclose(fp);
    }

    t_args->lines = lines;
    t_args->words = words;
    t_args->chars = chars;

    return NULL;
}