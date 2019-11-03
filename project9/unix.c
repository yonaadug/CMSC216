/* Name: Yonathan Kebede
 * TerpID: ykebed12
 * UID: 115659780
 *
 * I pledge on my honor that I have not given or recieved
 * any unauthorized assistance on this examination or assignment.
 * 
 * This file contains functions for a unix filesystem simulation
 * in continuation from project 8. The functions created are, pwd,
 * ls, touch, cd, mkdir. 
 */

#include "unix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*Function finds a subdirectory or file in the current directory
  named arg and returns a pointer to it, else it returns NULL */
Data *find_data(const char arg[], Data *curr_dir) {

    Data *found_child;

    if(arg != NULL && curr_dir != NULL && curr_dir->child != NULL) {

        found_child = curr_dir->child;

        /*Loop to go through each child in the in the linked list of 
            subdirectories and files within a folder */
        while (found_child != NULL && strcmp(found_child->name, arg)) {
            found_child = found_child->next;
        }

        /* Returns a found_child or NULL*/
        return found_child;
    }

    return NULL;
}

/* Function inserts a file/folder in the filesystem in order */
void insert_data(Unix *filesystem, Data *new_data) {

    Data *curr_dir, *curr_child, *prev_child = NULL;

    new_data->next = NULL;
    new_data->child = NULL;
    new_data->parent = filesystem->curr_dir;
 
    curr_dir = filesystem->curr_dir;
    curr_child = curr_dir->child;

    /* Make the new file the first child if the
       child of the current directory is NULL
       (current directory is empty) */
    if (curr_child == NULL)
        curr_dir->child = new_data;
    else {

        /* Loop through linked list till we reach NULL or
        strcmp(name,arg) is > 0 */
        while (curr_child != NULL &&
            strcmp(curr_child->name, new_data->name) < 0) {
            
            prev_child = curr_child;
            curr_child = curr_child->next;
        }

        /*check if new_data should be a the beginning*/
        if (prev_child == NULL) {
            
            curr_dir->child = new_data;
            new_data->next = curr_child;

        /* New file is placed in the middle or end of the 
        end of the "child" linked list*/
        } else {
            prev_child->next = new_data;
            new_data->next = curr_child;
        }
    }
}

/* Function prints every subdirectory and file in the current
   directory */
void print_ls(Data *curr_dir) {

    Data *curr_child = curr_dir->child;

    if (curr_child != NULL) {
        
        /*Loop through each child and print files and folder*/
        do {
            /*Print / at end if folder, else print normally*/
            if (curr_child->data_type == folder) {
                printf("%s/\n", curr_child->name);
            } else {
                printf("%s\n", curr_child->name);
            }
            
            curr_child = curr_child->next;

        } while (curr_child != NULL);

    }
}

/* This initializes the unix struct*/
void mkfs(Unix *filesystem) {

    Data *curr_dir;

    if (filesystem != NULL) {
        filesystem->root = malloc(sizeof(Data));

        /*Check if memory was allocated*/
        if (filesystem->root != NULL) {
            filesystem->curr_dir = filesystem->root;
            curr_dir = filesystem->root;

            curr_dir->name = malloc(sizeof(char) * 2);

            /*Check if memory was allocated*/
            if (curr_dir->name != NULL) {
                strcpy(curr_dir->name, "/");
                curr_dir->next = NULL;
                curr_dir->child = NULL;

                /*Root parent is just root, 
                (gives ease for other functions)*/
                curr_dir->parent = curr_dir;

            } else {
                free(filesystem->root);
                printf("\nMemory allocation error\n");
            }
        } else {
            printf("\nMemory allocation error\n");
        }
    } 
}

/* Create file and place it current directory in an ascending
 * order in current directory child linked list of files and
 * folders */
int touch(Unix *filesystem, const char arg[]) {

    Data *new_file;
    
    /* Continue to make file if its not an error according to 
       the project description */
    if (filesystem != NULL && arg != NULL && strcmp("", arg) &&
        !(strchr(arg, '/') != NULL && strlen(arg) > 1)) {

        /* Continue to make file if arg is not ".", "..", or "/" 
           or any of the previously defined folders or files  */
        if (strcmp(".", arg) != 0 && strcmp("..", arg) != 0 && 
            strcmp("/", arg) != 0 &&
            find_data(arg, filesystem->curr_dir) == NULL) {
            
            /*Create new child (file)*/
            new_file = malloc(sizeof(Data));
            
            /* Allocate memory for name if new_file was allocated memory*/
            if (new_file != NULL) {
                new_file->name = malloc(sizeof(char) * (strlen(arg) + 1));
            }

            /*Check if the memory allocation was succesful*/
            if (new_file != NULL && new_file->name != NULL) {

                new_file->data_type = file;
                strcpy(new_file->name,arg);

                insert_data(filesystem, new_file);

            } else {

                /*Free everything if one of the fomponents
                  was not allocated memory successfully*/
                free(new_file->name);
                free(new_file);
                return 0;
            }
        }
        return 1;
    } 
    return 0;   
}

/* This function makes a directory in the current dir
   with a name in arg */
int mkdir(Unix *filesystem, const char arg[]) {

    Data *new_folder;

    /* Continue if function parameters do not result in
       errors*/
    if (filesystem != NULL && arg != NULL &&
        find_data(arg, filesystem->curr_dir) == NULL &&
        strcmp(arg, ".") && strcmp(arg, "..") &&
        strchr(arg, '/') == NULL && strcmp(arg, "")) {
        
        /*Allocate data for the new folder*/
        new_folder = malloc(sizeof(Data));
        new_folder->name = malloc(sizeof(char) * (strlen(arg) + 1));

        /*If allocation was successful, insert new folder*/
        if (new_folder != NULL && new_folder->name != NULL) {
            new_folder->data_type = folder;
            strcpy(new_folder->name,arg);
            insert_data(filesystem, new_folder);

        } else {
            free(new_folder->name);
            free(new_folder);
            return 0;
        }

        return 1;
    }

    return 0;
}

