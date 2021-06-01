#ifndef DEFINES_H_
#define DEFINES_H_

#include <stdlib.h>
#include <stdint.h>

#define REG_WIDTH 32
#define reg_t uint##REG_WIDTH_t

#define MEMSIZE 1024
#define NREGS 16
#define NO_PROC 0
#define BOT 0

typedef uint32_t proc_t;

enum ins_t
{
	LD = 1,
	ST,
	LDA,
	STL,
	LDX,
	STX,
	LDAX,
	STLX,
	ASSIGN,
	DMBLD,
	DMBST,
	DMBSY,
	ISB,
	ACI,
	TERM,		// Terminate, i.e. special last instruction
};

enum op_type
{
	PLUS = 1,
	MINUS,
	MULT,
	EQ, 		// comparison instructions begin
	GEQ,
	LEQ,
	NEQ,
	XOR,
};

enum status_t
{
	FETCH = 1,
	INIT,
	COMMIT
};

enum parse_node_type{
	VAL = 1,			// Has a literal value (3,4,23,...)
	REG,				// Has a register with ID given
	OP,					// Is an operand
};

#endif