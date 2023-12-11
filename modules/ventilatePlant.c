#include "ventilatePlant.h"

/*
환풍 기능(증산 작용 활성화를 위한 환풍 기능)
*/
void *ventilate_plant(void *arg){
    int cnt = 0; //cnt는 펄스 값이 바뀔 때 마다 방향에 따라 바뀔 변수입니다. 초기 상태는 0입니다.
    int current = 0; //current는 펄스 값이 바뀔 때 마다 읽어들일 변수입니다.

    int last =0;
    int duty = 0;
    int dir = 0;
    int divisor = 0;

    pinMode(ENCODER_CLK, INPUT); //ENCODER_CLK를 INPUT로 설정합니다.
    pinMode(ENCODER_DT, INPUT); //ENCODER_DT를 INPUT로 설정합니다.

    last = digitalRead(ENCODER_CLK); // 전역변수 last를 초기 펄스 상태로 초기화해줍니다.

    pinMode(MOTOR_PWM_PIN1 , PWM_OUTPUT); //GPIO 18 PWM
    pinMode(MOTOR_PWM_PIN2 , PWM_OUTPUT); //GPIO 19 PWM
    pwmSetMode(PWM_MODE_MS);

    pwmSetRange(100);
    divisor = 192 / 2;
    duty = 0;

    pwmSetClock(divisor);

    printf("로터리 엔코더 cnt = %d \n", cnt); //cnt가 0일 때 프로그램이 실행된 걸 보여주기 위해 한번 출력합니다.

    while(1) {
        current = digitalRead(ENCODER_CLK); //current에 ENCODER_CLK의 값을 넣어줍니다.

        if(current != last && current == 1) { //current가 last와 비교해서 바뀌면 아래의 반복문을 실행합니다.
            if (digitalRead(ENCODER_DT) != current) { //ENCODER_DT핀의 값으로 회전 방향을 판단합니다. 여기서는 CW 방향입니다.
                cnt++; // CW 방향이므로 cnt 1 증가
                printf("cnt = %d \n", cnt);
                
                duty = cnt * 10;
                pwmWrite(MOTOR_PWM_PIN2, duty);
                pwmWrite(MOTOR_PWM_PIN1, 1);

            }
            else { //CCW 방향을 판단합니다.
                cnt--; //CCW 방향이므로 cnt 1 감소
                printf("cnt = %d \n", cnt);

                duty = cnt * 10;
                pwmWrite(MOTOR_PWM_PIN2, duty);
                pwmWrite(MOTOR_PWM_PIN1, 1);
            }
        }
        delay(1); //오작동하지 않도록 딜레이를 넣어줍니다.
        last = current; //다음 비교를 위해 last를 current로 바꿔줍니다.
    }
}