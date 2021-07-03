#define NREGS 5
#define ADDRSIZE 3
#define NPROC 2
#define NCONTEXT 10


// declaration of helper variables
int registers[NREGS*NPROC];
int memory[ADDRSIZE];
int muinit[ADDRSIZE*NCONTEXT], mu[ADDRSIZE*NCONTEXT];
int deltainit[ADDRSIZE*NCONTEXT], delta[ADDRSIZE*NCONTEXT];
int nu[NPROC*ADDRSIZE];
int iR[NPROC*ADDRSIZE], cR[NPROC*ADDRSIZE], iW[NPROC*ADDRSIZE],cW[NPROC*ADDRSIZE];
int iL[NPROC*NREGS], cL[NPROC*NREGS], iS[NPROC*ADDRSIZE],cS[NPROC*ADDRSIZE];
int iReg[NPROC*NREGS], cReg[NPROC*NREGS];
int cDY[NPROC], cDS[NPROC], cDL[NPROC], cISB[NPROC], iAddr[NPROC];
int ctrl[NPROC], active[NCONTEXT];
int old_cDY, old_cW, old_cR, new_cW, new_iReg, new_cReg;


// the following macros are for easy reading
#define REGP(p,r) registers[p*NREGS+r]
#define ADDR_AT(p,r) memory[REGP(p,r)]
#define MUINIT(x,k) muinit[x*NCONTEXT+k]
#define MU(x,k) mu[x*NCONTEXT+k]
#define DELTAINIT(x,k) deltainit[x*NCONTEXT+k]
#define DELTA(x,k) delta[x*NCONTEXT+k]
#define NU(p,x) nu[p*ADDRSIZE+x]
#define IR(p,x) iR[p*ADDRSIZE+x]
#define CR(p,x) cR[p*ADDRSIZE+x]
#define IW(p,x) iW[p*ADDRSIZE+x]
#define CW(p,x) cW[p*ADDRSIZE+x]
#define IL(p,r) iL[p*NREGS+r]
#define CL(p,r) cL[p*NREGS+r]
#define IS(p,x) iS[p*ADDRSIZE+x]
#define CS(p,x) cS[p*ADDRSIZE+x]
#define IREG(p,r) iReg[p*NREGS+r]
#define CREG(p,r) cReg[p*NREGS+r]
#define ASSUME(stmt) __CPROVER_assume(stmt)
#define ASSERT(stmt) __CPROVER_assert(stmt, "Assert error")

#define max(a,b) \
  ({ __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a > _b ? _a : _b; })

int __get_rng();
int get_rng(int from, int to)
{
    int ret = __get_rng();
    ASSUME(ret >= from && ret <= to);
    return ret;
}

int main(int argc, char **argv)
{
    /* initProc */
    for (int p = 0; p < NPROC; p++) {
        for (int x = 0; x < ADDRSIZE; x++) {
            IR(p,x) = 0;
            IW(p,x) = 0;
            CR(p,x) = 0;
            CW(p,x) = 0;
            NU(p,x) = 0;
            IS(p,x) = 0;
            CS(p,x) = 0;
        }
        for (int r = 0; r < NREGS; r++) {
            IL(p,r) = 0;
            CL(p,r) = 0;
            IREG(p,r) = 0;
            CREG(p,r) = 0;
        }
        ctrl[p] = 0;
        iAddr[p] = 0;
        cDY[p] = 0;
        cISB[p] = 0;
        cDS[p] = 0;
        cDL[p] = 0;
    }
    
    for (int k = 0; k < NCONTEXT; k++) {
        active[k] = get_rng(0,NPROC-1);
        if (k != 0) {
            for (int x = 0; x < ADDRSIZE; x++) {
                MUINIT(x,k) = __get_rng();
                MU(x,k) = MUINIT(x,k);
                DELTAINIT(x,k) = get_rng(-1,NPROC-1);
                DELTA(x,k) = DELTAINIT(x,k);
            }
        } else {
            for (int x = 0; x < ADDRSIZE; x++) {
                MU(x,k) = 0;
                DELTA(x,k) = -1;
            }
        }
    }
    // any initial memory values here
    MU(0,0) = 1;
    MU(2,0) = 1;
    // register initial values
    
    // Process 0 BEGIN
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,4) = new_iReg;
    CREG(0,4) = new_cReg;
    REGP(0,4) = 0;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,3) = new_iReg;
    CREG(0,3) = new_cReg;
    REGP(0,3) = 1;
    
    /* ST */
    // Guess
    IW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(0,REGP(0,4));
    CW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(0,REGP(0,4))] == 0);
    ASSUME(IW(0,REGP(0,4)) >= max(IREG(0,3),IREG(0,4)));
    ASSUME(IW(0,REGP(0,4)) >= max(cDY[0],cISB[0]));
    ASSUME(IW(0,REGP(0,4)) >= max(cDS[0],cDL[0]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(0,REGP(0,4)) >= CL(0,r));
    }
    ASSUME(CW(0,REGP(0,4)) >= IW(0, REGP(0,4)));
    ASSUME(active[CW(0,REGP(0,4))] == 0);
    ASSUME(CW(0,REGP(0,4)) >= max(CREG(0,3),IREG(0,4)));
    ASSUME(CW(0,REGP(0,4)) >= max(old_cW,CR(0,REGP(0,4))));
    ASSUME(CW(0,REGP(0,4)) >= ctrl[0]);
    ASSUME(CW(0,REGP(0,4)) >= iAddr[0]);
    // Update
    iAddr[0] = max(iAddr[0], IREG(0,4));
    MU(REGP(0,4),CW(0,REGP(0,4))) = REGP(0,3);
    NU(0,REGP(0,4)) = REGP(0,3);
    DELTA(REGP(0,4),CW(0,REGP(0,4))) = -1;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,4) = new_iReg;
    CREG(0,4) = new_cReg;
    REGP(0,4) = 1;
    
