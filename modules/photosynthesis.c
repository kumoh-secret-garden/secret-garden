#include "photosynthesis.h"

/*
광합성 기능(LED를 통한 광합성 기능)
    리모컨을 통해 사용자로부터 밝기 값 받아오기
    LED를 사용해 식물에 빛 공급
    밝기 조절 : 0 ~ 100
*/

void *control_light(void *arg)
{

    struct lirc_config *config; // IR 설정 값 저장소
    int brightness = 40;        // LED 초기값

    softPwmCreate(LED_PIN, brightness, MAX_BRIGHTNESS); // softPWM 설정

    if (lirc_init("lirc", 1) == -1)
    { // lirc 초기화
        return NULL;
    }

    // lirc 설정 파일을 읽음
    if (lirc_readconfig(NULL, &config, NULL) == 0)
    {
        char *code;
        char *c;

        while (lirc_nextcode(&code) == 0)
        {
            // IR코드 수신되면
            if (code != NULL)
            {
                if ((lirc_code2char(config, code, &c)) == 0 && c != NULL)
                {
                    if (strcmp(c, "KEY_UP") == 0)
                    { // 수신값이 "KEY_UP"일 때 밝기 증가
                        brightness += 20;
                        if (brightness > 100)
                        {
                            brightness = MAX_BRIGHTNESS;
                        }
                    }
                    else if (strcmp(c, "KEY_DOWN") == 0)
                    { // 수신값이 "KEY_DOWN"일 때 밝기 감소
                        brightness -= 20;
                        if (brightness < 0)
                        {
                            brightness = 0;
                        }
                    }
                    softPwmWrite(LED_PIN, brightness); // LED 값 설정
                    printf("[LED] Current Brightness: %d\n", brightness);
                }
            }
        }
        free(code);
        lirc_freeconfig(config);
    }

    // 연결 설정 해제
    softPwmStop(LED_PIN);
    lirc_deinit();
}