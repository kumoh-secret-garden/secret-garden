#ifndef TEMP_HUMID_SENSOR_H
#define TEMP_HUMID_SENSOR_H

#include "common.h"

#define DHT_DATA_GPIO 4 // 실제로 온습도 센서의 데이터 핀

/*
온습도 센서(온도, 습도 반환 기능)
- 모니터링 기능에서 사용됨
by 조우성
*/
void *read_dht_data(void *arg);

#endif