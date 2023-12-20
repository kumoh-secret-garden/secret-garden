#include "../libs/waterPlant.h"

extern ClimateData temp_humid_info; // 온습도 정보
extern time_t current_time;       // 현재 시각
extern float soil_moisture;       // 토양 수분
extern pthread_mutex_t mtx_temp_humid_info;  // 온습도 정보를 보호하기 위한 뮤텍스
extern pthread_mutex_t mtx_current_time;  // 현재 시각을 보호하기 위한 뮤텍스
extern pthread_mutex_t mtx_soil_moisture; // 토양 수분을 보호하기 위한 뮤텍스

void turnOnWaterPump();
void turnOffWaterPump();

int initI2C()
{
    // if (wiringPiSetupGpio() < 0)
    // {
    //     printf("Failed to set up wiringPi");
    //     return -1;
    // }

    int i2c_fd = wiringPiI2CSetupInterface(I2C_DEV, SLAVE_ADDR);
    if (i2c_fd < 0)
    {
        printf("Failed to set up I2C");
    }

    return i2c_fd;
}

void setupWaterPump()
{
    pinMode(WATER_PUMP_PIN, OUTPUT); // 워터 펌프 핀을 출력 모드로 설정
}

void controlWaterPump(float percent)
{
    if (percent < 50)
    {
        turnOnWaterPump();
        delay(2000); // 2초간 물 주기
        turnOffWaterPump();
    }
}

void turnOnWaterPump()
{
    digitalWrite(WATER_PUMP_PIN, HIGH); // 워터 펌프 켜기
    printf("[워터 펌프 On]\n");
}

void turnOffWaterPump()
{
    digitalWrite(WATER_PUMP_PIN, LOW); // 워터 펌프 끄기
    printf("[워터 펌프 Off]\n");
}

/*
물주기 기능(토양의 수분을 측정한 물주기 기능)
by 정연준
*/
void *waterPlant(void *arg)
{
    int i2c_fd = initI2C();

    if (i2c_fd < 0)
        return NULL;

    setupWaterPump();

    while (1)
    {
        printf("[토양 수분 측정 Start...]\n");
        wiringPiI2CWrite(i2c_fd, 0x40 | ADC_CHANNEL);
        int pre_val = wiringPiI2CRead(i2c_fd);
        int cur_val = wiringPiI2CRead(i2c_fd);
        float percent = 100 - ((float)cur_val / 255) * 100;
        printf("토양 수분(%): %.2f%\n", percent);
        printf("[토양 수분 측정 End...]\n");
        // 뮤텍스 잠금
        pthread_mutex_lock(&mtx_soil_moisture);

        // soil_moisture 갱신
        soil_moisture = percent;

        // 뮤텍스 해제
        pthread_mutex_unlock(&mtx_soil_moisture);

        // 워터 펌프 제어
        controlWaterPump(percent);

        sleep(10); // 10초 마다 실행
    }

    return NULL;
}
