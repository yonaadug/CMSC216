/* Yonathan Kebede
 * UID: 115659780
 * Discussion Section: 0302
 * I pledge on my honor that I have not given or recieved
 * any unauthorized assistance on this examination or assignment.
 *
 */


#include <stdio.h>
#include "machine.h"


unsigned int get_opcode(Word instruction) {
  return instruction >> 28;
}

unsigned int get_addr_im(Word instruction) {
  return (instruction >> 9) & 0x7ffff;
}

unsigned int get_r1(Word instruction) {
  return (instruction >> 6) & 0x7;
}

unsigned int get_r2(Word instruction) {
  return (instruction >> 3) & 0x7;
}

unsigned int get_r3(Word instruction) {
  return instruction & 0x7;
}

int print_instruction(Word instruction) {

  int opcode_num, r1, r2, r3;
  char opcode[15][5] = {"plus", "diff", "mult", "quot", "mod", "and",
                        "or", "not", "br", "read", "wrt", "move", "lw",
                        "sw", "li"};
  
  if (is_valid_instruction(instruction)) {

    /*Get and print opcode*/    
    opcode_num = get_opcode(instruction);
    printf("%-7s", opcode[opcode_num]);

    
    /*Get and print registers*/
    r1 = get_r1(instruction);
    printf("R%d", r1);

    if (opcode_num <= NOT || opcode_num == MOVE) {
      r2 = get_r2(instruction);
      printf("  R%d", r2);
    }

    if (opcode_num <= OR) {
      r3 = get_r3(instruction);
      printf("  R%d", r3);
    }


    /*If opcode uses memory address/operand, and is memory address 
      add leading zeros for up to five digits, else the li opcode*/
    if (opcode_num == BR || opcode_num == LW ||
        opcode_num == SW) {
      
      /*print address*/
      printf(" %05d", get_addr_im(instruction));
    } else if (opcode_num == LI) {

      /*print immediate*/
      printf(" %d", get_addr_im(instruction));
    }

  }


  return 0;
  
}


  
int disassemble(const Word program[], unsigned int instr_num,
                unsigned int data_num) {

  int mem_address = 0;
  int i;

  if (program != NULL && instr_num >= 1 &&
      (instr_num + data_num) <= NUM_WORDS) {


    /*loop through program array*/
    for (i = 0; i < (instr_num + data_num); i++) {

      printf("%04x: ",mem_address);
      mem_address += 4;
      
      if (i < instr_num) {
        /*print code segment*/
        print_instruction(program[i]);
        printf("\n");
      } else {
        /*print data segment*/
        printf("%08x\n", program[i]);

      }
      
    }

    return 1;
    
  } else {
    
    return 0;
  }

}


int is_valid_instruction(Word word) {

  int opcode = get_opcode(word);
  int r1 = get_r1(word);
  int r2 = get_r2(word);
  int r3 = get_r3(word);
  int address = get_addr_im(word);

  int invalid_reg = r1 == 7 ||
    (r2 == 7 && (opcode <= NOT || opcode == MOVE)) ||
    (r3 == 7 && (opcode <= OR));

  int invalid_addr = (opcode == BR || opcode == LW || opcode == SW)
    && (address >= NUM_BYTES || address % 4 != 0);

  int invalid_opcode_reg = (opcode != BR && opcode != WRT &&
                            opcode != SW) && (r1 == R0 || r1 == R6);  
  
  /*if invalid return 0 else return 1*/
  if (opcode == 15 || invalid_reg ||
      invalid_addr || invalid_opcode_reg) {

    return 0;
  }


  return 1;

}

  
int relocate(const Word program[], unsigned int instr_num,
             unsigned int data_num, int offset, Word relocated_program[],
             unsigned short *const instrs_changed) {
  
  int opcode, address, word, i;
  *instrs_changed = 0;

  
  /*If invalid, return 0*/
  if (program == NULL || (instr_num + data_num) > NUM_WORDS ||
      instr_num == 0 || (offset % 4) != 0 || instrs_changed == NULL) {    
    return 0;
  }


  for (i = 0; i < instr_num; i++) {
    word = program[i];
    opcode = get_opcode(word);

    /*return 0 if instruction in program is invalid*/
    if (!is_valid_instruction(word)) {
      return 0;
    }

    /*checks if opcode is */
    if (opcode == BR || opcode == LW || opcode == SW) {

      address = get_addr_im(word) + offset;
      /*Make sure address is divisible by 4, less than 12288 and more than 0*/
      if (address % 4 || address > 12287 || address < 0) {
        return 0;
      }
      
      /*rewrite word instruction with valid new address*/
      word = (((opcode << 19) | address) << 9) | (word & 0x1ff);
      *instrs_changed += 1;
      
    }

    relocated_program[i] = word;    
  }

  for (i = instr_num; i < instr_num + data_num; i++) {
    relocated_program[i] = program[i];
  }

  return 1;
  
}
