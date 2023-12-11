#include "waterPlant.h"

int init_I2C()
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

void setup_water_pump()
{
    pinMode(WATER_PUMP_PIN, OUTPUT); // 워터 펌프 핀을 출력 모드로 설정
}

void control_water_pump(float percent)
{
    if (percent < 50)
    {
        turnOnWaterPump();
        delay(1000); // 1초간 물 주기
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
void *water_plant(void *arg)
{
    int i2c_fd = init_I2C();

    if (i2c_fd < 0)
        return NULL;

    setup_water_pump();

    while (1)
    {
        printf("[물주기 기능 토양 수분 측정 On]\n");
        wiringPiI2CWrite(i2c_fd, 0x40 | ADC_CHANNEL);
        int preVal = wiringPiI2CRead(i2c_fd);
        int curVal = wiringPiI2CRead(i2c_fd);
        float percent = 100 - ((float)curVal / 255) * 100;
        printf("토양 수분(%): %.2f%\n", percent);
        printf("[물주기 기능 토양 수분 측정 On]\n");
        // 뮤텍스 잠금
        pthread_mutex_lock(&mtx_soil_moisture);

        // soil_moisture 갱신
        soil_moisture = percent;

        // 뮤텍스 해제
        pthread_mutex_unlock(&mtx_soil_moisture);

        // 워터 펌프 제어
        control_water_pump(percent);

        sleep(30); // 30초 마다 실행
    }

    return NULL;
}
