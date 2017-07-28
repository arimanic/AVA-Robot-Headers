#ifndef ringControl_h
#define ringControl_h

int findCross(int crossNum);
void setCrossPos(int newPos);
void setTargetPos(int pos);
int getTargetPos();
bool moveToPos(int targetPos);
void toysInWater(double curTime);

void fullCircleMove();

int getCrossPos();

int findNextToy(int pos, double curTime);



#endif // !ringControl_h

