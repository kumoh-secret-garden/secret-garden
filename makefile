smart_garden : main.o monitorPlant.o photosynthesis.o playMusic.o rotatePot.o rtcModule.o tempHumidSensor.o ventilatePlant.o waterPlant.o
	gcc -o smart_garden main.o monitorPlant.o photosynthesis.o playMusic.o rotatePot.o rtcModule.o tempHumidSensor.o ventilatePlant.o waterPlant.o -llirc_client -lpthread -lwiringPi

main.o : main.c main.h common.h
	gcc -c main.c

monitorPlant.o : modules/monitorPlant.c libs/monitorPlant.h common.h
	gcc -c modules/monitorPlant.c

photosynthesis.o : modules/photosynthesis.c libs/photosynthesis.h common.h
	gcc -c modules/photosynthesis.c

playMusic.o : modules/playMusic.c libs/playMusic.h common.h
	gcc -c modules/playMusic.c

rotatePot.o : modules/rotatePot.c libs/rotatePot.h common.h
	gcc -c modules/rotatePot.c

rtcModule.o : modules/rtcModule.c libs/rtcModule.h common.h
	gcc -c modules/rtcModule.c

tempHumidSensor.o : modules/tempHumidSensor.c libs/tempHumidSensor.h common.h
	gcc -c modules/tempHumidSensor.c

ventilatePlant.o : modules/ventilatePlant.c libs/ventilatePlant.h common.h
	gcc -c modules/ventilatePlant.c

waterPlant.o : modules/waterPlant.c libs/waterPlant.h common.h
	gcc -c modules/waterPlant.c