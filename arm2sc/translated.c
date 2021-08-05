#define NREGS 13
#define ADDRSIZE 3
#define NPROC 3
#define NCONTEXT 10


// declaration of helper variables
int registers[NREGS*NPROC];
int memory[ADDRSIZE];
int muinit[ADDRSIZE*NCONTEXT], mu[ADDRSIZE*NCONTEXT];
int nwinit[ADDRSIZE*NCONTEXT], nw[ADDRSIZE*NCONTEXT];
int deltainit[ADDRSIZE*NCONTEXT], delta[ADDRSIZE*NCONTEXT];
int nu[NPROC*ADDRSIZE], pw[NPROC*ADDRSIZE];
int cR[NPROC*ADDRSIZE], iW[NPROC*ADDRSIZE],cW[NPROC*ADDRSIZE],cX[NPROC*ADDRSIZE];
int cL[NPROC*NREGS], iS[NPROC*ADDRSIZE],cS[NPROC*ADDRSIZE];
int iReg[NPROC*NREGS], cReg[NPROC*NREGS];
int cDY[NPROC], cDS[NPROC], cDL[NPROC], cISB[NPROC], cAddr[NPROC];
int ctrl[NPROC], active[NCONTEXT];
int old_cR, old_cDY, new_iW, old_cW, new_cW, new_iReg, new_cReg;


