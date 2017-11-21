#MQTTLIB_C = paho-mqtt3c <---!
#MQTTLIB_CS = paho-mqtt3cs
#MQTTLIB_A = paho-mqtt3a
#MQTTLIB_AS = paho-mqtt3as

prog: main.o timeStr.o mqttLib.o	
	gcc -Wall -Wextra  -o mqqtbridge main.o timeStr.o mqttLib.o -l paho-mqtt3c

all: 
	make main15.o
	make timeStr.o
	make prog
	./mqqtbridge
	
run:
	make
	./mqqtbridge
	
timeStr.o: ./lib/timeStr.c
	gcc -c  ./lib/timeStr.c	
	
main15.o: main.c
	gcc -c  main.c
	
uartLib.o: ./lib/uartLib.c
	gcc -c  ./lib/uartLib.c
	
mqttLib.o: ./lib/mqttLib.c
	gcc -c  ./lib/mqttLib.c
	
test.o: ./lib/test.c
	gcc -c  ./lib/test.c
	
	
	
	
	
	
	
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	