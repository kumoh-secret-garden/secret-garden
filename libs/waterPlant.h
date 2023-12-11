#ifndef WATER_PLANT_H
#define WATER_PLANT_H

#include "../common.h"
#include <stdio.h>
#include <unistd.h>
#include <wiringPiI2C.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define SOIL_MOISTURE_GPIO 17 // 실제로 토양 수분 센서의 데이터 핀이 연결된 GPIO 핀 번호
#define WATER_PUMP_PIN 27     // 실제로 워터 펌프의 제어 핀이 연결된 GPIO 핀 번호
#define SLAVE_ADDR 0x48
#define I2C_DEV "/dev/i2c-1"
#define ADC_CHANNEL 2

/*
물주기 기능(토양의 수분을 측정한 물주기 기능)
by 정연준
*/
void *water_plant(void *arg);

#endif