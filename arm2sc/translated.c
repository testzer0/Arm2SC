#define NREGS 8
#define ADDRSIZE 7
#define NPROC 3
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
int old_cDY, old_cW, old_cR, new_cW;


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
    // register initial values
    
    // Process 0 BEGIN
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
    IREG(0,3) = get_rng(0,NCONTEXT-1);
    CREG(0,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,3)] == 0);
    ASSUME(active[CREG(0,3)] == 0);
    ASSUME(CREG(0,3) >= max(ctrl[0],IREG(0,3)));
    // Update
    REGP(0,3) = 1;
    
    /* assign */
    // Guess
    IREG(0,4) = get_rng(0,NCONTEXT-1);
    CREG(0,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,4)] == 0);
    ASSUME(active[CREG(0,4)] == 0);
    ASSUME(CREG(0,4) >= max(ctrl[0],IREG(0,4)));
    // Update
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
    IREG(0,3) = get_rng(0,NCONTEXT-1);
    CREG(0,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,3)] == 0);
    ASSUME(active[CREG(0,3)] == 0);
    ASSUME(CREG(0,3) >= max(ctrl[0],IREG(0,3)));
    // Update
    REGP(0,3) = 0;
    
    /* assign */
    // Guess
    IREG(0,4) = get_rng(0,NCONTEXT-1);
    CREG(0,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,4)] == 0);
    ASSUME(active[CREG(0,4)] == 0);
    ASSUME(CREG(0,4) >= max(ctrl[0],IREG(0,4)));
    // Update
    REGP(0,4) = 3;
    
p0findmax:
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
    IREG(0,5) = IR(0,REGP(0,4));
    CREG(0,5) = CR(0,REGP(0,4));
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
        REGP(0,5) = NU(0,REGP(0,4));
    } else {
        REGP(0,5) = MU(REGP(0,4),IR(0,REGP(0,4)));
    }
    
    /* assign */
    // Guess
    IREG(0,0) = get_rng(0,NCONTEXT-1);
    CREG(0,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,0)] == 0);
    ASSUME(IREG(0,0) >= IREG(0,3));
    ASSUME(active[CREG(0,0)] == 0);
    ASSUME(CREG(0,0) >= max(ctrl[0],IREG(0,0)));
    ASSUME(CREG(0,0) >= CREG(0,3));
    // Update
    REGP(0,0) = REGP(0,3);
    
    /* assign */
    // Guess
    IREG(0,1) = get_rng(0,NCONTEXT-1);
    CREG(0,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,1)] == 0);
    ASSUME(IREG(0,1) >= IREG(0,5));
    ASSUME(active[CREG(0,1)] == 0);
    ASSUME(CREG(0,1) >= max(ctrl[0],IREG(0,1)));
    ASSUME(CREG(0,1) >= CREG(0,5));
    // Update
    REGP(0,1) = REGP(0,5);
    
    /* BGE */
    ctrl[0] = ctrl[0] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[0] < NCONTEXT);
    
    ASSUME(ctrl[0] >= IREG(0,0));
    ASSUME(ctrl[0] >= IREG(0,1));
    if (REGP(0,0) >= REGP(0,1))
        goto p0label0;
    
    /* assign */
    // Guess
    IREG(0,3) = get_rng(0,NCONTEXT-1);
    CREG(0,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,3)] == 0);
    ASSUME(IREG(0,3) >= IREG(0,5));
    ASSUME(active[CREG(0,3)] == 0);
    ASSUME(CREG(0,3) >= max(ctrl[0],IREG(0,3)));
    ASSUME(CREG(0,3) >= CREG(0,5));
    // Update
    REGP(0,3) = REGP(0,5);
    
p0label0:
    /* assign */
    // Guess
    IREG(0,4) = get_rng(0,NCONTEXT-1);
    CREG(0,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,4)] == 0);
    ASSUME(IREG(0,4) >= IREG(0,4));
    ASSUME(active[CREG(0,4)] == 0);
    ASSUME(CREG(0,4) >= max(ctrl[0],IREG(0,4)));
    ASSUME(CREG(0,4) >= CREG(0,4));
    // Update
    REGP(0,4) = (REGP(0,4) + 1);
    
    /* assign */
    // Guess
    IREG(0,0) = get_rng(0,NCONTEXT-1);
    CREG(0,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,0)] == 0);
    ASSUME(IREG(0,0) >= IREG(0,4));
    ASSUME(active[CREG(0,0)] == 0);
    ASSUME(CREG(0,0) >= max(ctrl[0],IREG(0,0)));
    ASSUME(CREG(0,0) >= CREG(0,4));
    // Update
    REGP(0,0) = REGP(0,4);
    
    /* assign */
    // Guess
    IREG(0,1) = get_rng(0,NCONTEXT-1);
    CREG(0,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,1)] == 0);
    ASSUME(active[CREG(0,1)] == 0);
    ASSUME(CREG(0,1) >= max(ctrl[0],IREG(0,1)));
    // Update
    REGP(0,1) = 6;
    
    /* BNE */
    ctrl[0] = ctrl[0] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[0] < NCONTEXT);
    
    ASSUME(ctrl[0] >= IREG(0,0));
    ASSUME(ctrl[0] >= IREG(0,1));
    if (REGP(0,0) != REGP(0,1))
        goto p0findmax;
    
    /* assign */
    // Guess
    IREG(0,3) = get_rng(0,NCONTEXT-1);
    CREG(0,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,3)] == 0);
    ASSUME(IREG(0,3) >= IREG(0,3));
    ASSUME(active[CREG(0,3)] == 0);
    ASSUME(CREG(0,3) >= max(ctrl[0],IREG(0,3)));
    ASSUME(CREG(0,3) >= CREG(0,3));
    // Update
    REGP(0,3) = (REGP(0,3) + 1);
    
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
    IREG(0,4) = get_rng(0,NCONTEXT-1);
    CREG(0,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,4)] == 0);
    ASSUME(active[CREG(0,4)] == 0);
    ASSUME(CREG(0,4) >= max(ctrl[0],IREG(0,4)));
    // Update
    REGP(0,4) = 3;
    
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
    IREG(0,7) = get_rng(0,NCONTEXT-1);
    CREG(0,7) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,7)] == 0);
    ASSUME(IREG(0,7) >= IREG(0,3));
    ASSUME(active[CREG(0,7)] == 0);
    ASSUME(CREG(0,7) >= max(ctrl[0],IREG(0,7)));
    ASSUME(CREG(0,7) >= CREG(0,3));
    // Update
    REGP(0,7) = REGP(0,3);
    
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
    IREG(0,3) = get_rng(0,NCONTEXT-1);
    CREG(0,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,3)] == 0);
    ASSUME(active[CREG(0,3)] == 0);
    ASSUME(CREG(0,3) >= max(ctrl[0],IREG(0,3)));
    // Update
    REGP(0,3) = 0;
    
    /* assign */
    // Guess
    IREG(0,4) = get_rng(0,NCONTEXT-1);
    CREG(0,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,4)] == 0);
    ASSUME(active[CREG(0,4)] == 0);
    ASSUME(CREG(0,4) >= max(ctrl[0],IREG(0,4)));
    // Update
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
    IREG(0,4) = get_rng(0,NCONTEXT-1);
    CREG(0,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,4)] == 0);
    ASSUME(active[CREG(0,4)] == 0);
    ASSUME(CREG(0,4) >= max(ctrl[0],IREG(0,4)));
    // Update
    REGP(0,4) = 0;
    
