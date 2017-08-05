#ifndef ir_h
#define ir_h



void setIRTimer(long time);
long getIRTimer();
long timeLeft(long time);
void setIRThresh(int thresh);

int getIRThresh();


bool gateStop();

void getIRs();

int getIR(int IRNum);

#endif // !ir_h
