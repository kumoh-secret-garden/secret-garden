#ifndef TEMP_HUMID_SENSOR_H
#define TEMP_HUMID_SENSOR_H

#include "common.h"

#define DHT_DATA_GPIO 17 // 실제로 온습도 센서의 데이터 핀

typedef struct
{
    float temperature;
    float humidity;
} ClimateData;

/*
온습도 센서(온도, 습도 반환 기능)
- 모니터링 기능에서 사용됨
- 블루투스 모듈에서 호출됨
by 조우성
*/
ClimateData read_dht_data();

#endif