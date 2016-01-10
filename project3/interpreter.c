#include<stdio.h>
#include "machine.h"
#include "interpreter.h"

/*
Takes a program of SPIM instructions and loads them into SPIM's
memory starting from address 0, it then sets the R11 program counter
to 0.

Returns 1 if successfully loaded
Returns 0 if failed/invalid params
 */
int load_program(Machine *const spim, const Word program[], int program_size) {
  int count = 0;
  if ((spim == NULL || program == NULL) || (program_size >
					    (sizeof(spim->memory)/4))) {
    return 0;
  } else {
    if (program_size < 0) {
      spim->registers[R11] = 0; /* reset counter register R11 to 0 */
      return 1;
    } else {
      while (count <= program_size) {
	if (count == program_size) {
	  spim->registers[R11] = 0; /* reset counter register R11 to 0 */
	  return 1; /* program loaded */
	} else {
	  spim->memory[count] = program[count]; /* store instructions */
	  count++;
	}
      }
    }
  }
  return 0;
}

Status run_SPIM_program(Machine *const spim, int max_instr,
			int *const num_instr, int trace_flag) {
  Word instr;
  unsigned int op;
  unsigned int reg1;
  unsigned int reg2;
  unsigned int reg3;
  unsigned int addr;
  *num_instr = 0;
  
  if (spim == NULL || num_instr == NULL) { /*invalid param*/
      return PARAMETER_ERROR;
  } else if (max_instr <= 0) { /*no process*/
      return TIMEOUT;
  }
   
  while (*num_instr <= max_instr) { /*perform fetch-decode-execute*/
    if (spim->memory[(spim->registers[R11])/4] == 0) { /*hit a halt command*/
      return HALTED;
    } else if (*num_instr == max_instr) { /*reached max_instr*/
      return TIMEOUT;
    } else if (valid_instruction(spim->memory[(spim->registers[R11])/4]) == 0) {
      return INVALID_INSTRUCTION;
    } else {
    /*do the command*/
      instr = spim->memory[(spim->registers[R11])/4]; /*get instr*/
      op = instr & 0xf0000000;
      op = op >> 28; /*isolate opcode*/

      reg1 = instr & 0x0f000000;
      reg1 = reg1 >> 24; /*isolate reg1*/

      reg2 = instr & 0x00f00000;
      reg2 = reg2 >>  20; /*isolate reg2*/

      reg3 = instr & 0x000f0000;
      reg3 = reg3 >> 16; /*isolate reg3*/

      addr = instr & 0x0000ffff; /*isolate memory addr*/

      if (op == 1) { /*add*/
	spim->registers[reg1] = spim->registers[reg2] + spim->registers[reg3];
	(*num_instr)++;
	spim->registers[R11] += 4;
      } else if (op == 2) { /*mul*/
	spim->registers[reg1] = spim->registers[reg2] * spim->registers[reg3];
	(*num_instr)++;
	spim->registers[R11] += 4;
      } else if (op == 3) { /*neg*/
	spim->registers[reg1] = spim->registers[reg2] * -1;
	(*num_instr)++;
	spim->registers[R11] += 4;
      } else if (op == 4) { /*shl*/
	spim->registers[reg1] = spim->registers[reg2] << addr;
	(*num_instr)++;
	spim->registers[R11] += 4;
      } else if (op == 5) { /*and*/
	spim->registers[reg1] = spim->registers[reg2] && spim->registers[reg3];
	(*num_instr)++;
	spim->registers[R11] += 4;
      } else if (op == 6) { /*not*/
	spim->memory[reg1] = !(spim->memory[reg2]);
	(*num_instr)++;
	spim->registers[R11] += 4;
      } else if (op == 7) { /*lw*/
	spim->registers[reg1] = spim->memory[addr/4];
	(*num_instr)++;
	spim->registers[R11] += 4;
      } else if (op == 8) { /*li*/
	spim->registers[reg1] = addr;
	(*num_instr)++;
	spim->registers[R11] += 4;
      } else if (op == 9) { /*sw*/
	spim->memory[addr/4] = spim->registers[reg1];
	(*num_instr)++;
	spim->registers[R11] += 4;
      } else if (op == 10) { /*move*/
	spim->registers[reg1] = spim->registers[reg2];
	(*num_instr)++;
	spim->registers[R11] += 4;
      } else if (op == 11) { /*bne*/
	if (spim->registers[reg1] != spim->registers[reg2]) {
	  (*num_instr)++;
	  spim->registers[R11] = addr;
	} else {
	  (*num_instr)++;
	  spim->registers[R11] += 4;
	}
      } else if (op == 12) { /*read*/
	scanf("%d", &(spim->registers[reg1]));
	(*num_instr)++;
	spim->registers[R11] += 4;
      } else if (op == 13) { /*write*/
	printf("%d\n", spim->registers[reg1]);
	(*num_instr)++;
	spim->registers[R11] += 4;
      }
    }
  }
  return TIMEOUT;
}

/*
Resets the SPIM machine, simply resets the R11 counter register
back to 0. No other modification done so that the currently loaded
program can be restarted again from beginning

Returns 1 if reset is successful
Returns 0 if failed/invalid params
 */
int reset(Machine *const spim) {
  if (spim == NULL) {
    return 0;
  } else {
    spim->registers[R11] = 0;
    return 1;
  }
}
