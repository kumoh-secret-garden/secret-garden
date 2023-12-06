#include "rtcModule.h"

static const char *I2C_DEV = "/dev/i2c-1"; // I2C 연결을 위한 장치 파일

/*
현재 시간을 받아오는 함수
- 모니터링 기능에서 사용됨
- 블루투스 모듈에서 호출됨
*/
time_t getCurrentTime()
{
}

/*
특정 시간마다 다른 센서들을 실행시키는 스케줄러 함수
*/
void *scheduler(void *arg)
{

    // 스텝 모터, 스피커, 블루투스 모듈 주기적으로 실행시켜야함
}