p0waitenter:
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
    IREG(0,0) = get_rng(0,NCONTEXT-1);
    CREG(0,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,0)] == 0);
    ASSUME(IREG(0,0) >= IREG(0,3));
    ASSUME(active[CREG(0,0)] == 0);
    ASSUME(CREG(0,0) >= max(ctrl[0],IREG(0,0)));
    ASSUME(CREG(0,0) >= CREG(0,3));
    // Update
    REGP(0,0) = REGP(0,3);
    
    /* assign */
    // Guess
    IREG(0,1) = get_rng(0,NCONTEXT-1);
    CREG(0,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,1)] == 0);
    ASSUME(active[CREG(0,1)] == 0);
    ASSUME(CREG(0,1) >= max(ctrl[0],IREG(0,1)));
    // Update
    REGP(0,1) = 1;
    
    /* BEQ */
    ctrl[0] = ctrl[0] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[0] < NCONTEXT);
    
    ASSUME(ctrl[0] >= IREG(0,0));
    ASSUME(ctrl[0] >= IREG(0,1));
    if (REGP(0,0) == REGP(0,1))
        goto p0waitenter;
    
    /* assign */
    // Guess
    IREG(0,4) = get_rng(0,NCONTEXT-1);
    CREG(0,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,4)] == 0);
    ASSUME(IREG(0,4) >= IREG(0,4));
    ASSUME(active[CREG(0,4)] == 0);
    ASSUME(CREG(0,4) >= max(ctrl[0],IREG(0,4)));
    ASSUME(CREG(0,4) >= CREG(0,4));
    // Update
    REGP(0,4) = (REGP(0,4) + 1);
    
    /* assign */
    // Guess
    IREG(0,0) = get_rng(0,NCONTEXT-1);
    CREG(0,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,0)] == 0);
    ASSUME(IREG(0,0) >= IREG(0,4));
    ASSUME(active[CREG(0,0)] == 0);
    ASSUME(CREG(0,0) >= max(ctrl[0],IREG(0,0)));
    ASSUME(CREG(0,0) >= CREG(0,4));
    // Update
    REGP(0,0) = REGP(0,4);
    
    /* assign */
    // Guess
    IREG(0,1) = get_rng(0,NCONTEXT-1);
    CREG(0,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,1)] == 0);
    ASSUME(active[CREG(0,1)] == 0);
    ASSUME(CREG(0,1) >= max(ctrl[0],IREG(0,1)));
    // Update
    REGP(0,1) = 3;
    
    /* BNE */
    ctrl[0] = ctrl[0] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[0] < NCONTEXT);
    
    ASSUME(ctrl[0] >= IREG(0,0));
    ASSUME(ctrl[0] >= IREG(0,1));
    if (REGP(0,0) != REGP(0,1))
        goto p0waitenter;
    
    /* assign */
    // Guess
    IREG(0,3) = get_rng(0,NCONTEXT-1);
    CREG(0,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,3)] == 0);
    ASSUME(active[CREG(0,3)] == 0);
    ASSUME(CREG(0,3) >= max(ctrl[0],IREG(0,3)));
    // Update
    REGP(0,3) = 3;
    
    /* assign */
    // Guess
    IREG(0,4) = get_rng(0,NCONTEXT-1);
    CREG(0,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,4)] == 0);
    ASSUME(active[CREG(0,4)] == 0);
    ASSUME(CREG(0,4) >= max(ctrl[0],IREG(0,4)));
    // Update
    REGP(0,4) = 3;
    
p0waitfinish:
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
    IREG(0,5) = IR(0,REGP(0,4));
    CREG(0,5) = CR(0,REGP(0,4));
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
        REGP(0,5) = NU(0,REGP(0,4));
    } else {
        REGP(0,5) = MU(REGP(0,4),IR(0,REGP(0,4)));
    }
    
    /* CBZ */
    ctrl[0] = ctrl[0] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[0] < NCONTEXT);
    
    ASSUME(ctrl[0] >= IREG(0,5));
    if (REGP(0,5) == 0)
        goto p0next;
    
    /* assign */
    // Guess
    IREG(0,0) = get_rng(0,NCONTEXT-1);
    CREG(0,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,0)] == 0);
    ASSUME(IREG(0,0) >= IREG(0,5));
    ASSUME(active[CREG(0,0)] == 0);
    ASSUME(CREG(0,0) >= max(ctrl[0],IREG(0,0)));
    ASSUME(CREG(0,0) >= CREG(0,5));
    // Update
    REGP(0,0) = REGP(0,5);
    
    /* assign */
    // Guess
    IREG(0,1) = get_rng(0,NCONTEXT-1);
    CREG(0,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,1)] == 0);
    ASSUME(IREG(0,1) >= IREG(0,7));
    ASSUME(active[CREG(0,1)] == 0);
    ASSUME(CREG(0,1) >= max(ctrl[0],IREG(0,1)));
    ASSUME(CREG(0,1) >= CREG(0,7));
    // Update
    REGP(0,1) = REGP(0,7);
    
    /* BGT */
    ctrl[0] = ctrl[0] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[0] < NCONTEXT);
    
    ASSUME(ctrl[0] >= IREG(0,0));
    ASSUME(ctrl[0] >= IREG(0,1));
    if (REGP(0,0) > REGP(0,1))
        goto p0next;
    
    /* assign */
    // Guess
    IREG(0,0) = get_rng(0,NCONTEXT-1);
    CREG(0,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,0)] == 0);
    ASSUME(IREG(0,0) >= IREG(0,4));
    ASSUME(active[CREG(0,0)] == 0);
    ASSUME(CREG(0,0) >= max(ctrl[0],IREG(0,0)));
    ASSUME(CREG(0,0) >= CREG(0,4));
    // Update
    REGP(0,0) = REGP(0,4);
    
    /* assign */
    // Guess
    IREG(0,1) = get_rng(0,NCONTEXT-1);
    CREG(0,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,1)] == 0);
    ASSUME(IREG(0,1) >= IREG(0,3));
    ASSUME(active[CREG(0,1)] == 0);
    ASSUME(CREG(0,1) >= max(ctrl[0],IREG(0,1)));
    ASSUME(CREG(0,1) >= CREG(0,3));
    // Update
    REGP(0,1) = REGP(0,3);
    
p0next:
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
    IREG(0,4) = get_rng(0,NCONTEXT-1);
    CREG(0,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,4)] == 0);
    ASSUME(IREG(0,4) >= IREG(0,4));
    ASSUME(active[CREG(0,4)] == 0);
    ASSUME(CREG(0,4) >= max(ctrl[0],IREG(0,4)));
    ASSUME(CREG(0,4) >= CREG(0,4));
    // Update
    REGP(0,4) = (REGP(0,4) + 1);
    
    /* assign */
    // Guess
    IREG(0,0) = get_rng(0,NCONTEXT-1);
    CREG(0,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,0)] == 0);
    ASSUME(IREG(0,0) >= IREG(0,4));
    ASSUME(active[CREG(0,0)] == 0);
    ASSUME(CREG(0,0) >= max(ctrl[0],IREG(0,0)));
    ASSUME(CREG(0,0) >= CREG(0,4));
    // Update
    REGP(0,0) = REGP(0,4);
    
    /* assign */
    // Guess
    IREG(0,1) = get_rng(0,NCONTEXT-1);
    CREG(0,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,1)] == 0);
    ASSUME(active[CREG(0,1)] == 0);
    ASSUME(CREG(0,1) >= max(ctrl[0],IREG(0,1)));
    // Update
    REGP(0,1) = 6;
    
    /* BNE */
    ctrl[0] = ctrl[0] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[0] < NCONTEXT);
    
    ASSUME(ctrl[0] >= IREG(0,0));
    ASSUME(ctrl[0] >= IREG(0,1));
    if (REGP(0,0) != REGP(0,1))
        goto p0waitfinish;
    
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
    IREG(0,3) = get_rng(0,NCONTEXT-1);
    CREG(0,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,3)] == 0);
    ASSUME(active[CREG(0,3)] == 0);
    ASSUME(CREG(0,3) >= max(ctrl[0],IREG(0,3)));
    // Update
    REGP(0,3) = 6;
    
    /* LD */
    // Guess
    IR(0,REGP(0,3)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(0,REGP(0,3));
    CR(0,REGP(0,3)) = get_rng(0,NCONTEXT-1);
    IREG(0,4) = IR(0,REGP(0,3));
    CREG(0,4) = CR(0,REGP(0,3));
    // Check
    ASSUME(active[IR(0,REGP(0,3))] == 0);
    ASSUME(IR(0,REGP(0,3)) >= IW(0,REGP(0,3)));
    ASSUME(IR(0,REGP(0,3)) >= IREG(0,3));
    ASSUME(IR(0,REGP(0,3)) >= max(cDY[0],cISB[0]));
    ASSUME(IR(0,REGP(0,3)) >= cDL[0]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(0,REGP(0,3)) >= IL(0,rdp));
    }
    ASSUME(CR(0,REGP(0,3)) >= IR(0, REGP(0,3)));
    ASSUME(active[CR(0,REGP(0,3))] == 0);
    ASSUME(CR(0,REGP(0,3)) >= max(IREG(0,3),ctrl[0]));
    ASSUME(CR(0,REGP(0,3)) >= max(old_cR,CW(0,REGP(0,3))));
    // Update
    iAddr[0] = max(iAddr[0], IREG(0,3));
    if (IR(0,REGP(0,3)) < CW(0,REGP(0,3))) {
        REGP(0,4) = NU(0,REGP(0,3));
    } else {
        REGP(0,4) = MU(REGP(0,3),IR(0,REGP(0,3)));
    }
    
    /* assign */
    // Guess
    IREG(0,4) = get_rng(0,NCONTEXT-1);
    CREG(0,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,4)] == 0);
    ASSUME(IREG(0,4) >= IREG(0,4));
    ASSUME(active[CREG(0,4)] == 0);
    ASSUME(CREG(0,4) >= max(ctrl[0],IREG(0,4)));
    ASSUME(CREG(0,4) >= CREG(0,4));
    // Update
    REGP(0,4) = (REGP(0,4) + 1);
    
    /* ST */
    // Guess
    IW(0,REGP(0,3)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(0,REGP(0,3));
    CW(0,REGP(0,3)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(0,REGP(0,3))] == 0);
    ASSUME(IW(0,REGP(0,3)) >= max(IREG(0,4),IREG(0,3)));
    ASSUME(IW(0,REGP(0,3)) >= max(cDY[0],cISB[0]));
    ASSUME(IW(0,REGP(0,3)) >= max(cDS[0],cDL[0]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(0,REGP(0,3)) >= CL(0,r));
    }
    ASSUME(CW(0,REGP(0,3)) >= IW(0, REGP(0,3)));
    ASSUME(active[CW(0,REGP(0,3))] == 0);
    ASSUME(CW(0,REGP(0,3)) >= max(CREG(0,4),IREG(0,3)));
    ASSUME(CW(0,REGP(0,3)) >= max(old_cW,CR(0,REGP(0,3))));
    ASSUME(CW(0,REGP(0,3)) >= ctrl[0]);
    ASSUME(CW(0,REGP(0,3)) >= iAddr[0]);
    // Update
    iAddr[0] = max(iAddr[0], IREG(0,3));
    MU(REGP(0,3),CW(0,REGP(0,3))) = REGP(0,4);
    NU(0,REGP(0,3)) = REGP(0,4);
    DELTA(REGP(0,3),CW(0,REGP(0,3))) = -1;
    
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
    IREG(0,3) = get_rng(0,NCONTEXT-1);
    CREG(0,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,3)] == 0);
    ASSUME(active[CREG(0,3)] == 0);
    ASSUME(CREG(0,3) >= max(ctrl[0],IREG(0,3)));
    // Update
    REGP(0,3) = 0;
    
    /* assign */
    // Guess
    IREG(0,4) = get_rng(0,NCONTEXT-1);
    CREG(0,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(0,4)] == 0);
    ASSUME(active[CREG(0,4)] == 0);
    ASSUME(CREG(0,4) >= max(ctrl[0],IREG(0,4)));
    // Update
    REGP(0,4) = 3;
    
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
    IREG(1,3) = get_rng(0,NCONTEXT-1);
    CREG(1,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,3)] == 1);
    ASSUME(active[CREG(1,3)] == 1);
    ASSUME(CREG(1,3) >= max(ctrl[1],IREG(1,3)));
    // Update
    REGP(1,3) = 1;
    
    /* assign */
    // Guess
    IREG(1,4) = get_rng(0,NCONTEXT-1);
    CREG(1,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,4)] == 1);
    ASSUME(active[CREG(1,4)] == 1);
    ASSUME(CREG(1,4) >= max(ctrl[1],IREG(1,4)));
    // Update
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
    IREG(1,3) = get_rng(0,NCONTEXT-1);
    CREG(1,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,3)] == 1);
    ASSUME(active[CREG(1,3)] == 1);
    ASSUME(CREG(1,3) >= max(ctrl[1],IREG(1,3)));
    // Update
    REGP(1,3) = 0;
    
    /* assign */
    // Guess
    IREG(1,4) = get_rng(0,NCONTEXT-1);
    CREG(1,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,4)] == 1);
    ASSUME(active[CREG(1,4)] == 1);
    ASSUME(CREG(1,4) >= max(ctrl[1],IREG(1,4)));
    // Update
    REGP(1,4) = 3;
    
