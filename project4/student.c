/* Name: Yonathan Kebede
 * TerpID: ykebed12
 * UID: 115659780
 *
 * I pledge on my honor that I have not given or recieved
 * any unauthorized assistance on this examination or assignment.
 *
 */

#include "student.h"
#include <string.h>

/*Creates instance of a student struct*/
Student new_student(const char name[], unsigned int id, float shoe_size) {

  Student student;

  if (name != NULL) {
    strcpy(student.name, name);
  } else {
    strcpy(student.name, "");
  }
  
  student.id = id;
  student.shoe_size = shoe_size;

  return student;
}

/*Initializes an instance of student pointer */
void init_student(Student *const student, const char name[], unsigned int id,
		  float shoe_size) {

  if (student != NULL) {

    if (name != NULL) {
      strcpy(student->name, name);
    } else {
      strcpy(student->name, "");
    }

    student->id = id;
    student->shoe_size = shoe_size;
    
  }

  return;
}

/*Checks if student has a specified id*/
unsigned int has_id(Student student, unsigned int id) {
  return student.id == id;
}

/*Checks if student has a specified name*/
unsigned int has_name(Student student, const char name[]) {

  if (name == NULL) {
    return 0;
  }
  
  return !strcmp(student.name, name);
}

/*Gets id from student*/
unsigned int get_id(Student student) {
  return student.id;
}

/*Get shoe size from student*/
float get_shoe_size(Student student) {
  return student.shoe_size;
}

/*Change shoe_size of the student*/
Student change_shoe_size(Student student, float new_shoe_size) {
  student.shoe_size = new_shoe_size;
  return student;
}

/*Changes the name of the student point*/
void change_name(Student *const student, const char new_name[]) {
  if (student == NULL) {
    return;
    
  } else if (new_name == NULL) {
    strcpy(student->name, "");
    
  } else {
    strcpy(student->name, new_name);
  }

  return;
}
