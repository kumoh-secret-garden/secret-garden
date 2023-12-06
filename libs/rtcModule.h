#ifndef RTC_MODULE_H
#define RTC_MODULE_H

#include <time.h>
#include "common.h"
#include "rotatePot.h"
#include "playMusic.h"

#define SLAVE_ADDR_01 0x68 // i2c_fd device ID
#define SEC_REG 0x00       // seconds register
#define MIN_REG 0x01       // minutes register
#define HOUR_REG 0x02      // hours register
#define DAY_REG 0x03       // day of week register
#define DATE_REG 0x04      // date register
#define MONTH_REG 0x05     // month register
#define YEAR_REG 0x06      // year register

/*
현재 시간을 받아오는 함수
- 모니터링 기능에서 사용됨
- 블루투스 모듈에서 호출됨
by 정연준
*/
time_t getCurrentTime();

/*
특정 시간마다 다른 센서들을 실행시키는 스케줄러 함수
by 정연준
*/
void *scheduler(void *arg);

#endif