p1findmax:
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
    IREG(1,5) = IR(1,REGP(1,4));
    CREG(1,5) = CR(1,REGP(1,4));
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
        REGP(1,5) = NU(1,REGP(1,4));
    } else {
        REGP(1,5) = MU(REGP(1,4),IR(1,REGP(1,4)));
    }
    
    /* assign */
    // Guess
    IREG(1,0) = get_rng(0,NCONTEXT-1);
    CREG(1,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,0)] == 1);
    ASSUME(IREG(1,0) >= IREG(1,3));
    ASSUME(active[CREG(1,0)] == 1);
    ASSUME(CREG(1,0) >= max(ctrl[1],IREG(1,0)));
    ASSUME(CREG(1,0) >= CREG(1,3));
    // Update
    REGP(1,0) = REGP(1,3);
    
    /* assign */
    // Guess
    IREG(1,1) = get_rng(0,NCONTEXT-1);
    CREG(1,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,1)] == 1);
    ASSUME(IREG(1,1) >= IREG(1,5));
    ASSUME(active[CREG(1,1)] == 1);
    ASSUME(CREG(1,1) >= max(ctrl[1],IREG(1,1)));
    ASSUME(CREG(1,1) >= CREG(1,5));
    // Update
    REGP(1,1) = REGP(1,5);
    
    /* BGE */
    ctrl[1] = ctrl[1] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[1] < NCONTEXT);
    
    ASSUME(ctrl[1] >= IREG(1,0));
    ASSUME(ctrl[1] >= IREG(1,1));
    if (REGP(1,0) >= REGP(1,1))
        goto p1label0;
    
    /* assign */
    // Guess
    IREG(1,3) = get_rng(0,NCONTEXT-1);
    CREG(1,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,3)] == 1);
    ASSUME(IREG(1,3) >= IREG(1,5));
    ASSUME(active[CREG(1,3)] == 1);
    ASSUME(CREG(1,3) >= max(ctrl[1],IREG(1,3)));
    ASSUME(CREG(1,3) >= CREG(1,5));
    // Update
    REGP(1,3) = REGP(1,5);
    
p1label0:
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
    IREG(1,4) = get_rng(0,NCONTEXT-1);
    CREG(1,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,4)] == 1);
    ASSUME(IREG(1,4) >= IREG(1,4));
    ASSUME(active[CREG(1,4)] == 1);
    ASSUME(CREG(1,4) >= max(ctrl[1],IREG(1,4)));
    ASSUME(CREG(1,4) >= CREG(1,4));
    // Update
    REGP(1,4) = (REGP(1,4) + 1);
    
    /* assign */
    // Guess
    IREG(1,0) = get_rng(0,NCONTEXT-1);
    CREG(1,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,0)] == 1);
    ASSUME(IREG(1,0) >= IREG(1,4));
    ASSUME(active[CREG(1,0)] == 1);
    ASSUME(CREG(1,0) >= max(ctrl[1],IREG(1,0)));
    ASSUME(CREG(1,0) >= CREG(1,4));
    // Update
    REGP(1,0) = REGP(1,4);
    
    /* assign */
    // Guess
    IREG(1,1) = get_rng(0,NCONTEXT-1);
    CREG(1,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,1)] == 1);
    ASSUME(active[CREG(1,1)] == 1);
    ASSUME(CREG(1,1) >= max(ctrl[1],IREG(1,1)));
    // Update
    REGP(1,1) = 6;
    
    /* BNE */
    ctrl[1] = ctrl[1] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[1] < NCONTEXT);
    
    ASSUME(ctrl[1] >= IREG(1,0));
    ASSUME(ctrl[1] >= IREG(1,1));
    if (REGP(1,0) != REGP(1,1))
        goto p1findmax;
    
    /* assign */
    // Guess
    IREG(1,3) = get_rng(0,NCONTEXT-1);
    CREG(1,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,3)] == 1);
    ASSUME(IREG(1,3) >= IREG(1,3));
    ASSUME(active[CREG(1,3)] == 1);
    ASSUME(CREG(1,3) >= max(ctrl[1],IREG(1,3)));
    ASSUME(CREG(1,3) >= CREG(1,3));
    // Update
    REGP(1,3) = (REGP(1,3) + 1);
    
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
    IREG(1,4) = get_rng(0,NCONTEXT-1);
    CREG(1,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,4)] == 1);
    ASSUME(active[CREG(1,4)] == 1);
    ASSUME(CREG(1,4) >= max(ctrl[1],IREG(1,4)));
    // Update
    REGP(1,4) = 4;
    
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
    IREG(1,7) = get_rng(0,NCONTEXT-1);
    CREG(1,7) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,7)] == 1);
    ASSUME(IREG(1,7) >= IREG(1,3));
    ASSUME(active[CREG(1,7)] == 1);
    ASSUME(CREG(1,7) >= max(ctrl[1],IREG(1,7)));
    ASSUME(CREG(1,7) >= CREG(1,3));
    // Update
    REGP(1,7) = REGP(1,3);
    
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
    IREG(1,3) = get_rng(0,NCONTEXT-1);
    CREG(1,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,3)] == 1);
    ASSUME(active[CREG(1,3)] == 1);
    ASSUME(CREG(1,3) >= max(ctrl[1],IREG(1,3)));
    // Update
    REGP(1,3) = 0;
    
    /* assign */
    // Guess
    IREG(1,4) = get_rng(0,NCONTEXT-1);
    CREG(1,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,4)] == 1);
    ASSUME(active[CREG(1,4)] == 1);
    ASSUME(CREG(1,4) >= max(ctrl[1],IREG(1,4)));
    // Update
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
    IREG(1,4) = get_rng(0,NCONTEXT-1);
    CREG(1,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,4)] == 1);
    ASSUME(active[CREG(1,4)] == 1);
    ASSUME(CREG(1,4) >= max(ctrl[1],IREG(1,4)));
    // Update
    REGP(1,4) = 0;
    
