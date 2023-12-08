#ifndef TEMP_HUMID_SENSOR_H
#define TEMP_HUMID_SENSOR_H

#include "common.h"
#include <stdlib.h> //표준 유틸리티용 라이브러리
#include <stdint.h> //정수 자료형 라이브러리

#define DHT_DATA_GPIO 4 // 온습도 센서의 데이터 핀
#define MAX_TIMINGS	85 // 최대 신호 추출 개수

/*
온습도 센서(온도, 습도 반환 기능)
- 모니터링 기능에서 사용됨
by 조우성
*/
void *syncTempHumidInfo(void *arg); // 특정 주기 마다 common.h의 tempHumidInfo 값을 갱신하는 방식으로 바꿔야 함.
void readDHTInfo(); // 온습도 센서의 정보를 받아옴
#endif