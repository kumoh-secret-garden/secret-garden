#ifndef ROTATEPOT_H
#define ROTATEPOT_H

#include "common.h"

/*
핀 번호 배열
*/
static const int PIN_ARR[4] = {1, 1, 1, 1};

/*
화분 회전 기능(빛이 골고루 닿을 수 있도록 화분을 회전하는 기능)
*/
void* rotate_pot(void* arg);

#endif