p0loop1:
    /* dmb.sy */
    // Guess
    old_cDY = cDY[0];
    cDY[0] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[0] >= old_cDY);
    ASSUME(cDY[0] >= max(cISB[0],cDL[0]));
    ASSUME(cDY[0] >= max(cDS[0],ctrl[0]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[0] >= CW(0,x));
        ASSUME(cDY[0] >= CR(0,x));
    }
    
    /* LD */
    // Guess
    IR(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(0,REGP(0,4));
    CR(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    IREG(0,3) = IR(0,REGP(0,4));
    CREG(0,3) = CR(0,REGP(0,4));
    // Check
    ASSUME(active[IR(0,REGP(0,4))] == 0);
    ASSUME(IR(0,REGP(0,4)) >= IW(0,REGP(0,4)));
    ASSUME(IR(0,REGP(0,4)) >= IREG(0,4));
    ASSUME(IR(0,REGP(0,4)) >= max(cDY[0],cISB[0]));
    ASSUME(IR(0,REGP(0,4)) >= cDL[0]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(0,REGP(0,4)) >= IL(0,rdp));
    }
    ASSUME(CR(0,REGP(0,4)) >= IR(0, REGP(0,4)));
    ASSUME(active[CR(0,REGP(0,4))] == 0);
    ASSUME(CR(0,REGP(0,4)) >= max(IREG(0,4),ctrl[0]));
    ASSUME(CR(0,REGP(0,4)) >= max(old_cR,CW(0,REGP(0,4))));
    // Update
    iAddr[0] = max(iAddr[0], IREG(0,4));
    if (IR(0,REGP(0,4)) < CW(0,REGP(0,4))) {
        REGP(0,3) = NU(0,REGP(0,4));
    } else {
        REGP(0,3) = MU(REGP(0,4),IR(0,REGP(0,4)));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(new_iReg >= IREG(0,3));
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    ASSUME(new_cReg >= CREG(0,3));
    // Update
    IREG(0,0) = new_iReg;
    CREG(0,0) = new_cReg;
    REGP(0,0) = REGP(0,3);
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,1) = new_iReg;
    CREG(0,1) = new_cReg;
    REGP(0,1) = 3;
    
    /* BGE */
    ctrl[0] = ctrl[0] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[0] < NCONTEXT);
    
    ASSUME(ctrl[0] >= IREG(0,0));
    ASSUME(ctrl[0] >= IREG(0,1));
    if (REGP(0,0) >= REGP(0,1))
        goto p0loop1;
    
    /* dmb.sy */
    // Guess
    old_cDY = cDY[0];
    cDY[0] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[0] >= old_cDY);
    ASSUME(cDY[0] >= max(cISB[0],cDL[0]));
    ASSUME(cDY[0] >= max(cDS[0],ctrl[0]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[0] >= CW(0,x));
        ASSUME(cDY[0] >= CR(0,x));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,3) = new_iReg;
    CREG(0,3) = new_cReg;
    REGP(0,3) = 3;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,4) = new_iReg;
    CREG(0,4) = new_cReg;
    REGP(0,4) = 0;
    
    /* ST */
    // Guess
    IW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(0,REGP(0,4));
    CW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(0,REGP(0,4))] == 0);
    ASSUME(IW(0,REGP(0,4)) >= max(IREG(0,3),IREG(0,4)));
    ASSUME(IW(0,REGP(0,4)) >= max(cDY[0],cISB[0]));
    ASSUME(IW(0,REGP(0,4)) >= max(cDS[0],cDL[0]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(0,REGP(0,4)) >= CL(0,r));
    }
    ASSUME(CW(0,REGP(0,4)) >= IW(0, REGP(0,4)));
    ASSUME(active[CW(0,REGP(0,4))] == 0);
    ASSUME(CW(0,REGP(0,4)) >= max(CREG(0,3),IREG(0,4)));
    ASSUME(CW(0,REGP(0,4)) >= max(old_cW,CR(0,REGP(0,4))));
    ASSUME(CW(0,REGP(0,4)) >= ctrl[0]);
    ASSUME(CW(0,REGP(0,4)) >= iAddr[0]);
    // Update
    iAddr[0] = max(iAddr[0], IREG(0,4));
    MU(REGP(0,4),CW(0,REGP(0,4))) = REGP(0,3);
    NU(0,REGP(0,4)) = REGP(0,3);
    DELTA(REGP(0,4),CW(0,REGP(0,4))) = -1;
    
    /* dmb.sy */
    // Guess
    old_cDY = cDY[0];
    cDY[0] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[0] >= old_cDY);
    ASSUME(cDY[0] >= max(cISB[0],cDL[0]));
    ASSUME(cDY[0] >= max(cDS[0],ctrl[0]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[0] >= CW(0,x));
        ASSUME(cDY[0] >= CR(0,x));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,4) = new_iReg;
    CREG(0,4) = new_cReg;
    REGP(0,4) = 1;
    
    /* LD */
    // Guess
    IR(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(0,REGP(0,4));
    CR(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    IREG(0,3) = IR(0,REGP(0,4));
    CREG(0,3) = CR(0,REGP(0,4));
    // Check
    ASSUME(active[IR(0,REGP(0,4))] == 0);
    ASSUME(IR(0,REGP(0,4)) >= IW(0,REGP(0,4)));
    ASSUME(IR(0,REGP(0,4)) >= IREG(0,4));
    ASSUME(IR(0,REGP(0,4)) >= max(cDY[0],cISB[0]));
    ASSUME(IR(0,REGP(0,4)) >= cDL[0]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(0,REGP(0,4)) >= IL(0,rdp));
    }
    ASSUME(CR(0,REGP(0,4)) >= IR(0, REGP(0,4)));
    ASSUME(active[CR(0,REGP(0,4))] == 0);
    ASSUME(CR(0,REGP(0,4)) >= max(IREG(0,4),ctrl[0]));
    ASSUME(CR(0,REGP(0,4)) >= max(old_cR,CW(0,REGP(0,4))));
    // Update
    iAddr[0] = max(iAddr[0], IREG(0,4));
    if (IR(0,REGP(0,4)) < CW(0,REGP(0,4))) {
        REGP(0,3) = NU(0,REGP(0,4));
    } else {
        REGP(0,3) = MU(REGP(0,4),IR(0,REGP(0,4)));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(new_iReg >= IREG(0,3));
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    ASSUME(new_cReg >= CREG(0,3));
    // Update
    IREG(0,0) = new_iReg;
    CREG(0,0) = new_cReg;
    REGP(0,0) = REGP(0,3);
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,1) = new_iReg;
    CREG(0,1) = new_cReg;
    REGP(0,1) = 1;
    
    /* BNE */
    ctrl[0] = ctrl[0] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[0] < NCONTEXT);
    
    ASSUME(ctrl[0] >= IREG(0,0));
    ASSUME(ctrl[0] >= IREG(0,1));
    if (REGP(0,0) != REGP(0,1))
        goto p0skip;
    
    /* dmb.sy */
    // Guess
    old_cDY = cDY[0];
    cDY[0] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[0] >= old_cDY);
    ASSUME(cDY[0] >= max(cISB[0],cDL[0]));
    ASSUME(cDY[0] >= max(cDS[0],ctrl[0]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[0] >= CW(0,x));
        ASSUME(cDY[0] >= CR(0,x));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,3) = new_iReg;
    CREG(0,3) = new_cReg;
    REGP(0,3) = 2;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,4) = new_iReg;
    CREG(0,4) = new_cReg;
    REGP(0,4) = 0;
    
    /* ST */
    // Guess
    IW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(0,REGP(0,4));
    CW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(0,REGP(0,4))] == 0);
    ASSUME(IW(0,REGP(0,4)) >= max(IREG(0,3),IREG(0,4)));
    ASSUME(IW(0,REGP(0,4)) >= max(cDY[0],cISB[0]));
    ASSUME(IW(0,REGP(0,4)) >= max(cDS[0],cDL[0]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(0,REGP(0,4)) >= CL(0,r));
    }
    ASSUME(CW(0,REGP(0,4)) >= IW(0, REGP(0,4)));
    ASSUME(active[CW(0,REGP(0,4))] == 0);
    ASSUME(CW(0,REGP(0,4)) >= max(CREG(0,3),IREG(0,4)));
    ASSUME(CW(0,REGP(0,4)) >= max(old_cW,CR(0,REGP(0,4))));
    ASSUME(CW(0,REGP(0,4)) >= ctrl[0]);
    ASSUME(CW(0,REGP(0,4)) >= iAddr[0]);
    // Update
    iAddr[0] = max(iAddr[0], IREG(0,4));
    MU(REGP(0,4),CW(0,REGP(0,4))) = REGP(0,3);
    NU(0,REGP(0,4)) = REGP(0,3);
    DELTA(REGP(0,4),CW(0,REGP(0,4))) = -1;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,4) = new_iReg;
    CREG(0,4) = new_cReg;
    REGP(0,4) = 1;
    