p1waitenter:
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
    IREG(1,0) = get_rng(0,NCONTEXT-1);
    CREG(1,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,0)] == 1);
    ASSUME(IREG(1,0) >= IREG(1,3));
    ASSUME(active[CREG(1,0)] == 1);
    ASSUME(CREG(1,0) >= max(ctrl[1],IREG(1,0)));
    ASSUME(CREG(1,0) >= CREG(1,3));
    // Update
    REGP(1,0) = REGP(1,3);
    
    /* assign */
    // Guess
    IREG(1,1) = get_rng(0,NCONTEXT-1);
    CREG(1,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,1)] == 1);
    ASSUME(active[CREG(1,1)] == 1);
    ASSUME(CREG(1,1) >= max(ctrl[1],IREG(1,1)));
    // Update
    REGP(1,1) = 1;
    
    /* BEQ */
    ctrl[1] = ctrl[1] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[1] < NCONTEXT);
    
    ASSUME(ctrl[1] >= IREG(1,0));
    ASSUME(ctrl[1] >= IREG(1,1));
    if (REGP(1,0) == REGP(1,1))
        goto p1waitenter;
    
    /* assign */
    // Guess
    IREG(1,4) = get_rng(0,NCONTEXT-1);
    CREG(1,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,4)] == 1);
    ASSUME(IREG(1,4) >= IREG(1,4));
    ASSUME(active[CREG(1,4)] == 1);
    ASSUME(CREG(1,4) >= max(ctrl[1],IREG(1,4)));
    ASSUME(CREG(1,4) >= CREG(1,4));
    // Update
    REGP(1,4) = (REGP(1,4) + 1);
    
    /* assign */
    // Guess
    IREG(1,0) = get_rng(0,NCONTEXT-1);
    CREG(1,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,0)] == 1);
    ASSUME(IREG(1,0) >= IREG(1,4));
    ASSUME(active[CREG(1,0)] == 1);
    ASSUME(CREG(1,0) >= max(ctrl[1],IREG(1,0)));
    ASSUME(CREG(1,0) >= CREG(1,4));
    // Update
    REGP(1,0) = REGP(1,4);
    
    /* assign */
    // Guess
    IREG(1,1) = get_rng(0,NCONTEXT-1);
    CREG(1,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,1)] == 1);
    ASSUME(active[CREG(1,1)] == 1);
    ASSUME(CREG(1,1) >= max(ctrl[1],IREG(1,1)));
    // Update
    REGP(1,1) = 3;
    
    /* BNE */
    ctrl[1] = ctrl[1] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[1] < NCONTEXT);
    
    ASSUME(ctrl[1] >= IREG(1,0));
    ASSUME(ctrl[1] >= IREG(1,1));
    if (REGP(1,0) != REGP(1,1))
        goto p1waitenter;
    
    /* assign */
    // Guess
    IREG(1,3) = get_rng(0,NCONTEXT-1);
    CREG(1,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,3)] == 1);
    ASSUME(active[CREG(1,3)] == 1);
    ASSUME(CREG(1,3) >= max(ctrl[1],IREG(1,3)));
    // Update
    REGP(1,3) = 4;
    
    /* assign */
    // Guess
    IREG(1,4) = get_rng(0,NCONTEXT-1);
    CREG(1,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,4)] == 1);
    ASSUME(active[CREG(1,4)] == 1);
    ASSUME(CREG(1,4) >= max(ctrl[1],IREG(1,4)));
    // Update
    REGP(1,4) = 3;
    
p1waitfinish:
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
    IREG(1,5) = IR(1,REGP(1,4));
    CREG(1,5) = CR(1,REGP(1,4));
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
        REGP(1,5) = NU(1,REGP(1,4));
    } else {
        REGP(1,5) = MU(REGP(1,4),IR(1,REGP(1,4)));
    }
    
    /* CBZ */
    ctrl[1] = ctrl[1] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[1] < NCONTEXT);
    
    ASSUME(ctrl[1] >= IREG(1,5));
    if (REGP(1,5) == 0)
        goto p1next;
    
    /* assign */
    // Guess
    IREG(1,0) = get_rng(0,NCONTEXT-1);
    CREG(1,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,0)] == 1);
    ASSUME(IREG(1,0) >= IREG(1,5));
    ASSUME(active[CREG(1,0)] == 1);
    ASSUME(CREG(1,0) >= max(ctrl[1],IREG(1,0)));
    ASSUME(CREG(1,0) >= CREG(1,5));
    // Update
    REGP(1,0) = REGP(1,5);
    
    /* assign */
    // Guess
    IREG(1,1) = get_rng(0,NCONTEXT-1);
    CREG(1,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,1)] == 1);
    ASSUME(IREG(1,1) >= IREG(1,7));
    ASSUME(active[CREG(1,1)] == 1);
    ASSUME(CREG(1,1) >= max(ctrl[1],IREG(1,1)));
    ASSUME(CREG(1,1) >= CREG(1,7));
    // Update
    REGP(1,1) = REGP(1,7);
    
    /* BGT */
    ctrl[1] = ctrl[1] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[1] < NCONTEXT);
    
    ASSUME(ctrl[1] >= IREG(1,0));
    ASSUME(ctrl[1] >= IREG(1,1));
    if (REGP(1,0) > REGP(1,1))
        goto p1next;
    
    /* assign */
    // Guess
    IREG(1,0) = get_rng(0,NCONTEXT-1);
    CREG(1,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,0)] == 1);
    ASSUME(IREG(1,0) >= IREG(1,4));
    ASSUME(active[CREG(1,0)] == 1);
    ASSUME(CREG(1,0) >= max(ctrl[1],IREG(1,0)));
    ASSUME(CREG(1,0) >= CREG(1,4));
    // Update
    REGP(1,0) = REGP(1,4);
    
    /* assign */
    // Guess
    IREG(1,1) = get_rng(0,NCONTEXT-1);
    CREG(1,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,1)] == 1);
    ASSUME(IREG(1,1) >= IREG(1,3));
    ASSUME(active[CREG(1,1)] == 1);
    ASSUME(CREG(1,1) >= max(ctrl[1],IREG(1,1)));
    ASSUME(CREG(1,1) >= CREG(1,3));
    // Update
    REGP(1,1) = REGP(1,3);
    
