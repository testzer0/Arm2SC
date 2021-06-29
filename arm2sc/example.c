#define NREGS 16
#define ADDRSIZE 64
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
    // any initial memory values here
    // register initial values
    REGP(0,2) = 1;
    REGP(0,3) = 0;
    REGP(1,2) = 0;
    REGP(1,3) = 1;
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
    REGP(0,4) = 2;
    
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
    REGP(0,5) = 1;
    
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
    ASSUME(IW(0,REGP(0,3)) >= max(IREG(0,5),IREG(0,3)));
    ASSUME(IW(0,REGP(0,3)) >= max(cDY[0],cISB[0]));
    ASSUME(IW(0,REGP(0,3)) >= max(cDS[0],cDL[0]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(0,REGP(0,3)) >= CL(0,r));
    }
    ASSUME(CW(0,REGP(0,3)) >= IW(0, REGP(0,3)));
    ASSUME(active[CW(0,REGP(0,3))] == 0);
    ASSUME(CW(0,REGP(0,3)) >= max(CREG(0,5),IREG(0,3)));
    ASSUME(CW(0,REGP(0,3)) >= max(old_cW,CR(0,REGP(0,3))));
    ASSUME(CW(0,REGP(0,3)) >= ctrl[0]);
    ASSUME(CW(0,REGP(0,3)) >= iAddr[0]);
    // Update
    iAddr[0] = max(iAddr[0], IREG(0,3));
    MU(REGP(0,3),CW(0,REGP(0,3))) = REGP(0,5);
    NU(0,REGP(0,3)) = REGP(0,5);
    DELTA(REGP(0,3),CW(0,REGP(0,3))) = -1;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    // Process 0 END
    
    // Process 1 BEGIN
    cnt = get_rng(0,NCONTEXT-1);
    ASSUME(active[cnt] == 1);
    
    /* assign */
    // Guess
    IREG(1,4) = get_rng(0,NCONTEXT-1);
    CREG(1,4) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IREG(1,4) >= cnt);
    ASSUME(active[IREG(1,4)] == 1);
    ASSUME(active[CREG(1,4)] == 1);
    ASSUME(CREG(1,4) >= max(ctrl[1],IREG(1,4)));
    // Update
    REGP(1,4) = 2;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    ASSUME(active[cnt] == 1);
    
    /* ST */
    // Guess
    IW(1,REGP(1,2)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(1,REGP(1,2));
    CW(1,REGP(1,2)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IW(1,REGP(1,2)) >= cnt);
    ASSUME(active[IW(1,REGP(1,2))] == 1);
    ASSUME(IW(1,REGP(1,2)) >= max(IREG(1,4),IREG(1,2)));
    ASSUME(IW(1,REGP(1,2)) >= max(cDY[1],cISB[1]));
    ASSUME(IW(1,REGP(1,2)) >= max(cDS[1],cDL[1]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(1,REGP(1,2)) >= CL(1,r));
    }
    ASSUME(CW(1,REGP(1,2)) >= IW(1, REGP(1,2)));
    ASSUME(active[CW(1,REGP(1,2))] == 1);
    ASSUME(CW(1,REGP(1,2)) >= max(CREG(1,4),IREG(1,2)));
    ASSUME(CW(1,REGP(1,2)) >= max(old_cW,CR(1,REGP(1,2))));
    ASSUME(CW(1,REGP(1,2)) >= ctrl[1]);
    ASSUME(CW(1,REGP(1,2)) >= iAddr[1]);
    // Update
    iAddr[1] = max(iAddr[1], IREG(1,2));
    MU(REGP(1,2),CW(1,REGP(1,2))) = REGP(1,4);
    NU(1,REGP(1,2)) = REGP(1,4);
    DELTA(REGP(1,2),CW(1,REGP(1,2))) = -1;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    ASSUME(active[cnt] == 1);
    
    /* assign */
    // Guess
    IREG(1,5) = get_rng(0,NCONTEXT-1);
    CREG(1,5) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IREG(1,5) >= cnt);
    ASSUME(active[IREG(1,5)] == 1);
    ASSUME(active[CREG(1,5)] == 1);
    ASSUME(CREG(1,5) >= max(ctrl[1],IREG(1,5)));
    // Update
    REGP(1,5) = 1;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    ASSUME(active[cnt] == 1);
    
    /* ST */
    // Guess
    IW(1,REGP(1,3)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(1,REGP(1,3));
    CW(1,REGP(1,3)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IW(1,REGP(1,3)) >= cnt);
    ASSUME(active[IW(1,REGP(1,3))] == 1);
    ASSUME(IW(1,REGP(1,3)) >= max(IREG(1,5),IREG(1,3)));
    ASSUME(IW(1,REGP(1,3)) >= max(cDY[1],cISB[1]));
    ASSUME(IW(1,REGP(1,3)) >= max(cDS[1],cDL[1]));
    for (int r = 0; r < NREGS; r++) {
        ASSUME(IW(1,REGP(1,3)) >= CL(1,r));
    }
    ASSUME(CW(1,REGP(1,3)) >= IW(1, REGP(1,3)));
    ASSUME(active[CW(1,REGP(1,3))] == 1);
    ASSUME(CW(1,REGP(1,3)) >= max(CREG(1,5),IREG(1,3)));
    ASSUME(CW(1,REGP(1,3)) >= max(old_cW,CR(1,REGP(1,3))));
    ASSUME(CW(1,REGP(1,3)) >= ctrl[1]);
    ASSUME(CW(1,REGP(1,3)) >= iAddr[1]);
    // Update
    iAddr[1] = max(iAddr[1], IREG(1,3));
    MU(REGP(1,3),CW(1,REGP(1,3))) = REGP(1,5);
    NU(1,REGP(1,3)) = REGP(1,5);
    DELTA(REGP(1,3),CW(1,REGP(1,3))) = -1;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    // Process 1 END
    
    /* verProc */
    for (int x = 0; x < ADDRSIZE; x++) {
        for (int k = 0; k < NCONTEXT-1; k++) {
            ASSUME(MU(x,k) == MUINIT(x,k+1));
            ASSUME(DELTA(x,k) == DELTAINIT(x,k+1));
        }
    }
    if (
        (MU(1,NCONTEXT-1) == 2) &&
        (MU(0,NCONTEXT-1) == 2) &&
    1)
        ASSERT(0);
    
    return 0;
}