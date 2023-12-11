#include "main.h"

int init()
{
    if (wiringPiSetupGpio() < 0)
    {
        printf("Failed to set up wiringPi");
        return -1;
    }
    return 0;
}

void createThread(pthread_t *thread, void *(*start_routine)(void *), void *arg)
{
    int ret = pthread_create(thread, NULL, start_routine, arg);
    if (ret != 0)
    {
        printf("Error: pthread_create() failed\n");
        exit(EXIT_FAILURE);
    }
}

int main()
{
    pthread_t photosynthesis_thread, sync_current_time_thread, scheduler_thread,
        temp_humid_sensor_thread, ventilate_plant_thread, water_plant_thread;

    if (init() < 0)
        return -1;

    // 뮤텍스 초기화
    pthread_mutex_init(&mtx_tempHumidInfo, NULL);
    pthread_mutex_init(&mtx_current_time, NULL);
    pthread_mutex_init(&mtx_soil_moisture, NULL);

    // 각 스레드에서 수행할 함수 지정
    createThread(&photosynthesis_thread, control_light, NULL);
    createThread(&sync_current_time_thread, syncCurrentTime, NULL);
    createThread(&scheduler_thread, scheduler, NULL);
    createThread(&temp_humid_sensor_thread, syncTempHumidInfo, NULL);
    createThread(&ventilate_plant_thread, ventilate_plant, NULL);
    createThread(&water_plant_thread, water_plant, NULL);

    pthread_join(photosynthesis_thread, NULL);
    pthread_join(sync_current_time_thread, NULL);
    pthread_join(scheduler_thread, NULL);
    pthread_join(temp_humid_sensor_thread, NULL);
    pthread_join(ventilate_plant_thread, NULL);
    pthread_join(water_plant_thread, NULL);

    // 각 스레드를 detach 상태로 설정
    // pthread_detach(photosynthesis_thread);
    // pthread_detach(watering_thread);
    // pthread_detach(music_thread);
    // pthread_detach(rotating_thread);
    // pthread_detach(monitoring_thread);
    // pthread_detach(ventilating_thread);

    // // 메인 스레드는 무한 루프를 돌며 작동
    // while (1)
    // {
    //     sleep(10);
    // }

    // 뮤텍스 삭제
    pthread_mutex_destroy(&mtx_tempHumidInfo);
    pthread_mutex_destroy(&mtx_current_time);
    pthread_mutex_destroy(&mtx_soil_moisture);

    return 0;
}