p1next:
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
    IREG(1,4) = get_rng(0,NCONTEXT-1);
    CREG(1,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,4)] == 1);
    ASSUME(IREG(1,4) >= IREG(1,4));
    ASSUME(active[CREG(1,4)] == 1);
    ASSUME(CREG(1,4) >= max(ctrl[1],IREG(1,4)));
    ASSUME(CREG(1,4) >= CREG(1,4));
    // Update
    REGP(1,4) = (REGP(1,4) + 1);
    
    /* assign */
    // Guess
    IREG(1,0) = get_rng(0,NCONTEXT-1);
    CREG(1,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,0)] == 1);
    ASSUME(IREG(1,0) >= IREG(1,4));
    ASSUME(active[CREG(1,0)] == 1);
    ASSUME(CREG(1,0) >= max(ctrl[1],IREG(1,0)));
    ASSUME(CREG(1,0) >= CREG(1,4));
    // Update
    REGP(1,0) = REGP(1,4);
    
    /* assign */
    // Guess
    IREG(1,1) = get_rng(0,NCONTEXT-1);
    CREG(1,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,1)] == 1);
    ASSUME(active[CREG(1,1)] == 1);
    ASSUME(CREG(1,1) >= max(ctrl[1],IREG(1,1)));
    // Update
    REGP(1,1) = 6;
    
    /* BNE */
    ctrl[1] = ctrl[1] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[1] < NCONTEXT);
    
    ASSUME(ctrl[1] >= IREG(1,0));
    ASSUME(ctrl[1] >= IREG(1,1));
    if (REGP(1,0) != REGP(1,1))
        goto p1waitfinish;
    
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
    IREG(1,3) = get_rng(0,NCONTEXT-1);
    CREG(1,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,3)] == 1);
    ASSUME(active[CREG(1,3)] == 1);
    ASSUME(CREG(1,3) >= max(ctrl[1],IREG(1,3)));
    // Update
    REGP(1,3) = 6;
    
    /* LD */
    // Guess
    IR(1,REGP(1,3)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(1,REGP(1,3));
    CR(1,REGP(1,3)) = get_rng(0,NCONTEXT-1);
    IREG(1,4) = IR(1,REGP(1,3));
    CREG(1,4) = CR(1,REGP(1,3));
    // Check
    ASSUME(active[IR(1,REGP(1,3))] == 1);
    ASSUME(IR(1,REGP(1,3)) >= IW(1,REGP(1,3)));
    ASSUME(IR(1,REGP(1,3)) >= IREG(1,3));
    ASSUME(IR(1,REGP(1,3)) >= max(cDY[1],cISB[1]));
    ASSUME(IR(1,REGP(1,3)) >= cDL[1]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(1,REGP(1,3)) >= IL(1,rdp));
    }
    ASSUME(CR(1,REGP(1,3)) >= IR(1, REGP(1,3)));
    ASSUME(active[CR(1,REGP(1,3))] == 1);
    ASSUME(CR(1,REGP(1,3)) >= max(IREG(1,3),ctrl[1]));
    ASSUME(CR(1,REGP(1,3)) >= max(old_cR,CW(1,REGP(1,3))));
    // Update
    iAddr[1] = max(iAddr[1], IREG(1,3));
    if (IR(1,REGP(1,3)) < CW(1,REGP(1,3))) {
        REGP(1,4) = NU(1,REGP(1,3));
    } else {
        REGP(1,4) = MU(REGP(1,3),IR(1,REGP(1,3)));
    }
    
    /* assign */
    // Guess
    IREG(1,4) = get_rng(0,NCONTEXT-1);
    CREG(1,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,4)] == 1);
    ASSUME(IREG(1,4) >= IREG(1,4));
    ASSUME(active[CREG(1,4)] == 1);
    ASSUME(CREG(1,4) >= max(ctrl[1],IREG(1,4)));
    ASSUME(CREG(1,4) >= CREG(1,4));
    // Update
    REGP(1,4) = (REGP(1,4) + 1);
    
    /* ST */
    // Guess
    IW(1,REGP(1,3)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(1,REGP(1,3));
    CW(1,REGP(1,3)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(1,REGP(1,3))] == 1);
    ASSUME(IW(1,REGP(1,3)) >= max(IREG(1,4),IREG(1,3)));
    ASSUME(IW(1,REGP(1,3)) >= max(cDY[1],cISB[1]));
    ASSUME(IW(1,REGP(1,3)) >= max(cDS[1],cDL[1]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(1,REGP(1,3)) >= CL(1,r));
    }
    ASSUME(CW(1,REGP(1,3)) >= IW(1, REGP(1,3)));
    ASSUME(active[CW(1,REGP(1,3))] == 1);
    ASSUME(CW(1,REGP(1,3)) >= max(CREG(1,4),IREG(1,3)));
    ASSUME(CW(1,REGP(1,3)) >= max(old_cW,CR(1,REGP(1,3))));
    ASSUME(CW(1,REGP(1,3)) >= ctrl[1]);
    ASSUME(CW(1,REGP(1,3)) >= iAddr[1]);
    // Update
    iAddr[1] = max(iAddr[1], IREG(1,3));
    MU(REGP(1,3),CW(1,REGP(1,3))) = REGP(1,4);
    NU(1,REGP(1,3)) = REGP(1,4);
    DELTA(REGP(1,3),CW(1,REGP(1,3))) = -1;
    
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
    IREG(1,3) = get_rng(0,NCONTEXT-1);
    CREG(1,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,3)] == 1);
    ASSUME(active[CREG(1,3)] == 1);
    ASSUME(CREG(1,3) >= max(ctrl[1],IREG(1,3)));
    // Update
    REGP(1,3) = 0;
    
    /* assign */
    // Guess
    IREG(1,4) = get_rng(0,NCONTEXT-1);
    CREG(1,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(1,4)] == 1);
    ASSUME(active[CREG(1,4)] == 1);
    ASSUME(CREG(1,4) >= max(ctrl[1],IREG(1,4)));
    // Update
    REGP(1,4) = 4;
    
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
    
    // Process 2 BEGIN
    /* dmb.sy */
    // Guess
    old_cDY = cDY[2];
    cDY[2] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[2] >= old_cDY);
    ASSUME(cDY[2] >= max(cISB[2],cDL[2]));
    ASSUME(cDY[2] >= max(cDS[2],ctrl[2]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[2] >= CW(2,x));
        ASSUME(cDY[2] >= CR(2,x));
    }
    
    /* assign */
    // Guess
    IREG(2,3) = get_rng(0,NCONTEXT-1);
    CREG(2,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,3)] == 2);
    ASSUME(active[CREG(2,3)] == 2);
    ASSUME(CREG(2,3) >= max(ctrl[2],IREG(2,3)));
    // Update
    REGP(2,3) = 1;
    
    /* assign */
    // Guess
    IREG(2,4) = get_rng(0,NCONTEXT-1);
    CREG(2,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,4)] == 2);
    ASSUME(active[CREG(2,4)] == 2);
    ASSUME(CREG(2,4) >= max(ctrl[2],IREG(2,4)));
    // Update
    REGP(2,4) = 2;
    
    /* ST */
    // Guess
    IW(2,REGP(2,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(2,REGP(2,4));
    CW(2,REGP(2,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(2,REGP(2,4))] == 2);
    ASSUME(IW(2,REGP(2,4)) >= max(IREG(2,3),IREG(2,4)));
    ASSUME(IW(2,REGP(2,4)) >= max(cDY[2],cISB[2]));
    ASSUME(IW(2,REGP(2,4)) >= max(cDS[2],cDL[2]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(2,REGP(2,4)) >= CL(2,r));
    }
    ASSUME(CW(2,REGP(2,4)) >= IW(2, REGP(2,4)));
    ASSUME(active[CW(2,REGP(2,4))] == 2);
    ASSUME(CW(2,REGP(2,4)) >= max(CREG(2,3),IREG(2,4)));
    ASSUME(CW(2,REGP(2,4)) >= max(old_cW,CR(2,REGP(2,4))));
    ASSUME(CW(2,REGP(2,4)) >= ctrl[2]);
    ASSUME(CW(2,REGP(2,4)) >= iAddr[2]);
    // Update
    iAddr[2] = max(iAddr[2], IREG(2,4));
    MU(REGP(2,4),CW(2,REGP(2,4))) = REGP(2,3);
    NU(2,REGP(2,4)) = REGP(2,3);
    DELTA(REGP(2,4),CW(2,REGP(2,4))) = -1;
    
    /* assign */
    // Guess
    IREG(2,3) = get_rng(0,NCONTEXT-1);
    CREG(2,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,3)] == 2);
    ASSUME(active[CREG(2,3)] == 2);
    ASSUME(CREG(2,3) >= max(ctrl[2],IREG(2,3)));
    // Update
    REGP(2,3) = 0;
    
    /* assign */
    // Guess
    IREG(2,4) = get_rng(0,NCONTEXT-1);
    CREG(2,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,4)] == 2);
    ASSUME(active[CREG(2,4)] == 2);
    ASSUME(CREG(2,4) >= max(ctrl[2],IREG(2,4)));
    // Update
    REGP(2,4) = 3;
    
p2findmax:
    /* dmb.sy */
    // Guess
    old_cDY = cDY[2];
    cDY[2] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[2] >= old_cDY);
    ASSUME(cDY[2] >= max(cISB[2],cDL[2]));
    ASSUME(cDY[2] >= max(cDS[2],ctrl[2]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[2] >= CW(2,x));
        ASSUME(cDY[2] >= CR(2,x));
    }
    
    /* LD */
    // Guess
    IR(2,REGP(2,4)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(2,REGP(2,4));
    CR(2,REGP(2,4)) = get_rng(0,NCONTEXT-1);
    IREG(2,5) = IR(2,REGP(2,4));
    CREG(2,5) = CR(2,REGP(2,4));
    // Check
    ASSUME(active[IR(2,REGP(2,4))] == 2);
    ASSUME(IR(2,REGP(2,4)) >= IW(2,REGP(2,4)));
    ASSUME(IR(2,REGP(2,4)) >= IREG(2,4));
    ASSUME(IR(2,REGP(2,4)) >= max(cDY[2],cISB[2]));
    ASSUME(IR(2,REGP(2,4)) >= cDL[2]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(2,REGP(2,4)) >= IL(2,rdp));
    }
    ASSUME(CR(2,REGP(2,4)) >= IR(2, REGP(2,4)));
    ASSUME(active[CR(2,REGP(2,4))] == 2);
    ASSUME(CR(2,REGP(2,4)) >= max(IREG(2,4),ctrl[2]));
    ASSUME(CR(2,REGP(2,4)) >= max(old_cR,CW(2,REGP(2,4))));
    // Update
    iAddr[2] = max(iAddr[2], IREG(2,4));
    if (IR(2,REGP(2,4)) < CW(2,REGP(2,4))) {
        REGP(2,5) = NU(2,REGP(2,4));
    } else {
        REGP(2,5) = MU(REGP(2,4),IR(2,REGP(2,4)));
    }
    
    /* assign */
    // Guess
    IREG(2,0) = get_rng(0,NCONTEXT-1);
    CREG(2,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,0)] == 2);
    ASSUME(IREG(2,0) >= IREG(2,3));
    ASSUME(active[CREG(2,0)] == 2);
    ASSUME(CREG(2,0) >= max(ctrl[2],IREG(2,0)));
    ASSUME(CREG(2,0) >= CREG(2,3));
    // Update
    REGP(2,0) = REGP(2,3);
    
    /* assign */
    // Guess
    IREG(2,1) = get_rng(0,NCONTEXT-1);
    CREG(2,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,1)] == 2);
    ASSUME(IREG(2,1) >= IREG(2,5));
    ASSUME(active[CREG(2,1)] == 2);
    ASSUME(CREG(2,1) >= max(ctrl[2],IREG(2,1)));
    ASSUME(CREG(2,1) >= CREG(2,5));
    // Update
    REGP(2,1) = REGP(2,5);
    
    /* BGE */
    ctrl[2] = ctrl[2] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[2] < NCONTEXT);
    
    ASSUME(ctrl[2] >= IREG(2,0));
    ASSUME(ctrl[2] >= IREG(2,1));
    if (REGP(2,0) >= REGP(2,1))
        goto p2label0;
    
    /* assign */
    // Guess
    IREG(2,3) = get_rng(0,NCONTEXT-1);
    CREG(2,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,3)] == 2);
    ASSUME(IREG(2,3) >= IREG(2,5));
    ASSUME(active[CREG(2,3)] == 2);
    ASSUME(CREG(2,3) >= max(ctrl[2],IREG(2,3)));
    ASSUME(CREG(2,3) >= CREG(2,5));
    // Update
    REGP(2,3) = REGP(2,5);
    
