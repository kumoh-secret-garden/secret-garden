#include "../libs/tempHumidSensor.h"

/*
온습도 센서에서 정보를 받아오는 함수
*/

void readDHTInfo()
{
	uint8_t laststate = HIGH;		  // DHT핀의 상태 저장용 변수(현재 신호가 HIGH인지 LOW인지 확인하기 위한 용도)
	uint8_t counter = 0;			  // 신호의 길이를 측정하기 위한 카운터 변수
	uint8_t j = 0, i;				  // 40개의 신호 인덱스 용 변수
	int dataDHT[5] = {0, 0, 0, 0, 0}; // 온습도 및 checksum 데이터 저장용 변수 배열

	dataDHT[0] = dataDHT[1] = dataDHT[2] = dataDHT[3] = dataDHT[4] = 0; // 초기 데이터 값은 0으로 지정

	/* DHT11센서와의 통신을 개시하기 위해 DATA핀을 18ms동안 LOW로 출력 */
	pinMode(DHT_DATA_GPIO, OUTPUT);
	digitalWrite(DHT_DATA_GPIO, LOW);
	delay(18);

	/* 핀을 입력모드로 설정해서 DHT11로 부터 응답을 기다림 */
	pinMode(DHT_DATA_GPIO, INPUT);

	/* DHT11에서 오는 신호 검출 및 데이터비트 추출 */
	for (i = 0; i < MAX_TIMINGS; i++) // 총 85번 동안 신호를 확인
	{
		counter = 0;									// 초기 카운터는 0
		while (digitalRead(DHT_DATA_GPIO) == laststate) // DHT핀의 신호를 읽어서 현재 지정한 DATA핀 신호와 같은 동안==즉 신호의 변환이 없는 동안
		{
			counter++;			  // 카운터 변수 1 증가
			delayMicroseconds(1); // 1uS(마이크로초) 동안 대기
			if (counter == 255)	  // 카운터가 255까지 도달하면, 즉 너무 오래 동안 대기하면==오류가 생겼다는 의미 임
			{
				break; // 카운터 세기 중지
			}
		}
		laststate = digitalRead(DHT_DATA_GPIO); // 현재 핀 상태 저장

		if (counter == 255) // 카운터가 255이상 도달했다면, 데이터비트 수신 중지== for문 밖으로 나가서 처음부터 새로 받겠다는 의미임
			break;

		/* 첫번째 3개의 신호는 무시하고 짝수번째에 해당하는 신호길이를 읽어 0인지 1인지에 따라 온습도 변수에 저장
		   첫번째 3개의 신호는 DHT11의 응답 용 신호로 실제 데이터 길이를 통해 정보를 수신하는 값이 아니므로 무시함.
		   짝수만 추출하는 이유는 짝수 번째의 신호 길이에 따라 해당 신호가 0을 의미하는지 1을 의미하는지를 나타냄.
		 */
		if ((i >= 4) && (i % 2 == 0)) // 4번째 이후의 신호이면서 짝수번째 신호라면
		{
			/* 가각의 데이터 비트를 온도 및 습도 변수에 하나씩 넣어줌 */
			dataDHT[j / 8] <<= 1;	 // 이진수의 자리수를 하나씩 옆으로 이동시킴
			if (counter > 16)		 // 카운터의 값이 16보다 크다면, 즉 신호의 길이가 길어서 비트 1로 인식된다면
				dataDHT[j / 8] |= 1; // 해당 비트는 1을 넣어줌
			j++;					 // 다음 데이터를 위해 인덱스 값을 하나 증가 시킴
		}
	}

	/*
	 * 40비트를 다 확인했다면 (8비트 x 5 ) 체크섬 데이터와 오류체크를 해서
	 * 오류가 없으면 데이터를 출력함.
	 */
	if ((j >= 40) && (dataDHT[4] == ((dataDHT[0] + dataDHT[1] + dataDHT[2] + dataDHT[3]) & 0xFF)))
	{ // 에러가 없으면 습도 및 온도 출력
		if (dataDHT[0] != dataDHT[1] != dataDHT[2] != dataDHT[3] != 0)
		{
			printf("Humidity = %d.%d , Temperature = %d.%d C\n", dataDHT[0], dataDHT[1], dataDHT[2], dataDHT[3]);

			ClimateData sensorTempHumidInfo = {(float)dataDHT[0] + ((float)dataDHT[1] * 0.1f), (float)dataDHT[2] + ((float)dataDHT[3] * 0.1f)};

			// 뮤텍스 잠금
			pthread_mutex_lock(&mtx_tempHumidInfo);

			// tempHumidInfo 갱신
			tempHumidInfo = sensorTempHumidInfo; //

			// 뮤텍스 해제
			pthread_mutex_unlock(&mtx_tempHumidInfo);
		}
		else
		{
			printf("Data not good, skip, all value 0.\n"); // 전부 다 0일시 Data not good 메시지 출력
		}
	}
	else
	{
		printf("Data not good, skip\n"); // 에러 발생시 Data not good 메시지 출력
	}
}

/*
온습도 센서(온도, 습도 반환 기능)
- 모니터링 기능에서 사용됨
- 블루투스 모듈에서 호출됨

- 기능 : 한번 실행되면 계속해서 tempHumidInfo를 알맞은 값을 센서가 인식할때 마다 갱신해줌
- 주기 : 2초마다 갱신
*/

void *syncTempHumidInfo(void *arg)
{
	while (1)
	{
		printf("[온습도 센서 On]\n");
		readDHTInfo(); // 온도 및 습도 데이터 획득 및 출력
		printf("[온습도 센서 On]\n");
		sleep(2); // 다음 읽기까지 2초 대기
	}

	return (0);
}
