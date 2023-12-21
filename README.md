# SmartGarden : 스마트한 식물 관리 시스템 with RaspberryPi
****************
## 프로젝트 소개

RespberryPi 4.0 Model B를 사용하여 식물 성장에 대한 다양한 기능을 통해 사용자들이 보다 쉽게 식물을 관리하도록 돕습니다.
사용자는 본 시스템을 통해 식물에게 필요한 수분, 온도, 습도 등을 사용자 단말기를 통해 확인할 수 있고, 
이를 바탕으로 식물의 물주기, 빛 공급, 화분 회전, 환풍, 음악 재생 등의 기능을 사용해 식물의 환경을 조정할 수 있습니다.

<br>

### 주요 기능
  - 광합성
  - 물주기
  - 음악 재생
  - 화분 회전
  - 환풍
  - 식물 상태 모니터링

<br>

### 사용 센서
<img src="https://github.com/kumoh-secret-garden/secret-garden/assets/119781387/b596a37b-d5cd-4bae-9687-123dd0a72e48" height="250" />

### 사용 액추에이터
<img src="https://github.com/kumoh-secret-garden/secret-garden/assets/119781387/b8938bd5-c229-44df-84c7-fa4e06cd1f5b" height="250" />

<br><br>

### 전체 시스템 구조
<img src="https://github.com/kumoh-secret-garden/secret-garden/assets/119781387/245b3b4d-fe79-42e4-9b19-c169eeca4d40" height="500" />

### GPIO 번호 설정
- 리모컨 - 23번
- LED - 25번
- 토양 수분 센서 - 17번
- 워터 펌프 - 27번
- RTC 모듈 - 2번, 3번
- 온/습도 센서 - 4번
- 블루투스 모듈 - 0번, 1번
- DC 모터 - 18번, 19번
- 스피커 - 26번
- 스텝 모터 - 12번, 16번, 20번, 21번
- 로터리 엔코더 - 5번, 6번
- 릴레이 모듈 - 7번

<br>

### 전체 시스템 기능
<img src="https://github.com/kumoh-secret-garden/secret-garden/assets/119781387/ad5fd1de-592b-4e01-8d08-0021cd15e9e5" height="500" />

<br>

# 기능 동작
## 광합성
사용되는 모듈 : 리모컨, IR 센서, LED

사용자가 리모컨을 이용하여 입력하면 IR 센서가 적외선 신호를 감지하여 LED의 밝기를5단계로 조절한다.
    
## 물주기
사용되는 모듈 : 토양 수분 센서, ADC 모듈, 릴레이 모듈, 워터 펌프

물주기 기능은 10초마다 동작된다.
토양 수분 센서에서 흙에 포함된 수분을 측정하고, ADC 모듈을 통해 디지털 값으로 변환 후 
수분 측정 값이 50% 이하라면, 릴레이 모듈을 통해 워터 펌프를 동작시켜 흙에 수분을 공급한다.

## 음악 재생
사용되는 모듈 : RTC 모듈, 스피커

시스템 내 스케줄러 기능을 통해 쓰레드 간 공유 변수인 시간 정보를 참조하여 특정 시간(모니터링은 30초)마다 음악 재생 기능이 실행된다.
시스템에는 3개의 음악이 존재한다.
스케줄러에 의해 호출될 때마다 임의의 음악이 선택되어 스피커를 통해 재생된다.

## 화분 회전
사용되는 모듈 : RTC 모듈, 스텝 모터

시스템 내 스케줄러 기능을 통해 쓰레드 간 공유 변수인 시간 정보를 참조하여 특정 시간(모니터링은 5초)마다 화분 회전 기능이 실행된다.
스케줄러에 의해 호출되면 스텝 모터를 10도 회전시킨다.
시계 방향으로 180도 회저하면 다시 반대방향으로 회전하며 -180도에 도달하면 또다시 반대 방향으로 회전하는 식으로 동작한다.

## 환풍
사용되는 모듈 : 로터리 엔코더, DC 모터

로터리 엔코터의 회전 값을 입력받아 DC 모터의 회전 세기를 조절한다.


## 식물 상태 모니터링
사용되는 모듈 : RTC 모듈, 블루투스 모듈, 온습도 센서, 토양 수분 세서

시스템 내 스케줄러 기능을 통해 쓰레드 간 공유 변수인 시간 정보를 참조하여 특정 시간(모니터링은 10초)마다 모니터링 기능이 실행된다.
모니터링 기능은 라즈베리파이와 스마트폰 간 블루투스 통신을 통해 이루어지며, 공유 변수인 시간, 온도, 습도, 토양 수분 정보를 뮤텍스를 통해 참조하여 사용자에게 제공한다.