p2label0:
    /* dmb.sy */
    // Guess
    old_cDY = cDY[2];
    cDY[2] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[2] >= old_cDY);
    ASSUME(cDY[2] >= max(cISB[2],cDL[2]));
    ASSUME(cDY[2] >= max(cDS[2],ctrl[2]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[2] >= CW(2,x));
        ASSUME(cDY[2] >= CR(2,x));
    }
    
    /* assign */
    // Guess
    IREG(2,4) = get_rng(0,NCONTEXT-1);
    CREG(2,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,4)] == 2);
    ASSUME(IREG(2,4) >= IREG(2,4));
    ASSUME(active[CREG(2,4)] == 2);
    ASSUME(CREG(2,4) >= max(ctrl[2],IREG(2,4)));
    ASSUME(CREG(2,4) >= CREG(2,4));
    // Update
    REGP(2,4) = (REGP(2,4) + 1);
    
    /* assign */
    // Guess
    IREG(2,0) = get_rng(0,NCONTEXT-1);
    CREG(2,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,0)] == 2);
    ASSUME(IREG(2,0) >= IREG(2,4));
    ASSUME(active[CREG(2,0)] == 2);
    ASSUME(CREG(2,0) >= max(ctrl[2],IREG(2,0)));
    ASSUME(CREG(2,0) >= CREG(2,4));
    // Update
    REGP(2,0) = REGP(2,4);
    
    /* assign */
    // Guess
    IREG(2,1) = get_rng(0,NCONTEXT-1);
    CREG(2,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,1)] == 2);
    ASSUME(active[CREG(2,1)] == 2);
    ASSUME(CREG(2,1) >= max(ctrl[2],IREG(2,1)));
    // Update
    REGP(2,1) = 6;
    
    /* BNE */
    ctrl[2] = ctrl[2] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[2] < NCONTEXT);
    
    ASSUME(ctrl[2] >= IREG(2,0));
    ASSUME(ctrl[2] >= IREG(2,1));
    if (REGP(2,0) != REGP(2,1))
        goto p2findmax;
    
    /* assign */
    // Guess
    IREG(2,3) = get_rng(0,NCONTEXT-1);
    CREG(2,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,3)] == 2);
    ASSUME(IREG(2,3) >= IREG(2,3));
    ASSUME(active[CREG(2,3)] == 2);
    ASSUME(CREG(2,3) >= max(ctrl[2],IREG(2,3)));
    ASSUME(CREG(2,3) >= CREG(2,3));
    // Update
    REGP(2,3) = (REGP(2,3) + 1);
    
    /* dmb.sy */
    // Guess
    old_cDY = cDY[2];
    cDY[2] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[2] >= old_cDY);
    ASSUME(cDY[2] >= max(cISB[2],cDL[2]));
    ASSUME(cDY[2] >= max(cDS[2],ctrl[2]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[2] >= CW(2,x));
        ASSUME(cDY[2] >= CR(2,x));
    }
    
    /* assign */
    // Guess
    IREG(2,4) = get_rng(0,NCONTEXT-1);
    CREG(2,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,4)] == 2);
    ASSUME(active[CREG(2,4)] == 2);
    ASSUME(CREG(2,4) >= max(ctrl[2],IREG(2,4)));
    // Update
    REGP(2,4) = 5;
    
    /* ST */
    // Guess
    IW(2,REGP(2,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(2,REGP(2,4));
    CW(2,REGP(2,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(2,REGP(2,4))] == 2);
    ASSUME(IW(2,REGP(2,4)) >= max(IREG(2,3),IREG(2,4)));
    ASSUME(IW(2,REGP(2,4)) >= max(cDY[2],cISB[2]));
    ASSUME(IW(2,REGP(2,4)) >= max(cDS[2],cDL[2]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(2,REGP(2,4)) >= CL(2,r));
    }
    ASSUME(CW(2,REGP(2,4)) >= IW(2, REGP(2,4)));
    ASSUME(active[CW(2,REGP(2,4))] == 2);
    ASSUME(CW(2,REGP(2,4)) >= max(CREG(2,3),IREG(2,4)));
    ASSUME(CW(2,REGP(2,4)) >= max(old_cW,CR(2,REGP(2,4))));
    ASSUME(CW(2,REGP(2,4)) >= ctrl[2]);
    ASSUME(CW(2,REGP(2,4)) >= iAddr[2]);
    // Update
    iAddr[2] = max(iAddr[2], IREG(2,4));
    MU(REGP(2,4),CW(2,REGP(2,4))) = REGP(2,3);
    NU(2,REGP(2,4)) = REGP(2,3);
    DELTA(REGP(2,4),CW(2,REGP(2,4))) = -1;
    
    /* assign */
    // Guess
    IREG(2,7) = get_rng(0,NCONTEXT-1);
    CREG(2,7) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,7)] == 2);
    ASSUME(IREG(2,7) >= IREG(2,3));
    ASSUME(active[CREG(2,7)] == 2);
    ASSUME(CREG(2,7) >= max(ctrl[2],IREG(2,7)));
    ASSUME(CREG(2,7) >= CREG(2,3));
    // Update
    REGP(2,7) = REGP(2,3);
    
    /* dmb.sy */
    // Guess
    old_cDY = cDY[2];
    cDY[2] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[2] >= old_cDY);
    ASSUME(cDY[2] >= max(cISB[2],cDL[2]));
    ASSUME(cDY[2] >= max(cDS[2],ctrl[2]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[2] >= CW(2,x));
        ASSUME(cDY[2] >= CR(2,x));
    }
    
    /* assign */
    // Guess
    IREG(2,3) = get_rng(0,NCONTEXT-1);
    CREG(2,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,3)] == 2);
    ASSUME(active[CREG(2,3)] == 2);
    ASSUME(CREG(2,3) >= max(ctrl[2],IREG(2,3)));
    // Update
    REGP(2,3) = 0;
    
    /* assign */
    // Guess
    IREG(2,4) = get_rng(0,NCONTEXT-1);
    CREG(2,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,4)] == 2);
    ASSUME(active[CREG(2,4)] == 2);
    ASSUME(CREG(2,4) >= max(ctrl[2],IREG(2,4)));
    // Update
    REGP(2,4) = 2;
    
    /* ST */
    // Guess
    IW(2,REGP(2,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(2,REGP(2,4));
    CW(2,REGP(2,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(2,REGP(2,4))] == 2);
    ASSUME(IW(2,REGP(2,4)) >= max(IREG(2,3),IREG(2,4)));
    ASSUME(IW(2,REGP(2,4)) >= max(cDY[2],cISB[2]));
    ASSUME(IW(2,REGP(2,4)) >= max(cDS[2],cDL[2]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(2,REGP(2,4)) >= CL(2,r));
    }
    ASSUME(CW(2,REGP(2,4)) >= IW(2, REGP(2,4)));
    ASSUME(active[CW(2,REGP(2,4))] == 2);
    ASSUME(CW(2,REGP(2,4)) >= max(CREG(2,3),IREG(2,4)));
    ASSUME(CW(2,REGP(2,4)) >= max(old_cW,CR(2,REGP(2,4))));
    ASSUME(CW(2,REGP(2,4)) >= ctrl[2]);
    ASSUME(CW(2,REGP(2,4)) >= iAddr[2]);
    // Update
    iAddr[2] = max(iAddr[2], IREG(2,4));
    MU(REGP(2,4),CW(2,REGP(2,4))) = REGP(2,3);
    NU(2,REGP(2,4)) = REGP(2,3);
    DELTA(REGP(2,4),CW(2,REGP(2,4))) = -1;
    
    /* assign */
    // Guess
    IREG(2,4) = get_rng(0,NCONTEXT-1);
    CREG(2,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,4)] == 2);
    ASSUME(active[CREG(2,4)] == 2);
    ASSUME(CREG(2,4) >= max(ctrl[2],IREG(2,4)));
    // Update
    REGP(2,4) = 0;
    
