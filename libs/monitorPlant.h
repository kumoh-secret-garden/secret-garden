#ifndef MONITOR_PLANT_H
#define MONITOR_PLANT_H

#include "common.h"
#include "soilMoistureSensor.h"
#include "rtcModule.h"
#include "tempHumidSensor.h"

#define BAUD_RATE 115200 // 블루투스의 보율이 바뀔 경우 이 값을 변경해야 한다.
#define UART_TX_GPI 0    // 전송(TX)을 위한 핀
#define UART_RX_GPIO 1   // 수신(RX)을 위한 핀

/*
식물 상태 모니터링 기능(온도, 습도, 토양 수분, 시간 정보 제공 기능)
by 정영한
*/
void *monitor_plant(void *arg);

#endif