<br>

# 제한조건
![image](https://github.com/kumoh-secret-garden/secret-garden/assets/119781387/78dfb851-e59f-4743-827f-76508ea39758)
시스템은 멀티쓰레드로 동작한다.
공유변수로는 시간 정보(current_time), 토양 수분 정보(soil_moisture), 온습도 정보(temp_humid_info)가 존재한다.
각각의 공유변수는 여러 쓰레드에서 뮤텍스를 통해 갱신, 조회된다.

<br>

# 가산점 요소
라즈베리파이 -> 스마트폰 통신
![image](https://github.com/kumoh-secret-garden/secret-garden/assets/119781387/101337f5-4566-428e-a891-c90fd39bf30f)

<br>

# 개발 시 문제점 및 해결 방안
## 뮤텍스 사용 시 문제점
![image](https://github.com/kumoh-secret-garden/secret-garden/assets/119781387/19e2c8fc-8e11-4074-a989-37648879cd83)

각 모듈함수에 extern으로 외부 변수로 선언함으로써 문제를 해결하였다.

## 리모컨 등록 과정에서의 문제점
![image](https://github.com/kumoh-secret-garden/secret-garden/assets/119781387/2b2bfcd7-c99b-4e0a-b33f-f2d3e40eda5c)

IR 센서에 리모컨 키를 등록하는 과정에서 키 값이 디코드되지 않는 문제가 발생했다.
이러한 문제를 해결하기 위해 리모컨의 키 값을 사용하여 raw codes로 입력하였다.
그리고 리모컨 키에 따라 KEY_UP, KEY_DOWN 구분하여 문제를 해결하였다.

<br>

# 프로젝트 실행
## 프로젝트 환경 설정 및 준비
### 리모컨으로 LED 밝기 조절 기능 구현
  - 기본 설정
    - /boot/config.txt 에서 아래 값으로 변경
    - `dtoverlay=gpio-ir, gpio_pin=23`
    - /etc/lirc/lircd_options.config 에서 아래 값으로 변경
    - `driver = default \\n device = /dev/lirc0`
    - sudo apt-get ir-keytable lirc liblircclient-dev # 라이브러리 설치
    - irrecord로 리모컨 등록 필요 (이때 raw_code로 작성)
      - raw_code는 sudo mode2 -m -d /dev/lirc0
      - (참고 : https://asimuzzaman.com/posts/how-to-use-raspberry-pi-as-infrared-ir-remote)
  - 빌드 시 -llirc_client 필요

<br>

- 라이브러리 설치
```
sudo apt update
```
```
sudo apt install lirc ir-keytable liblircclient-dev
```
```
sudo nano /etc/lirc/lirc_options.conf
```

<br>

- 값 설정

/etc/lirc/lirc_options.conf
``` 
driver          = default
device          = /dev/lirc0
```

/boot/config.txt
```
#dtoverlay=gpio-ir,gpio_pin=17
#dtoverlay=gpio-ir-tx,gpio_pin=18
```
/boot/config.txt의 주석처리된 부분을 다음과 같이 변경해준다.

```
dtoverlay=gpio-ir,gpio_pin=23
```

<br>

- 리모컨 등록
```
sudo mode2 -m -d /dev/lirc0
```
위의 명령어를 실행하고 UP, DOWN 버튼을 눌렀을 때의 출력 값을 복사하여 

```
sudo nano {리모컨이름}.lircd.conf
```
에 다음과 같이 입력한다.

```
begin raw_codes
  name KEY_UP
  <up 버튼을 눌렀을 때의 출력값>

  name KEY_DOWN
  <down 버튼을 눌렀을 때의 출력값>
end raw_codes
```

<br>

## 프로젝트 사용 방법
```
make
```

```
sudo ./smart_garden
```

- 주의사항
RTC 시간이 설정되지 않은 경우, 시간 설정 필요

<br>

## 팀원 및 참고 자료

![image](https://github.com/kumoh-secret-garden/secret-garden/assets/119781387/fe87307b-c2f4-486e-abba-c4c7de0bb916)

<br>

## 시연 동영상

[![예제](https://github.com/kumoh-secret-garden/secret-garden/assets/119781387/fe58ed98-2d65-419f-807a-637b54e323d9)](https://youtu.be/IZx6PI5mARU)


