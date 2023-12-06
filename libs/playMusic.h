#ifndef PLAY_MUSIC_H
#define PLAY_MUSIC_H

#include "common.h"

#define BUZZER_GPIO 26
#define RANGE 100
#define DUTY 50

/*
음악 재생 기능(특정 시간마다 음악을 재생하는 기능)
by 이지현
*/
void *play_music(void *arg);

#endif