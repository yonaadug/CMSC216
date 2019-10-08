#include <stdio.h>

void printLine(char file[], int line_count);

int main() {
  
  char file[999];
  int i = 0;
  char c;

  /*
   This loop will read input and print lines with
   correct number of spaces when a tab character is
   used
   */
  do {

    c = getchar();
    
      /*Not a new line character, so put 'c' in the array*/
    file[i] = c;
    i++;

    if (c == '\n' || c == EOF) {
      /*New line character in 'c' so print the
	line stored in the array and print a new line after*/
      printLine (file, i);

      i = 0;
    }
    
  } while (c != EOF);
 

  return 0;
}

/*Method that will take the character array and print
 everything inside it. If it sees a tab character, the 
 method will print the respective number of spaces
 */
void printLine (char file[], int line_count) {

  int i, j;
  int tab_space = 0;
  char c;

  /*Processes each character in array*/
  for (j = 0; j < line_count; j++) {
    c = file[j];

    if (c == '\t') {
      /*tab character detected*/
      
      tab_space = 8 - (j % 8);

      /*Loop will print spaces, replacing the tab*/
      for (i = 0; i < tab_space; i++) {
	printf(" ");
      }
      
    } else if (c != EOF) {
      /*Print every character if it is not a tab*/
      printf("%c",c);
    }
      
  }

  return;
}

