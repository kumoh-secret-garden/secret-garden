#include "rtcModule.h"
#include <wiringPiI2C.h>

static const char *I2C_DEV = "/dev/i2c-1"; // I2C 연결을 위한 장치 파일

// BCD를 10진수로 변환하는 함수
int bcdToDec(int val);

/*
현재 시간을 받아오는 함수
- 모니터링 기능에서 사용됨
*/
void *syncCurrentTime(void *arg)
{
    int i2c_fd;

    if (wiringPiSetup() < 0)
    {
        printf("wiringPiSetup() is failed");
        return -1;
    }

    i2c_fd = wiringPiI2CSetupInterface(I2C_DEV, SLAVE_ADDR_01);

    if (i2c_fd == -1)
    {
        printf("i2c_fd device setup failed");
        return -1;
    }

    while (1)
    {
        struct tm timeinfo = {0};

        // BCD 형태로 저장된 시간 정보를 10진수 형태로 변환
        timeinfo.tm_year = bcdToDec(wiringPiI2CReadReg8(i2c_fd, YEAR_REG)) + 100; // tm_year는 1900년부터의 연도를 나타냅니다.
        timeinfo.tm_mon = bcdToDec(wiringPiI2CReadReg8(i2c_fd, MONTH_REG)) - 1;   // tm_mon는 0부터 시작합니다.
        timeinfo.tm_mday = bcdToDec(wiringPiI2CReadReg8(i2c_fd, DATE_REG));
        timeinfo.tm_hour = bcdToDec(wiringPiI2CReadReg8(i2c_fd, HOUR_REG) & ~(1 << 6));
        timeinfo.tm_min = bcdToDec(wiringPiI2CReadReg8(i2c_fd, MIN_REG));
        timeinfo.tm_sec = bcdToDec(wiringPiI2CReadReg8(i2c_fd, SEC_REG));

        // 뮤텍스 잠금
        pthread_mutex_lock(&mtx_current_time);

        // current_time 갱신
        current_time = mktime(&timeinfo); // struct tm을 time_t로 변환

        // 뮤텍스 해제
        pthread_mutex_unlock(&mtx_current_time);

        // 1초 대기
        sleep(1);
    }

    return NULL;
}

/*
특정 시간마다 다른 센서들을 실행시키는 스케줄러 함수
*/
void *scheduler(void *arg)
{
    time_t lastMonitorTime = 0;
    time_t lastRotateTime = 0;
    time_t lastMusicTime = 0;

    while (1)
    {
        sleep(1); // 1초마다 스케줄러 작동

        time_t currentTime = getCurrentTime();

        // 모니터링 기능은 30초마다 실행
        if (difftime(currentTime, lastMonitorTime) >= 30)
        {
            monitor_plant(NULL);
            lastMonitorTime = currentTime;
        }

        // 화분 회전 기능은 1분마다 실행
        if (difftime(currentTime, lastRotateTime) >= 60)
        {
            rotate_pot(NULL);
            lastRotateTime = currentTime;
        }

        // 음악재생 기능은 3분마다 실행
        if (difftime(currentTime, lastMusicTime) >= 180)
        {
            play_music(NULL);
            lastMusicTime = currentTime;
        }
    }
}

// BCD를 10진수로 변환하는 함수
int bcdToDec(int val)
{
    return ((val / 16 * 10) + (val % 16));
}