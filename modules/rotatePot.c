#include "../libs/rotatePot.h"

extern ClimateData temp_humid_info; // 온습도 정보
extern time_t current_time;       // 현재 시각
extern float soil_moisture;       // 토양 수분
extern pthread_mutex_t mtx_temp_humid_info;  // 온습도 정보를 보호하기 위한 뮤텍스
extern pthread_mutex_t mtx_current_time;  // 현재 시각을 보호하기 위한 뮤텍스
extern pthread_mutex_t mtx_soil_moisture; // 토양 수분을 보호하기 위한 뮤텍스

int steps = (4096 * 10) / 360;

int one_two_phase[8][4] = {{1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}, {1, 0, 0, 1}};

void initStep()
{
    for (int i = 0; i < 4; i++)
    {
        pinMode(GPIO_ARR[i], OUTPUT);
    }
}

void rotateCw()
{
    for (int i = 0; i < steps; i++)
    {
        digitalWrite(GPIO_ARR[3], one_two_phase[i % 8][0]);
        digitalWrite(GPIO_ARR[2], one_two_phase[i % 8][1]);
        digitalWrite(GPIO_ARR[1], one_two_phase[i % 8][2]);
        digitalWrite(GPIO_ARR[0], one_two_phase[i % 8][3]);
        delay(2);
    }
}

void rotateCcw()
{
    for (int i = 0; i < steps; i++)
    {
        digitalWrite(GPIO_ARR[0], one_two_phase[i % 8][0]);
        digitalWrite(GPIO_ARR[1], one_two_phase[i % 8][1]);
        digitalWrite(GPIO_ARR[2], one_two_phase[i % 8][2]);
        digitalWrite(GPIO_ARR[3], one_two_phase[i % 8][3]);
        delay(2);
    }
}

void oneTwoPhaseRotateAngle()
{
    printf("angle = %d\n", angle);

    if (direction == CW)
    { // CW

        if (angle < 180)
        {
            rotateCw();
            angle += 10;
        }
        else
        {
            direction = CCW;
            rotateCcw();
            angle -= 10;
        }
    }
    else if (direction == CCW)
    { // CCW

        if (angle > -180)
        {
            rotateCcw();
            angle -= 10;
        }
        else
        {
            direction = CW;
            rotateCw();
            angle += 10;
        }
    }
}

/*
화분 회전 기능(빛이 골고루 닿을 수 있도록 화분을 회전하는 기능)
*/
void *rotatePot(void *arg)
{
    // RTC 모듈에 의해 호출됨
    // wiringPiSetupGpio();
    initStep();

    oneTwoPhaseRotateAngle();
}