p0loop2:
    /* dmb.sy */
    // Guess
    old_cDY = cDY[0];
    cDY[0] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[0] >= old_cDY);
    ASSUME(cDY[0] >= max(cISB[0],cDL[0]));
    ASSUME(cDY[0] >= max(cDS[0],ctrl[0]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[0] >= CW(0,x));
        ASSUME(cDY[0] >= CR(0,x));
    }
    
    /* LD */
    // Guess
    IR(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(0,REGP(0,4));
    CR(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    IREG(0,3) = IR(0,REGP(0,4));
    CREG(0,3) = CR(0,REGP(0,4));
    // Check
    ASSUME(active[IR(0,REGP(0,4))] == 0);
    ASSUME(IR(0,REGP(0,4)) >= IW(0,REGP(0,4)));
    ASSUME(IR(0,REGP(0,4)) >= IREG(0,4));
    ASSUME(IR(0,REGP(0,4)) >= max(cDY[0],cISB[0]));
    ASSUME(IR(0,REGP(0,4)) >= cDL[0]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(0,REGP(0,4)) >= IL(0,rdp));
    }
    ASSUME(CR(0,REGP(0,4)) >= IR(0, REGP(0,4)));
    ASSUME(active[CR(0,REGP(0,4))] == 0);
    ASSUME(CR(0,REGP(0,4)) >= max(IREG(0,4),ctrl[0]));
    ASSUME(CR(0,REGP(0,4)) >= max(old_cR,CW(0,REGP(0,4))));
    // Update
    iAddr[0] = max(iAddr[0], IREG(0,4));
    if (IR(0,REGP(0,4)) < CW(0,REGP(0,4))) {
        REGP(0,3) = NU(0,REGP(0,4));
    } else {
        REGP(0,3) = MU(REGP(0,4),IR(0,REGP(0,4)));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(new_iReg >= IREG(0,3));
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    ASSUME(new_cReg >= CREG(0,3));
    // Update
    IREG(0,0) = new_iReg;
    CREG(0,0) = new_cReg;
    REGP(0,0) = REGP(0,3);
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,1) = new_iReg;
    CREG(0,1) = new_cReg;
    REGP(0,1) = 4;
    
    /* BNE */
    ctrl[0] = ctrl[0] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[0] < NCONTEXT);
    
    ASSUME(ctrl[0] >= IREG(0,0));
    ASSUME(ctrl[0] >= IREG(0,1));
    if (REGP(0,0) != REGP(0,1))
        goto p0loop2;
    
p0skip:
    /* dmb.sy */
    // Guess
    old_cDY = cDY[0];
    cDY[0] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[0] >= old_cDY);
    ASSUME(cDY[0] >= max(cISB[0],cDL[0]));
    ASSUME(cDY[0] >= max(cDS[0],ctrl[0]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[0] >= CW(0,x));
        ASSUME(cDY[0] >= CR(0,x));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,3) = new_iReg;
    CREG(0,3) = new_cReg;
    REGP(0,3) = 4;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,4) = new_iReg;
    CREG(0,4) = new_cReg;
    REGP(0,4) = 0;
    
    /* ST */
    // Guess
    IW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(0,REGP(0,4));
    CW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(0,REGP(0,4))] == 0);
    ASSUME(IW(0,REGP(0,4)) >= max(IREG(0,3),IREG(0,4)));
    ASSUME(IW(0,REGP(0,4)) >= max(cDY[0],cISB[0]));
    ASSUME(IW(0,REGP(0,4)) >= max(cDS[0],cDL[0]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(0,REGP(0,4)) >= CL(0,r));
    }
    ASSUME(CW(0,REGP(0,4)) >= IW(0, REGP(0,4)));
    ASSUME(active[CW(0,REGP(0,4))] == 0);
    ASSUME(CW(0,REGP(0,4)) >= max(CREG(0,3),IREG(0,4)));
    ASSUME(CW(0,REGP(0,4)) >= max(old_cW,CR(0,REGP(0,4))));
    ASSUME(CW(0,REGP(0,4)) >= ctrl[0]);
    ASSUME(CW(0,REGP(0,4)) >= iAddr[0]);
    // Update
    iAddr[0] = max(iAddr[0], IREG(0,4));
    MU(REGP(0,4),CW(0,REGP(0,4))) = REGP(0,3);
    NU(0,REGP(0,4)) = REGP(0,3);
    DELTA(REGP(0,4),CW(0,REGP(0,4))) = -1;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,4) = new_iReg;
    CREG(0,4) = new_cReg;
    REGP(0,4) = 1;
    
