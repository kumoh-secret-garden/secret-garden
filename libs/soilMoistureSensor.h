#ifndef SOIL_MOISTURE_SENSOR_H
#define SOIL_MOISTURE_SENSOR_H

#include "common.h"

#define SOIL_MOISTURE_GPIO 17 // 실제로 토양 수분 센서의 데이터 핀이 연결된 GPIO 핀 번호

/*
현재 토양 속 수분값을 받아오는 함수
- 모니터링 기능에서 사용됨
- 블루투스 모듈에서 호출됨
by 정연준
*/
float getSoilMoisture();

#endif