// the following macros are for easy reading
#define REGP(p,r) registers[p*NREGS+r]
#define ADDR_AT(p,r) memory[REGP(p,r)]
#define MUINIT(x,k) muinit[x*NCONTEXT+k]
#define MU(x,k) mu[x*NCONTEXT+k]
#define DELTAINIT(x,k) deltainit[x*NCONTEXT+k]
#define DELTA(x,k) delta[x*NCONTEXT+k]
#define NWINIT(x,k) nwinit[x*NCONTEXT+k]
#define NW(x,k) nw[x*NCONTEXT+k]
#define PW(p,x) pw[p*ADDRSIZE+x]
#define NU(p,x) nu[p*ADDRSIZE+x]
#define CR(p,x) cR[p*ADDRSIZE+x]
#define IW(p,x) iW[p*ADDRSIZE+x]
#define CW(p,x) cW[p*ADDRSIZE+x]
#define CL(p,r) cL[p*NREGS+r]
#define IS(p,x) iS[p*ADDRSIZE+x]
#define CS(p,x) cS[p*ADDRSIZE+x]
#define CX(p,x) cX[p*ADDRSIZE+x]
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
            IW(p,x) = 0;
            CR(p,x) = 0;
            CW(p,x) = 0;
            NU(p,x) = 0;
            PW(p,x) = 0;
            IS(p,x) = 0;
            CS(p,x) = 0;
            CX(p,x) = 0;
        }
        for (int r = 0; r < NREGS; r++) {
            CL(p,r) = 0;
            CREG(p,r) = 0;
        }
        ctrl[p] = 0;
        cAddr[p] = 0;
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
                NWINIT(x,k) = __get_rng();
                NW(x,k) = NWINIT(x,k);
                DELTAINIT(x,k) = get_rng(-1,NPROC-1);
                DELTA(x,k) = DELTAINIT(x,k);
            }
        } else {
            for (int x = 0; x < ADDRSIZE; x++) {
                MU(x,k) = 0;
                DELTA(x,k) = -1;
                NW(x,k) = 0;
            }
        }
    }
    // any initial memory values here
    // register initial values
    REGP(0,3) = 1;
    REGP(0,2) = 2;
    REGP(1,2) = 2;
    REGP(1,3) = 0;
    REGP(1,4) = 1;
    REGP(2,2) = 2;
    
    // Process 0 BEGIN
    /* assign */
    // Guess
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 0);
    // Update
    CREG(0,4) = new_cReg;
    REGP(0,4) = 2;
    
    /* ST */
    // Guess
    IW(0,REGP(0,3)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(0,REGP(0,3));
    CW(0,REGP(0,3)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(0,REGP(0,3))] == 0);
    ASSUME(IW(0,REGP(0,3)) >= max(CREG(0,4),CREG(0,3)));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(CW(0,REGP(0,3)) >= CL(0,r));
    }
    ASSUME(CW(0,REGP(0,3)) >= IW(0, REGP(0,3)));
    ASSUME(active[CW(0,REGP(0,3))] == 0);
    ASSUME(CW(0,REGP(0,3)) >= max(cDY[0],cISB[0]));
    ASSUME(CW(0,REGP(0,3)) >= max(cDS[0],cDL[0]));
    ASSUME(CW(0,REGP(0,3)) >= max(old_cW,CR(0,REGP(0,3))));
    ASSUME(CW(0,REGP(0,3)) >= ctrl[0]);
    ASSUME(CW(0,REGP(0,3)) >= cAddr[0]);
    // Update
    cAddr[0] = max(cAddr[0], CREG(0,3));
    MU(REGP(0,3),CW(0,REGP(0,3))) = REGP(0,4);
    NU(0,REGP(0,3)) = REGP(0,4);
    NW(REGP(0,3),CW(0,REGP(0,3))) += 1;
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
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 0);
    // Update
    CREG(0,5) = new_cReg;
    REGP(0,5) = 1;
    
    /* ST */
    // Guess
    IW(0,REGP(0,2)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(0,REGP(0,2));
    CW(0,REGP(0,2)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(0,REGP(0,2))] == 0);
    ASSUME(IW(0,REGP(0,2)) >= max(CREG(0,5),CREG(0,2)));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(CW(0,REGP(0,2)) >= CL(0,r));
    }
    ASSUME(CW(0,REGP(0,2)) >= IW(0, REGP(0,2)));
    ASSUME(active[CW(0,REGP(0,2))] == 0);
    ASSUME(CW(0,REGP(0,2)) >= max(cDY[0],cISB[0]));
    ASSUME(CW(0,REGP(0,2)) >= max(cDS[0],cDL[0]));
    ASSUME(CW(0,REGP(0,2)) >= max(old_cW,CR(0,REGP(0,2))));
    ASSUME(CW(0,REGP(0,2)) >= ctrl[0]);
    ASSUME(CW(0,REGP(0,2)) >= cAddr[0]);
    // Update
    cAddr[0] = max(cAddr[0], CREG(0,2));
    MU(REGP(0,2),CW(0,REGP(0,2))) = REGP(0,5);
    NU(0,REGP(0,2)) = REGP(0,5);
    NW(REGP(0,2),CW(0,REGP(0,2))) += 1;
    DELTA(REGP(0,2),CW(0,REGP(0,2))) = -1;
    
    // Process 0 END
    
    // Process 1 BEGIN
    /* LD */
    // Guess
    old_cR = CR(1,REGP(1,2));
    CR(1,REGP(1,2)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[CR(1,REGP(1,2))] == 1);
    ASSUME(CR(1,REGP(1,2)) >= IW(1,REGP(1,2)));
    ASSUME(CR(1,REGP(1,2)) >= CREG(1,2));
    ASSUME(CR(1,REGP(1,2)) >= max(cDY[1],cISB[1]));
    ASSUME(CR(1,REGP(1,2)) >= cDL[1]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(CR(1,REGP(1,2)) >= CL(1,rdp));
    }
    // Update
    CREG(1,5) = CR(1,REGP(1,2));
    cAddr[1] = max(cAddr[1], CREG(1,2));
    if (CR(1,REGP(1,2)) < CW(1,REGP(1,2))) {
        REGP(1,5) = NU(1,REGP(1,2));
    } else {
        if (PW(1,REGP(1,2)) != NW(REGP(1,2),CR(1,REGP(1,2))))
            ASSUME(CR(1,REGP(1,2)) >= old_cR);
        REGP(1,5) = MU(REGP(1,2),CR(1,REGP(1,2)));
        PW(1,REGP(1,2)) = NW(REGP(1,2),CR(1,REGP(1,2)));
    }
    
    /* LD */
    // Guess
    old_cR = CR(1,REGP(1,2));
    CR(1,REGP(1,2)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[CR(1,REGP(1,2))] == 1);
    ASSUME(CR(1,REGP(1,2)) >= IW(1,REGP(1,2)));
    ASSUME(CR(1,REGP(1,2)) >= CREG(1,2));
    ASSUME(CR(1,REGP(1,2)) >= max(cDY[1],cISB[1]));
    ASSUME(CR(1,REGP(1,2)) >= cDL[1]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(CR(1,REGP(1,2)) >= CL(1,rdp));
    }
    // Update
    CREG(1,6) = CR(1,REGP(1,2));
    cAddr[1] = max(cAddr[1], CREG(1,2));
    if (CR(1,REGP(1,2)) < CW(1,REGP(1,2))) {
        REGP(1,6) = NU(1,REGP(1,2));
    } else {
        if (PW(1,REGP(1,2)) != NW(REGP(1,2),CR(1,REGP(1,2))))
            ASSUME(CR(1,REGP(1,2)) >= old_cR);
        REGP(1,6) = MU(REGP(1,2),CR(1,REGP(1,2)));
        PW(1,REGP(1,2)) = NW(REGP(1,2),CR(1,REGP(1,2)));
    }
    
    /* CBNZ */
    ctrl[1] = ctrl[1] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[1] < NCONTEXT);
    
    ASSUME(ctrl[1] >= CREG(1,6));
    if (REGP(1,6) != 0)
        goto LC00;
    