p0loop3:
    /* dmb.sy */
    // Guess
    old_cDY = cDY[0];
    cDY[0] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[0] >= old_cDY);
    ASSUME(cDY[0] >= max(cISB[0],cDL[0]));
    ASSUME(cDY[0] >= max(cDS[0],ctrl[0]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[0] >= CW(0,x));
        ASSUME(cDY[0] >= CR(0,x));
    }
    
    /* LD */
    // Guess
    IR(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(0,REGP(0,4));
    CR(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    IREG(0,3) = IR(0,REGP(0,4));
    CREG(0,3) = CR(0,REGP(0,4));
    // Check
    ASSUME(active[IR(0,REGP(0,4))] == 0);
    ASSUME(IR(0,REGP(0,4)) >= IW(0,REGP(0,4)));
    ASSUME(IR(0,REGP(0,4)) >= IREG(0,4));
    ASSUME(IR(0,REGP(0,4)) >= max(cDY[0],cISB[0]));
    ASSUME(IR(0,REGP(0,4)) >= cDL[0]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(0,REGP(0,4)) >= IL(0,rdp));
    }
    ASSUME(CR(0,REGP(0,4)) >= IR(0, REGP(0,4)));
    ASSUME(active[CR(0,REGP(0,4))] == 0);
    ASSUME(CR(0,REGP(0,4)) >= max(IREG(0,4),ctrl[0]));
    ASSUME(CR(0,REGP(0,4)) >= max(old_cR,CW(0,REGP(0,4))));
    // Update
    iAddr[0] = max(iAddr[0], IREG(0,4));
    if (IR(0,REGP(0,4)) < CW(0,REGP(0,4))) {
        REGP(0,3) = NU(0,REGP(0,4));
    } else {
        REGP(0,3) = MU(REGP(0,4),IR(0,REGP(0,4)));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(new_iReg >= IREG(0,3));
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    ASSUME(new_cReg >= CREG(0,3));
    // Update
    IREG(0,0) = new_iReg;
    CREG(0,0) = new_cReg;
    REGP(0,0) = REGP(0,3);
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,1) = new_iReg;
    CREG(0,1) = new_cReg;
    REGP(0,1) = 2;
    
    /* BGE */
    ctrl[0] = ctrl[0] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[0] < NCONTEXT);
    
    ASSUME(ctrl[0] >= IREG(0,0));
    ASSUME(ctrl[0] >= IREG(0,1));
    if (REGP(0,0) >= REGP(0,1))
        goto p0loop3;
    
    /* dmb.sy */
    // Guess
    old_cDY = cDY[0];
    cDY[0] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[0] >= old_cDY);
    ASSUME(cDY[0] >= max(cISB[0],cDL[0]));
    ASSUME(cDY[0] >= max(cDS[0],ctrl[0]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[0] >= CW(0,x));
        ASSUME(cDY[0] >= CR(0,x));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,4) = new_iReg;
    CREG(0,4) = new_cReg;
    REGP(0,4) = 2;
    
    /* LD */
    // Guess
    IR(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(0,REGP(0,4));
    CR(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    IREG(0,3) = IR(0,REGP(0,4));
    CREG(0,3) = CR(0,REGP(0,4));
    // Check
    ASSUME(active[IR(0,REGP(0,4))] == 0);
    ASSUME(IR(0,REGP(0,4)) >= IW(0,REGP(0,4)));
    ASSUME(IR(0,REGP(0,4)) >= IREG(0,4));
    ASSUME(IR(0,REGP(0,4)) >= max(cDY[0],cISB[0]));
    ASSUME(IR(0,REGP(0,4)) >= cDL[0]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(0,REGP(0,4)) >= IL(0,rdp));
    }
    ASSUME(CR(0,REGP(0,4)) >= IR(0, REGP(0,4)));
    ASSUME(active[CR(0,REGP(0,4))] == 0);
    ASSUME(CR(0,REGP(0,4)) >= max(IREG(0,4),ctrl[0]));
    ASSUME(CR(0,REGP(0,4)) >= max(old_cR,CW(0,REGP(0,4))));
    // Update
    iAddr[0] = max(iAddr[0], IREG(0,4));
    if (IR(0,REGP(0,4)) < CW(0,REGP(0,4))) {
        REGP(0,3) = NU(0,REGP(0,4));
    } else {
        REGP(0,3) = MU(REGP(0,4),IR(0,REGP(0,4)));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(new_iReg >= IREG(0,3));
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    ASSUME(new_cReg >= CREG(0,3));
    // Update
    IREG(0,3) = new_iReg;
    CREG(0,3) = new_cReg;
    REGP(0,3) = (REGP(0,3) + 1);
    
    /* ST */
    // Guess
    IW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(0,REGP(0,4));
    CW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(0,REGP(0,4))] == 0);
    ASSUME(IW(0,REGP(0,4)) >= max(IREG(0,3),IREG(0,4)));
    ASSUME(IW(0,REGP(0,4)) >= max(cDY[0],cISB[0]));
    ASSUME(IW(0,REGP(0,4)) >= max(cDS[0],cDL[0]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(0,REGP(0,4)) >= CL(0,r));
    }
    ASSUME(CW(0,REGP(0,4)) >= IW(0, REGP(0,4)));
    ASSUME(active[CW(0,REGP(0,4))] == 0);
    ASSUME(CW(0,REGP(0,4)) >= max(CREG(0,3),IREG(0,4)));
    ASSUME(CW(0,REGP(0,4)) >= max(old_cW,CR(0,REGP(0,4))));
    ASSUME(CW(0,REGP(0,4)) >= ctrl[0]);
    ASSUME(CW(0,REGP(0,4)) >= iAddr[0]);
    // Update
    iAddr[0] = max(iAddr[0], IREG(0,4));
    MU(REGP(0,4),CW(0,REGP(0,4))) = REGP(0,3);
    NU(0,REGP(0,4)) = REGP(0,3);
    DELTA(REGP(0,4),CW(0,REGP(0,4))) = -1;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,4) = new_iReg;
    CREG(0,4) = new_cReg;
    REGP(0,4) = 1;
    
p0loop4:
    /* dmb.sy */
    // Guess
    old_cDY = cDY[0];
    cDY[0] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[0] >= old_cDY);
    ASSUME(cDY[0] >= max(cISB[0],cDL[0]));
    ASSUME(cDY[0] >= max(cDS[0],ctrl[0]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[0] >= CW(0,x));
        ASSUME(cDY[0] >= CR(0,x));
    }
    
    /* LD */
    // Guess
    IR(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(0,REGP(0,4));
    CR(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    IREG(0,3) = IR(0,REGP(0,4));
    CREG(0,3) = CR(0,REGP(0,4));
    // Check
    ASSUME(active[IR(0,REGP(0,4))] == 0);
    ASSUME(IR(0,REGP(0,4)) >= IW(0,REGP(0,4)));
    ASSUME(IR(0,REGP(0,4)) >= IREG(0,4));
    ASSUME(IR(0,REGP(0,4)) >= max(cDY[0],cISB[0]));
    ASSUME(IR(0,REGP(0,4)) >= cDL[0]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(0,REGP(0,4)) >= IL(0,rdp));
    }
    ASSUME(CR(0,REGP(0,4)) >= IR(0, REGP(0,4)));
    ASSUME(active[CR(0,REGP(0,4))] == 0);
    ASSUME(CR(0,REGP(0,4)) >= max(IREG(0,4),ctrl[0]));
    ASSUME(CR(0,REGP(0,4)) >= max(old_cR,CW(0,REGP(0,4))));
    // Update
    iAddr[0] = max(iAddr[0], IREG(0,4));
    if (IR(0,REGP(0,4)) < CW(0,REGP(0,4))) {
        REGP(0,3) = NU(0,REGP(0,4));
    } else {
        REGP(0,3) = MU(REGP(0,4),IR(0,REGP(0,4)));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(new_iReg >= IREG(0,3));
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    ASSUME(new_cReg >= CREG(0,3));
    // Update
    IREG(0,0) = new_iReg;
    CREG(0,0) = new_cReg;
    REGP(0,0) = REGP(0,3);
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,1) = new_iReg;
    CREG(0,1) = new_cReg;
    REGP(0,1) = 3;
    
    /* BEQ */
    ctrl[0] = ctrl[0] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[0] < NCONTEXT);
    
    ASSUME(ctrl[0] >= IREG(0,0));
    ASSUME(ctrl[0] >= IREG(0,1));
    if (REGP(0,0) == REGP(0,1))
        goto p0end;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(new_iReg >= IREG(0,3));
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    ASSUME(new_cReg >= CREG(0,3));
    // Update
    IREG(0,0) = new_iReg;
    CREG(0,0) = new_cReg;
    REGP(0,0) = REGP(0,3);
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,1) = new_iReg;
    CREG(0,1) = new_cReg;
    REGP(0,1) = 2;
    
    /* BNE */
    ctrl[0] = ctrl[0] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[0] < NCONTEXT);
    
    ASSUME(ctrl[0] >= IREG(0,0));
    ASSUME(ctrl[0] >= IREG(0,1));
    if (REGP(0,0) != REGP(0,1))
        goto p0loop4;
    
