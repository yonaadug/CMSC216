
#include "student.h"
#include <string.h>
#include <stdlib.h>

Student *new_student(const char name[], unsigned int id, float shoe_size) {

    Student * student = malloc(sizeof(Student));
    student->id = id;
    student->shoe_size = shoe_size;
    
    if (name == NULL) {
        student->name = malloc(sizeof(char));
        strcpy(student->name, "");
    } else {
        student->name = malloc((strlen(name) + 1) * sizeof(char));
        strcpy(student->name, name);

    }
    
    return student;
}


unsigned int has_id(Student *const student, unsigned int id) {
    return (student == NULL)? 0: student->id == id;
}

unsigned int has_name(Student *const student, const char name[]) {
    return (name != NULL) && (student != NULL) && (!strcmp(student->name, name));
}

unsigned int get_id(Student *const student) {
    return (student == NULL)? 0: student->id;
}

float get_shoe_size(Student *const student) {
    return (student == NULL)? 0.0: student->shoe_size;
}

void change_shoe_size(Student *const student, float new_shoe_size) {
    if (student != NULL) {
        student->shoe_size = new_shoe_size;
    }
    return;
}

void change_name(Student *const student, const char new_name[]) {
    if (student != NULL) {
        if (new_name == NULL) {
            student->name = realloc(student->name, (sizeof(char)));
            strcpy(student->name, "");
        } else {
            student->name = realloc(student->name, (strlen(new_name) + 1) * sizeof(char));
            strcpy(student->name, new_name);
        } 
    }

    return;
}

void copy_student(Student *student1, Student *const student2) {
    if (student1 != NULL && student2 != NULL) {

        student1->shoe_size = student2->shoe_size;
        student1->id = student2->id;
        change_name(student1, student2->name);
    }

    return;
}