LC00:
    /* LD */
    // Guess
    old_cR = CR(1,REGP(1,3));
    CR(1,REGP(1,3)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[CR(1,REGP(1,3))] == 1);
    ASSUME(CR(1,REGP(1,3)) >= IW(1,REGP(1,3)));
    ASSUME(CR(1,REGP(1,3)) >= CREG(1,3));
    ASSUME(CR(1,REGP(1,3)) >= max(cDY[1],cISB[1]));
    ASSUME(CR(1,REGP(1,3)) >= cDL[1]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(CR(1,REGP(1,3)) >= CL(1,rdp));
    }
    // Update
    CREG(1,7) = CR(1,REGP(1,3));
    cAddr[1] = max(cAddr[1], CREG(1,3));
    if (CR(1,REGP(1,3)) < CW(1,REGP(1,3))) {
        REGP(1,7) = NU(1,REGP(1,3));
    } else {
        if (PW(1,REGP(1,3)) != NW(REGP(1,3),CR(1,REGP(1,3))))
            ASSUME(CR(1,REGP(1,3)) >= old_cR);
        REGP(1,7) = MU(REGP(1,3),CR(1,REGP(1,3)));
        PW(1,REGP(1,3)) = NW(REGP(1,3),CR(1,REGP(1,3)));
    }
    
    /* assign */
    // Guess
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= CREG(1,7));
    ASSUME(new_cReg >= CREG(1,7));
    // Update
    CREG(1,8) = new_cReg;
    REGP(1,8) = (REGP(1,7) ^ REGP(1,7));
    
    /* assign */
    // Guess
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 1);
    // Update
    CREG(1,9) = new_cReg;
    REGP(1,9) = 1;
    
    /* assign */
    // Guess
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= CREG(1,4));
    ASSUME(new_cReg >= CREG(1,8));
    // Update
    CREG(1,11) = new_cReg;
    REGP(1,11) = (REGP(1,4) + REGP(1,8));
    
    /* ST */
    // Guess
    IW(1,REGP(1,11)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(1,REGP(1,11));
    CW(1,REGP(1,11)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(1,REGP(1,11))] == 1);
    ASSUME(IW(1,REGP(1,11)) >= max(CREG(1,9),CREG(1,11)));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(CW(1,REGP(1,11)) >= CL(1,r));
    }
    ASSUME(CW(1,REGP(1,11)) >= IW(1, REGP(1,11)));
    ASSUME(active[CW(1,REGP(1,11))] == 1);
    ASSUME(CW(1,REGP(1,11)) >= max(cDY[1],cISB[1]));
    ASSUME(CW(1,REGP(1,11)) >= max(cDS[1],cDL[1]));
    ASSUME(CW(1,REGP(1,11)) >= max(old_cW,CR(1,REGP(1,11))));
    ASSUME(CW(1,REGP(1,11)) >= ctrl[1]);
    ASSUME(CW(1,REGP(1,11)) >= cAddr[1]);
    // Update
    cAddr[1] = max(cAddr[1], CREG(1,11));
    MU(REGP(1,11),CW(1,REGP(1,11))) = REGP(1,9);
    NU(1,REGP(1,11)) = REGP(1,9);
    NW(REGP(1,11),CW(1,REGP(1,11))) += 1;
    DELTA(REGP(1,11),CW(1,REGP(1,11))) = -1;
    
    /* LD */
    // Guess
    old_cR = CR(1,REGP(1,4));
    CR(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[CR(1,REGP(1,4))] == 1);
    ASSUME(CR(1,REGP(1,4)) >= IW(1,REGP(1,4)));
    ASSUME(CR(1,REGP(1,4)) >= CREG(1,4));
    ASSUME(CR(1,REGP(1,4)) >= max(cDY[1],cISB[1]));
    ASSUME(CR(1,REGP(1,4)) >= cDL[1]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(CR(1,REGP(1,4)) >= CL(1,rdp));
    }
    // Update
    CREG(1,12) = CR(1,REGP(1,4));
    cAddr[1] = max(cAddr[1], CREG(1,4));
    if (CR(1,REGP(1,4)) < CW(1,REGP(1,4))) {
        REGP(1,12) = NU(1,REGP(1,4));
    } else {
        if (PW(1,REGP(1,4)) != NW(REGP(1,4),CR(1,REGP(1,4))))
            ASSUME(CR(1,REGP(1,4)) >= old_cR);
        REGP(1,12) = MU(REGP(1,4),CR(1,REGP(1,4)));
        PW(1,REGP(1,4)) = NW(REGP(1,4),CR(1,REGP(1,4)));
    }
    
    // Process 1 END
    
    // Process 2 BEGIN
    /* assign */
    // Guess
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 2);
    // Update
    CREG(2,3) = new_cReg;
    REGP(2,3) = 2;
    
    /* ST */
    // Guess
    IW(2,REGP(2,2)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(2,REGP(2,2));
    CW(2,REGP(2,2)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(2,REGP(2,2))] == 2);
    ASSUME(IW(2,REGP(2,2)) >= max(CREG(2,3),CREG(2,2)));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(CW(2,REGP(2,2)) >= CL(2,r));
    }
    ASSUME(CW(2,REGP(2,2)) >= IW(2, REGP(2,2)));
    ASSUME(active[CW(2,REGP(2,2))] == 2);
    ASSUME(CW(2,REGP(2,2)) >= max(cDY[2],cISB[2]));
    ASSUME(CW(2,REGP(2,2)) >= max(cDS[2],cDL[2]));
    ASSUME(CW(2,REGP(2,2)) >= max(old_cW,CR(2,REGP(2,2))));
    ASSUME(CW(2,REGP(2,2)) >= ctrl[2]);
    ASSUME(CW(2,REGP(2,2)) >= cAddr[2]);
    // Update
    cAddr[2] = max(cAddr[2], CREG(2,2));
    MU(REGP(2,2),CW(2,REGP(2,2))) = REGP(2,3);
    NU(2,REGP(2,2)) = REGP(2,3);
    NW(REGP(2,2),CW(2,REGP(2,2))) += 1;
    DELTA(REGP(2,2),CW(2,REGP(2,2))) = -1;
    
    // Process 2 END
    
    /* verProc */
    for (int x = 0; x < ADDRSIZE; x++) {
        for (int k = 0; k < NCONTEXT-1; k++) {
            ASSUME(MU(x,k) == MUINIT(x,k+1));
            ASSUME(NW(x,k) == NWINIT(x,k+1));
            ASSUME(DELTA(x,k) == DELTAINIT(x,k+1));
        }
    }
    if (
        (MU(1,NCONTEXT-1) == 2) &&
        (MU(2,NCONTEXT-1) == 2) &&
        (REGP(1,5) == 1) &&
        (REGP(1,6) == 2) &&
        (REGP(1,12) == 1) &&
    1)
        ASSERT(0);
    
    return 0;
}