p2waitenter:
    /* dmb.sy */
    // Guess
    old_cDY = cDY[2];
    cDY[2] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[2] >= old_cDY);
    ASSUME(cDY[2] >= max(cISB[2],cDL[2]));
    ASSUME(cDY[2] >= max(cDS[2],ctrl[2]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[2] >= CW(2,x));
        ASSUME(cDY[2] >= CR(2,x));
    }
    
    /* LD */
    // Guess
    IR(2,REGP(2,4)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(2,REGP(2,4));
    CR(2,REGP(2,4)) = get_rng(0,NCONTEXT-1);
    IREG(2,3) = IR(2,REGP(2,4));
    CREG(2,3) = CR(2,REGP(2,4));
    // Check
    ASSUME(active[IR(2,REGP(2,4))] == 2);
    ASSUME(IR(2,REGP(2,4)) >= IW(2,REGP(2,4)));
    ASSUME(IR(2,REGP(2,4)) >= IREG(2,4));
    ASSUME(IR(2,REGP(2,4)) >= max(cDY[2],cISB[2]));
    ASSUME(IR(2,REGP(2,4)) >= cDL[2]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(2,REGP(2,4)) >= IL(2,rdp));
    }
    ASSUME(CR(2,REGP(2,4)) >= IR(2, REGP(2,4)));
    ASSUME(active[CR(2,REGP(2,4))] == 2);
    ASSUME(CR(2,REGP(2,4)) >= max(IREG(2,4),ctrl[2]));
    ASSUME(CR(2,REGP(2,4)) >= max(old_cR,CW(2,REGP(2,4))));
    // Update
    iAddr[2] = max(iAddr[2], IREG(2,4));
    if (IR(2,REGP(2,4)) < CW(2,REGP(2,4))) {
        REGP(2,3) = NU(2,REGP(2,4));
    } else {
        REGP(2,3) = MU(REGP(2,4),IR(2,REGP(2,4)));
    }
    
    /* assign */
    // Guess
    IREG(2,0) = get_rng(0,NCONTEXT-1);
    CREG(2,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,0)] == 2);
    ASSUME(IREG(2,0) >= IREG(2,3));
    ASSUME(active[CREG(2,0)] == 2);
    ASSUME(CREG(2,0) >= max(ctrl[2],IREG(2,0)));
    ASSUME(CREG(2,0) >= CREG(2,3));
    // Update
    REGP(2,0) = REGP(2,3);
    
    /* assign */
    // Guess
    IREG(2,1) = get_rng(0,NCONTEXT-1);
    CREG(2,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,1)] == 2);
    ASSUME(active[CREG(2,1)] == 2);
    ASSUME(CREG(2,1) >= max(ctrl[2],IREG(2,1)));
    // Update
    REGP(2,1) = 1;
    
    /* BEQ */
    ctrl[2] = ctrl[2] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[2] < NCONTEXT);
    
    ASSUME(ctrl[2] >= IREG(2,0));
    ASSUME(ctrl[2] >= IREG(2,1));
    if (REGP(2,0) == REGP(2,1))
        goto p2waitenter;
    
    /* assign */
    // Guess
    IREG(2,4) = get_rng(0,NCONTEXT-1);
    CREG(2,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,4)] == 2);
    ASSUME(IREG(2,4) >= IREG(2,4));
    ASSUME(active[CREG(2,4)] == 2);
    ASSUME(CREG(2,4) >= max(ctrl[2],IREG(2,4)));
    ASSUME(CREG(2,4) >= CREG(2,4));
    // Update
    REGP(2,4) = (REGP(2,4) + 1);
    
    /* assign */
    // Guess
    IREG(2,0) = get_rng(0,NCONTEXT-1);
    CREG(2,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,0)] == 2);
    ASSUME(IREG(2,0) >= IREG(2,4));
    ASSUME(active[CREG(2,0)] == 2);
    ASSUME(CREG(2,0) >= max(ctrl[2],IREG(2,0)));
    ASSUME(CREG(2,0) >= CREG(2,4));
    // Update
    REGP(2,0) = REGP(2,4);
    
    /* assign */
    // Guess
    IREG(2,1) = get_rng(0,NCONTEXT-1);
    CREG(2,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,1)] == 2);
    ASSUME(active[CREG(2,1)] == 2);
    ASSUME(CREG(2,1) >= max(ctrl[2],IREG(2,1)));
    // Update
    REGP(2,1) = 3;
    
    /* BNE */
    ctrl[2] = ctrl[2] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[2] < NCONTEXT);
    
    ASSUME(ctrl[2] >= IREG(2,0));
    ASSUME(ctrl[2] >= IREG(2,1));
    if (REGP(2,0) != REGP(2,1))
        goto p2waitenter;
    
    /* assign */
    // Guess
    IREG(2,3) = get_rng(0,NCONTEXT-1);
    CREG(2,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,3)] == 2);
    ASSUME(active[CREG(2,3)] == 2);
    ASSUME(CREG(2,3) >= max(ctrl[2],IREG(2,3)));
    // Update
    REGP(2,3) = 5;
    
    /* assign */
    // Guess
    IREG(2,4) = get_rng(0,NCONTEXT-1);
    CREG(2,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,4)] == 2);
    ASSUME(active[CREG(2,4)] == 2);
    ASSUME(CREG(2,4) >= max(ctrl[2],IREG(2,4)));
    // Update
    REGP(2,4) = 3;
    
p2waitfinish:
    /* dmb.sy */
    // Guess
    old_cDY = cDY[2];
    cDY[2] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[2] >= old_cDY);
    ASSUME(cDY[2] >= max(cISB[2],cDL[2]));
    ASSUME(cDY[2] >= max(cDS[2],ctrl[2]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[2] >= CW(2,x));
        ASSUME(cDY[2] >= CR(2,x));
    }
    
    /* LD */
    // Guess
    IR(2,REGP(2,4)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(2,REGP(2,4));
    CR(2,REGP(2,4)) = get_rng(0,NCONTEXT-1);
    IREG(2,5) = IR(2,REGP(2,4));
    CREG(2,5) = CR(2,REGP(2,4));
    // Check
    ASSUME(active[IR(2,REGP(2,4))] == 2);
    ASSUME(IR(2,REGP(2,4)) >= IW(2,REGP(2,4)));
    ASSUME(IR(2,REGP(2,4)) >= IREG(2,4));
    ASSUME(IR(2,REGP(2,4)) >= max(cDY[2],cISB[2]));
    ASSUME(IR(2,REGP(2,4)) >= cDL[2]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(2,REGP(2,4)) >= IL(2,rdp));
    }
    ASSUME(CR(2,REGP(2,4)) >= IR(2, REGP(2,4)));
    ASSUME(active[CR(2,REGP(2,4))] == 2);
    ASSUME(CR(2,REGP(2,4)) >= max(IREG(2,4),ctrl[2]));
    ASSUME(CR(2,REGP(2,4)) >= max(old_cR,CW(2,REGP(2,4))));
    // Update
    iAddr[2] = max(iAddr[2], IREG(2,4));
    if (IR(2,REGP(2,4)) < CW(2,REGP(2,4))) {
        REGP(2,5) = NU(2,REGP(2,4));
    } else {
        REGP(2,5) = MU(REGP(2,4),IR(2,REGP(2,4)));
    }
    
    /* CBZ */
    ctrl[2] = ctrl[2] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[2] < NCONTEXT);
    
    ASSUME(ctrl[2] >= IREG(2,5));
    if (REGP(2,5) == 0)
        goto p2next;
    
    /* assign */
    // Guess
    IREG(2,0) = get_rng(0,NCONTEXT-1);
    CREG(2,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,0)] == 2);
    ASSUME(IREG(2,0) >= IREG(2,5));
    ASSUME(active[CREG(2,0)] == 2);
    ASSUME(CREG(2,0) >= max(ctrl[2],IREG(2,0)));
    ASSUME(CREG(2,0) >= CREG(2,5));
    // Update
    REGP(2,0) = REGP(2,5);
    
    /* assign */
    // Guess
    IREG(2,1) = get_rng(0,NCONTEXT-1);
    CREG(2,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,1)] == 2);
    ASSUME(IREG(2,1) >= IREG(2,7));
    ASSUME(active[CREG(2,1)] == 2);
    ASSUME(CREG(2,1) >= max(ctrl[2],IREG(2,1)));
    ASSUME(CREG(2,1) >= CREG(2,7));
    // Update
    REGP(2,1) = REGP(2,7);
    
    /* BGT */
    ctrl[2] = ctrl[2] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[2] < NCONTEXT);
    
    ASSUME(ctrl[2] >= IREG(2,0));
    ASSUME(ctrl[2] >= IREG(2,1));
    if (REGP(2,0) > REGP(2,1))
        goto p2next;
    
    /* assign */
    // Guess
    IREG(2,0) = get_rng(0,NCONTEXT-1);
    CREG(2,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,0)] == 2);
    ASSUME(IREG(2,0) >= IREG(2,4));
    ASSUME(active[CREG(2,0)] == 2);
    ASSUME(CREG(2,0) >= max(ctrl[2],IREG(2,0)));
    ASSUME(CREG(2,0) >= CREG(2,4));
    // Update
    REGP(2,0) = REGP(2,4);
    
    /* assign */
    // Guess
    IREG(2,1) = get_rng(0,NCONTEXT-1);
    CREG(2,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,1)] == 2);
    ASSUME(IREG(2,1) >= IREG(2,3));
    ASSUME(active[CREG(2,1)] == 2);
    ASSUME(CREG(2,1) >= max(ctrl[2],IREG(2,1)));
    ASSUME(CREG(2,1) >= CREG(2,3));
    // Update
    REGP(2,1) = REGP(2,3);
    
