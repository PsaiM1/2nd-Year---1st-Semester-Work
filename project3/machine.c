#include<stdio.h>
#include "machine.h"
/*
  Author: PrasannaSai Meruga
  Class: CMSC216, Herman
  Section: Majeed 10 AM

  The purpose of this program is to provide some of the basic functions
  that will manipulate the instructions that will be used in the SPIM
  processor. 

*/

/*
  Prints the instruction that is passed in as the parameter
  prints the instruction name,registers, and memory address depending on
  the instruction
*/
void print_instruction(Word instruction) {
  Word temp = instruction;
  Word temp2 = instruction;
  Word temp3 = instruction;
  Word temp4 = instruction;
  Word temp_instruct = instruction;
  
  temp = temp & 0xf0000000;
  temp = temp >> 28;

  temp2 = temp2 & 0x0f000000; /* contains reg1*/
  temp2 = temp2 >> 24;

  temp3 = temp3 & 0x00f00000; /* contains reg2*/
  temp3 = temp3 >> 20;

  temp4 = temp4 & 0x000f0000; /* contains reg3*/
  temp4 = temp4 >> 16;

  temp_instruct = temp_instruct & 0x0000ffff; /*isolates the address*/
  
  if (temp == 0) {
    printf("halt\n");
  } else if (temp == 1) {
    printf("add R%02d R%02d R%02d\n", temp2, temp3, temp4);
  } else if (temp == 2) {
    printf("mul R%02d R%02d R%02d\n", temp2, temp3, temp4);
  } else if (temp == 3) {
    printf("neg R%02d R%02d\n", temp2, temp3);
  } else if (temp == 4) {
    printf("shl R%02d R%02d %05d\n", temp2, temp3, temp_instruct);
  } else if (temp == 5) {
    printf("and R%02d R%02d R%02d\n", temp2, temp3, temp4);
  } else if (temp == 6) {
    printf("not R%02d R%02d\n", temp2, temp3);
  } else if (temp == 7) {
    printf("lw R%02d %05d\n", temp2, temp_instruct);
  } else if (temp == 8) {
    printf("li R%02d %05d\n", temp2, temp_instruct);
  } else if (temp == 9) {
    printf("sw R%02d %05d\n", temp2, temp_instruct);
  } else if (temp == 10) {
    printf("move R%02d R%02d\n", temp2, temp3);
  } else if (temp == 11) {
    printf("bne R%02d R%02d %05d\n", temp2, temp3, temp_instruct);
  } else if (temp == 12) {
    printf("read R%02d\n", temp2);
  } else if (temp == 13) {
    printf("write R%02d\n", temp2);
  }
}

/*
  Goes through an array of instructions and prints out their addresses
  and then the output from the print_instructions function. It continues
  to print for every instruction until the number of instructions printed
  is at most num_words, could possibly be less due to invalid instruction
*/
int disassemble(const Word memory[], int starting_address, int num_words) {
  if ((starting_address % 4 == 0) && (starting_address < 12288/4) && 
      (starting_address >= 0) && (memory != NULL) && (starting_address/4
						      + num_words < 12288/4)) {
    if (num_words <= 0) {
      return 0;
    } else {
      int count = 0;
      int index = starting_address/4;
      while (count <= num_words) {
	/*check for valid instruct*/
	if (valid_instruction(memory[index]) && (count != num_words)) {
	  printf("0x%04x: ", index * 4);
	  print_instruction(memory[index]);
	  index++;
	  count++;
        } else { /*early invalid instruct or count = num_words*/
	  return count;
        }	
      }
    }
  } else {
    return -1; /*invalid params*/
  }

  return 0;
}

