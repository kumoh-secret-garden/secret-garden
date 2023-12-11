#ifndef ROTATEPOT_H
#define ROTATEPOT_H

#include "../common.h"

#define CW 0
#define CCW 1

/*
핀 번호 배열
*/
static const int GPIO_ARR[4] = {12, 16, 20, 21};
static int angle = 0;
static int direction = 0;

/*
화분 회전 기능(빛이 골고루 닿을 수 있도록 화분을 회전하는 기능)
by 정영한
*/
void *rotate_pot(void *arg);

#endif
