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

#endif