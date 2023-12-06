#ifndef PHOTOSYNTHESIS_H
#define PHOTOSYNTHESIS_H

#include "common.h"

#define IR_RECEIVER_GPIO 23
#define IR_SEND_GPIO 24
#define LED_PIN 25

/*
광합성 기능(LED를 통한 광합성 기능)
by 정영한
*/
void *control_light(void *arg);

#endif