/*
  Takes the opcode, reg1, reg2, reg3, and memory_addr and makes an instruction
  that is stored in the const pointer instruction
*/
int encode_instruction(unsigned int opcode, unsigned int reg1,
		       unsigned int reg2, unsigned int reg3,
		       unsigned int memory_addr, Word *const instruction) {
  /*bit shift the ints to the appropriate bit positions for use later*/
  unsigned int opcode_temp = opcode << 28;
  unsigned int reg1_temp = reg1 << 24;
  unsigned int reg2_temp = reg2 << 20;
  unsigned int reg3_temp = reg3 << 16;
  
  /* checks for valid params and valid instruction */
  if ((opcode >= 0 && opcode <= 13) && (reg1 > 0 && reg1 < 11) &&
      (reg2 >= 0 && reg2 <= 11) && (reg3 >= 0 && reg3 <= 11) &&
      (memory_addr >= 0 && memory_addr <= 49152) && (memory_addr % 4 == 0)
      && instruction != NULL) {
    
    *instruction = *instruction & 0; /* clears to zero */
    if (opcode == 0) { /*special case for halt*/
      *instruction = *instruction & 0;
      return 1;
    }
   
    if (opcode == 1) {
      *instruction = *instruction | opcode_temp;
      *instruction = *instruction | reg1_temp;
      *instruction = *instruction | reg2_temp;
      *instruction = *instruction | reg3_temp;
      return 1;
    } else if (opcode == 2) {
      *instruction = *instruction | opcode_temp;
      *instruction = *instruction | reg1_temp;
      *instruction = *instruction | reg2_temp;
      *instruction = *instruction | reg3_temp;
      return 1;
    } else if (opcode == 3) {
      *instruction = *instruction | opcode_temp;
      *instruction = *instruction | reg1_temp;
      *instruction = *instruction | reg2_temp;
      return 1;
    } else if (opcode == 4) {
      if (memory_addr > 31) { /*shl cannot shift more than 31*/
	return 0;
      } else {
	*instruction = *instruction | opcode_temp;
	*instruction = *instruction | reg1_temp;
	*instruction = *instruction | reg2_temp;
	*instruction = *instruction | memory_addr;
	return 1;
      }
    } else if (opcode == 5) {
      *instruction = *instruction | opcode_temp;
      *instruction = *instruction | reg1_temp;
      *instruction = *instruction | reg2_temp;
      *instruction = *instruction | reg3_temp;
      return 1;
    } else if (opcode == 6) {
      *instruction = *instruction | opcode_temp;
      *instruction = *instruction | reg1_temp;
      *instruction = *instruction | reg2_temp;
      return 1;
    } else if (opcode == 7) {
      *instruction = *instruction | opcode_temp;
      *instruction = *instruction | reg1_temp;
      *instruction = *instruction | memory_addr;
      return 1;
    } else if (opcode == 8) {
      *instruction = *instruction | opcode_temp;
      *instruction = *instruction | reg1_temp;
      *instruction = *instruction | memory_addr;
      return 1;
    } else if (opcode == 9) {
      *instruction = *instruction | opcode_temp;
      *instruction = *instruction | reg1_temp;
      *instruction = *instruction | memory_addr;
      return 1;
    } else if (opcode == 10) {
      *instruction = *instruction | opcode_temp;
      *instruction = *instruction | reg1_temp;
      *instruction = *instruction | reg2_temp;
      return 1;
    } else if (opcode == 11) {
      *instruction = *instruction | opcode_temp;
      *instruction = *instruction | reg1_temp;
      *instruction = *instruction | reg2_temp;
      *instruction = *instruction | memory_addr;
      return 1;
    } else if (opcode == 12) {
      *instruction = *instruction | opcode_temp;
      *instruction = *instruction | reg1_temp;
      return 1;
    } else if (opcode == 13) {
      *instruction = *instruction | opcode_temp;
      *instruction = *instruction | reg1_temp;
      return 1;
    }
  } else { /* not valid params */
    return 0; 
  }

  return 0;
}

/*
  Checks if the instruction passed in is valid by checking if the instructions
  opcode, registers, and memory address fall within the appropriate ranges
  and have the appropriate properties such as memory addresses being divisible
  by zero.
*/
int valid_instruction(Word instruction) {
  Word temp = instruction;
  Word temp2 = instruction;
  Word temp3 = instruction;
  Word temp4 = instruction;
  Word temp_instruct = instruction;
   
  temp = temp & 0xf0000000;
  temp = temp >> 28;

  temp2 = temp2 & 0x0f000000; /* contains reg1*/
  temp2 = temp2 >> 24;

  temp3 = temp3 & 0x00f00000; /* contains reg2*/
  temp3 = temp3 >> 20;

  temp4 = temp4 & 0x000f0000; /* contains reg3*/
  temp4 = temp4 >> 16;

  temp_instruct = temp_instruct & 0x0000ffff; /*isolates the address*/
  if (temp == 0) {
    return 1;
  } else if ((temp == 1) && (temp2 > 0 && temp2 < 11) &&
	     (temp3 >= 0 && temp3 <= 11) && (temp4 >= 0 && temp4 <= 11)) {
    return 1;
  } else if ((temp == 2) && (temp2 > 0 && temp2 < 11) &&
	     (temp3 >= 0 && temp3 <= 11) && (temp4 >= 0 && temp4 <= 11)) {
    return 1;
  } else if ((temp == 3) && (temp2 > 0 && temp2 < 11) &&
	     (temp3 >= 0 && temp3 <= 11)) {
     return 1;
  } else if ((temp == 4) && (temp2 > 0 && temp2 < 11) &&
	     (temp3 >= 0 && temp3 <= 11) &&
	     (temp_instruct >= 0 && temp_instruct <= 49151) &&
	     temp_instruct < 32) {
    return 1;
  } else if ((temp == 5) && (temp2 > 0 && temp2 < 11) &&
	     (temp3 >= 0 && temp3 <= 11) && (temp4 >= 0 && temp4 <= 11)) {
    return 1;
  } else if ((temp == 6) && (temp2 > 0 && temp2 < 11) &&
	     (temp3 >= 0 && temp3 <= 11)) {
    return 1;
  } else if ((temp == 7) && (temp2 > 0 && temp2 < 11) &&
	     (temp_instruct >= 0 && temp_instruct <= 49151) &&
	     (temp_instruct % 4 == 0)) {
    return 1;
  } else if ((temp == 8) && (temp2 > 0 && temp2 < 11) &&
	     (temp_instruct >= 0)) {
    return 1;
  } else if ((temp == 9) && (temp2 >= 0 && temp2 <= 11) &&
	     (temp_instruct >= 0 && temp_instruct <= 49151) &&
	     (temp_instruct % 4 == 0)) {
    return 1;
  } else if ((temp == 10) && (temp2 > 0 && temp2 < 11) &&
	     (temp3 >= 0 && temp3 <= 11)) {
    return 1;
  } else if ((temp == 11) && (temp2 >= 0 && temp2 <= 11) &&
	     (temp3 >= 0 && temp3 <= 11) &&
	     (temp_instruct >= 0 && temp_instruct <= 49151) &&
	     (temp_instruct % 4 == 0)) {
    return 1;
  } else if ((temp == 12) && (temp2 > 0 && temp2 < 11)) {
    return 1;
  } else if ((temp == 13) && (temp2 >= 0 && temp2 <= 11)) {
    return 1;
  } else {
    return 0;
  }
  return 0;
}

