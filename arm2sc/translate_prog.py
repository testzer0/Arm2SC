import os
import sys
from enum import Enum

#############################################
# 			     translate.py 			    #
# ========================================= #
# Translates an input AArch64 multi-thread- #
# ed program to an equivalent SC program by #
# making use of context bounding. 			#
#############################################

if len(sys.argv) == 1:
	indir = os.path.join(os.getcwd(), 'bench/burns_unsafe1')
	outfile = os.path.join(os.getcwd(), 'arm2sc/translated.c')
elif len(sys.argv) == 2:
	indir = os.path.join(os.getcwd(), 'bench/'+sys.argv[1])
	outfile = os.path.join(os.getcwd(), 'arm2sc/translated.c')
else:
	indir = os.path.join(os.getcwd(), 'bench/'+sys.argv[1])
	outfile = os.path.join(os.getcwd(), 'arm2sc/'+sys.argv[2])

class InstrType(Enum):
	LD = 1
	LDA = 2
	LDX = 3
	LDAX = 4
	ST = 5
	STL = 6
	STX = 7
	STLX = 8
	ASSIGN = 9
	DMBSY = 10
	ISB = 11
	DMBLD = 12
	DMBST = 13
	LABEL = 14
	ACI = 15

class Expression:
	# A simple class for an expression
	# Holds the types and values of two operands, and the operation in the string form
	# Type 0 = register, type 1 = integer, and type -1 = does not exist
	def __init__(self, type1, val1, type2=-1, val2=-1, op=-1):
		self.type1 = type1
		self.type2 = type2
		self.val1 = val1
		self.val2 = val2
		self.op = op

	def get_regs(self):
		# returns the list of used registers
		regs = []
		if (self.type1 == 0):
			regs.append(self.val1)
		if (self.type2 == 0):
			regs.append(self.val2)
		return regs

	def get_exp(self, p):
		# returns the expression in string form, given the process
		if (self.type2 == -1):
			# only one argument
			if (self.type1 == 0):
				ret = f"REGP({p},{self.val1})"
			else:
				ret = str(self.val1)
		else:
			ret = "("
			if (self.type1 == 0):
				ret += f"REGP({p},{self.val1})"
			else:
				ret += str(self.val1)
			ret += " " + str(self.op) + " "
			if (self.type2 == 0):
				ret += f"REGP({p},{self.val2})"
			else:
				ret += str(self.val2)
			ret += ")"
		return ret

nregs = 16
addrsize = 64
nproc = 0
ncontext = 10 # later read in as argument
# ncontext = 50 # for complete testing only

maxregs = 0

code = []
incode = []
init_addr_with_zeros = True							# whether to initialize addr with zeroes
init_reg = []
init_addr_diff = {}
final_conds = []									# final conditions
use_or = False 										# whether the conditions are separated by OR

def add_indented_code(line, indentlevel=0):
	### Add code with the given level of indentation ###
	# One indent is assumed to be 4 spaces
	code.append((" "*4*indentlevel)+line)

def add_preamble(indentlevel=0):
	### Preamble code ### 

	# Add macros for number of registers and address size
	add_indented_code("#define NREGS "+str(nregs), indentlevel)
	add_indented_code("#define ADDRSIZE "+str(addrsize), indentlevel)
	add_indented_code("#define NPROC "+str(nproc), indentlevel)
	add_indented_code("#define NCONTEXT "+str(ncontext),indentlevel)
	
	# Add declaration for registers and address space
	add_indented_code("",indentlevel)
	add_indented_code("",indentlevel)
	add_indented_code("// declaration of helper variables", indentlevel)
	add_indented_code("int registers[NREGS*NPROC];", indentlevel)
	add_indented_code("int memory[ADDRSIZE];", indentlevel)
	add_indented_code("int muinit[ADDRSIZE*NCONTEXT], mu[ADDRSIZE*NCONTEXT];", indentlevel)
	add_indented_code("int deltainit[ADDRSIZE*NCONTEXT], delta[ADDRSIZE*NCONTEXT];", indentlevel)
	add_indented_code("int nu[NPROC*ADDRSIZE];", indentlevel)
	add_indented_code("int cR[NPROC*ADDRSIZE], iW[NPROC*ADDRSIZE],cW[NPROC*ADDRSIZE];", indentlevel)
	add_indented_code("int cL[NPROC*NREGS], iS[NPROC*ADDRSIZE],cS[NPROC*ADDRSIZE];", indentlevel)
	add_indented_code("int iReg[NPROC*NREGS], cReg[NPROC*NREGS];", indentlevel)
	add_indented_code("int cDY[NPROC], cDS[NPROC], cDL[NPROC], cISB[NPROC], iAddr[NPROC];", indentlevel)
	add_indented_code("int ctrl[NPROC], active[NCONTEXT];", indentlevel)
	add_indented_code("int old_cDY, old_cW, old_cR, new_cW, new_iReg, new_cReg;", indentlevel)
	add_indented_code("", indentlevel)

	# define macros for easy access
	add_indented_code("",indentlevel)
	add_indented_code("// the following macros are for easy reading", indentlevel)
	add_indented_code("#define REGP(p,r) registers[p*NREGS+r]", indentlevel)
	add_indented_code("#define ADDR_AT(p,r) memory[REGP(p,r)]", indentlevel)
	add_indented_code("#define MUINIT(x,k) muinit[x*NCONTEXT+k]", indentlevel)
	add_indented_code("#define MU(x,k) mu[x*NCONTEXT+k]", indentlevel)
	add_indented_code("#define DELTAINIT(x,k) deltainit[x*NCONTEXT+k]", indentlevel)
	add_indented_code("#define DELTA(x,k) delta[x*NCONTEXT+k]", indentlevel)
	add_indented_code("#define NU(p,x) nu[p*ADDRSIZE+x]", indentlevel)
	add_indented_code("#define CR(p,x) cR[p*ADDRSIZE+x]", indentlevel)
	add_indented_code("#define IW(p,x) iW[p*ADDRSIZE+x]", indentlevel)
	add_indented_code("#define CW(p,x) cW[p*ADDRSIZE+x]", indentlevel)
	add_indented_code("#define CL(p,r) cL[p*NREGS+r]", indentlevel)
	add_indented_code("#define IS(p,x) iS[p*ADDRSIZE+x]", indentlevel)
	add_indented_code("#define CS(p,x) cS[p*ADDRSIZE+x]", indentlevel)
	add_indented_code("#define IREG(p,r) iReg[p*NREGS+r]", indentlevel)
	add_indented_code("#define CREG(p,r) cReg[p*NREGS+r]", indentlevel)
	add_indented_code("#define ASSUME(stmt) __CPROVER_assume(stmt)", indentlevel)
	add_indented_code("#define ASSERT(stmt) __CPROVER_assert(stmt, \"Assert error\")", indentlevel)
	add_indented_code("", indentlevel)
	add_indented_code("#define max(a,b) \\", indentlevel)
	add_indented_code("  ({ __typeof__ (a) _a = (a); \\", indentlevel)
	add_indented_code("  __typeof__ (b) _b = (b); \\", indentlevel)
	add_indented_code("  _a > _b ? _a : _b; })", indentlevel)
	add_indented_code("", indentlevel)

