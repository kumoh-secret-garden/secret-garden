smart_garden : main.o monitor_plant.o photosynthesis.o play_music.o rotate_pot.o rtc_module.o temp_humid_sensor.o ventilate_plant.o water_plant.o
	gcc -o smart_garden main.o monitor_plant.o photosynthesis.o play_music.o rotate_pot.o rtc_module.o temp_humid_sensor.o ventilate_plant.o water_plant.o

main.o : main.c main.h common.h
	gcc -c main.c

monitor_plant.o : monitorPlant.c monitorPlant.h common.h
	gcc -c monitorPlant.c

photosynthesis.o : photosynthesis.c photosynthesis.h common.h
	gcc -c photosynthesis.c -llirc_client

play_music.o : playMusic.c playMusic.h common.h
	gcc -c playMusic.c

rotate_pot.o : rotatePot.c rotatePot.h common.h
	gcc -c rotatePot.c

rtc_module.o : rtcModule.c rtcModule.h common.h
	gcc -c rtcModule.c

temp_humid_sensor.o : tempHumidSensor.c tempHumidSensor.h common.h
	gcc -c tempHumidSensor.c

ventilate_plant.o : ventilatePlant.c ventilatePlant.h common.h
	gcc -c ventilatePlant.c

water_plant.o : waterPlant.c waterPlant.h common.h
	gcc -c waterPlant.c