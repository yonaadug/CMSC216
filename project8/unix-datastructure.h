#if !defined(UNIX_DATASTRUCT_H) 
#define UNIX_DATASTRUCT_H

typedef enum {file, folder} Data_type;

typedef struct data {
    
    Data_type data_type;

    struct data *parent;
    struct data *next;

    struct data *child;

    char *name;

} Data;


typedef struct unix {
    Data *root;
    Data *curr_dir;
} Unix;

#endif