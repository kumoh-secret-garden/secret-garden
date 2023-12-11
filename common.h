#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>

typedef struct
{
    float temperature;
    float humidity;
} ClimateData;

static ClimateData tempHumidInfo; // 온습도 정보
static time_t current_time;       // 현재 시각
static float soil_moisture;       // 토양 수분

static mtx_tempHumidInfo;                 // 온습도 정보를 보호하기 위한 뮤텍스
static pthread_mutex_t mtx_current_time;  // 현재 시각을 보호하기 위한 뮤텍스
static pthread_mutex_t mtx_soil_moisture; // 토양 수분을 보호하기 위한 뮤텍스

#endif