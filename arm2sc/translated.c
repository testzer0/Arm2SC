#define NREGS 5
#define ADDRSIZE 3
#define NPROC 2
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
    
    // Process 0 BEGIN
    /* assign */
    // Guess
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 0);
    // Update
    CREG(0,3) = new_cReg;
    REGP(0,3) = 1;
    
    /* assign */
    // Guess
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 0);
    // Update
    CREG(0,4) = new_cReg;
    REGP(0,4) = 0;
    
    /* ST */
    // Guess
    IW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(0,REGP(0,4));
    CW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(0,REGP(0,4))] == 0);
    ASSUME(IW(0,REGP(0,4)) >= max(CREG(0,3),CREG(0,4)));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(CW(0,REGP(0,4)) >= CL(0,r));
    }
    ASSUME(CW(0,REGP(0,4)) >= IW(0, REGP(0,4)));
    ASSUME(active[CW(0,REGP(0,4))] == 0);
    ASSUME(CW(0,REGP(0,4)) >= max(cDY[0],cISB[0]));
    ASSUME(CW(0,REGP(0,4)) >= max(cDS[0],cDL[0]));
    ASSUME(CW(0,REGP(0,4)) >= max(old_cW,CR(0,REGP(0,4))));
    ASSUME(CW(0,REGP(0,4)) >= ctrl[0]);
    ASSUME(CW(0,REGP(0,4)) >= cAddr[0]);
    // Update
    cAddr[0] = max(cAddr[0], CREG(0,4));
    MU(REGP(0,4),CW(0,REGP(0,4))) = REGP(0,3);
    NU(0,REGP(0,4)) = REGP(0,3);
    NW(REGP(0,4),CW(0,REGP(0,4))) += 1;
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
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 0);
    // Update
    CREG(0,4) = new_cReg;
    REGP(0,4) = 1;
    
