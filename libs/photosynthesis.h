#ifndef PHOTOSYNTHESIS_H
#define PHOTOSYNTHESIS_H

#include "common.h"

#define REMOTE_CONTROLLER_GPIO 1
#define LED_GPIO 1

/*
광합성 기능(LED를 통한 광합성 기능)
by 정영한
*/
void* control_light(void* arg);

#endif