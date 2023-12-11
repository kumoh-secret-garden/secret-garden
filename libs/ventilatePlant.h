#ifndef VENTILATE_PLANT_H
#define VENTILATE_PLANT_H

#include "../common.h"

#define ENCODER_CLK 5 // 로터리 엔코더의 CLK번호 5
#define ENCODER_DT 6  // 로터리 엔코더의 DT번호 6

#define MOTOR_PWM_PIN1 18 // 실제로 DC 모터의 PWM 핀이 연결된 GPIO 핀 번호
#define MOTOR_PWM_PIN2 19 // 실제로 DC 모터의 PWM 핀이 연결된 GPIO 핀 번호

/*
환풍 기능(증산 작용 활성화를 위한 환풍 기능)
by 조우성
-로터리 엔코더 값의 10배의 duty로 dc모터를 회전시킴
*/
void *ventilate_plant(void *arg);

#endif