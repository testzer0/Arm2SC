#define NREGS 4
#define ADDRSIZE 2
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
    REGP(0,4) = 0;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
loop:
    ASSUME(active[cnt] == 0);
    
    /* LD */
    // Guess
    IR(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(0,REGP(0,4));
    CR(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    IREG(0,3) = IR(0,REGP(0,4));
    CREG(0,3) = CR(0,REGP(0,4));
    // Check
    ASSUME(IR(0,REGP(0,4)) >= cnt);
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
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    /* CBNZ */
    ctrl[0] = ctrl[0] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[0] < NCONTEXT);
    
    ASSUME(ctrl[0] >= IREG(0,3));
    if (REG(0,3) != 0)
        goto loop;
    
    ASSUME(active[cnt] == 0);
    
    /* assign */
    // Guess
    IREG(0,3) = get_rng(0,NCONTEXT-1);
    CREG(0,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IREG(0,3) >= cnt);
    ASSUME(active[IREG(0,3)] == 0);
    ASSUME(active[CREG(0,3)] == 0);
    ASSUME(CREG(0,3) >= max(ctrl[0],IREG(0,3)));
    // Update
    REGP(0,3) = 1;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    ASSUME(active[cnt] == 0);
    
    /* ST */
    // Guess
    IW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(0,REGP(0,4));
    CW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IW(0,REGP(0,4)) >= cnt);
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
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
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
    
    /* LD */
    // Guess
    IR(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(0,REGP(0,4));
    CR(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    IREG(0,3) = IR(0,REGP(0,4));
    CREG(0,3) = CR(0,REGP(0,4));
    // Check
    ASSUME(IR(0,REGP(0,4)) >= cnt);
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
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    ASSUME(active[cnt] == 0);
    
    /* ST */
    // Guess
    IW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(0,REGP(0,4));
    CW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IW(0,REGP(0,4)) >= cnt);
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
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    ASSUME(active[cnt] == 0);
    
    /* assign */
    // Guess
    IREG(0,3) = get_rng(0,NCONTEXT-1);
    CREG(0,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IREG(0,3) >= cnt);
    ASSUME(active[IREG(0,3)] == 0);
    ASSUME(active[CREG(0,3)] == 0);
    ASSUME(CREG(0,3) >= max(ctrl[0],IREG(0,3)));
    // Update
    REGP(0,3) = 0;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
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
    REGP(0,4) = 0;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    ASSUME(active[cnt] == 0);
    
    /* ST */
    // Guess
    IW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(0,REGP(0,4));
    CW(0,REGP(0,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IW(0,REGP(0,4)) >= cnt);
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
    REGP(1,4) = 0;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
loop:
    ASSUME(active[cnt] == 1);
    
    /* LD */
    // Guess
    IR(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(1,REGP(1,4));
    CR(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    IREG(1,3) = IR(1,REGP(1,4));
    CREG(1,3) = CR(1,REGP(1,4));
    // Check
    ASSUME(IR(1,REGP(1,4)) >= cnt);
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
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    /* CBNZ */
    ctrl[1] = ctrl[1] + get_rng(0,NCONTEXT-1);
    ASSUME(ctrl[1] < NCONTEXT);
    
    ASSUME(ctrl[1] >= IREG(1,3));
    if (REG(1,3) != 0)
        goto loop;
    
    ASSUME(active[cnt] == 1);
    
    /* assign */
    // Guess
    IREG(1,3) = get_rng(0,NCONTEXT-1);
    CREG(1,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IREG(1,3) >= cnt);
    ASSUME(active[IREG(1,3)] == 1);
    ASSUME(active[CREG(1,3)] == 1);
    ASSUME(CREG(1,3) >= max(ctrl[1],IREG(1,3)));
    // Update
    REGP(1,3) = 2;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    ASSUME(active[cnt] == 1);
    
    /* ST */
    // Guess
    IW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(1,REGP(1,4));
    CW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IW(1,REGP(1,4)) >= cnt);
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
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
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
    REGP(1,4) = 1;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    ASSUME(active[cnt] == 1);
    
    /* LD */
    // Guess
    IR(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cR = CR(1,REGP(1,4));
    CR(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    IREG(1,3) = IR(1,REGP(1,4));
    CREG(1,3) = CR(1,REGP(1,4));
    // Check
    ASSUME(IR(1,REGP(1,4)) >= cnt);
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
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    ASSUME(active[cnt] == 1);
    
    /* ST */
    // Guess
    IW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(1,REGP(1,4));
    CW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IW(1,REGP(1,4)) >= cnt);
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
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    ASSUME(active[cnt] == 1);
    
    /* assign */
    // Guess
    IREG(1,3) = get_rng(0,NCONTEXT-1);
    CREG(1,3) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IREG(1,3) >= cnt);
    ASSUME(active[IREG(1,3)] == 1);
    ASSUME(active[CREG(1,3)] == 1);
    ASSUME(CREG(1,3) >= max(ctrl[1],IREG(1,3)));
    // Update
    REGP(1,3) = 0;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
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
    REGP(1,4) = 0;
    
    cnt = cnt + get_rng(0,NCONTEXT-1);
    ASSUME(cnt < NCONTEXT);
    
    ASSUME(active[cnt] == 1);
    
    /* ST */
    // Guess
    IW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    old_cW = CW(1,REGP(1,4));
    CW(1,REGP(1,4)) = get_rng(0,NCONTEXT-1);
    // Check
    ASSUME(IW(1,REGP(1,4)) >= cnt);
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
        (MU(1,NCONTEXT-1) != 2) &&
    1)
        ASSERT(0);
    
    return 0;
}