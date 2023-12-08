#include "rotatePot.h"


#define CW 0
#define CCW 1

int steps = (4096 * 10) / 360;


int one_two_phase[8][4] 
= {{1, 0, 0, 0}, {1, 1, 0, 0},
{0, 1, 0, 0}, {0, 1, 1, 0},
{0, 0, 1, 0}, {0, 0, 1, 1},
{0, 0, 0, 1}, {1, 0, 0, 1}};


void init_step() {
    for(int i = 0; i< 4; i++){
        pinMode(GPIO_ARR[i], OUTPUT);
    }
}

void rotate_cw() {
    for(int i = 0; i < steps; i++) {
        digitalWrite(GPIO_ARR[3], one_two_phase[i%8][0]);
        digitalWrite(GPIO_ARR[2], one_two_phase[i%8][1]);
        digitalWrite(GPIO_ARR[1], one_two_phase[i%8][2]);
        digitalWrite(GPIO_ARR[0], one_two_phase[i%8][3]);
        delay(2);
    }
}

void rotate_ccw() {
    for(int i = 0; i < steps; i++) {
        digitalWrite(GPIO_ARR[0], one_two_phase[i%8][0]);
        digitalWrite(GPIO_ARR[1], one_two_phase[i%8][1]);
        digitalWrite(GPIO_ARR[2], one_two_phase[i%8][2]);
        digitalWrite(GPIO_ARR[3], one_two_phase[i%8][3]);
        delay(2);
    }
}

void one_two_phase_rotate_angle() {
    printf("angle = %d\n", angle);

    
   
    if(direction == 0) { // CW

        if(angle < 180) {
            rotate_cw();
            angle += 10;
        }
        else {
            direction = CCW;
            rotate_ccw();
            angle -= 10;
        }
    } else if(direction == 1) { // CCW

        if(angle > -180) {
            rotate_ccw();
            angle -= 10;
        }
        else {
            direction = CW;
            rotate_cw();
            angle += 10;
        }
    }
}

/*
화분 회전 기능(빛이 골고루 닿을 수 있도록 화분을 회전하는 기능)
*/
void* rotate_pot(void* arg){
    // RTC 모듈에 의해 호출됨
    wiringPiSetupGpio();
    init_step();
    
    one_two_phase_rotate_angle();
}