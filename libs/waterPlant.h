#ifndef WATER_PLANT_H
#define WATER_PLANT_H

#include "common.h"

#define SOIL_MOISTURE_GPIO 17 // 실제로 토양 수분 센서의 데이터 핀이 연결된 GPIO 핀 번호
#define WATER_PUMP_PIN 27     // 실제로 워터 펌프의 제어 핀이 연결된 GPIO 핀 번호

/*
물주기 기능(토양의 수분을 측정한 물주기 기능)
by 정연준
*/
void *water_plant(void *arg);

#endif