/* Changes current directory in filesystem to arg
   if arg is an existing subdirecory */
int cd(Unix *filesystem, const char arg[]) {

    Data *curr_dir, *next_dir;

    /* Make sure inputs do not result in an error
       according to project description */
    if (filesystem != NULL && arg != NULL && 
        !(strchr(arg, '/') != NULL && strlen(arg) > 1)) {

        curr_dir = filesystem->curr_dir;
        
        if (!strcmp("", arg) || !strcmp(".", arg)) {

            /* no effect because it changes current directory
              to current directory */

        } else if (!strcmp("..", arg)) {

            filesystem->curr_dir = curr_dir->parent;

        } else if (!strcmp("/", arg)) {

            filesystem->curr_dir = filesystem->root;
        
        } else {

            /* if cd is none of the special characters search if a
                a file/subdirectory is in the list*/

            next_dir = find_data(arg, curr_dir);

            if (next_dir != NULL && next_dir->data_type == folder) {
                filesystem->curr_dir = next_dir;

            } else {

                /* Return 0 if directory was not found or arg is filename */
                return 0;
            }
        }

        /* Return 1 if all is valid*/
        return 1;

    }
    /*Return 0 if function parameters are null*/
    return 0;
}

/* Function prints the subdirectory contents or file (arg) */
int ls(Unix *filesystem, const char arg[]) {

    Data *curr_dir, *found_data;

    /* Check if input paramenters are null */
    if (filesystem != NULL && arg != NULL &&
        !(strchr(arg, '/') != NULL && strlen(arg) > 1)) {

        curr_dir = filesystem->curr_dir;
        
        /* validate arg and print accordingly */
        if (!strcmp("", arg) || !strcmp(".", arg)) {

            print_ls(curr_dir);
            
        } else if (!strcmp("..", arg)) {

            print_ls(curr_dir->parent);
        
        } else if (!strcmp("/", arg)) {
            
            print_ls(filesystem->root);
            
        } else {

            found_data = find_data(arg, curr_dir);

            if (found_data != NULL) {

                if (found_data->data_type == file) {
                    printf("%s\n",found_data->name);
                } else {
                    print_ls(found_data);
                }
                
            } else {
                /*return 0 if arg is not an existing file or directory*/
                return 0;
            }
        }
        
        return 1;
    }
    /* return 0 if arg and/or filesystem is NULL*/
    return 0;
}

/* Recursive helper that helps print the pwd from the 
   root to the current directory */
void pwd_helper(Data *curr_dir, Data *root) {

    if (curr_dir != root) {
        pwd_helper(curr_dir->parent, root);
        printf("/%s", curr_dir->name);
    }

}


/* Prints working directory from the root "/" to 
   the current directory */
void pwd(Unix *filesystem) {

    
    if (filesystem != NULL) {

        /* check if current directory is the root*/
        if (filesystem->root != filesystem->curr_dir) {
            /* call to the pwd_helper to print from root*/
            pwd_helper(filesystem->curr_dir, filesystem->root);
            /* print new line after working directory is printed*/
            printf("\n");
        } else {
            /* if current directory is root,
               just print / with new line */
            printf("/\n");
        }

    }
}

/* Helper function that helps delete subdirectories and
   files recursively */
void rmfs_helper(Data *curr_dir) {

    Data *child, *next_child;

    if (curr_dir != NULL) {
        
        child = curr_dir->child;

        /* Loop through each file/folder within the current
        directory */
        while (child != NULL) {

            next_child = child->next;

            /* If the child is a directory, delete recursively
            of its contents */
            if (child->data_type == folder) {
                rmfs_helper(child->child);
            }

            /* free the name and child */
            free(child->name);
            free(child);

            /* reassign child the next element */
            child = next_child;
        }
    }

}

/* This function deallocates every folder and file
   created in the Unix filesystem*/
void rmfs(Unix *filesystem) {

    Data *root;

    if (filesystem != NULL) {

        root = filesystem->root;

        /* This frees any memory with the root */
        rmfs_helper(root);

        /*free memory used by the root and filesystem */
        free(root->name);
        free(root->child);
        free(root->next);
        free(root);
    }
}

/*This function deletes a file or folder if exists and returns 1 if
  it successfully deleted the file. Returns 0 otherwise*/
int rm(Unix *filesystem, const char arg[]) {

    Data *child, *prev_child = NULL;

    if (filesystem != NULL && arg != NULL && strcmp (arg, ".") &&
        strcmp(arg, "..") && strchr(arg, '/') == NULL && strcmp(arg, "") ) {
        
        child = filesystem->curr_dir;

        /* Loop to find the child, while keeping track of 
           the previous element*/
        while (child != NULL && strcmp(child->name, arg)) {
            prev_child = child;
            child = child->next;
        }

        /*if the child is found*/
        if (child != NULL) {

            /* check if the found child is the first node in
               the list and reorganizes the linked list*/
            if (prev_child == NULL) {
                filesystem->curr_dir->child = child->next;
            } else {
                /* reorganizes the list if the found node is 
                   the beginning or end */
                prev_child->next = child->next;
            }

            /* Delete the folder/file*/

            /* if the child is a folder*/
            if (child->data_type == folder) {
                /* this helps delete and folders and files
                   within a folder and any other files and
                   folders within the subdirectories 
                   recursively */
                rmfs_helper(child);
            }

            free(child->child);
            free(child->name);
            free(child);


            return 1;
        }

    }

    return 0;

}


