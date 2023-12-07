#include "rotatePot.h"
#include <wiringPi.h>
#include <stdio.h>

#define CW 0
#define CCW 1


int one_two_phase[8][4] 
= {{1, 0, 0, 0}, {1, 1, 0, 0},
{0, 1, 0, 0}, {0, 1, 1, 0},
{0, 0, 1, 0}, {0, 0, 1, 1},
{0, 0, 0, 1}, {1, 0, 0, 1}};


void init_Step() {
    for(int i = 0; i< 4; i++){
        pinMode(GPIO_ARR[i], OUTPUT);
    }
}

void one_two_Phase_Rotate_Angle() {
    printf("angle = %d\n", angle);

    int steps = (4096 * 10) / 360;
   
    if(direction == 0) { // CW

        if(angle < 180) {
            for(int i = 0; i < steps; i++) {
                digitalWrite(GPIO_ARR[3], one_two_phase[i%8][0]);
                digitalWrite(GPIO_ARR[2], one_two_phase[i%8][1]);
                digitalWrite(GPIO_ARR[1], one_two_phase[i%8][2]);
                digitalWrite(GPIO_ARR[0], one_two_phase[i%8][3]);
                delay(2);
            }
            angle += 10;
        }
        else {
            direction = CCW;
        }
    } else if(direction == 1) { // CCW

        if(angle > -180) {
            for(int i = 0; i < steps; i++) {
                digitalWrite(GPIO_ARR[0], one_two_phase[i%8][0]);
                digitalWrite(GPIO_ARR[1], one_two_phase[i%8][1]);
                digitalWrite(GPIO_ARR[2], one_two_phase[i%8][2]);
                digitalWrite(GPIO_ARR[3], one_two_phase[i%8][3]);
                delay(2);
            }
            angle -= 10;
        }
        else {
            direction = CW;
        }
    }
}

/*
화분 회전 기능(빛이 골고루 닿을 수 있도록 화분을 회전하는 기능)
*/
void* rotate_pot(void* arg){
    // RTC 모듈에 의해 호출됨
    wiringPiSetupGpio();
    init_Step();
    
    one_two_Phase_Rotate_Angle();
}