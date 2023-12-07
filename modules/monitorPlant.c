#include "monitorPlant.h"
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <time.h>

#define BAUD_RATE 115200

static const char* UART_DEV = "/dev/ttyAMA1";


// 시간을 문자열로 변환하는 함수
void format_time(char *buffer, time_t time) {
    struct tm *tm_info = localtime(&time);
    strftime(buffer, 26, "[%Y/%m/%d %H:%M:%S]", tm_info);
}

// 데이터를 문자열로 변환하는 함수
void format_data(char *buffer, ClimateData data, float soil_moisture) {
    sprintf(buffer, "토양 수분 = %.2f\n온도 = %.2f\n습도 = %.2f\n", soil_moisture, data.temperature, data.humidity);
}


/*
식물 상태 모니터링 기능(온도, 습도, 토양 수분, 시간 정보 제공 기능)
*/
void* monitor_plant(void* arg){
    int fd_serial;
    char time_buffer[26];
    char data_buffer[100];
    
    if(wiringPiSetup() < 0) return NULL;
    if((fd_serial = serialOpen(UART_DEV, BAUD_RATE)) < 0) {
        printf("Unable to open serial device.\n");
        return NULL;
    }
    
    
    // 락을 걸고 데이터를 읽는다
    pthread_mutex_lock(&mtx_current_time);
    format_time(time_buffer, current_time);
    pthread_mutex_unlock(&mtx_current_time);
    
    pthread_mutex_lock(&mtx_tempHumidInfo);
    pthread_mutex_lock(&mtx_soil_moisture);
    format_data(data_buffer, tempHumidInfo, soil_moisture);
    pthread_mutex_unlock(&mtx_soil_moisture);
    pthread_mutex_unlock(&mtx_tempHumidInfo);
    
    // 데이터를 전송한다
    if(write(fd_serial, time_buffer, strlen(time_buffer)+1) == -1) {
        printf("Error: Unable to write time_buffer.\n");
        return NULL;
    }
    write(fd_serial, "\n", 1);
    if(write(fd_serial, data_buffer, strlen(data_buffer)+1) == -1) {
        printf("Error: Unable to write data_buffer.\n");
        return NULL;
    }
    
    // 약간의 딜레이를 준다
    delay(10);
    
    
    return NULL;
}

