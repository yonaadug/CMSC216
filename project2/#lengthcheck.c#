#include <stdio.h>

void printLine (char file[], int line_size);

int main() {

  char file[999];
  char c;
  int i = 0;

  /*read input and print output till you 
reach the EOF character*/
  do {

    c = getchar();
    
    if (c == '\n') {
      
      /*New line character found so it will 
	print the line*/
      printLine(file, i);
      i = 0;
      printf("\n");
      
    } else if (c != EOF){
      /*Load characters into array*/
      
      file[i] = c;
      i++;
      
    }
      
  } while (c != EOF);
  

  return 0;
}

/*Method that will print each line with the 
  correct format
*/  
void printLine (char file[], int line_size) {

  int i;

  if (line_size > 80) {
    printf ("X %3d: ", line_size);
  } else {
    printf ("  %3d: ", line_size);
  }

  for (i = 0; i < line_size; i++) {
    printf ("%c", file[i]);
  }

  return;
}
    
    
    
