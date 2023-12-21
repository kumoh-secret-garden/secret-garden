#ifndef PHOTOSYNTHESIS_H
#define PHOTOSYNTHESIS_H

#include "../common.h"
#include <stdlib.h>
#include <softPwm.h>
#include <lirc/lirc_client.h> // 빌드 시 `-llirc_client` 필요

#define IR_RECEIVER_GPIO 23
#define LED_PIN 24
#define LED_PIN2 25
#define MAX_BRIGHTNESS 100

/*
광합성 기능(LED를 통한 광합성 기능)
by 이지현
*/
void *controlLight(void *arg);

#endif