p2next:
    /* dmb.sy */
    // Guess
    old_cDY = cDY[2];
    cDY[2] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[2] >= old_cDY);
    ASSUME(cDY[2] >= max(cISB[2],cDL[2]));
    ASSUME(cDY[2] >= max(cDS[2],ctrl[2]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[2] >= CW(2,x));
        ASSUME(cDY[2] >= CR(2,x));
    }
    
    /* assign */
    // Guess
    IREG(2,4) = get_rng(0,NCONTEXT-1);
    CREG(2,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,4)] == 2);
    ASSUME(IREG(2,4) >= IREG(2,4));
    ASSUME(active[CREG(2,4)] == 2);
    ASSUME(CREG(2,4) >= max(ctrl[2],IREG(2,4)));
    ASSUME(CREG(2,4) >= CREG(2,4));
    // Update
    REGP(2,4) = (REGP(2,4) + 1);
    
    /* assign */
    // Guess
    IREG(2,0) = get_rng(0,NCONTEXT-1);
    CREG(2,0) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,0)] == 2);
    ASSUME(IREG(2,0) >= IREG(2,4));
    ASSUME(active[CREG(2,0)] == 2);
    ASSUME(CREG(2,0) >= max(ctrl[2],IREG(2,0)));
    ASSUME(CREG(2,0) >= CREG(2,4));
    // Update
    REGP(2,0) = REGP(2,4);
    
    /* assign */
    // Guess
    IREG(2,1) = get_rng(0,NCONTEXT-1);
    CREG(2,1) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,1)] == 2);
    ASSUME(active[CREG(2,1)] == 2);
    ASSUME(CREG(2,1) >= max(ctrl[2],IREG(2,1)));
    // Update
    REGP(2,1) = 6;
    
    /* BNE */
    ctrl[2] = ctrl[2] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[2] < NCONTEXT);
    
    ASSUME(ctrl[2] >= IREG(2,0));
    ASSUME(ctrl[2] >= IREG(2,1));
    if (REGP(2,0) != REGP(2,1))
        goto p2waitfinish;
    
    /* dmb.sy */
    // Guess
    old_cDY = cDY[2];
    cDY[2] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[2] >= old_cDY);
    ASSUME(cDY[2] >= max(cISB[2],cDL[2]));
    ASSUME(cDY[2] >= max(cDS[2],ctrl[2]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[2] >= CW(2,x));
        ASSUME(cDY[2] >= CR(2,x));
    }
    
    /* assign */
    // Guess
    IREG(2,3) = get_rng(0,NCONTEXT-1);
    CREG(2,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,3)] == 2);
    ASSUME(active[CREG(2,3)] == 2);
    ASSUME(CREG(2,3) >= max(ctrl[2],IREG(2,3)));
    // Update
    REGP(2,3) = 6;
    
    /* LD */
    // Guess
    IR(2,REGP(2,3)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(2,REGP(2,3));
    CR(2,REGP(2,3)) = get_rng(0,NCONTEXT-1);
    IREG(2,4) = IR(2,REGP(2,3));
    CREG(2,4) = CR(2,REGP(2,3));
    // Check
    ASSUME(active[IR(2,REGP(2,3))] == 2);
    ASSUME(IR(2,REGP(2,3)) >= IW(2,REGP(2,3)));
    ASSUME(IR(2,REGP(2,3)) >= IREG(2,3));
    ASSUME(IR(2,REGP(2,3)) >= max(cDY[2],cISB[2]));
    ASSUME(IR(2,REGP(2,3)) >= cDL[2]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(2,REGP(2,3)) >= IL(2,rdp));
    }
    ASSUME(CR(2,REGP(2,3)) >= IR(2, REGP(2,3)));
    ASSUME(active[CR(2,REGP(2,3))] == 2);
    ASSUME(CR(2,REGP(2,3)) >= max(IREG(2,3),ctrl[2]));
    ASSUME(CR(2,REGP(2,3)) >= max(old_cR,CW(2,REGP(2,3))));
    // Update
    iAddr[2] = max(iAddr[2], IREG(2,3));
    if (IR(2,REGP(2,3)) < CW(2,REGP(2,3))) {
        REGP(2,4) = NU(2,REGP(2,3));
    } else {
        REGP(2,4) = MU(REGP(2,3),IR(2,REGP(2,3)));
    }
    
    /* assign */
    // Guess
    IREG(2,4) = get_rng(0,NCONTEXT-1);
    CREG(2,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,4)] == 2);
    ASSUME(IREG(2,4) >= IREG(2,4));
    ASSUME(active[CREG(2,4)] == 2);
    ASSUME(CREG(2,4) >= max(ctrl[2],IREG(2,4)));
    ASSUME(CREG(2,4) >= CREG(2,4));
    // Update
    REGP(2,4) = (REGP(2,4) + 1);
    
    /* ST */
    // Guess
    IW(2,REGP(2,3)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(2,REGP(2,3));
    CW(2,REGP(2,3)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(2,REGP(2,3))] == 2);
    ASSUME(IW(2,REGP(2,3)) >= max(IREG(2,4),IREG(2,3)));
    ASSUME(IW(2,REGP(2,3)) >= max(cDY[2],cISB[2]));
    ASSUME(IW(2,REGP(2,3)) >= max(cDS[2],cDL[2]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(2,REGP(2,3)) >= CL(2,r));
    }
    ASSUME(CW(2,REGP(2,3)) >= IW(2, REGP(2,3)));
    ASSUME(active[CW(2,REGP(2,3))] == 2);
    ASSUME(CW(2,REGP(2,3)) >= max(CREG(2,4),IREG(2,3)));
    ASSUME(CW(2,REGP(2,3)) >= max(old_cW,CR(2,REGP(2,3))));
    ASSUME(CW(2,REGP(2,3)) >= ctrl[2]);
    ASSUME(CW(2,REGP(2,3)) >= iAddr[2]);
    // Update
    iAddr[2] = max(iAddr[2], IREG(2,3));
    MU(REGP(2,3),CW(2,REGP(2,3))) = REGP(2,4);
    NU(2,REGP(2,3)) = REGP(2,4);
    DELTA(REGP(2,3),CW(2,REGP(2,3))) = -1;
    
    /* dmb.sy */
    // Guess
    old_cDY = cDY[2];
    cDY[2] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[2] >= old_cDY);
    ASSUME(cDY[2] >= max(cISB[2],cDL[2]));
    ASSUME(cDY[2] >= max(cDS[2],ctrl[2]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[2] >= CW(2,x));
        ASSUME(cDY[2] >= CR(2,x));
    }
    
    /* assign */
    // Guess
    IREG(2,3) = get_rng(0,NCONTEXT-1);
    CREG(2,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,3)] == 2);
    ASSUME(active[CREG(2,3)] == 2);
    ASSUME(CREG(2,3) >= max(ctrl[2],IREG(2,3)));
    // Update
    REGP(2,3) = 0;
    
    /* assign */
    // Guess
    IREG(2,4) = get_rng(0,NCONTEXT-1);
    CREG(2,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IREG(2,4)] == 2);
    ASSUME(active[CREG(2,4)] == 2);
    ASSUME(CREG(2,4) >= max(ctrl[2],IREG(2,4)));
    // Update
    REGP(2,4) = 5;
    
    /* ST */
    // Guess
    IW(2,REGP(2,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(2,REGP(2,4));
    CW(2,REGP(2,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(2,REGP(2,4))] == 2);
    ASSUME(IW(2,REGP(2,4)) >= max(IREG(2,3),IREG(2,4)));
    ASSUME(IW(2,REGP(2,4)) >= max(cDY[2],cISB[2]));
    ASSUME(IW(2,REGP(2,4)) >= max(cDS[2],cDL[2]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(2,REGP(2,4)) >= CL(2,r));
    }
    ASSUME(CW(2,REGP(2,4)) >= IW(2, REGP(2,4)));
    ASSUME(active[CW(2,REGP(2,4))] == 2);
    ASSUME(CW(2,REGP(2,4)) >= max(CREG(2,3),IREG(2,4)));
    ASSUME(CW(2,REGP(2,4)) >= max(old_cW,CR(2,REGP(2,4))));
    ASSUME(CW(2,REGP(2,4)) >= ctrl[2]);
    ASSUME(CW(2,REGP(2,4)) >= iAddr[2]);
    // Update
    iAddr[2] = max(iAddr[2], IREG(2,4));
    MU(REGP(2,4),CW(2,REGP(2,4))) = REGP(2,3);
    NU(2,REGP(2,4)) = REGP(2,3);
    DELTA(REGP(2,4),CW(2,REGP(2,4))) = -1;
    
    // Process 2 END
    
    /* verProc */
    for (int x = 0; x < ADDRSIZE; x++) {
        for (int k = 0; k < NCONTEXT-1; k++) {
            ASSUME(MU(x,k) == MUINIT(x,k+1));
            ASSUME(DELTA(x,k) == DELTAINIT(x,k+1));
        }
    }
    if (
        (MU(6,NCONTEXT-1) == 2) &&
    1)
        ASSERT(0);
    
    return 0;
}