#ifndef VENTILATE_PLANT_H
#define VENTILATE_PLANT_H

#include "common.h"
 
#define MOTOR_PWM_PIN1 18 // 실제로 DC 모터의 PWM 핀이 연결된 GPIO 핀 번호
#define MOTOR_PWM_PIN2 19 // 실제로 DC 모터의 PWM 핀이 연결된 GPIO 핀 번호

/*
환풍 기능(증산 작용 활성화를 위한 환풍 기능)
by 조우성
-파라미터의 값만큼의 속도로 dc모터가 회전함(20~30추천)
*/
void *ventilate_plant(int arg);

#endif