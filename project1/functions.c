#include "functions.h"

/* This file contains 3 functions which calculate:
   .. the sum of cubes from 0 to n
   .. the quadrant number of a point in an x-y graph
   .. the number of occurances of a digit in a number
*/


/* This method calculates the sum of cubes
 * from i = 0 to i = n
 */
int sum_of_cubes(int n) {

  int sum;
  
  if (n >= 0) {
    
    sum = n * n * (n + 1) * (n + 1) / 4;
  } else {
    
    /* n is a negative number so
     * this is invalid and should
     * return -1
     */
    sum = -1;
  }

  return sum;
}

/* This method determines which quadrant a
 * point is, given its x and y value
 */
int quadrant(int x, int y) {

  /* variable that holds the quadrant
     number */
  int quadrant;

  
  if (x == 0 || y == 0){    
    quadrant = -1;  /* No quadrants */
  } else if (x > 0) {

    if (y > 0) {
      quadrant = 1; /* Quadrant 1 */
    } else {
      quadrant = 4; /* Quadrant 4 */
    }

  } else {

    if (y > 0) {
      quadrant = 2; /* Quadrant 2 */
    } else {
      quadrant = 3; /* Quadrant 3 */
    }

  }

  return quadrant;
}

/* This counts the occurances of a digit 
 * in the variable num
 */
int num_occurrences_of_digit(long num, int digit) {

  /* The varianble count, will count the
     the number of times digit appears */
  int count = 0;

  /* if digit is not between 0-9 (inclusive)
     then it is incorrect */
  if (digit > 9 || digit < 0) {
    return (-1);
  }

  /* Change num to positive if negative
     for ease of calculation */
  if (num < 0) {
    num = (-1) * num;
  }
  

  /* do-while loop will cut last digit
     and compare if it is the same as digit */
  while (num > 10) {
    
    if ((num % 10) == digit) {
      count = count + 1;
    }

    num = num / 10; 
    
  }

  /* See if the first number is also the
     digit */
  if (num == digit) {
    count = count + 1;
  }
  
  return count;
}
