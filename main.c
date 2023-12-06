#include "main.h"
#include <pthread.h>

int main()
{
    // wiringPi 라이브러리 초기화
    if (wiringPiSetup() == -1)
    {
        printf("wiringPi setup failed!\n");
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

    // 모든 스레드가 종료될 때까지 대기
    pthread_join(photosynthesis_thread, NULL);
    pthread_join(watering_thread, NULL);
    pthread_join(music_thread, NULL);
    pthread_join(rotating_thread, NULL);
    pthread_join(monitoring_thread, NULL);
    pthread_join(ventilating_thread, NULL);

    return 0;
}
