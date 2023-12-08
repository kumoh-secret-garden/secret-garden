#ifndef PLAY_MUSIC_H
#define PLAY_MUSIC_H

#include "common.h"
#include <softTone.h>
#include <time.h>

#define BUZZER_GPIO 26
#define TOTAL_NOTES 12
#define SONG_COUNT 3

// 계이름 표 구조
typedef struct {
    char* note_name;
    float frequency;
} Note;

// 노래 목록 구조
typedef struct{
    int *notes;
    int length;
} Song;

/*
음악 재생 기능(특정 시간마다 음악을 재생하는 기능)
by 이지현
*/
void *play_music(void *arg);

#endif