p0loop:
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
    old_cR = CR(0,REGP(0,4));
    CR(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[CR(0,REGP(0,4))] == 0);
    ASSUME(CR(0,REGP(0,4)) >= IW(0,REGP(0,4)));
    ASSUME(CR(0,REGP(0,4)) >= CREG(0,4));
    ASSUME(CR(0,REGP(0,4)) >= max(cDY[0],cISB[0]));
    ASSUME(CR(0,REGP(0,4)) >= cDL[0]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(CR(0,REGP(0,4)) >= CL(0,rdp));
    }
    // Update
    CREG(0,3) = CR(0,REGP(0,4));
    cAddr[0] = max(cAddr[0], CREG(0,4));
    if (CR(0,REGP(0,4)) < CW(0,REGP(0,4))) {
        REGP(0,3) = NU(0,REGP(0,4));
    } else {
        if (PW(0,REGP(0,4)) != NW(REGP(0,4),CR(0,REGP(0,4))))
            ASSUME(CR(0,REGP(0,4)) >= old_cR);
        REGP(0,3) = MU(REGP(0,4),CR(0,REGP(0,4)));
        PW(0,REGP(0,4)) = NW(REGP(0,4),CR(0,REGP(0,4)));
    }
    
    /* CBNZ */
    ctrl[0] = ctrl[0] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[0] < NCONTEXT);
    
    ASSUME(ctrl[0] >= CREG(0,3));
    if (REGP(0,3) != 0)
        goto p0loop;
    
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
    CREG(0,4) = new_cReg;
    REGP(0,4) = 2;
    
    /* LD */
    // Guess
    old_cR = CR(0,REGP(0,4));
    CR(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[CR(0,REGP(0,4))] == 0);
    ASSUME(CR(0,REGP(0,4)) >= IW(0,REGP(0,4)));
    ASSUME(CR(0,REGP(0,4)) >= CREG(0,4));
    ASSUME(CR(0,REGP(0,4)) >= max(cDY[0],cISB[0]));
    ASSUME(CR(0,REGP(0,4)) >= cDL[0]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(CR(0,REGP(0,4)) >= CL(0,rdp));
    }
    // Update
    CREG(0,3) = CR(0,REGP(0,4));
    cAddr[0] = max(cAddr[0], CREG(0,4));
    if (CR(0,REGP(0,4)) < CW(0,REGP(0,4))) {
        REGP(0,3) = NU(0,REGP(0,4));
    } else {
        if (PW(0,REGP(0,4)) != NW(REGP(0,4),CR(0,REGP(0,4))))
            ASSUME(CR(0,REGP(0,4)) >= old_cR);
        REGP(0,3) = MU(REGP(0,4),CR(0,REGP(0,4)));
        PW(0,REGP(0,4)) = NW(REGP(0,4),CR(0,REGP(0,4)));
    }
    
    /* assign */
    // Guess
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 0);
    ASSUME(new_cReg >= CREG(0,3));
    // Update
    CREG(0,3) = new_cReg;
    REGP(0,3) = (REGP(0,3) + 1);
    
    /* ST */
    // Guess
    IW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(0,REGP(0,4));
    CW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(0,REGP(0,4))] == 0);
    ASSUME(IW(0,REGP(0,4)) >= max(CREG(0,3),CREG(0,4)));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(CW(0,REGP(0,4)) >= CL(0,r));
    }
    ASSUME(CW(0,REGP(0,4)) >= IW(0, REGP(0,4)));
    ASSUME(active[CW(0,REGP(0,4))] == 0);
    ASSUME(CW(0,REGP(0,4)) >= max(cDY[0],cISB[0]));
    ASSUME(CW(0,REGP(0,4)) >= max(cDS[0],cDL[0]));
    ASSUME(CW(0,REGP(0,4)) >= max(old_cW,CR(0,REGP(0,4))));
    ASSUME(CW(0,REGP(0,4)) >= ctrl[0]);
    ASSUME(CW(0,REGP(0,4)) >= cAddr[0]);
    // Update
    cAddr[0] = max(cAddr[0], CREG(0,4));
    MU(REGP(0,4),CW(0,REGP(0,4))) = REGP(0,3);
    NU(0,REGP(0,4)) = REGP(0,3);
    NW(REGP(0,4),CW(0,REGP(0,4))) += 1;
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
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 0);
    // Update
    CREG(0,3) = new_cReg;
    REGP(0,3) = 0;
    
    /* assign */
    // Guess
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 0);
    // Update
    CREG(0,4) = new_cReg;
    REGP(0,4) = 0;
    
    /* ST */
    // Guess
    IW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(0,REGP(0,4));
    CW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(0,REGP(0,4))] == 0);
    ASSUME(IW(0,REGP(0,4)) >= max(CREG(0,3),CREG(0,4)));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(CW(0,REGP(0,4)) >= CL(0,r));
    }
    ASSUME(CW(0,REGP(0,4)) >= IW(0, REGP(0,4)));
    ASSUME(active[CW(0,REGP(0,4))] == 0);
    ASSUME(CW(0,REGP(0,4)) >= max(cDY[0],cISB[0]));
    ASSUME(CW(0,REGP(0,4)) >= max(cDS[0],cDL[0]));
    ASSUME(CW(0,REGP(0,4)) >= max(old_cW,CR(0,REGP(0,4))));
    ASSUME(CW(0,REGP(0,4)) >= ctrl[0]);
    ASSUME(CW(0,REGP(0,4)) >= cAddr[0]);
    // Update
    cAddr[0] = max(cAddr[0], CREG(0,4));
    MU(REGP(0,4),CW(0,REGP(0,4))) = REGP(0,3);
    NU(0,REGP(0,4)) = REGP(0,3);
    NW(REGP(0,4),CW(0,REGP(0,4))) += 1;
    DELTA(REGP(0,4),CW(0,REGP(0,4))) = -1;
    
    // Process 0 END
    
    // Process 1 BEGIN