p0end:
    /* dmb.sy */
    // Guess
    old_cDY = cDY[0];
    cDY[0] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[0] >= old_cDY);
    ASSUME(cDY[0] >= max(cISB[0],cDL[0]));
    ASSUME(cDY[0] >= max(cDS[0],ctrl[0]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[0] >= CW(0,x));
        ASSUME(cDY[0] >= CR(0,x));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,4) = new_iReg;
    CREG(0,4) = new_cReg;
    REGP(0,4) = 0;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 0);
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= max(ctrl[0],new_iReg));
    // Update
    IREG(0,3) = new_iReg;
    CREG(0,3) = new_cReg;
    REGP(0,3) = 0;
    
    /* ST */
    // Guess
    IW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(0,REGP(0,4));
    CW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(0,REGP(0,4))] == 0);
    ASSUME(IW(0,REGP(0,4)) >= max(IREG(0,3),IREG(0,4)));
    ASSUME(IW(0,REGP(0,4)) >= max(cDY[0],cISB[0]));
    ASSUME(IW(0,REGP(0,4)) >= max(cDS[0],cDL[0]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(0,REGP(0,4)) >= CL(0,r));
    }
    ASSUME(CW(0,REGP(0,4)) >= IW(0, REGP(0,4)));
    ASSUME(active[CW(0,REGP(0,4))] == 0);
    ASSUME(CW(0,REGP(0,4)) >= max(CREG(0,3),IREG(0,4)));
    ASSUME(CW(0,REGP(0,4)) >= max(old_cW,CR(0,REGP(0,4))));
    ASSUME(CW(0,REGP(0,4)) >= ctrl[0]);
    ASSUME(CW(0,REGP(0,4)) >= iAddr[0]);
    // Update
    iAddr[0] = max(iAddr[0], IREG(0,4));
    MU(REGP(0,4),CW(0,REGP(0,4))) = REGP(0,3);
    NU(0,REGP(0,4)) = REGP(0,3);
    DELTA(REGP(0,4),CW(0,REGP(0,4))) = -1;
    
    // Process 0 END
    
    // Process 1 BEGIN
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,4) = new_iReg;
    CREG(1,4) = new_cReg;
    REGP(1,4) = 1;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,3) = new_iReg;
    CREG(1,3) = new_cReg;
    REGP(1,3) = 1;
    
    /* ST */
    // Guess
    IW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(1,REGP(1,4));
    CW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(1,REGP(1,4))] == 1);
    ASSUME(IW(1,REGP(1,4)) >= max(IREG(1,3),IREG(1,4)));
    ASSUME(IW(1,REGP(1,4)) >= max(cDY[1],cISB[1]));
    ASSUME(IW(1,REGP(1,4)) >= max(cDS[1],cDL[1]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(1,REGP(1,4)) >= CL(1,r));
    }
    ASSUME(CW(1,REGP(1,4)) >= IW(1, REGP(1,4)));
    ASSUME(active[CW(1,REGP(1,4))] == 1);
    ASSUME(CW(1,REGP(1,4)) >= max(CREG(1,3),IREG(1,4)));
    ASSUME(CW(1,REGP(1,4)) >= max(old_cW,CR(1,REGP(1,4))));
    ASSUME(CW(1,REGP(1,4)) >= ctrl[1]);
    ASSUME(CW(1,REGP(1,4)) >= iAddr[1]);
    // Update
    iAddr[1] = max(iAddr[1], IREG(1,4));
    MU(REGP(1,4),CW(1,REGP(1,4))) = REGP(1,3);
    NU(1,REGP(1,4)) = REGP(1,3);
    DELTA(REGP(1,4),CW(1,REGP(1,4))) = -1;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,4) = new_iReg;
    CREG(1,4) = new_cReg;
    REGP(1,4) = 0;
    
