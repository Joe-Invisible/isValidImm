#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct RotateState {
	char isValid			: 1;	// A boolean value indicating whether is the immediate valid. 1 for valid and 0 otherwise.
	char : 3;
	unsigned char rotate	: 4;	// Half the number of bits rotated right.
	unsigned char encoded	: 8;	// The actual immediate value encoded into the instruction.
	short : 16;
} RS;

/* 
Note: depending on the compiler, aggregates may not be returned from EAX (?). 
In the case of MSVC compiler, it does return this tiny RS by register. Please
kindly use the prepared executable or do a type punning in case the compiler 
does not want to cooperate.
*/

extern RS isValidImm(int32_t n);

RS fromInt32(int32_t _rs) {
	return *(RS*)&_rs;
}

int main(int argc, char** argv) {
	if (argc < 3 && printf_s("Invalid syntax - vimm num base\n")) return -1;
	
	int32_t imm = (int32_t)strtoll(argv[1], NULL, strtol(argv[2], NULL, 10));
	RS result = isValidImm(imm);

	if (result.isValid) {
		printf_s("Valid! Right rotation: %d; Encoding: 0x%X.\n", result.rotate * 2, result.encoded);
		return 0;
	}
	printf_s("Invalid!\n");

	return 0;
}