def add_rng_function(indentlevel=0):
	add_indented_code("int __get_rng();", indentlevel)
	add_indented_code("int get_rng(int from, int to)", indentlevel)
	add_indented_code("{", indentlevel)
	add_indented_code("int ret = __get_rng();", indentlevel+1)
	add_indented_code("ASSUME(ret >= from && ret <= to);", indentlevel+1)
	add_indented_code("return ret;", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code("", indentlevel)

def add_control(p, indentlevel=0):
	add_indented_code(f"ctrl[{p}] = ctrl[{p}] + get_rng(0,NCONTEXT-1);", indentlevel)
	add_indented_code(f"ASSUME(ctrl[{p}] < NCONTEXT);", indentlevel)
	add_indented_code("", indentlevel)

def add_initProc(indentlevel=0):
	add_indented_code("/* initProc */", indentlevel)
	add_indented_code("for (int p = 0; p < NPROC; p++) {", indentlevel)
	add_indented_code("for (int x = 0; x < ADDRSIZE; x++) {", indentlevel+1)
	add_indented_code("IW(p,x) = 0;", indentlevel+2)
	add_indented_code("CR(p,x) = 0;", indentlevel+2)
	add_indented_code("CW(p,x) = 0;", indentlevel+2)
	add_indented_code("NU(p,x) = 0;", indentlevel+2)
	add_indented_code("IS(p,x) = 0;", indentlevel+2)
	add_indented_code("CS(p,x) = 0;", indentlevel+2)
	add_indented_code("}", indentlevel+1)
	add_indented_code("for (int r = 0; r < NREGS; r++) {", indentlevel+1)
	add_indented_code("CL(p,r) = 0;", indentlevel+2)
	add_indented_code("IREG(p,r) = 0;", indentlevel+2)
	add_indented_code("CREG(p,r) = 0;", indentlevel+2)
	add_indented_code("}", indentlevel+1)
	add_indented_code("ctrl[p] = 0;", indentlevel+1)
	add_indented_code("iAddr[p] = 0;", indentlevel+1)
	add_indented_code("cDY[p] = 0;", indentlevel+1)
	add_indented_code("cISB[p] = 0;", indentlevel+1)
	add_indented_code("cDS[p] = 0;", indentlevel+1)
	add_indented_code("cDL[p] = 0;", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code("", indentlevel)
	add_indented_code("for (int k = 0; k < NCONTEXT; k++) {", indentlevel)
	add_indented_code("active[k] = get_rng(0,NPROC-1);", indentlevel+1)
	add_indented_code("if (k != 0) {", indentlevel+1)
	add_indented_code("for (int x = 0; x < ADDRSIZE; x++) {", indentlevel+2)
	add_indented_code("MUINIT(x,k) = __get_rng();", indentlevel+3)
	add_indented_code("MU(x,k) = MUINIT(x,k);", indentlevel+3)
	add_indented_code("DELTAINIT(x,k) = get_rng(-1,NPROC-1);", indentlevel+3)
	add_indented_code("DELTA(x,k) = DELTAINIT(x,k);", indentlevel+3)
	add_indented_code("}", indentlevel+2)
	add_indented_code("} else {", indentlevel+1)
	add_indented_code("for (int x = 0; x < ADDRSIZE; x++) {", indentlevel+2)
	if init_addr_with_zeros:
		add_indented_code("MU(x,k) = 0;", indentlevel+3)
	else:
		add_indented_code("MU(x,k) = __get_rng();", indentlevel+3)
	add_indented_code("DELTA(x,k) = -1;", indentlevel+3)
	add_indented_code("}", indentlevel+2)
	add_indented_code("}", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code("// any initial memory values here", indentlevel)
	for addr, value in init_addr_diff.items():
		add_indented_code(f"MU({addr},0) = {value};", indentlevel)
	add_indented_code("// register initial values", indentlevel)
	for istmt in init_reg:
		add_indented_code(istmt, indentlevel)
	add_indented_code("", indentlevel)

def add_ST(p, rprime, r, indentlevel=0):
	add_indented_code("/* ST */", indentlevel)
	add_indented_code("// Guess", indentlevel)
	add_indented_code(f"IW({p},REGP({p},{rprime})) = get_rng(0,NCONTEXT-1);", indentlevel)
	add_indented_code(f"old_cW = CW({p},REGP({p},{rprime}));", indentlevel)
	add_indented_code(f"CW({p},REGP({p},{rprime})) = get_rng(0,NCONTEXT-1);", indentlevel)
	add_indented_code("// Check", indentlevel)
	add_indented_code(f"ASSUME(active[IW({p},REGP({p},{rprime}))] == {p});", indentlevel)
	add_indented_code(f"ASSUME(IW({p},REGP({p},{rprime})) >= max(IREG({p},{r}),IREG({p},{rprime})));", indentlevel)
	add_indented_code(f"ASSUME(IW({p},REGP({p},{rprime})) >= max(cDY[{p}],cISB[{p}]));", indentlevel)
	add_indented_code(f"ASSUME(IW({p},REGP({p},{rprime})) >= max(cDS[{p}],cDL[{p}]));", indentlevel)
	add_indented_code("for (int r = 0; r < NREGS; r++) {", indentlevel)
	add_indented_code(f"ASSUME(IW({p},REGP({p},{rprime})) >= CL({p},r));", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code(f"ASSUME(CW({p},REGP({p},{rprime})) >= IW({p}, REGP({p},{rprime})));", indentlevel)
	add_indented_code(f"ASSUME(active[CW({p},REGP({p},{rprime}))] == {p});", indentlevel)
	add_indented_code(f"ASSUME(CW({p},REGP({p},{rprime})) >= max(CREG({p},{r}),IREG({p},{rprime})));", indentlevel)
	add_indented_code(f"ASSUME(CW({p},REGP({p},{rprime})) >= max(old_cW,CR({p},REGP({p},{rprime}))));", indentlevel)
	add_indented_code(f"ASSUME(CW({p},REGP({p},{rprime})) >= ctrl[{p}]);", indentlevel)
	add_indented_code(f"ASSUME(CW({p},REGP({p},{rprime})) >= iAddr[{p}]);", indentlevel)
	add_indented_code("// Update", indentlevel)
	add_indented_code(f"iAddr[{p}] = max(iAddr[{p}], IREG({p},{rprime}));", indentlevel)
	add_indented_code(f"MU(REGP({p},{rprime}),CW({p},REGP({p},{rprime}))) = REGP({p},{r});", indentlevel)
	add_indented_code(f"NU({p},REGP({p},{rprime})) = REGP({p},{r});", indentlevel)
	add_indented_code(f"DELTA(REGP({p},{rprime}),CW({p},REGP({p},{rprime}))) = -1;", indentlevel)
	add_indented_code(f"", indentlevel)

def add_STL(p, rprime, r, indentlevel=0):
	add_indented_code("/* STL */", indentlevel)
	add_indented_code("// Guess", indentlevel)
	add_indented_code(f"IW({p},REGP({p},{rprime})) = get_rng(0,NCONTEXT-1);", indentlevel)
	add_indented_code(f"old_cW = CW({p},REGP({p},{rprime}));", indentlevel)
	add_indented_code(f"CW({p},REGP({p},{rprime})) = get_rng(0,NCONTEXT-1);", indentlevel)
	add_indented_code(f"IS({p},REGP({p},{rprime})) = IW({p},REGP({p},{rprime}));", indentlevel)
	add_indented_code(f"CS({p},REGP({p},{rprime})) = CW({p},REGP({p},{rprime}));", indentlevel)
	add_indented_code("// Check", indentlevel)
	add_indented_code(f"ASSUME(active[IW({p},REGP({p},{rprime}))] == {p});", indentlevel)
	add_indented_code(f"ASSUME(IW({p},REGP({p},{rprime})) >= max(IREG({p},{r}),IREG({p},{rprime})));", indentlevel)
	add_indented_code(f"ASSUME(IW({p},REGP({p},{rprime})) >= max(cDY[{p}],cISB[{p}]));", indentlevel)
	add_indented_code(f"ASSUME(IW({p},REGP({p},{rprime})) >= max(cDS[{p}],cDL[{p}]));", indentlevel)
	add_indented_code("for (int x = 0; x < ADDRSIZE; x++) {", indentlevel)
	add_indented_code(f"ASSUME(IW({p},REGP({p},{rprime})) >= max(CR({p},x),CW({p},x)));", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code(f"ASSUME(CW({p},REGP({p},{rprime})) >= IW({p}, REGP({p},{rprime})));", indentlevel)
	add_indented_code(f"ASSUME(active[CW({p},REGP({p},{rprime}))] == {p});", indentlevel)
	add_indented_code(f"ASSUME(CW({p},REGP({p},{rprime})) >= max(CREG({p},{r}),IREG({p},{rprime})));", indentlevel)
	add_indented_code(f"ASSUME(CW({p},REGP({p},{rprime})) >= max(old_cW,CR({p},REGP({p},{rprime}))));", indentlevel)
	add_indented_code(f"ASSUME(CW({p},REGP({p},{rprime})) >= ctrl[{p}]);", indentlevel)
	add_indented_code(f"ASSUME(CW({p},REGP({p},{rprime})) >= iAddr[{p}]);", indentlevel)
	add_indented_code("// Update", indentlevel)
	add_indented_code(f"iAddr[{p}] = max(iAddr[{p}], IREG({p},{rprime}));", indentlevel)
	add_indented_code(f"MU(REGP({p},{rprime}),CW({p},REGP({p},{rprime}))) = REGP({p},{r});", indentlevel)
	add_indented_code(f"NU({p},REGP({p},{rprime})) = REGP({p},{r});", indentlevel)
	add_indented_code(f"DELTA(REGP({p},{rprime}),CW({p},REGP({p},{rprime}))) = -1;", indentlevel)
	add_indented_code(f"", indentlevel)

def add_STX(p, rdoubleprime, rprime, r, indentlevel=0):
	add_indented_code("/* STX */", indentlevel)
	add_indented_code("// Guess", indentlevel)
	add_indented_code(f"old_cW = CW({p},REGP({p},{rprime}));", indentlevel)
	add_indented_code(f"new_cW = get_rng(0,NCONTEXT-1);", indentlevel)
	add_indented_code("// Check", indentlevel)
	add_indented_code(f"ASSUME(active[new_cW] == {p});", indentlevel)
	add_indented_code(f"ASSUME(new_cW >= max(cDY[{p}],cISB[{p}]));", indentlevel)
	add_indented_code(f"ASSUME(new_cW >= max(cDS[{p}],cDL[{p}]));", indentlevel)
	add_indented_code("for (int r = 0; r < NREGS; r++) {", indentlevel)
	add_indented_code(f"ASSUME(IW({p},REGP({p},{rprime})) >= CL({p},r));", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code(f"ASSUME(new_cW >= max(CREG({p},{r}),IREG({p},{rprime})));", indentlevel)
	add_indented_code(f"ASSUME(new_cW >= max(old_cW,CR({p},REGP({p},{rprime}))));", indentlevel)
	add_indented_code(f"ASSUME(new_cW >= ctrl[{p}]);", indentlevel)
	add_indented_code(f"ASSUME(new_cW >= iAddr[{p}]);", indentlevel)
	add_indented_code("// Update", indentlevel)
	add_indented_code(f"iAddr[{p}] = max(iAddr[{p}], IREG({p},{rprime}));", indentlevel)
	add_indented_code(f"if (DELTA(REGP({p},{rprime}),new_cW) == {p}) {{", indentlevel)
	add_indented_code(f"MU(REGP({p},{rprime}),new_cW) = REGP({p},{r});", indentlevel+1)
	add_indented_code(f"NU({p},REGP({p},{rprime})) = REGP({p},{r});", indentlevel+1)
	add_indented_code(f"DELTA(REGP({p},{rprime}),new_cW) = -1;", indentlevel+1)
	add_indented_code(f"REGP({p},{rdoubleprime}) = 0;", indentlevel+1)
	add_indented_code(f"IW({p},REGP({p},{rprime})) = new_cW;", indentlevel+1)
	add_indented_code(f"CW({p},REGP({p},{rprime})) = new_cW;", indentlevel+1)
	add_indented_code("} else {", indentlevel)
	add_indented_code(f"REGP({p},{rdoubleprime}) = 1;", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code(f"IREG({p},{rdoubleprime}) = new_cW;", indentlevel)
	add_indented_code(f"CREG({p},{rdoubleprime}) = new_cW;", indentlevel)
	add_indented_code(f"", indentlevel)

def add_STLX(p, rdoubleprime, rprime, r, indentlevel=0):
	add_indented_code("/* STLX */", indentlevel)
	add_indented_code("// Guess", indentlevel)
	add_indented_code(f"old_cW = CW({p},REGP({p},{rprime}));", indentlevel)
	add_indented_code(f"new_cW = get_rng(0,NCONTEXT-1);", indentlevel)
	add_indented_code("// Check", indentlevel)
	add_indented_code(f"ASSUME(active[new_cW] == {p});", indentlevel)
	add_indented_code(f"ASSUME(new_cW >= max(cDY[{p}],cISB[{p}]));", indentlevel)
	add_indented_code(f"ASSUME(new_cW >= max(cDS[{p}],cDL[{p}]));", indentlevel)
	add_indented_code("for (int x = 0; x < ADDRSIZE; x++) {", indentlevel)
	add_indented_code(f"ASSUME(new_cW >= max(CR({p},x),CW({p},x)));", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code(f"ASSUME(new_cW >= max(CREG({p},{r}),IREG({p},{rprime})));", indentlevel)
	add_indented_code(f"ASSUME(new_cW >= max(old_cW,CR({p},REGP({p},{rprime}))));", indentlevel)
	add_indented_code(f"ASSUME(new_cW >= ctrl[{p}]);", indentlevel)
	add_indented_code(f"ASSUME(new_cW >= iAddr[{p}]);", indentlevel)
	add_indented_code("// Update", indentlevel)
	add_indented_code(f"iAddr[{p}] = max(iAddr[{p}], IREG({p},{rprime}));", indentlevel)
	add_indented_code(f"if (DELTA(REGP({p},{rprime}),new_cW) == {p}) {{", indentlevel)
	add_indented_code(f"MU(REGP({p},{rprime}),new_cW) = REGP({p},{r});", indentlevel+1)
	add_indented_code(f"NU({p},REGP({p},{rprime})) = REGP({p},{r});", indentlevel+1)
	add_indented_code(f"DELTA(REGP({p},{rprime}),new_cW) = -1;", indentlevel+1)
	add_indented_code(f"REGP({p},{rdoubleprime}) = 0;", indentlevel+1)
	add_indented_code(f"IW({p},REGP({p},{rprime})) = new_cW;", indentlevel+1)
	add_indented_code(f"CW({p},REGP({p},{rprime})) = new_cW;", indentlevel+1)
	add_indented_code(f"IS({p},REGP({p},{rprime})) = new_cW;", indentlevel+1)
	add_indented_code(f"CS({p},REGP({p},{rprime})) = new_cW;", indentlevel+1)
	add_indented_code("} else {", indentlevel)
	add_indented_code(f"REGP({p},{rdoubleprime}) = 1;", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code(f"IREG({p},{rdoubleprime}) = new_cW;", indentlevel)
	add_indented_code(f"CREG({p},{rdoubleprime}) = new_cW;", indentlevel)
	add_indented_code(f"", indentlevel)

def add_assign(p, r, exp, indentlevel=0):
	add_indented_code("/* assign */", indentlevel)
	add_indented_code("// Guess", indentlevel)
	add_indented_code(f"new_iReg = get_rng(0,NCONTEXT-1);", indentlevel)
	add_indented_code(f"new_cReg = get_rng(0,NCONTEXT-1);", indentlevel)
	add_indented_code("// Check", indentlevel)
	add_indented_code(f"ASSUME(active[new_iReg] == {p});", indentlevel)
	for rprime in exp.get_regs():
		add_indented_code(f"ASSUME(new_iReg >= IREG({p},{rprime}));", indentlevel)
	add_indented_code(f"ASSUME(active[new_cReg] == {p});", indentlevel)
	add_indented_code(f"ASSUME(new_cReg >= max(ctrl[{p}],new_iReg));", indentlevel)
	for rprime in exp.get_regs():
		add_indented_code(f"ASSUME(new_cReg >= CREG({p},{rprime}));", indentlevel)
	add_indented_code("// Update", indentlevel)
	add_indented_code(f"IREG({p},{r}) = new_iReg;", indentlevel)
	add_indented_code(f"CREG({p},{r}) = new_cReg;", indentlevel)
	add_indented_code(f"REGP({p},{r}) = " + exp.get_exp(p) + ";", indentlevel)
	add_indented_code("", indentlevel)

def add_LD(p, rprime, r, indentlevel=0):
	add_indented_code("/* LD */", indentlevel)
	add_indented_code("// Guess", indentlevel)
	add_indented_code(f"old_cR = CR({p},REGP({p},{r}));", indentlevel)
	add_indented_code(f"CR({p},REGP({p},{r})) = get_rng(0,NCONTEXT-1);", indentlevel)
	add_indented_code(f"IREG({p},{rprime}) = CR({p},REGP({p},{r}));", indentlevel)
	add_indented_code(f"CREG({p},{rprime}) = CR({p},REGP({p},{r}));", indentlevel)
	add_indented_code("// Check", indentlevel)
	add_indented_code(f"ASSUME(active[CR({p},REGP({p},{r}))] == {p});", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= IW({p},REGP({p},{r})));", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= IREG({p},{r}));", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= max(cDY[{p}],cISB[{p}]));", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= cDL[{p}]);", indentlevel)
	add_indented_code("for (int rdp = 0; rdp < NREGS; rdp++) {", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= CL({p},rdp));", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code("// Update", indentlevel)
	add_indented_code(f"iAddr[{p}] = max(iAddr[{p}], IREG({p},{r}));", indentlevel)
	add_indented_code(f"if (CR({p},REGP({p},{r})) < CW({p},REGP({p},{r}))) {{", indentlevel)
	add_indented_code(f"REGP({p},{rprime}) = NU({p},REGP({p},{r}));", indentlevel+1)
	add_indented_code("} else {", indentlevel)
	add_indented_code(f"REGP({p},{rprime}) = MU(REGP({p},{r}),CR({p},REGP({p},{r})));", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code("", indentlevel)

def add_LDA(p, rprime, r, indentlevel=0):
	add_indented_code("/* LDA */", indentlevel)
	add_indented_code("// Guess", indentlevel)
	add_indented_code(f"old_cR = CR({p},REGP({p},{r}));", indentlevel)
	add_indented_code(f"CR({p},REGP({p},{r})) = get_rng(0,NCONTEXT-1);", indentlevel)
	add_indented_code(f"IREG({p},{rprime}) = CR({p},REGP({p},{r}));", indentlevel)
	add_indented_code(f"CREG({p},{rprime}) = CR({p},REGP({p},{r}));", indentlevel)
	add_indented_code(f"CL({p},{rprime}) = CR({p},REGP({p},{r}));", indentlevel)
	add_indented_code("// Check", indentlevel)
	add_indented_code(f"ASSUME(active[CR({p},REGP({p},{r}))] == {p});", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= IW({p},REGP({p},{r})));", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= IREG({p},{r}));", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= max(cDY[{p}],cISB[{p}]));", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= cDL[{p}]);", indentlevel)
	add_indented_code("for (int rdp = 0; rdp < NREGS; rdp++) {", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= CL({p},rdp));", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code("for (int x = 0; x < ADDRSIZE; x++) {", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= CS({p},x));", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code("// Update", indentlevel)
	add_indented_code(f"iAddr[{p}] = max(iAddr[{p}], IREG({p},{r}));", indentlevel)
	add_indented_code(f"if (CR({p},REGP({p},{r})) < CW({p},REGP({p},{r}))) {{", indentlevel)
	add_indented_code(f"REGP({p},{rprime}) = NU({p},REGP({p},{r}));", indentlevel+1)
	add_indented_code("} else {", indentlevel)
	add_indented_code(f"REGP({p},{rprime}) = MU(REGP({p},{r}),CR({p},REGP({p},{r})));", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code("", indentlevel)

def add_LDX(p, rprime, r, indentlevel=0):
	add_indented_code("/* LDX */", indentlevel)
	add_indented_code("// Guess", indentlevel)
	add_indented_code(f"CR({p},REGP({p},{r})) = get_rng(0,NCONTEXT-1);", indentlevel)
	add_indented_code(f"old_cR = CR({p},REGP({p},{r}));", indentlevel)
	add_indented_code(f"CR({p},REGP({p},{r})) = get_rng(0,NCONTEXT-1);", indentlevel)
	add_indented_code(f"IREG({p},{rprime}) = CR({p},REGP({p},{r}));", indentlevel)
	add_indented_code(f"CREG({p},{rprime}) = CR({p},REGP({p},{r}));", indentlevel)
	add_indented_code("// Check", indentlevel)
	add_indented_code(f"ASSUME(active[CR({p},REGP({p},{r}))] == {p});", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= IW({p},REGP({p},{r})));", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= IREG({p},{r}));", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= max(cDY[{p}],cISB[{p}]));", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= cDL[{p}]);", indentlevel)
	add_indented_code("for (int rdp = 0; rdp < NREGS; rdp++) {", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= CL({p},rdp));", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code("// Update", indentlevel)
	add_indented_code(f"iAddr[{p}] = max(iAddr[{p}], IREG({p},{r}));", indentlevel)
	add_indented_code(f"if (CR({p},REGP({p},{r})) < CW({p},REGP({p},{r}))) {{", indentlevel)
	add_indented_code(f"REGP({p},{rprime}) = NU({p},REGP({p},{r}));", indentlevel+1)
	add_indented_code("} else {", indentlevel)
	add_indented_code(f"REGP({p},{rprime}) = MU(REGP({p},{r}),CR({p},REGP({p},{r})));", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code(f"DELTA(REGP({p},{r}),CR({p},REGP({p},{r}))) = {p};", indentlevel)
	add_indented_code("", indentlevel)

def add_LDAX(p, rprime, r, indentlevel=0):
	add_indented_code("/* LDAX */", indentlevel)
	add_indented_code("// Guess", indentlevel)
	add_indented_code(f"CR({p},REGP({p},{r})) = get_rng(0,NCONTEXT-1);", indentlevel)
	add_indented_code(f"old_cR = CR({p},REGP({p},{r}));", indentlevel)
	add_indented_code(f"CR({p},REGP({p},{r})) = get_rng(0,NCONTEXT-1);", indentlevel)
	add_indented_code(f"IREG({p},{rprime}) = CR({p},REGP({p},{r}));", indentlevel)
	add_indented_code(f"CREG({p},{rprime}) = CR({p},REGP({p},{r}));", indentlevel)
	add_indented_code(f"CL({p},{rprime}) = CR({p},REGP({p},{r}));", indentlevel)
	add_indented_code("// Check", indentlevel)
	add_indented_code(f"ASSUME(active[CR({p},REGP({p},{r}))] == {p});", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= IW({p},REGP({p},{r})));", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= IREG({p},{r}));", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= max(cDY[{p}],cISB[{p}]));", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= cDL[{p}]);", indentlevel)
	add_indented_code("for (int rdp = 0; rdp < NREGS; rdp++) {", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= CL({p},rdp));", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code("for (int x = 0; x < ADDRSIZE; x++) {", indentlevel)
	add_indented_code(f"ASSUME(CR({p},REGP({p},{r})) >= CS({p},x));", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code("// Update", indentlevel)
	add_indented_code(f"iAddr[{p}] = max(iAddr[{p}], IREG({p},{r}));", indentlevel)
	add_indented_code(f"if (CR({p},REGP({p},{r})) < CW({p},REGP({p},{r}))) {{", indentlevel)
	add_indented_code(f"REGP({p},{rprime}) = NU({p},REGP({p},{r}));", indentlevel+1)
	add_indented_code("} else {", indentlevel)
	add_indented_code(f"REGP({p},{rprime}) = MU(REGP({p},{r}),CR({p},REGP({p},{r})));", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code(f"DELTA(REGP({p},{r}),CR({p},REGP({p},{r}))) = {p};", indentlevel)
	add_indented_code("", indentlevel)

def add_dmb_sy(p, indentlevel=0):
	add_indented_code("/* dmb.sy */", indentlevel)
	add_indented_code("// Guess", indentlevel)
	add_indented_code(f"old_cDY = cDY[{p}];", indentlevel)
	add_indented_code(f"cDY[{p}] = get_rng(0,NCONTEXT-1);", indentlevel)
	add_indented_code("// Check", indentlevel)
	add_indented_code(f"ASSUME(cDY[{p}] >= old_cDY);", indentlevel)
	add_indented_code(f"ASSUME(cDY[{p}] >= max(cISB[{p}],cDL[{p}]));", indentlevel)
	add_indented_code(f"ASSUME(cDY[{p}] >= max(cDS[{p}],ctrl[{p}]));", indentlevel)
	# cL and cS are <= cR and cW respectively
	add_indented_code("for (int x = 0; x < ADDRSIZE; x++) {", indentlevel)
	add_indented_code(f"ASSUME(cDY[{p}] >= CW({p},x));", indentlevel+1)
	add_indented_code(f"ASSUME(cDY[{p}] >= CR({p},x));", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code("", indentlevel)

def add_isb(p, indentlevel=0):
	add_indented_code("/* isb */", indentlevel)
	add_indented_code("// Guess", indentlevel)
	add_indented_code(f"cISB[{p}] = get_rng(0,NCONTEXT-1);", indentlevel)
	add_indented_code("// Check", indentlevel)
	add_indented_code(f"ASSUME(cISB[{p}] >= cDY[{p}]);", indentlevel)
	add_indented_code(f"ASSUME(cISB[{p}] >= ctrl[{p}]);", indentlevel)
	# we need all po-prev instructions to have fully defined memory footprints
	# time to use iAddr
	add_indented_code(f"ASSUME(cISB[{p}] >= iAddr[{p}]);", indentlevel)
	add_indented_code("", indentlevel)

def add_dmb_ld(p, indentlevel=0):
	add_indented_code("/* dmb.ld */", indentlevel)
	add_indented_code("// Guess", indentlevel)
	add_indented_code(f"cDL[{p}] = get_rng(0,NCONTEXT-1);", indentlevel)
	add_indented_code("// Check", indentlevel)
	add_indented_code(f"ASSUME(cDL[{p}] >= cDY[{p}]);", indentlevel)
	add_indented_code(f"ASSUME(cDL[{p}] >= ctrl[{p}]);", indentlevel)
	# cL and cS are <= cR and cW respectively
	add_indented_code("for (int x = 0; x < ADDRSIZE; x++) {", indentlevel)
	add_indented_code(f"ASSUME(cDL[{p}] >= CR({p},x));", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code("", indentlevel)


def add_dmb_st(p, indentlevel=0):
	add_indented_code("/* dmb.st */", indentlevel)
	add_indented_code("// Guess", indentlevel)
	add_indented_code(f"cDS[{p}] = get_rng(0,NCONTEXT-1);", indentlevel)
	add_indented_code("// Check", indentlevel)
	add_indented_code(f"ASSUME(cDS[{p}] >= cDY[{p}]);", indentlevel)
	add_indented_code(f"ASSUME(cDS[{p}] >= ctrl[{p}]);", indentlevel)
	# cL and cS are <= cR and cW respectively
	add_indented_code("for (int x = 0; x < ADDRSIZE; x++) {", indentlevel)
	add_indented_code(f"ASSUME(cDS[{p}] >= CW({p},x));", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code("", indentlevel)

def add_verProc(indentlevel=0):
	add_indented_code("/* verProc */", indentlevel)
	add_indented_code("for (int x = 0; x < ADDRSIZE; x++) {", indentlevel)
	add_indented_code("for (int k = 0; k < NCONTEXT-1; k++) {", indentlevel+1)
	add_indented_code("ASSUME(MU(x,k) == MUINIT(x,k+1));", indentlevel+2)
	add_indented_code("ASSUME(DELTA(x,k) == DELTAINIT(x,k+1));", indentlevel+2)
	add_indented_code("}", indentlevel+1)
	add_indented_code("}", indentlevel)
	add_indented_code("if (", indentlevel)
	if use_or:
		for cnd in final_conds:
			add_indented_code(cnd + " ||", indentlevel+1)
		add_indented_code("0)", indentlevel)
	else:
		for cnd in final_conds:
			add_indented_code(cnd + " &&", indentlevel+1)
		add_indented_code("1)", indentlevel)
	add_indented_code("ASSERT(0);", indentlevel+1)
	add_indented_code("", indentlevel)
	
def write_translated_code():
	### Write the code to the output file ###
	with open(outfile,'w+') as file:
		file.write('\n'.join(str(line) for line in code))

class Instruction:
	def __init__(self, p, i_type, op1=None, op2=None, op3=None):
		self.p = p
		self.i_type = i_type
		self.op1 = op1
		self.op2 = op2
		self.op3 = op3

def parse_file_without_comments_or_empty_lines(filename, prefix=None):
	if prefix:
		filename = os.path.join(prefix,filename)
	lines = []
	with open(filename) as f:
		for line in f.readlines():
			line = line.strip()
			if line.startswith("//") or not line:
				continue 
			lines.append(line)
	return lines

def register(r):
	# Since registers 0 and 1 are reserved for CMP/B.XY instructions, and
	# 2 for holding temporary values for offseted instructions,
	# translate register r to r+3
	global maxregs
	maxregs = max(maxregs, r)
	return r+3

def parse_test(idir):
	global nproc, addrsize, nregs, maxreg, incode, init_addr_diff, use_or

	initial_memory_values = {}							# specific initial values

	init = parse_file_without_comments_or_empty_lines('init.cnds', idir)
	nproc = int(init[0])
	addrsize = int(init[1]) 

	init = init[2:]
	for line in init:
		parts = line.split(':')
		part1 = int(parts[0].strip())
		part2 = int(parts[1].strip())
		if part2 != 0:
			init_addr_diff[part1] = part2

	for proc in range(nproc):
		incode.append([])
		proc_code = parse_file_without_comments_or_empty_lines( \
			"thread"+str(proc)+".aarch64", idir)
		for line in proc_code:
			# There are two possibilities here
			# one is that the line end with ':'; this represents a label
			# Otherwise, its an instruction
			if line.endswith(':'):
				# label - append procid to make it unique
				stmt = Instruction(proc, InstrType.LABEL.value, "p"+str(proc)+line[:-1])
				incode[proc].append(stmt)
				continue 
			# Not a label: remove the semicolon, and infer the operands
			line = line[:-1].strip()
			spaceparts = line.split(" ")
			operation = spaceparts[0]
			if (len(spaceparts) > 1):
				operands = spaceparts[1].split(',')
			if operation in ['LDR','LDAR','LDAXR','LDXR']:
				operands[0] = register(int(operands[0][1:]))
				if len(operands) > 2:
					# has the offset and stuff
					# operands array is of the form : ["R1" "[R2" "#x]"]   
					operands[1] = register(int(operands[1][2:]))
					if ']' in operands[2]:
						operands[2] = register(int(operands[2][1:-1]))
					else:
						operands[2] = register(int(operands[2][1:]))
					# Now add an assign statement to the private register 2
					# followed by a load
					exp = Expression(0, operands[1], 0, operands[2],'+')
					stmt1 = Instruction(proc, InstrType.ASSIGN.value, 2, exp)
					stmt2 = Instruction(proc, InstrType[operation[:-1]].value, 	\
						operands[0], 2)
					incode[proc].append(stmt1)
					incode[proc].append(stmt2)
				else:
					operands[1] = register(int(operands[1][2:-1]))
					stmt = Instruction(proc, InstrType[operation[:-1]].value, 	\
						operands[0], operands[1])
					incode[proc].append(stmt)
			elif operation in ['STR', 'STLR']:
				operands[0] = register(int(operands[0][1:]))
				if len(operands) > 2:
					# has the offset and stuff
					# operands array is of the form : ["R1" "[R2" "#x]"]   
					operands[1] = register(int(operands[1][2:]))
					if ']' in operands[2]:
						operands[2] = register(int(operands[2][1:-1]))
					else:
						operands[2] = register(int(operands[2][1:]))
					# Now add an assign statement to the private register 2
					# followed by a store
					exp = Expression(0, operands[1], 0, operands[2],'+')
					stmt1 = Instruction(proc, InstrType.ASSIGN.value, 2, exp)
					stmt2 = Instruction(proc, InstrType[operation[:-1]].value, 	\
						2, operands[0])
					incode[proc].append(stmt1)
					incode[proc].append(stmt2)
				else:
					operands[1] = register(int(operands[1][2:-1]))
					stmt = Instruction(proc, InstrType[operation[:-1]].value, 	\
						operands[1], operands[0])
					incode[proc].append(stmt)
			elif operation in ['STXR', 'STLXR']:
				operands[0] = register(int(operands[0][1:]))
				operands[1] = register(int(operands[1][1:]))
				operands[2] = register(int(operands[2][2:-1]))
				stmt = Instruction(proc, InstrType[operation[:-1]].value,	\
					operands[0], operands[2],operands[1])
				incode[proc].append(stmt)
			elif operation == "DMB":
				stmt = Instruction(proc, InstrType[operation+operands[0]].value)
				incode[proc].append(stmt)
			elif operation == "ISB":
				stmt = Instruction(proc, InstrType.ISB.value)
				incode[proc].append(stmt)
			elif operation == "MOV":
				operands[0] = register(int(operands[0][1:]))
				if operands[1][0] == '#': 
					exp = Expression(1, int(operands[1][1:]))
					stmt = Instruction(proc, InstrType.ASSIGN.value,	\
						operands[0], exp)
				else:
					operands[1] = register(int(operands[1][1:]))
					exp = Expression(0, operands[1])
					stmt = Instruction(proc, InstrType.ASSIGN.value,	\
						operands[0], exp)
				incode[proc].append(stmt)
			elif operation == "CMP":
				if operands[0][0] == '#':
					exp = Expression(1, int(operands[0][1:]))
					stmt1 = Instruction(proc, InstrType.ASSIGN.value, 0, exp)
				else:
					operands[0] = register(int(operands[0][1:]))
					exp = Expression(0, operands[0])
					stmt1 = Instruction(proc, InstrType.ASSIGN.value, 0, exp)
				if operands[1][0] == '#':
					exp = Expression(1, int(operands[1][1:]))
					stmt2 = Instruction(proc, InstrType.ASSIGN.value, 1, exp)
				else:
					operands[1] = register(int(operands[1][1:]))
					exp = Expression(0, operands[1])
					stmt2 = Instruction(proc, InstrType.ASSIGN.value, 1, exp)
				incode[proc].append(stmt1)
				incode[proc].append(stmt2)
			elif operation in ["B.EQ", "B.GE", "B.NE", "B.GT"]:
				# append proc before label name, to make the label unique
				stmt = Instruction(proc, InstrType.ACI.value, operation[0]+operation[2:],  \
					"p"+str(proc)+operands[0])
				incode[proc].append(stmt)
			elif operation == "B":
				# append proc before label name, to make the label unique
				stmt = Instruction(proc, InstrType.ACI.value, operation, "p"+str(proc)+operands[0])
				incode[proc].append(stmt)
			elif operation == "EOR":
				operands[0] = register(int(operands[0][1:]))
				if operands[1][0] == '#':
					type1 = 1
					operands[1] = int(operands[1][1:])
				else:
					type1 = 0
					operands[1] = register(int(operands[1][1:]))
				if operands[2][0] == '#':
					type2 = 1
					operands[2] = int(operands[2][1:])
				else:
					type2 = 0
					operands[2] = register(int(operands[2][1:]))
				exp = Expression(type1, operands[1], type2, operands[2], '^')
				stmt = Instruction(proc, InstrType.ASSIGN.value, operands[0], exp)
				incode[proc].append(stmt)
			elif operation == "ADD":
				operands[0] = register(int(operands[0][1:]))
				if operands[1][0] == '#':
					type1 = 1
					operands[1] = int(operands[1][1:])
				else:
					type1 = 0
					operands[1] = register(int(operands[1][1:]))
				if operands[2][0] == '#':
					type2 = 1
					operands[2] = int(operands[2][1:])
				else:
					type2 = 0
					operands[2] = register(int(operands[2][1:]))
				exp = Expression(type1, operands[1], type2, operands[2], '+')
				stmt = Instruction(proc, InstrType.ASSIGN.value, operands[0], exp)
				incode[proc].append(stmt)
			elif operation == "SUB":
				operands[0] = register(int(operands[0][1:]))
				if operands[1][0] == '#':
					type1 = 1
					operands[1] = int(operands[1][1:])
				else:
					type1 = 0
					operands[1] = register(int(operands[1][1:]))
				if operands[2][0] == '#':
					type2 = 1
					operands[2] = int(operands[2][1:])
				else:
					type2 = 0
					operands[2] = register(int(operands[2][1:]))
				exp = Expression(type1, operands[1], type2, operands[2], '-')
				stmt = Instruction(proc, InstrType.ASSIGN.value, operands[0], exp)
				incode[proc].append(stmt)
			elif operation == "MUL":
				operands[0] = register(int(operands[0][1:]))
				if operands[1][0] == '#':
					type1 = 1
					operands[1] = int(operands[1][1:])
				else:
					type1 = 0
					operands[1] = register(int(operands[1][1:]))
				if operands[2][0] == '#':
					type2 = 1
					operands[2] = int(operands[2][1:])
				else:
					type2 = 0
					operands[2] = register(int(operands[2][1:]))
				exp = Expression(type1, operands[1], type2, operands[2], '*')
				stmt = Instruction(proc, InstrType.ASSIGN.value, operands[0], exp)
				incode[proc].append(stmt)
			elif operation == "DIV":
				# Is actually equivalent to 'UDIV' of AArch64
				operands[0] = register(int(operands[0][1:]))
				if operands[1][0] == '#':
					type1 = 1
					operands[1] = int(operands[1][1:])
				else:
					type1 = 0
					operands[1] = register(int(operands[1][1:]))
				if operands[2][0] == '#':
					type2 = 1
					operands[2] = int(operands[2][1:])
				else:
					type2 = 0
					operands[2] = register(int(operands[2][1:]))
				exp = Expression(type1, operands[1], type2, operands[2], '/')
				stmt = Instruction(proc, InstrType.ASSIGN.value, operands[0], exp)
				incode[proc].append(stmt)
			elif operation == "REM":
				# No such operator exists in AArch64
				# However, we can implement remainder using a divide and
				# a subtract: to save the hassle, we define another instruction
				operands[0] = register(int(operands[0][1:]))
				if operands[1][0] == '#':
					type1 = 1
					operands[1] = int(operands[1][1:])
				else:
					type1 = 0
					operands[1] = register(int(operands[1][1:]))
				if operands[2][0] == '#':
					type2 = 1
					operands[2] = int(operands[2][1:])
				else:
					type2 = 0
					operands[2] = register(int(operands[2][1:]))
				exp = Expression(type1, operands[1], type2, operands[2], '%')
				stmt = Instruction(proc, InstrType.ASSIGN.value, operands[0], exp)
				incode[proc].append(stmt)
			elif operation == "CBZ":
				operands[0] = register(int(operands[0][1:]))
				# append proc before label name, to make the label unique
				stmt = Instruction(proc, InstrType.ACI.value, "CBZ",	\
					operands[0], "p"+str(proc)+operands[1])
				incode[proc].append(stmt)
			elif operation == "CBNZ":
				operands[0] = register(int(operands[0][1:]))
				# append proc before label name, to make the label unique
				stmt = Instruction(proc, InstrType.ACI.value, "CBNZ",	\
					operands[0], "p"+str(proc)+operands[1])
				incode[proc].append(stmt)

	# extract the conditions
	check = parse_file_without_comments_or_empty_lines('check.cnds', idir)
	for line in check:
		contra = False
		geq = False
		if line.strip() == "USEOR":
			# We should use OR instead of and
			use_or = True
			continue
		if line.startswith("not"):
			contra = True
			line = line[3:].strip()
		if line.startswith("geq"):
			geq = True
			line = line[3:].strip()
		parts = line.split(':')
		parts[0] = int(parts[0].strip())
		parts[1] = int(parts[1].strip())
		if contra:
			if geq:
				istmt = f"(MU({parts[0]},NCONTEXT-1) < {int(parts[1])})"
			else:
				istmt = f"(MU({parts[0]},NCONTEXT-1) != {int(parts[1])})"
		else:
			if geq:
				istmt = f"(MU({parts[0]},NCONTEXT-1) >= {int(parts[1])})"
			else:
				istmt = f"(MU({parts[0]},NCONTEXT-1) == {int(parts[1])})"
		final_conds.append(istmt)

	nregs = maxregs + 4 		
	# 3 because 0-2 are reserved, and +1 because maxregs is off-by 1 [0-indexed]

def add_aci_instruction(instr, indentlevel=0):
	if (instr.op1 == "BEQ"):
		add_indented_code("/* BEQ */", indentlevel)
		add_control(instr.p, indentlevel)
		# Can commit BEQ only after registers 1 and 0 are ready
		add_indented_code(f"ASSUME(ctrl[{instr.p}] >= IREG({instr.p},0));", indentlevel)
		add_indented_code(f"ASSUME(ctrl[{instr.p}] >= IREG({instr.p},1));", indentlevel)
		add_indented_code(f"if (REGP({instr.p},0) == REGP({instr.p},1))", indentlevel)
		add_indented_code(f"goto {instr.op2};", indentlevel+1)
		add_indented_code("", indentlevel)
	elif (instr.op1 == "BNE"):
		add_indented_code("/* BNE */", indentlevel)
		add_control(instr.p, indentlevel)
		# Can commit BEQ only after registers 1 and 0 are ready
		add_indented_code(f"ASSUME(ctrl[{instr.p}] >= IREG({instr.p},0));", indentlevel)
		add_indented_code(f"ASSUME(ctrl[{instr.p}] >= IREG({instr.p},1));", indentlevel)
		add_indented_code(f"if (REGP({instr.p},0) != REGP({instr.p},1))", indentlevel)
		add_indented_code(f"goto {instr.op2};", indentlevel+1)
		add_indented_code("", indentlevel)
	elif (instr.op1 == "BGE"):
		add_indented_code("/* BGE */", indentlevel)
		add_control(instr.p, indentlevel)
		# Can commit BEQ only after registers 1 and 0 are ready
		add_indented_code(f"ASSUME(ctrl[{instr.p}] >= IREG({instr.p},0));", indentlevel)
		add_indented_code(f"ASSUME(ctrl[{instr.p}] >= IREG({instr.p},1));", indentlevel)
		add_indented_code(f"if (REGP({instr.p},0) >= REGP({instr.p},1))", indentlevel)
		add_indented_code(f"goto {instr.op2};", indentlevel+1)
		add_indented_code("", indentlevel)
	elif (instr.op1 == "BGT"):
		add_indented_code("/* BGT */", indentlevel)
		add_control(instr.p, indentlevel)
		# Can commit BEQ only after registers 1 and 0 are ready
		add_indented_code(f"ASSUME(ctrl[{instr.p}] >= IREG({instr.p},0));", indentlevel)
		add_indented_code(f"ASSUME(ctrl[{instr.p}] >= IREG({instr.p},1));", indentlevel)
		add_indented_code(f"if (REGP({instr.p},0) > REGP({instr.p},1))", indentlevel)
		add_indented_code(f"goto {instr.op2};", indentlevel+1)
		add_indented_code("", indentlevel)
	elif (instr.op1 == "CBZ"):
		add_indented_code("/* CBZ */", indentlevel)
		add_control(instr.p, indentlevel)
		# Shouldnt this be CREG? but then the litmus test e.g. RV+2+2W+rfi+ctrls.litmus fails
		add_indented_code(f"ASSUME(ctrl[{instr.p}] >= IREG({instr.p},{instr.op2}));", indentlevel)
		add_indented_code(f"if (REGP({instr.p},{instr.op2}) == 0)", indentlevel)
		add_indented_code(f"goto {instr.op3};", indentlevel+1)
		add_indented_code("", indentlevel)
	elif (instr.op1 == "CBNZ"):
		add_indented_code("/* CBNZ */", indentlevel)
		add_control(instr.p, indentlevel)
		# Shouldnt this be CREG? but then the litmus test e.g. RV+2+2W+rfi+ctrls.litmus fails
		add_indented_code(f"ASSUME(ctrl[{instr.p}] >= IREG({instr.p},{instr.op2}));", indentlevel)
		add_indented_code(f"if (REGP({instr.p},{instr.op2}) != 0)", indentlevel)
		add_indented_code(f"goto {instr.op3};", indentlevel+1)
		add_indented_code("", indentlevel)
	elif (instr.op1 == "B"):
		add_indented_code("/* B */", indentlevel)
		add_control(instr.p, indentlevel)
		add_indented_code(f"goto {instr.op2};", indentlevel)
		add_indented_code("", indentlevel)


def add_instruction(instr, indentlevel=0):
	# labels and goto's not handled yet
	if instr.i_type == InstrType.ACI.value:
		add_aci_instruction(instr, indentlevel)
		return
	if instr.i_type == InstrType.LABEL.value:
		add_indented_code(instr.op1 + ":", 0)
		return
	if instr.i_type == InstrType.LD.value:
		add_LD(instr.p, instr.op1, instr.op2, indentlevel)
	elif instr.i_type == InstrType.LDA.value:
		add_LDA(instr.p, instr.op1, instr.op2, indentlevel)
	elif instr.i_type == InstrType.LDX.value:
		add_LDX(instr.p, instr.op1, instr.op2, indentlevel)
	elif instr.i_type == InstrType.LDAX.value:
		add_LDAX(instr.p, instr.op1, instr.op2, indentlevel)
	elif instr.i_type == InstrType.ST.value:
		add_ST(instr.p, instr.op1, instr.op2, indentlevel)
	elif instr.i_type == InstrType.STL.value:
		add_STL(instr.p, instr.op1, instr.op2, indentlevel)
	elif instr.i_type == InstrType.STX.value:
		add_STX(instr.p, instr.op1, instr.op2, instr.op3, indentlevel)
	elif instr.i_type == InstrType.STLX.value:
		add_STLX(instr.p, instr.op1, instr.op2, instr.op3, indentlevel)
	elif instr.i_type == InstrType.ASSIGN.value:
		add_assign(instr.p, instr.op1, instr.op2, indentlevel)
	elif instr.i_type == InstrType.DMBSY.value:
		add_dmb_sy(instr.p, indentlevel)
	elif instr.i_type == InstrType.ISB.value:
		add_isb(instr.p, indentlevel)
	elif instr.i_type == InstrType.DMBLD.value:
		add_dmb_ld(instr.p, indentlevel)
	elif instr.i_type == InstrType.DMBST.value:
		add_dmb_st(instr.p, indentlevel)

def translate_code(indentlevel=0):
	add_preamble()
	add_rng_function()
	add_indented_code("int main(int argc, char **argv)", indentlevel)
	add_indented_code("{", indentlevel)
	add_initProc(indentlevel+1)
	for p in range(nproc):
		add_indented_code(f"// Process {p} BEGIN", indentlevel+1)
		for instr in incode[p]:
			add_instruction(instr, indentlevel+1)
		add_indented_code(f"// Process {p} END", indentlevel+1)
		add_indented_code("", indentlevel+1)
	add_verProc(indentlevel+1);
	add_indented_code("return 0;", indentlevel+1)
	add_indented_code("}", indentlevel)

parse_test(indir)
translate_code()
write_translated_code()



'''
for proc in range(nproc):
	print(f"=========== {proc} ===========")
	for instr in incode[proc]:
		print(f"{instr.i_type} {instr.op1} {instr.op2} {instr.op3}")
'''