p1loop1:
    /* dmb.sy */
    // Guess
    old_cDY = cDY[1];
    cDY[1] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[1] >= old_cDY);
    ASSUME(cDY[1] >= max(cISB[1],cDL[1]));
    ASSUME(cDY[1] >= max(cDS[1],ctrl[1]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[1] >= CW(1,x));
        ASSUME(cDY[1] >= CR(1,x));
    }
    
    /* LD */
    // Guess
    IR(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(1,REGP(1,4));
    CR(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    IREG(1,3) = IR(1,REGP(1,4));
    CREG(1,3) = CR(1,REGP(1,4));
    // Check
    ASSUME(active[IR(1,REGP(1,4))] == 1);
    ASSUME(IR(1,REGP(1,4)) >= IW(1,REGP(1,4)));
    ASSUME(IR(1,REGP(1,4)) >= IREG(1,4));
    ASSUME(IR(1,REGP(1,4)) >= max(cDY[1],cISB[1]));
    ASSUME(IR(1,REGP(1,4)) >= cDL[1]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(1,REGP(1,4)) >= IL(1,rdp));
    }
    ASSUME(CR(1,REGP(1,4)) >= IR(1, REGP(1,4)));
    ASSUME(active[CR(1,REGP(1,4))] == 1);
    ASSUME(CR(1,REGP(1,4)) >= max(IREG(1,4),ctrl[1]));
    ASSUME(CR(1,REGP(1,4)) >= max(old_cR,CW(1,REGP(1,4))));
    // Update
    iAddr[1] = max(iAddr[1], IREG(1,4));
    if (IR(1,REGP(1,4)) < CW(1,REGP(1,4))) {
        REGP(1,3) = NU(1,REGP(1,4));
    } else {
        REGP(1,3) = MU(REGP(1,4),IR(1,REGP(1,4)));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(new_iReg >= IREG(1,3));
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    ASSUME(new_cReg >= CREG(1,3));
    // Update
    IREG(1,0) = new_iReg;
    CREG(1,0) = new_cReg;
    REGP(1,0) = REGP(1,3);
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,1) = new_iReg;
    CREG(1,1) = new_cReg;
    REGP(1,1) = 3;
    
    /* BGE */
    ctrl[1] = ctrl[1] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[1] < NCONTEXT);
    
    ASSUME(ctrl[1] >= IREG(1,0));
    ASSUME(ctrl[1] >= IREG(1,1));
    if (REGP(1,0) >= REGP(1,1))
        goto p1loop1;
    
    /* dmb.sy */
    // Guess
    old_cDY = cDY[1];
    cDY[1] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[1] >= old_cDY);
    ASSUME(cDY[1] >= max(cISB[1],cDL[1]));
    ASSUME(cDY[1] >= max(cDS[1],ctrl[1]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[1] >= CW(1,x));
        ASSUME(cDY[1] >= CR(1,x));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,3) = new_iReg;
    CREG(1,3) = new_cReg;
    REGP(1,3) = 3;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,4) = new_iReg;
    CREG(1,4) = new_cReg;
    REGP(1,4) = 1;
    
    /* ST */
    // Guess
    IW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(1,REGP(1,4));
    CW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(1,REGP(1,4))] == 1);
    ASSUME(IW(1,REGP(1,4)) >= max(IREG(1,3),IREG(1,4)));
    ASSUME(IW(1,REGP(1,4)) >= max(cDY[1],cISB[1]));
    ASSUME(IW(1,REGP(1,4)) >= max(cDS[1],cDL[1]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(1,REGP(1,4)) >= CL(1,r));
    }
    ASSUME(CW(1,REGP(1,4)) >= IW(1, REGP(1,4)));
    ASSUME(active[CW(1,REGP(1,4))] == 1);
    ASSUME(CW(1,REGP(1,4)) >= max(CREG(1,3),IREG(1,4)));
    ASSUME(CW(1,REGP(1,4)) >= max(old_cW,CR(1,REGP(1,4))));
    ASSUME(CW(1,REGP(1,4)) >= ctrl[1]);
    ASSUME(CW(1,REGP(1,4)) >= iAddr[1]);
    // Update
    iAddr[1] = max(iAddr[1], IREG(1,4));
    MU(REGP(1,4),CW(1,REGP(1,4))) = REGP(1,3);
    NU(1,REGP(1,4)) = REGP(1,3);
    DELTA(REGP(1,4),CW(1,REGP(1,4))) = -1;
    
    /* dmb.sy */
    // Guess
    old_cDY = cDY[1];
    cDY[1] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[1] >= old_cDY);
    ASSUME(cDY[1] >= max(cISB[1],cDL[1]));
    ASSUME(cDY[1] >= max(cDS[1],ctrl[1]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[1] >= CW(1,x));
        ASSUME(cDY[1] >= CR(1,x));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,4) = new_iReg;
    CREG(1,4) = new_cReg;
    REGP(1,4) = 0;
    
    /* LD */
    // Guess
    IR(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(1,REGP(1,4));
    CR(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    IREG(1,3) = IR(1,REGP(1,4));
    CREG(1,3) = CR(1,REGP(1,4));
    // Check
    ASSUME(active[IR(1,REGP(1,4))] == 1);
    ASSUME(IR(1,REGP(1,4)) >= IW(1,REGP(1,4)));
    ASSUME(IR(1,REGP(1,4)) >= IREG(1,4));
    ASSUME(IR(1,REGP(1,4)) >= max(cDY[1],cISB[1]));
    ASSUME(IR(1,REGP(1,4)) >= cDL[1]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(1,REGP(1,4)) >= IL(1,rdp));
    }
    ASSUME(CR(1,REGP(1,4)) >= IR(1, REGP(1,4)));
    ASSUME(active[CR(1,REGP(1,4))] == 1);
    ASSUME(CR(1,REGP(1,4)) >= max(IREG(1,4),ctrl[1]));
    ASSUME(CR(1,REGP(1,4)) >= max(old_cR,CW(1,REGP(1,4))));
    // Update
    iAddr[1] = max(iAddr[1], IREG(1,4));
    if (IR(1,REGP(1,4)) < CW(1,REGP(1,4))) {
        REGP(1,3) = NU(1,REGP(1,4));
    } else {
        REGP(1,3) = MU(REGP(1,4),IR(1,REGP(1,4)));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(new_iReg >= IREG(1,3));
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    ASSUME(new_cReg >= CREG(1,3));
    // Update
    IREG(1,0) = new_iReg;
    CREG(1,0) = new_cReg;
    REGP(1,0) = REGP(1,3);
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,1) = new_iReg;
    CREG(1,1) = new_cReg;
    REGP(1,1) = 1;
    
    /* BNE */
    ctrl[1] = ctrl[1] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[1] < NCONTEXT);
    
    ASSUME(ctrl[1] >= IREG(1,0));
    ASSUME(ctrl[1] >= IREG(1,1));
    if (REGP(1,0) != REGP(1,1))
        goto p1skip;
    
    /* dmb.sy */
    // Guess
    old_cDY = cDY[1];
    cDY[1] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[1] >= old_cDY);
    ASSUME(cDY[1] >= max(cISB[1],cDL[1]));
    ASSUME(cDY[1] >= max(cDS[1],ctrl[1]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[1] >= CW(1,x));
        ASSUME(cDY[1] >= CR(1,x));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,3) = new_iReg;
    CREG(1,3) = new_cReg;
    REGP(1,3) = 2;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,4) = new_iReg;
    CREG(1,4) = new_cReg;
    REGP(1,4) = 1;
    
    /* ST */
    // Guess
    IW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(1,REGP(1,4));
    CW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(1,REGP(1,4))] == 1);
    ASSUME(IW(1,REGP(1,4)) >= max(IREG(1,3),IREG(1,4)));
    ASSUME(IW(1,REGP(1,4)) >= max(cDY[1],cISB[1]));
    ASSUME(IW(1,REGP(1,4)) >= max(cDS[1],cDL[1]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(1,REGP(1,4)) >= CL(1,r));
    }
    ASSUME(CW(1,REGP(1,4)) >= IW(1, REGP(1,4)));
    ASSUME(active[CW(1,REGP(1,4))] == 1);
    ASSUME(CW(1,REGP(1,4)) >= max(CREG(1,3),IREG(1,4)));
    ASSUME(CW(1,REGP(1,4)) >= max(old_cW,CR(1,REGP(1,4))));
    ASSUME(CW(1,REGP(1,4)) >= ctrl[1]);
    ASSUME(CW(1,REGP(1,4)) >= iAddr[1]);
    // Update
    iAddr[1] = max(iAddr[1], IREG(1,4));
    MU(REGP(1,4),CW(1,REGP(1,4))) = REGP(1,3);
    NU(1,REGP(1,4)) = REGP(1,3);
    DELTA(REGP(1,4),CW(1,REGP(1,4))) = -1;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,4) = new_iReg;
    CREG(1,4) = new_cReg;
    REGP(1,4) = 0;
    
p1loop2:
    /* dmb.sy */
    // Guess
    old_cDY = cDY[1];
    cDY[1] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[1] >= old_cDY);
    ASSUME(cDY[1] >= max(cISB[1],cDL[1]));
    ASSUME(cDY[1] >= max(cDS[1],ctrl[1]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[1] >= CW(1,x));
        ASSUME(cDY[1] >= CR(1,x));
    }
    
    /* LD */
    // Guess
    IR(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(1,REGP(1,4));
    CR(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    IREG(1,3) = IR(1,REGP(1,4));
    CREG(1,3) = CR(1,REGP(1,4));
    // Check
    ASSUME(active[IR(1,REGP(1,4))] == 1);
    ASSUME(IR(1,REGP(1,4)) >= IW(1,REGP(1,4)));
    ASSUME(IR(1,REGP(1,4)) >= IREG(1,4));
    ASSUME(IR(1,REGP(1,4)) >= max(cDY[1],cISB[1]));
    ASSUME(IR(1,REGP(1,4)) >= cDL[1]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(1,REGP(1,4)) >= IL(1,rdp));
    }
    ASSUME(CR(1,REGP(1,4)) >= IR(1, REGP(1,4)));
    ASSUME(active[CR(1,REGP(1,4))] == 1);
    ASSUME(CR(1,REGP(1,4)) >= max(IREG(1,4),ctrl[1]));
    ASSUME(CR(1,REGP(1,4)) >= max(old_cR,CW(1,REGP(1,4))));
    // Update
    iAddr[1] = max(iAddr[1], IREG(1,4));
    if (IR(1,REGP(1,4)) < CW(1,REGP(1,4))) {
        REGP(1,3) = NU(1,REGP(1,4));
    } else {
        REGP(1,3) = MU(REGP(1,4),IR(1,REGP(1,4)));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(new_iReg >= IREG(1,3));
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    ASSUME(new_cReg >= CREG(1,3));
    // Update
    IREG(1,0) = new_iReg;
    CREG(1,0) = new_cReg;
    REGP(1,0) = REGP(1,3);
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,1) = new_iReg;
    CREG(1,1) = new_cReg;
    REGP(1,1) = 4;
    
    /* BNE */
    ctrl[1] = ctrl[1] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[1] < NCONTEXT);
    
    ASSUME(ctrl[1] >= IREG(1,0));
    ASSUME(ctrl[1] >= IREG(1,1));
    if (REGP(1,0) != REGP(1,1))
        goto p1loop2;
    
