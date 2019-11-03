#if !defined(UNIX_DATASTRUCT_H) 
#define UNIX_DATASTRUCT_H

/* Enum type to declare what type of data*/
typedef enum {file, folder} Data_type;

/* Struct for a file or directory type*/
typedef struct data {
    
    /* This helps indicate if data is a 
       folder or file */
    Data_type data_type;

    /* Every data has a link to its parent*/
    struct data *parent;

    /* Data in the same directory is linked 
       with this */
    struct data *next;

    /* Folders use this for accessing any data 
       contained in it. For files, its set to NULL*/
    struct data *child;

    /* This is a pointer to the name of the 
       directory or file */
    char *name;

} Data;


/* Unix Filesystem always has access to the root and 
   current directory */
typedef struct unix {
    Data *root;
    Data *curr_dir;
} Unix;

#endif