p1loop:
    /* assign */
    // Guess
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 1);
    // Update
    CREG(1,3) = new_cReg;
    REGP(1,3) = 0;
    
    /* assign */
    // Guess
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 1);
    // Update
    CREG(1,4) = new_cReg;
    REGP(1,4) = 1;
    
    /* ST */
    // Guess
    IW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(1,REGP(1,4));
    CW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(1,REGP(1,4))] == 1);
    ASSUME(IW(1,REGP(1,4)) >= max(CREG(1,3),CREG(1,4)));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(CW(1,REGP(1,4)) >= CL(1,r));
    }
    ASSUME(CW(1,REGP(1,4)) >= IW(1, REGP(1,4)));
    ASSUME(active[CW(1,REGP(1,4))] == 1);
    ASSUME(CW(1,REGP(1,4)) >= max(cDY[1],cISB[1]));
    ASSUME(CW(1,REGP(1,4)) >= max(cDS[1],cDL[1]));
    ASSUME(CW(1,REGP(1,4)) >= max(old_cW,CR(1,REGP(1,4))));
    ASSUME(CW(1,REGP(1,4)) >= ctrl[1]);
    ASSUME(CW(1,REGP(1,4)) >= cAddr[1]);
    // Update
    cAddr[1] = max(cAddr[1], CREG(1,4));
    MU(REGP(1,4),CW(1,REGP(1,4))) = REGP(1,3);
    NU(1,REGP(1,4)) = REGP(1,3);
    NW(REGP(1,4),CW(1,REGP(1,4))) += 1;
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
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 1);
    // Update
    CREG(1,4) = new_cReg;
    REGP(1,4) = 0;
    
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
    CREG(1,3) = CR(1,REGP(1,4));
    cAddr[1] = max(cAddr[1], CREG(1,4));
    if (CR(1,REGP(1,4)) < CW(1,REGP(1,4))) {
        REGP(1,3) = NU(1,REGP(1,4));
    } else {
        if (PW(1,REGP(1,4)) != NW(REGP(1,4),CR(1,REGP(1,4))))
            ASSUME(CR(1,REGP(1,4)) >= old_cR);
        REGP(1,3) = MU(REGP(1,4),CR(1,REGP(1,4)));
        PW(1,REGP(1,4)) = NW(REGP(1,4),CR(1,REGP(1,4)));
    }
    
    /* CBNZ */
    ctrl[1] = ctrl[1] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[1] < NCONTEXT);
    
    ASSUME(ctrl[1] >= CREG(1,3));
    if (REGP(1,3) != 0)
        goto p1loop;
    
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
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 1);
    // Update
    CREG(1,4) = new_cReg;
    REGP(1,4) = 1;
    
    /* assign */
    // Guess
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 1);
    // Update
    CREG(1,3) = new_cReg;
    REGP(1,3) = 1;
    
    /* ST */
    // Guess
    IW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(1,REGP(1,4));
    CW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(1,REGP(1,4))] == 1);
    ASSUME(IW(1,REGP(1,4)) >= max(CREG(1,3),CREG(1,4)));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(CW(1,REGP(1,4)) >= CL(1,r));
    }
    ASSUME(CW(1,REGP(1,4)) >= IW(1, REGP(1,4)));
    ASSUME(active[CW(1,REGP(1,4))] == 1);
    ASSUME(CW(1,REGP(1,4)) >= max(cDY[1],cISB[1]));
    ASSUME(CW(1,REGP(1,4)) >= max(cDS[1],cDL[1]));
    ASSUME(CW(1,REGP(1,4)) >= max(old_cW,CR(1,REGP(1,4))));
    ASSUME(CW(1,REGP(1,4)) >= ctrl[1]);
    ASSUME(CW(1,REGP(1,4)) >= cAddr[1]);
    // Update
    cAddr[1] = max(cAddr[1], CREG(1,4));
    MU(REGP(1,4),CW(1,REGP(1,4))) = REGP(1,3);
    NU(1,REGP(1,4)) = REGP(1,3);
    NW(REGP(1,4),CW(1,REGP(1,4))) += 1;
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
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 1);
    // Update
    CREG(1,4) = new_cReg;
    REGP(1,4) = 0;
    
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
    CREG(1,3) = CR(1,REGP(1,4));
    cAddr[1] = max(cAddr[1], CREG(1,4));
    if (CR(1,REGP(1,4)) < CW(1,REGP(1,4))) {
        REGP(1,3) = NU(1,REGP(1,4));
    } else {
        if (PW(1,REGP(1,4)) != NW(REGP(1,4),CR(1,REGP(1,4))))
            ASSUME(CR(1,REGP(1,4)) >= old_cR);
        REGP(1,3) = MU(REGP(1,4),CR(1,REGP(1,4)));
        PW(1,REGP(1,4)) = NW(REGP(1,4),CR(1,REGP(1,4)));
    }
    
    /* CBNZ */
    ctrl[1] = ctrl[1] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[1] < NCONTEXT);
    
    ASSUME(ctrl[1] >= CREG(1,3));
    if (REGP(1,3) != 0)
        goto p1loop;
    
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
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 1);
    // Update
    CREG(1,4) = new_cReg;
    REGP(1,4) = 2;
    
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
    CREG(1,3) = CR(1,REGP(1,4));
    cAddr[1] = max(cAddr[1], CREG(1,4));
    if (CR(1,REGP(1,4)) < CW(1,REGP(1,4))) {
        REGP(1,3) = NU(1,REGP(1,4));
    } else {
        if (PW(1,REGP(1,4)) != NW(REGP(1,4),CR(1,REGP(1,4))))
            ASSUME(CR(1,REGP(1,4)) >= old_cR);
        REGP(1,3) = MU(REGP(1,4),CR(1,REGP(1,4)));
        PW(1,REGP(1,4)) = NW(REGP(1,4),CR(1,REGP(1,4)));
    }
    
    /* assign */
    // Guess
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 1);
    ASSUME(new_cReg >= CREG(1,3));
    // Update
    CREG(1,3) = new_cReg;
    REGP(1,3) = (REGP(1,3) + 1);
    
    /* ST */
    // Guess
    IW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(1,REGP(1,4));
    CW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(1,REGP(1,4))] == 1);
    ASSUME(IW(1,REGP(1,4)) >= max(CREG(1,3),CREG(1,4)));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(CW(1,REGP(1,4)) >= CL(1,r));
    }
    ASSUME(CW(1,REGP(1,4)) >= IW(1, REGP(1,4)));
    ASSUME(active[CW(1,REGP(1,4))] == 1);
    ASSUME(CW(1,REGP(1,4)) >= max(cDY[1],cISB[1]));
    ASSUME(CW(1,REGP(1,4)) >= max(cDS[1],cDL[1]));
    ASSUME(CW(1,REGP(1,4)) >= max(old_cW,CR(1,REGP(1,4))));
    ASSUME(CW(1,REGP(1,4)) >= ctrl[1]);
    ASSUME(CW(1,REGP(1,4)) >= cAddr[1]);
    // Update
    cAddr[1] = max(cAddr[1], CREG(1,4));
    MU(REGP(1,4),CW(1,REGP(1,4))) = REGP(1,3);
    NU(1,REGP(1,4)) = REGP(1,3);
    NW(REGP(1,4),CW(1,REGP(1,4))) += 1;
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
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 1);
    // Update
    CREG(1,3) = new_cReg;
    REGP(1,3) = 0;
    
    /* assign */
    // Guess
    new_cReg = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[new_cReg] == 1);
    // Update
    CREG(1,4) = new_cReg;
    REGP(1,4) = 1;
    
    /* ST */
    // Guess
    IW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(1,REGP(1,4));
    CW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(active[IW(1,REGP(1,4))] == 1);
    ASSUME(IW(1,REGP(1,4)) >= max(CREG(1,3),CREG(1,4)));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(CW(1,REGP(1,4)) >= CL(1,r));
    }
    ASSUME(CW(1,REGP(1,4)) >= IW(1, REGP(1,4)));
    ASSUME(active[CW(1,REGP(1,4))] == 1);
    ASSUME(CW(1,REGP(1,4)) >= max(cDY[1],cISB[1]));
    ASSUME(CW(1,REGP(1,4)) >= max(cDS[1],cDL[1]));
    ASSUME(CW(1,REGP(1,4)) >= max(old_cW,CR(1,REGP(1,4))));
    ASSUME(CW(1,REGP(1,4)) >= ctrl[1]);
    ASSUME(CW(1,REGP(1,4)) >= cAddr[1]);
    // Update
    cAddr[1] = max(cAddr[1], CREG(1,4));
    MU(REGP(1,4),CW(1,REGP(1,4))) = REGP(1,3);
    NU(1,REGP(1,4)) = REGP(1,3);
    NW(REGP(1,4),CW(1,REGP(1,4))) += 1;
    DELTA(REGP(1,4),CW(1,REGP(1,4))) = -1;
    
    // Process 1 END
    
    /* verProc */
    for (int x = 0; x < ADDRSIZE; x++) {
        for (int k = 0; k < NCONTEXT-1; k++) {
            ASSUME(MU(x,k) == MUINIT(x,k+1));
            ASSUME(NW(x,k) == NWINIT(x,k+1));
            ASSUME(DELTA(x,k) == DELTAINIT(x,k+1));
        }
    }
    if (
        (MU(2,NCONTEXT-1) != 2) &&
    1)
        ASSERT(0);
    
    return 0;
}