p1skip:
    /* dmb.sy */
    // Guess
    old_cDY = cDY[1];
    cDY[1] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[1] >= old_cDY);
    ASSUME(cDY[1] >= max(cISB[1],cDL[1]));
    ASSUME(cDY[1] >= max(cDS[1],ctrl[1]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[1] >= CW(1,x));
        ASSUME(cDY[1] >= CR(1,x));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,3) = new_iReg;
    CREG(1,3) = new_cReg;
    REGP(1,3) = 4;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,4) = new_iReg;
    CREG(1,4) = new_cReg;
    REGP(1,4) = 1;
    
    /* ST */
    // Guess
    IW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(1,REGP(1,4));
    CW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(1,REGP(1,4))] == 1);
    ASSUME(IW(1,REGP(1,4)) >= max(IREG(1,3),IREG(1,4)));
    ASSUME(IW(1,REGP(1,4)) >= max(cDY[1],cISB[1]));
    ASSUME(IW(1,REGP(1,4)) >= max(cDS[1],cDL[1]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(1,REGP(1,4)) >= CL(1,r));
    }
    ASSUME(CW(1,REGP(1,4)) >= IW(1, REGP(1,4)));
    ASSUME(active[CW(1,REGP(1,4))] == 1);
    ASSUME(CW(1,REGP(1,4)) >= max(CREG(1,3),IREG(1,4)));
    ASSUME(CW(1,REGP(1,4)) >= max(old_cW,CR(1,REGP(1,4))));
    ASSUME(CW(1,REGP(1,4)) >= ctrl[1]);
    ASSUME(CW(1,REGP(1,4)) >= iAddr[1]);
    // Update
    iAddr[1] = max(iAddr[1], IREG(1,4));
    MU(REGP(1,4),CW(1,REGP(1,4))) = REGP(1,3);
    NU(1,REGP(1,4)) = REGP(1,3);
    DELTA(REGP(1,4),CW(1,REGP(1,4))) = -1;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,4) = new_iReg;
    CREG(1,4) = new_cReg;
    REGP(1,4) = 0;
    
p1loop3:
    /* dmb.sy */
    // Guess
    old_cDY = cDY[1];
    cDY[1] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[1] >= old_cDY);
    ASSUME(cDY[1] >= max(cISB[1],cDL[1]));
    ASSUME(cDY[1] >= max(cDS[1],ctrl[1]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[1] >= CW(1,x));
        ASSUME(cDY[1] >= CR(1,x));
    }
    
    /* LD */
    // Guess
    IR(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(1,REGP(1,4));
    CR(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    IREG(1,3) = IR(1,REGP(1,4));
    CREG(1,3) = CR(1,REGP(1,4));
    // Check
    ASSUME(active[IR(1,REGP(1,4))] == 1);
    ASSUME(IR(1,REGP(1,4)) >= IW(1,REGP(1,4)));
    ASSUME(IR(1,REGP(1,4)) >= IREG(1,4));
    ASSUME(IR(1,REGP(1,4)) >= max(cDY[1],cISB[1]));
    ASSUME(IR(1,REGP(1,4)) >= cDL[1]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(1,REGP(1,4)) >= IL(1,rdp));
    }
    ASSUME(CR(1,REGP(1,4)) >= IR(1, REGP(1,4)));
    ASSUME(active[CR(1,REGP(1,4))] == 1);
    ASSUME(CR(1,REGP(1,4)) >= max(IREG(1,4),ctrl[1]));
    ASSUME(CR(1,REGP(1,4)) >= max(old_cR,CW(1,REGP(1,4))));
    // Update
    iAddr[1] = max(iAddr[1], IREG(1,4));
    if (IR(1,REGP(1,4)) < CW(1,REGP(1,4))) {
        REGP(1,3) = NU(1,REGP(1,4));
    } else {
        REGP(1,3) = MU(REGP(1,4),IR(1,REGP(1,4)));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(new_iReg >= IREG(1,3));
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    ASSUME(new_cReg >= CREG(1,3));
    // Update
    IREG(1,0) = new_iReg;
    CREG(1,0) = new_cReg;
    REGP(1,0) = REGP(1,3);
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,1) = new_iReg;
    CREG(1,1) = new_cReg;
    REGP(1,1) = 2;
    
    /* BGE */
    ctrl[1] = ctrl[1] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[1] < NCONTEXT);
    
    ASSUME(ctrl[1] >= IREG(1,0));
    ASSUME(ctrl[1] >= IREG(1,1));
    if (REGP(1,0) >= REGP(1,1))
        goto p1loop3;
    
    /* dmb.sy */
    // Guess
    old_cDY = cDY[1];
    cDY[1] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[1] >= old_cDY);
    ASSUME(cDY[1] >= max(cISB[1],cDL[1]));
    ASSUME(cDY[1] >= max(cDS[1],ctrl[1]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[1] >= CW(1,x));
        ASSUME(cDY[1] >= CR(1,x));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,4) = new_iReg;
    CREG(1,4) = new_cReg;
    REGP(1,4) = 2;
    
    /* LD */
    // Guess
    IR(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(1,REGP(1,4));
    CR(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    IREG(1,3) = IR(1,REGP(1,4));
    CREG(1,3) = CR(1,REGP(1,4));
    // Check
    ASSUME(active[IR(1,REGP(1,4))] == 1);
    ASSUME(IR(1,REGP(1,4)) >= IW(1,REGP(1,4)));
    ASSUME(IR(1,REGP(1,4)) >= IREG(1,4));
    ASSUME(IR(1,REGP(1,4)) >= max(cDY[1],cISB[1]));
    ASSUME(IR(1,REGP(1,4)) >= cDL[1]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(1,REGP(1,4)) >= IL(1,rdp));
    }
    ASSUME(CR(1,REGP(1,4)) >= IR(1, REGP(1,4)));
    ASSUME(active[CR(1,REGP(1,4))] == 1);
    ASSUME(CR(1,REGP(1,4)) >= max(IREG(1,4),ctrl[1]));
    ASSUME(CR(1,REGP(1,4)) >= max(old_cR,CW(1,REGP(1,4))));
    // Update
    iAddr[1] = max(iAddr[1], IREG(1,4));
    if (IR(1,REGP(1,4)) < CW(1,REGP(1,4))) {
        REGP(1,3) = NU(1,REGP(1,4));
    } else {
        REGP(1,3) = MU(REGP(1,4),IR(1,REGP(1,4)));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(new_iReg >= IREG(1,3));
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    ASSUME(new_cReg >= CREG(1,3));
    // Update
    IREG(1,3) = new_iReg;
    CREG(1,3) = new_cReg;
    REGP(1,3) = (REGP(1,3) + 1);
    
    /* ST */
    // Guess
    IW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(1,REGP(1,4));
    CW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(1,REGP(1,4))] == 1);
    ASSUME(IW(1,REGP(1,4)) >= max(IREG(1,3),IREG(1,4)));
    ASSUME(IW(1,REGP(1,4)) >= max(cDY[1],cISB[1]));
    ASSUME(IW(1,REGP(1,4)) >= max(cDS[1],cDL[1]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(1,REGP(1,4)) >= CL(1,r));
    }
    ASSUME(CW(1,REGP(1,4)) >= IW(1, REGP(1,4)));
    ASSUME(active[CW(1,REGP(1,4))] == 1);
    ASSUME(CW(1,REGP(1,4)) >= max(CREG(1,3),IREG(1,4)));
    ASSUME(CW(1,REGP(1,4)) >= max(old_cW,CR(1,REGP(1,4))));
    ASSUME(CW(1,REGP(1,4)) >= ctrl[1]);
    ASSUME(CW(1,REGP(1,4)) >= iAddr[1]);
    // Update
    iAddr[1] = max(iAddr[1], IREG(1,4));
    MU(REGP(1,4),CW(1,REGP(1,4))) = REGP(1,3);
    NU(1,REGP(1,4)) = REGP(1,3);
    DELTA(REGP(1,4),CW(1,REGP(1,4))) = -1;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,4) = new_iReg;
    CREG(1,4) = new_cReg;
    REGP(1,4) = 0;
    
