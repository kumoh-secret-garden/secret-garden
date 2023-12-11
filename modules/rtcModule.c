#include "../libs/rtcModule.h"

// BCD를 10진수로 변환하는 함수
static int bcdToDec(int val)
{
    return ((val / 16 * 10) + (val % 16));
}

// I2C 설정 함수
static int initI2C()
{
    // if (wiringPiSetup() < 0)
    // {
    //     printf("wiringPiSetup() is failed\n");
    //     return -1;
    // }

    int i2c_fd = wiringPiI2CSetupInterface(I2C_DEV, SLAVE_ADDR_01);

    if (i2c_fd == -1)
    {
        printf("i2c_fd device setup failed\n");
        return -1;
    }

    return i2c_fd;
}

// 시간 갱신 함수
static void updateTime(int i2c_fd)
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
}

// 스케줄링 함수
static void scheduleTask(time_t *lastTime, int interval, void *(*task)(void *), pthread_t *thread)
{
    // 뮤텍스 잠금
    pthread_mutex_lock(&mtx_current_time);

    // 안전하게 current_time 값 가져오기
    time_t currentTime = current_time;

    // 뮤텍스 해제
    pthread_mutex_unlock(&mtx_current_time);

    // 특정 기능은 interval 초마다 실행
    if (difftime(currentTime, *lastTime) >= interval)
    {
        pthread_create(thread, NULL, task, NULL);
        pthread_detach(*thread);
        *lastTime = currentTime;
    }
}

void *syncCurrentTime(void *arg)
{
    int i2c_fd = initI2C();
    if (i2c_fd < 0)
        return NULL;

    while (1)
    {
        updateTime(i2c_fd);
        sleep(1); // 1초 대기
    }

    return NULL;
}

void *scheduler(void *arg)
{
    time_t lastMonitorTime = 0, lastRotateTime = 0, lastMusicTime = 0;
    pthread_t monitorThread, rotateThread, musicThread;

    while (1)
    {
        scheduleTask(&lastMonitorTime, 30, monitor_plant, &monitorThread);
        scheduleTask(&lastRotateTime, 60, rotate_pot, &rotateThread);
        scheduleTask(&lastMusicTime, 180, play_music, &musicThread);

        delay(1000); // 1초마다 스케줄러 작동
    }

    return NULL;
}