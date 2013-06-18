
#include "MouseTool.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
//#include <unistd.h>
#ifdef __WIN32__
#define sleep(ms) Sleep(ms*1000)
#define usleep(ms) Sleep(ms);
#endif 

int main(int argc, char* argv[]){
    MouseTool t;
 
    sleep(5);
    int x, y, state;
    state = t.GetMouseState(&x, &y);
    printf("X: %d, Y: %d LButton is %s... %d\n", x, y, (state & MT_LBUTTON)?"DOWN":"UP", state);
    return 0;
}