p1loop4:
    /* LD */
    // Guess
    IR(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(1,REGP(1,4));
    CR(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    IREG(1,3) = IR(1,REGP(1,4));
    CREG(1,3) = CR(1,REGP(1,4));
    // Check
    ASSUME(active[IR(1,REGP(1,4))] == 1);
    ASSUME(IR(1,REGP(1,4)) >= IW(1,REGP(1,4)));
    ASSUME(IR(1,REGP(1,4)) >= IREG(1,4));
    ASSUME(IR(1,REGP(1,4)) >= max(cDY[1],cISB[1]));
    ASSUME(IR(1,REGP(1,4)) >= cDL[1]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(1,REGP(1,4)) >= IL(1,rdp));
    }
    ASSUME(CR(1,REGP(1,4)) >= IR(1, REGP(1,4)));
    ASSUME(active[CR(1,REGP(1,4))] == 1);
    ASSUME(CR(1,REGP(1,4)) >= max(IREG(1,4),ctrl[1]));
    ASSUME(CR(1,REGP(1,4)) >= max(old_cR,CW(1,REGP(1,4))));
    // Update
    iAddr[1] = max(iAddr[1], IREG(1,4));
    if (IR(1,REGP(1,4)) < CW(1,REGP(1,4))) {
        REGP(1,3) = NU(1,REGP(1,4));
    } else {
        REGP(1,3) = MU(REGP(1,4),IR(1,REGP(1,4)));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(new_iReg >= IREG(1,3));
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    ASSUME(new_cReg >= CREG(1,3));
    // Update
    IREG(1,0) = new_iReg;
    CREG(1,0) = new_cReg;
    REGP(1,0) = REGP(1,3);
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,1) = new_iReg;
    CREG(1,1) = new_cReg;
    REGP(1,1) = 3;
    
    /* BEQ */
    ctrl[1] = ctrl[1] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[1] < NCONTEXT);
    
    ASSUME(ctrl[1] >= IREG(1,0));
    ASSUME(ctrl[1] >= IREG(1,1));
    if (REGP(1,0) == REGP(1,1))
        goto p1end;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(new_iReg >= IREG(1,3));
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    ASSUME(new_cReg >= CREG(1,3));
    // Update
    IREG(1,0) = new_iReg;
    CREG(1,0) = new_cReg;
    REGP(1,0) = REGP(1,3);
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,1) = new_iReg;
    CREG(1,1) = new_cReg;
    REGP(1,1) = 2;
    
    /* BNE */
    ctrl[1] = ctrl[1] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[1] < NCONTEXT);
    
    ASSUME(ctrl[1] >= IREG(1,0));
    ASSUME(ctrl[1] >= IREG(1,1));
    if (REGP(1,0) != REGP(1,1))
        goto p1loop4;
    
p1end:
    /* dmb.sy */
    // Guess
    old_cDY = cDY[1];
    cDY[1] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[1] >= old_cDY);
    ASSUME(cDY[1] >= max(cISB[1],cDL[1]));
    ASSUME(cDY[1] >= max(cDS[1],ctrl[1]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[1] >= CW(1,x));
        ASSUME(cDY[1] >= CR(1,x));
    }
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,4) = new_iReg;
    CREG(1,4) = new_cReg;
    REGP(1,4) = 0;
    
    /* assign */
    // Guess
    new_iReg = get_rng(0,NCONTEXT-1);
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_iReg] == 1);
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= max(ctrl[1],new_iReg));
    // Update
    IREG(1,3) = new_iReg;
    CREG(1,3) = new_cReg;
    REGP(1,3) = 1;
    
    /* ST */
    // Guess
    IW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(1,REGP(1,4));
    CW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(1,REGP(1,4))] == 1);
    ASSUME(IW(1,REGP(1,4)) >= max(IREG(1,3),IREG(1,4)));
    ASSUME(IW(1,REGP(1,4)) >= max(cDY[1],cISB[1]));
    ASSUME(IW(1,REGP(1,4)) >= max(cDS[1],cDL[1]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(1,REGP(1,4)) >= CL(1,r));
    }
    ASSUME(CW(1,REGP(1,4)) >= IW(1, REGP(1,4)));
    ASSUME(active[CW(1,REGP(1,4))] == 1);
    ASSUME(CW(1,REGP(1,4)) >= max(CREG(1,3),IREG(1,4)));
    ASSUME(CW(1,REGP(1,4)) >= max(old_cW,CR(1,REGP(1,4))));
    ASSUME(CW(1,REGP(1,4)) >= ctrl[1]);
    ASSUME(CW(1,REGP(1,4)) >= iAddr[1]);
    // Update
    iAddr[1] = max(iAddr[1], IREG(1,4));
    MU(REGP(1,4),CW(1,REGP(1,4))) = REGP(1,3);
    NU(1,REGP(1,4)) = REGP(1,3);
    DELTA(REGP(1,4),CW(1,REGP(1,4))) = -1;
    
    // Process 1 END
    
    /* verProc */
    for (int x = 0; x < ADDRSIZE; x++) {
        for (int k = 0; k < NCONTEXT-1; k++) {
            ASSUME(MU(x,k) == MUINIT(x,k+1));
            ASSUME(DELTA(x,k) == DELTAINIT(x,k+1));
        }
    }
    if (
        (MU(2,NCONTEXT-1) != 2) &&
    1)
        ASSERT(0);
    
    return 0;
}