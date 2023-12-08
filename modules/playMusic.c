#include "playMusic.h"

/*
음악 재생 기능(특정 시간마다 음악을 재생하는 기능)
*/

// 계이름 표
Note note_table[TOTAL_NOTES] = {
    {"C", 261.63}, {"D", 293.66}, {"E", 329.63}, {"F", 349.63}, {"G", 392.00},
    {"A", 440.00}, {"B", 493.88}, {"5C", 523.25}, {"5D", 587.33}, {"5E", 659.25}, {"4F#", 369.99}, {"3B", 246.94}
};

//노래 악보
int jingle_bells[] = {
    1, 4, 4, 5, 4, 10, 2, 2, 2, 5, 5, 6, 5, 4, 10, 1, 1, 6, 6, 7, 6, 5, 4, 2, 1, 1, 2, 5, 10, 4, -1
    };
int rudolph[] = {
    4, 5, 4, 2, 7, 5, 4, -1, 4, 5, 4, 5, 4, 4, 7, 6, -1, 3, 4, 3, 1, 6, 5, 4, -1, 4, 5, 4, 5, 4, 4, 8, 7, -1
    };
int dont_cry[] = {
    2, 3, 4, 4, -1, 5, 6, 7, 7, -1, 2, 3, 4, 4, 4, 4, 4, 5, 4, 3, 3, 3, 3, 2, 4, 0, 2, 1, 3, 0, 0, -1
    };

// 노래 목록
Song songs[SONG_COUNT] = {
    {jingle_bells, sizeof(jingle_bells) / sizeof(int)}, // 징글벨
    {rudolph, sizeof(rudolph) / sizeof(int)}, // 루돌프 사슴 코
    {dont_cry, sizeof(dont_cry) / sizeof(int)}, // 울면 안돼
};

// RTC 모듈에 의해 호출됨
void* play_music(void* arg){
    srand(time(NULL)); // 노래를 랜덤으로 재생하기 위한 난수 생성
    int i;
    int song_idx = rand() % SONG_COUNT;
    Song song = songs[song_idx]; // 노래 목록 중 하나를 선택

    // wiringPiSetupGpio();

    printf("Start PlayMusic...\n");
    softToneCreate(BUZZER_GPIO); // GPIO 26에 softTone 생성
    for(i = 0; i < song.length; i++){ // 노래 재생
        if( song.notes[i] == -1){ // 악보의 값이 -1이면 쉼표로 취급함.
            delay(500);
        }
        else{
            softToneWrite(BUZZER_GPIO, note_table[song.notes[i]].frequency); // 해당 음을 재생
            delay(500);
        }
    }
    softToneWrite(BUZZER_GPIO, 0); // 음악 재생 종료
    printf("End PlayMusic...\n");
}