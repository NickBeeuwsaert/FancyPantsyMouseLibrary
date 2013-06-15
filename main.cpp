
#include "MouseTool.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[]){
    MouseTool t;
    /*for(int i = 0; i < 1024; i++){
        t.WarpPointer(i,(sin(i/50.0f)*50.0f));
        usleep(1000);
    }*/
    sleep(5);
    int x, y, state;
    state = t.GetMouseState(&x, &y);
    printf("X: %d, Y: %d LButton is %s\n", x, y, (state & MT_LBUTTON)?"DOWN":"UP");
    return 0;
}
