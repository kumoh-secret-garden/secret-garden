#include "main.h"

ClimateData temp_humid_info; // 온습도 정보
time_t current_time;       // 현재 시각
float soil_moisture;       // 토양 수분

pthread_mutex_t mtx_temp_humid_info;  // 온습도 정보를 보호하기 위한 뮤텍스
pthread_mutex_t mtx_current_time;  // 현재 시각을 보호하기 위한 뮤텍스
pthread_mutex_t mtx_soil_moisture; // 토양 수분을 보호하기 위한 뮤텍스

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
    pthread_mutex_init(&mtx_temp_humid_info, NULL);
    pthread_mutex_init(&mtx_current_time, NULL);
    pthread_mutex_init(&mtx_soil_moisture, NULL);

    // 각 스레드에서 수행할 함수 지정
    createThread(&photosynthesis_thread, controlLight, NULL);
    createThread(&sync_current_time_thread, syncCurrentTime, NULL);
    createThread(&scheduler_thread, scheduler, NULL);
    createThread(&temp_humid_sensor_thread, syncTempHumidInfo, NULL);
    createThread(&ventilate_plant_thread, ventilatePlant, NULL);
    createThread(&water_plant_thread, waterPlant, NULL);

    pthread_join(photosynthesis_thread, NULL);
    pthread_join(sync_current_time_thread, NULL);
    pthread_join(scheduler_thread, NULL);
    pthread_join(temp_humid_sensor_thread, NULL);
    pthread_join(ventilate_plant_thread, NULL);
    pthread_join(water_plant_thread, NULL);

    // 뮤텍스 삭제
    pthread_mutex_destroy(&mtx_temp_humid_info);
    pthread_mutex_destroy(&mtx_current_time);
    pthread_mutex_destroy(&mtx_soil_moisture);

    return 0;
}
