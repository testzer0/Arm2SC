#define NREGS 16
#define ADDRSIZE 64
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
int ctrl[NPROC], active[NCONTEXT], cnt;
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
                DELTAINIT(x,k) = -1;
                DELTA(x,k) = -1;
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
    REGP(0,2) = 1;
    REGP(0,3) = 0;
    REGP(1,2) = 1;
    REGP(2,2) = 0;
    REGP(2,3) = 1;
    cnt = 0;
    
    // Process 0 BEGIN
    cnt = get_rng(0,NCONTEXT-1);
    ASSUME(active[cnt] == 0);
    
    /* assign */
    // Guess
    IREG(0,4) = get_rng(0,NCONTEXT-1);
    CREG(0,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IREG(0,4) >= cnt);
    ASSUME(active[IREG(0,4)] == 0);
    ASSUME(active[CREG(0,4)] == 0);
    ASSUME(CREG(0,4) >= max(ctrl[0],IREG(0,4)));
    // Update
    REGP(0,4) = 1;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    ASSUME(active[cnt] == 0);
    
    /* ST */
    // Guess
    IW(0,REGP(0,2)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(0,REGP(0,2));
    CW(0,REGP(0,2)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IW(0,REGP(0,2)) >= cnt);
    ASSUME(active[IW(0,REGP(0,2))] == 0);
    ASSUME(IW(0,REGP(0,2)) >= max(IREG(0,4),IREG(0,2)));
    ASSUME(IW(0,REGP(0,2)) >= max(cDY[0],cISB[0]));
    ASSUME(IW(0,REGP(0,2)) >= max(cDS[0],cDL[0]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(0,REGP(0,2)) >= CL(0,r));
    }
    ASSUME(CW(0,REGP(0,2)) >= IW(0, REGP(0,2)));
    ASSUME(active[CW(0,REGP(0,2))] == 0);
    ASSUME(CW(0,REGP(0,2)) >= max(CREG(0,4),IREG(0,2)));
    ASSUME(CW(0,REGP(0,2)) >= max(old_cW,CR(0,REGP(0,2))));
    ASSUME(CW(0,REGP(0,2)) >= ctrl[0]);
    ASSUME(CW(0,REGP(0,2)) >= iAddr[0]);
    // Update
    iAddr[0] = max(iAddr[0], IREG(0,2));
    MU(REGP(0,2),CW(0,REGP(0,2))) = REGP(0,4);
    NU(0,REGP(0,2)) = REGP(0,4);
    DELTA(REGP(0,2),CW(0,REGP(0,2))) = -1;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    ASSUME(active[cnt] == 0);
    
    /* assign */
    // Guess
    IREG(0,5) = get_rng(0,NCONTEXT-1);
    CREG(0,5) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IREG(0,5) >= cnt);
    ASSUME(active[IREG(0,5)] == 0);
    ASSUME(active[CREG(0,5)] == 0);
    ASSUME(CREG(0,5) >= max(ctrl[0],IREG(0,5)));
    // Update
    REGP(0,5) = 2;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    ASSUME(active[cnt] == 0);
    
    /* ST */
    // Guess
    IW(0,REGP(0,2)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(0,REGP(0,2));
    CW(0,REGP(0,2)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IW(0,REGP(0,2)) >= cnt);
    ASSUME(active[IW(0,REGP(0,2))] == 0);
    ASSUME(IW(0,REGP(0,2)) >= max(IREG(0,5),IREG(0,2)));
    ASSUME(IW(0,REGP(0,2)) >= max(cDY[0],cISB[0]));
    ASSUME(IW(0,REGP(0,2)) >= max(cDS[0],cDL[0]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(0,REGP(0,2)) >= CL(0,r));
    }
    ASSUME(CW(0,REGP(0,2)) >= IW(0, REGP(0,2)));
    ASSUME(active[CW(0,REGP(0,2))] == 0);
    ASSUME(CW(0,REGP(0,2)) >= max(CREG(0,5),IREG(0,2)));
    ASSUME(CW(0,REGP(0,2)) >= max(old_cW,CR(0,REGP(0,2))));
    ASSUME(CW(0,REGP(0,2)) >= ctrl[0]);
    ASSUME(CW(0,REGP(0,2)) >= iAddr[0]);
    // Update
    iAddr[0] = max(iAddr[0], IREG(0,2));
    MU(REGP(0,2),CW(0,REGP(0,2))) = REGP(0,5);
    NU(0,REGP(0,2)) = REGP(0,5);
    DELTA(REGP(0,2),CW(0,REGP(0,2))) = -1;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    ASSUME(active[cnt] == 0);
    
    /* dmb.sy */
    // Guess
    old_cDY = cDY[0];
    cDY[0] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cDY[0] >= max(cnt, old_cDY));
    ASSUME(cDY[0] >= max(cISB[0],cDL[0]));
    ASSUME(cDY[0] >= max(cDS[0],ctrl[0]));
    for (int x = 0; x < ADDRSIZE; x++) {
        ASSUME(cDY[0] >= CW(0,x));
        ASSUME(cDY[0] >= CR(0,x));
    }
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    ASSUME(active[cnt] == 0);
    
    /* assign */
    // Guess
    IREG(0,6) = get_rng(0,NCONTEXT-1);
    CREG(0,6) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IREG(0,6) >= cnt);
    ASSUME(active[IREG(0,6)] == 0);
    ASSUME(active[CREG(0,6)] == 0);
    ASSUME(CREG(0,6) >= max(ctrl[0],IREG(0,6)));
    // Update
    REGP(0,6) = 1;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    ASSUME(active[cnt] == 0);
    
    /* ST */
    // Guess
    IW(0,REGP(0,3)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(0,REGP(0,3));
    CW(0,REGP(0,3)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IW(0,REGP(0,3)) >= cnt);
    ASSUME(active[IW(0,REGP(0,3))] == 0);
    ASSUME(IW(0,REGP(0,3)) >= max(IREG(0,6),IREG(0,3)));
    ASSUME(IW(0,REGP(0,3)) >= max(cDY[0],cISB[0]));
    ASSUME(IW(0,REGP(0,3)) >= max(cDS[0],cDL[0]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(0,REGP(0,3)) >= CL(0,r));
    }
    ASSUME(CW(0,REGP(0,3)) >= IW(0, REGP(0,3)));
    ASSUME(active[CW(0,REGP(0,3))] == 0);
    ASSUME(CW(0,REGP(0,3)) >= max(CREG(0,6),IREG(0,3)));
    ASSUME(CW(0,REGP(0,3)) >= max(old_cW,CR(0,REGP(0,3))));
    ASSUME(CW(0,REGP(0,3)) >= ctrl[0]);
    ASSUME(CW(0,REGP(0,3)) >= iAddr[0]);
    // Update
    iAddr[0] = max(iAddr[0], IREG(0,3));
    MU(REGP(0,3),CW(0,REGP(0,3))) = REGP(0,6);
    NU(0,REGP(0,3)) = REGP(0,6);
    DELTA(REGP(0,3),CW(0,REGP(0,3))) = -1;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    // Process 0 END
    
    // Process 1 BEGIN
    cnt = get_rng(0,NCONTEXT-1);
    ASSUME(active[cnt] == 1);
    
    /* LD */
    // Guess
    IR(1,REGP(1,2)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(1,REGP(1,2));
    CR(1,REGP(1,2)) = get_rng(0,NCONTEXT-1);
    IREG(1,3) = IR(1,REGP(1,2));
    CREG(1,3) = CR(1,REGP(1,2));
    // Check
    ASSUME(IR(1,REGP(1,2)) >= cnt);
    ASSUME(active[IR(1,REGP(1,2))] == 1);
    ASSUME(IR(1,REGP(1,2)) >= IW(1,REGP(1,2)));
    ASSUME(IR(1,REGP(1,2)) >= IREG(1,2));
    ASSUME(IR(1,REGP(1,2)) >= max(cDY[1],cISB[1]));
    ASSUME(IR(1,REGP(1,2)) >= cDL[1]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(1,REGP(1,2)) >= IL(1,rdp));
    }
    ASSUME(CR(1,REGP(1,2)) >= IR(1, REGP(1,2)));
    ASSUME(active[CR(1,REGP(1,2))] == 1);
    ASSUME(CR(1,REGP(1,2)) >= max(IREG(1,2),ctrl[1]));
    ASSUME(CR(1,REGP(1,2)) >= max(old_cR,CW(1,REGP(1,2))));
    // Update
    iAddr[1] = max(iAddr[1], IREG(1,2));
    if (IR(1,REGP(1,2)) < CW(1,REGP(1,2))) {
        REGP(1,3) = NU(1,REGP(1,2));
    } else {
        REGP(1,3) = MU(REGP(1,2),IR(1,REGP(1,2)));
    }
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    // Process 1 END
    
    // Process 2 BEGIN
    cnt = get_rng(0,NCONTEXT-1);
    ASSUME(active[cnt] == 2);
    
    /* LD */
    // Guess
    IR(2,REGP(2,2)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(2,REGP(2,2));
    CR(2,REGP(2,2)) = get_rng(0,NCONTEXT-1);
    IREG(2,4) = IR(2,REGP(2,2));
    CREG(2,4) = CR(2,REGP(2,2));
    // Check
    ASSUME(IR(2,REGP(2,2)) >= cnt);
    ASSUME(active[IR(2,REGP(2,2))] == 2);
    ASSUME(IR(2,REGP(2,2)) >= IW(2,REGP(2,2)));
    ASSUME(IR(2,REGP(2,2)) >= IREG(2,2));
    ASSUME(IR(2,REGP(2,2)) >= max(cDY[2],cISB[2]));
    ASSUME(IR(2,REGP(2,2)) >= cDL[2]);
    for (int rdp = 0; rdp < NREGS; rdp++) {
        ASSUME(IR(2,REGP(2,2)) >= IL(2,rdp));
    }
    ASSUME(CR(2,REGP(2,2)) >= IR(2, REGP(2,2)));
    ASSUME(active[CR(2,REGP(2,2))] == 2);
    ASSUME(CR(2,REGP(2,2)) >= max(IREG(2,2),ctrl[2]));
    ASSUME(CR(2,REGP(2,2)) >= max(old_cR,CW(2,REGP(2,2))));
    // Update
    iAddr[2] = max(iAddr[2], IREG(2,2));
    if (IR(2,REGP(2,2)) < CW(2,REGP(2,2))) {
        REGP(2,4) = NU(2,REGP(2,2));
    } else {
        REGP(2,4) = MU(REGP(2,2),IR(2,REGP(2,2)));
    }
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    /* CBNZ */
    ctrl[2] = ctrl[2] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[2] < NCONTEXT);
    
    ASSUME(ctrl[2] >= IREG(2,4));
    if (REG(2,4) != 0)
        goto LC00;
    
LC00:
    ASSUME(active[cnt] == 2);
    
    /* isb */
    // Guess
    cISB[2] = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(cISB[2] >= max(cnt, cDY[2]));
    ASSUME(cISB[2] >= ctrl[2]);
    ASSUME(cISB[2] >= iAddr[2]);
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    ASSUME(active[cnt] == 2);
    
    /* LD */
    // Guess
    IR(2,REGP(2,3)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(2,REGP(2,3));
    CR(2,REGP(2,3)) = get_rng(0,NCONTEXT-1);
    IREG(2,5) = IR(2,REGP(2,3));
    CREG(2,5) = CR(2,REGP(2,3));
    // Check
    ASSUME(IR(2,REGP(2,3)) >= cnt);
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
        REGP(2,5) = NU(2,REGP(2,3));
    } else {
        REGP(2,5) = MU(REGP(2,3),IR(2,REGP(2,3)));
    }
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    // Process 2 END
    
    /* verProc */
    for (int x = 0; x < ADDRSIZE; x++) {
        for (int k = 0; k < NCONTEXT-1; k++) {
            ASSUME(MU(x,k) == MUINIT(x,k+1));
            ASSUME(DELTA(x,k) == DELTAINIT(x,k+1));
        }
    }
    if (
        (MU(1,NCONTEXT-1) == 2) &&
        (REGP(1,3) == 1) &&
        (REGP(2,4) == 1) &&
        (REGP(2,5) == 0) &&
    1)
        ASSERT(0);
    
    return 0;
}