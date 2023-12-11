#include "main.h"

void init()
{
    if (wiringPiSetupGpio() < 0)
    {
        printf("Failed to set up wiringPi");
        return -1;
    }
}

int main()
{
    initI2C();

    // 뮤텍스 초기화
    pthread_mutex_init(&mtx_tempHumidInfo, NULL);
    pthread_mutex_init(&mtx_current_time, NULL);
    pthread_mutex_init(&mtx_soil_moisture, NULL);

    // wiringPi 라이브러리 초기화
    if (wiringPiSetup() == -1)
    {
        printf("wiringPi setup failed!");
        return -1;
    }

    // 각 기능을 수행할 스레드 생성
    pthread_t photosynthesis_thread, watering_thread, music_thread, rotating_thread, monitoring_thread, ventilating_thread;

    // 각 스레드에서 수행할 함수 지정
    pthread_create(&photosynthesis_thread, NULL, control_light, NULL);
    pthread_create(&watering_thread, NULL, water_plant, NULL);
    pthread_create(&music_thread, NULL, play_music, NULL);
    pthread_create(&rotating_thread, NULL, rotate_pot, NULL);
    pthread_create(&monitoring_thread, NULL, monitor_plant, NULL);
    pthread_create(&ventilating_thread, NULL, ventilate_plant, NULL);

    // 각 스레드를 detach 상태로 설정
    pthread_detach(photosynthesis_thread);
    pthread_detach(watering_thread);
    pthread_detach(music_thread);
    pthread_detach(rotating_thread);
    pthread_detach(monitoring_thread);
    pthread_detach(ventilating_thread);

    // 메인 스레드는 무한 루프를 돌며 작동
    while (1)
    {
        sleep(10);
    }

    // 뮤텍스 삭제
    pthread_mutex_destroy(&mtx_tempHumidInfo);
    pthread_mutex_destroy(&mtx_current_time);
    pthread_mutex_destroy(&mtx_soil_moisture);

    return 0;
}